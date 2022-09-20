/*
  ==============================================================================

    RackLayout.cpp
    Created: 14 Sep 2022 6:49:33pm
    Author:  thesp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "RackLayout.h"
#include "../../Common/UpdateBuffer.h"

RackLayout::RackLayout(xynth::GuiData& g) : guiData(g)
{
    comps.reserve(4);
    comps.emplace_back(std::make_unique<MovableComponent>(100));
    comps.emplace_back(std::make_unique<MovableComponent>(120));
    comps.emplace_back(std::make_unique<MovableComponent>(80));
    comps.emplace_back(std::make_unique<MovableComponent>(150));

    comps[0]->setName("0 - Distortion");
    comps[1]->setName("1 - Reverb");
    comps[2]->setName("2 - Filter");
    comps[3]->setName("3 - Gain");

    comps[0]->setId(CompIds::dist);
    comps[1]->setId(CompIds::reverb);
    comps[2]->setId(CompIds::filter);
    comps[3]->setId(CompIds::gain);

    for (auto& comp : comps)
        addAndMakeVisible(*comp);

    guiData.audioProcessor.updateBuffer.pushState(comps);
}

RackLayout::~RackLayout()
{
}

void RackLayout::paint (juce::Graphics& g)
{
    auto rect = getLocalBounds().toFloat().reduced(0.5f);

    g.setColour(juce::Colours::black.withAlpha(0.2f));
    g.fillRoundedRectangle(rect, 4.f);

    g.setColour(juce::Colours::black);
    g.drawRoundedRectangle(rect, 4.f, 1.f);

    drawDivider(g);
}

void RackLayout::drawDivider(juce::Graphics& g)
{
    if (closestMidPointIdx == -1) return;
    int curIdx = curMoving->getIdx();
    if (curIdx == closestMidPointIdx || curIdx + 1 == closestMidPointIdx) return;
    
    g.setColour(juce::Colours::white);
    g.drawVerticalLine(midPoints[closestMidPointIdx], 5, getHeight() - 5);
}


void RackLayout::resized()
{
    updatePositions();
}

void RackLayout::updatePositions()
{
    if (comps.size() == 0) return;

    auto rect = getLocalBounds().reduced(0, 5);
    midPoints.resize(comps.size() + 1);
    midPoints[0] = gapHalf;

    for (int i = 0; i < comps.size(); ++i)
    {
        auto& comp = comps[i];

        rect.removeFromLeft(gap);
        comp->setBounds(rect.removeFromLeft(comp->getDesiredWidth()));
        comp->setIdx(i);

        midPoints[i + 1] = comp->getBounds().getRight() + gapHalf;
    }
    repaint();
}

void RackLayout::mouseDrag(const juce::MouseEvent& e)
{
    if (curMoving == nullptr) return;

    int curIdx = curMoving->getIdx();
    int shortest = 9999999;
    int shortestIdx = -1;

    for (int i = 0; i < midPoints.size(); ++i)
    {
        int x = midPoints[i];
        int dist = std::abs(x - getMouseXYRelative().x);
        if (dist < shortest)
        {
            shortest = dist;
            shortestIdx = i;
        }
    }

    jassert(shortestIdx != -1); // should not happen
    closestMidPointIdx = shortestIdx;

    repaint();
}

void RackLayout::startMoving(MovableComponent* _curMoving)
{
    curMoving = _curMoving;
}

void RackLayout::stopMoving()
{
    const int curIdx = curMoving->getIdx();
    const int newIdx = closestMidPointIdx > curIdx ? closestMidPointIdx - 1 : closestMidPointIdx;

    if (curMoving == nullptr || closestMidPointIdx == -1 || comps.size() <= 1 || curIdx == newIdx)
    {
        return;
        curMoving = nullptr;
    }

    // Swap elements
    move(comps, curMoving->getIdx(), newIdx);

    // Reset system
    curMoving = nullptr;
    closestMidPointIdx = -1;
    updatePositions();

    guiData.audioProcessor.updateBuffer.pushState(comps);
}

