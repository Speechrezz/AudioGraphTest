/*
  ==============================================================================

    DistortionProcessor.cpp
    Created: 19 Sep 2022 5:49:58pm
    Author:  thesp

  ==============================================================================
*/

#include "DistortionProcessor.h"

namespace xynth
{
DistortionProcessor::DistortionProcessor()
{
    waveshaper.functionToUse = [](float x)
    {
        const float sign = std::copysign(1.f, x);
        x = std::abs(x * 4.f);
        if (x > 0.5f)
            x = 0.5f + (x - 0.5f) / (1.f + std::pow((x - 0.5f) * 2.f, 2.f));

        return sign * x * 1.3333333f * .25f;
    };
}

void DistortionProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec spec{ sampleRate, static_cast<juce::uint32> (samplesPerBlock), 2 };
    waveshaper.prepare(spec);
}

void DistortionProcessor::processBlock(juce::AudioSampleBuffer& buffer, juce::MidiBuffer&)
{
    juce::dsp::AudioBlock<float> block(buffer);
    juce::dsp::ProcessContextReplacing<float> context(block);
    waveshaper.process(context);
}

void DistortionProcessor::reset()
{
    waveshaper.reset();
}
} // namespace xynth