/*
  ==============================================================================

    DistortionProcessor.h
    Created: 19 Sep 2022 5:49:58pm
    Author:  thesp

  ==============================================================================
*/

#pragma once

#include "../Utils/ProcessorBase.h"

namespace xynth
{
class DistortionProcessor : public ProcessorBase
{
public:
    DistortionProcessor();
    ~DistortionProcessor() = default;

    const juce::String getName() const override { return "Distortion"; }

    void prepareToPlay(double, int) override;
    void processBlock(juce::AudioSampleBuffer& buffer, juce::MidiBuffer&) override;
    void reset() override;

private:
    juce::dsp::WaveShaper<float> waveshaper;

};
} // namespace xynth