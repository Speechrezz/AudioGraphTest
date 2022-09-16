/*
  ==============================================================================

    MovableComponent.cpp
    Created: 15 Sep 2022 10:53:02am
    Author:  thesp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MovableComponent.h"
#include "../Rack/RackLayout.h"

MovableComponent::MovableComponent(int _width) : width(_width)
{

}

MovableComponent::~MovableComponent()
{
}

void MovableComponent::paint (juce::Graphics& g)
{
    auto rect = getLocalBounds().toFloat();

    juce::Path clip;
    clip.addRoundedRectangle(rect, 4.f);
    g.reduceClipRegion(clip);

    g.setColour(juce::Colours::black.brighter(0.1f));
    g.fillRoundedRectangle(rect, 4.f);

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText (getName(), getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text

    auto bodyRect = rect;

    g.setColour(juce::Colours::black.brighter(0.2f));
    g.fillRect(bodyRect.removeFromTop(headerHeight));


    auto outlineColour = isMouseButtonDown() ? juce::Colours::darkgrey : juce::Colours::black;
    g.setColour(outlineColour);
    g.drawRoundedRectangle(rect.reduced(0.5f), 4.f, 1.f);
}

void MovableComponent::resized()
{

}

void MovableComponent::mouseDown(const juce::MouseEvent& e)
{
    repaint();

    if (e.y > headerHeight) return;

    isMoving = true;
    auto parent = dynamic_cast<RackLayout*>(getParentComponent());
    parent->startMoving(this);
}

void MovableComponent::mouseDrag(const juce::MouseEvent& e)
{
    if (!isMoving) return;
    auto parent = dynamic_cast<RackLayout*>(getParentComponent());
    parent->mouseDrag(e);
}

void MovableComponent::mouseUp(const juce::MouseEvent& e)
{
    repaint();

    if (!isMoving) return;
    auto parent = dynamic_cast<RackLayout*>(getParentComponent());
    parent->stopMoving();
    isMoving = false;
}
