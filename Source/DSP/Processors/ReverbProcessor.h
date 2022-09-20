/*
  ==============================================================================

    ReverbProcessor.h
    Created: 19 Sep 2022 5:50:41pm
    Author:  thesp

  ==============================================================================
*/

#pragma once

#include "../Utils/ProcessorBase.h"

namespace xynth
{
class ReverbProcessor : public ProcessorBase
{
public:
    ReverbProcessor();
    ~ReverbProcessor() = default;

    const juce::String getName() const override { return "Reverb"; }

    void prepareToPlay(double, int) override;
    void processBlock(juce::AudioSampleBuffer& buffer, juce::MidiBuffer&) override;
    void reset() override;

private:
    juce::dsp::Reverb reverb;
};
}