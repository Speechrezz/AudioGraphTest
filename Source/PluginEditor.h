/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "GUI/WindowLayout.h"
#include "GUI/Utils/GuiData.h"

class AudioGraphTestAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    AudioGraphTestAudioProcessorEditor (AudioGraphTestAudioProcessor&);
    ~AudioGraphTestAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    juce::SharedResourcePointer<xynth::DefaultLookAndFeel> defaultLnf;

private:
    AudioGraphTestAudioProcessor& audioProcessor;
    xynth::GuiData guiData;
    WindowLayout windowLayout;

    // Stores global plugin settings
    juce::ApplicationProperties properties;
    double scale{ 1.0 };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioGraphTestAudioProcessorEditor)
};
