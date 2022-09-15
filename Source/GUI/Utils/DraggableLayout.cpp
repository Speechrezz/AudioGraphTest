/*
  ==============================================================================

    DraggableLayout.cpp
    Created: 14 Sep 2022 5:16:48pm
    Author:  thesp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DraggableLayout.h"

DraggableLayout::DraggableLayout(xynth::GuiData& g) : guiData(g)
{
}

DraggableLayout::~DraggableLayout()
{
}

void DraggableLayout::paint (juce::Graphics& g)
{
    auto rect = getLocalBounds().toFloat();

    g.setColour(juce::Colours::black);
    g.fillRoundedRectangle(rect, 4.f);
    g.fillAll (juce::Colours::black);   // clear the background


    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("DraggableLayout", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void DraggableLayout::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void DraggableLayout::mouseDown(const juce::MouseEvent& e)
{
    dragger.startDraggingComponent(this, e);
}

void DraggableLayout::mouseDrag(const juce::MouseEvent& e)
{
    dragger.dragComponent(this, e, nullptr);

    constrain();
}

void DraggableLayout::mouseUp(const juce::MouseEvent& e)
{
}

void DraggableLayout::constrain()
{
    int minC = 0;
    int maxX = getParentComponent()->getWidth()  - getWidth()  - minC;
    int maxY = getParentComponent()->getHeight() - getHeight() - minC;
    if (getX() < minC)
        setBounds(minC, getY(), getWidth(), getHeight());
    if (getY() < minC)
        setBounds(getX(), minC, getWidth(), getHeight());

    if (getX() > maxX)
        setBounds(maxX, getY(), getWidth(), getHeight());
    if (getY() > maxY)
        setBounds(getX(), maxY, getWidth(), getHeight());
}
