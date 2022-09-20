/*
  ==============================================================================

    FilterProcessor.h
    Created: 19 Sep 2022 5:50:11pm
    Author:  thesp

  ==============================================================================
*/

#pragma once

#include "../Utils/ProcessorBase.h"

namespace xynth
{
class FilterProcessor : public ProcessorBase
{
public:
    FilterProcessor();
    ~FilterProcessor() = default;

    const juce::String getName() const override { return "Filter"; }

    void prepareToPlay(double, int) override;
    void processBlock(juce::AudioSampleBuffer& buffer, juce::MidiBuffer&) override;
    void reset() override;

private:
    juce::dsp::ProcessorDuplicator<
        juce::dsp::IIR::Filter<float>,
        juce::dsp::IIR::Coefficients<float>> filter;
};
}