/*
  ==============================================================================

    WindowLayout.cpp
    Created: 5 Sep 2022 3:26:44pm
    Author:  thesp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WindowLayout.h"

WindowLayout::WindowLayout(xynth::GuiData& g) : guiData(g), rack(g)
{
    addAndMakeVisible(rack);
}

WindowLayout::~WindowLayout()
{
}

void WindowLayout::paint (juce::Graphics& g)
{
    auto rect = getLocalBounds();
}

void WindowLayout::resized()
{
    auto rect = getLocalBounds();
    rect.reduce(20, 20);

    rack.setBounds(rect.removeFromTop(120));
}
