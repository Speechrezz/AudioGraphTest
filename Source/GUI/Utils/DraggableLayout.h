/*
  ==============================================================================

    DraggableLayout.h
    Created: 14 Sep 2022 5:16:48pm
    Author:  thesp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "GuiData.h"

class DraggableLayout  : public juce::Component
{
public:
    DraggableLayout(xynth::GuiData&);
    ~DraggableLayout() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void mouseDown(const juce::MouseEvent& e) override;
    void mouseDrag(const juce::MouseEvent& e) override;
    void mouseUp(const juce::MouseEvent& e) override;

    // For drawing
    //void mouseEnter(const juce::MouseEvent& e) override;
    //void mouseExit(const juce::MouseEvent& e) override;

private:
    void constrain();

    xynth::GuiData& guiData;

    juce::ComponentDragger dragger;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DraggableLayout)
};
