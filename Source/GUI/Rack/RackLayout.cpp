/*
  ==============================================================================

    RackLayout.cpp
    Created: 14 Sep 2022 6:49:33pm
    Author:  thesp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "RackLayout.h"

RackLayout::RackLayout(xynth::GuiData& g) : guiData(g)
{
    comps.reserve(3);
    comps.emplace_back(std::make_unique<MovableComponent>(100));
    comps.emplace_back(std::make_unique<MovableComponent>(120));
    comps.emplace_back(std::make_unique<MovableComponent>(80));
    comps.emplace_back(std::make_unique<MovableComponent>(150));
    comps[0]->setName("0 - Distortion");
    comps[1]->setName("1 - Reverb");
    comps[2]->setName("2 - OTT");
    comps[3]->setName("3 - IDK lmao");

    for (auto& comp : comps)
        addAndMakeVisible(*comp);

}

RackLayout::~RackLayout()
{
}

void RackLayout::paint (juce::Graphics& g)
{
    auto rect = getLocalBounds().toFloat().reduced(0.5f);

    g.setColour(juce::Colours::black);
    g.drawRoundedRectangle(rect, 4.f, 1.f);

    if (curMoving != nullptr && curMoving != newPosition && 
        !(newPosition == nullptr && curMoving->getIdx() == comps.size() - 1))
    {
        const int endIdx = comps.size() - 1;
        g.setColour(juce::Colours::white);

        auto& rect = newPosition == nullptr 
            ? comps[endIdx]->getBounds()
            : newPosition->getBounds();

        const int curIdx = curMoving->getIdx();
        const int newIdx = newPosition == nullptr ? endIdx : newPosition->getIdx();

        int x = newIdx <= curIdx ? rect.getX() - 5 : rect.getRight() + 5;

        g.drawVerticalLine(x, 0, getHeight());
    }
}

void RackLayout::resized()
{
    updatePositions();
}

void RackLayout::updatePositions()
{
    auto rect = getLocalBounds();

    for (int i = 0; i < comps.size(); ++i)
    {
        auto& comp = comps[i];

        rect.removeFromLeft(10);
        comp->setBounds(rect.removeFromLeft(comp->getDesiredWidth()));
        comp->setIdx(i);
    }
}

void RackLayout::mouseDrag(const juce::MouseEvent& e)
{
    if (curMoving == nullptr) return;
    

    int curIdx = curMoving->getIdx();

    for (int i = 0; i < comps.size(); ++i)
    {
        auto& comp = comps[i];

        if (comp->getScreenBounds().getCentreX() > e.getScreenX())
        {
            int j = i <= curIdx ? i : i - 1;
            newPosition = comps[j].get();
            repaint();
            return;
        }
    }

    newPosition = nullptr;
    repaint();
}

void RackLayout::startMoving(MovableComponent* _curMoving)
{
    curMoving = _curMoving;
    //DBG(curMoving->getName());
}

void RackLayout::stopMoving()
{
    if (curMoving == nullptr || curMoving == newPosition || comps.size() <= 1)
    {
        return;
        curMoving = nullptr;
    }

    const int newIdx = newPosition == nullptr ? comps.size() - 1 : newPosition->getIdx();

    move(comps, curMoving->getIdx(), newIdx);
    updatePositions();

    curMoving = nullptr;
    repaint();
}
