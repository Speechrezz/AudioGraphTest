/*
  ==============================================================================

    GainProcessor.h
    Created: 13 Sep 2022 1:48:55pm
    Author:  thesp

  ==============================================================================
*/

#pragma once

#include "Utils/ProcessorBase.h"

namespace xynth
{
class GainProcessor : public ProcessorBase
{
public:
    GainProcessor();
    ~GainProcessor() = default;

    const juce::String getName() const override { return "Gain"; }

    void prepareToPlay(double, int) override;
    void processBlock(juce::AudioSampleBuffer& buffer, juce::MidiBuffer&) override;
    void reset() override;

private:
    juce::dsp::Gain<float> gain;
};
}