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

    g.setColour(juce::Colours::black);
    g.fillRoundedRectangle(rect, 4.f);

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText (getName(), getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text


    if (isMouseButtonDown())
    {
        g.setColour(juce::Colours::grey);
        g.drawRoundedRectangle(rect.reduced(0.5f), 4.f, 1.f);
    }
}

void MovableComponent::resized()
{

}

void MovableComponent::mouseDown(const juce::MouseEvent& e)
{
    auto parent = dynamic_cast<RackLayout*>(getParentComponent());
    parent->startMoving(this);

    repaint();
}

void MovableComponent::mouseDrag(const juce::MouseEvent& e)
{
    auto parent = dynamic_cast<RackLayout*>(getParentComponent());

    parent->mouseDrag(e);
}

void MovableComponent::mouseUp(const juce::MouseEvent& e)
{
    auto parent = dynamic_cast<RackLayout*>(getParentComponent());

    parent->stopMoving();
    repaint();
}
