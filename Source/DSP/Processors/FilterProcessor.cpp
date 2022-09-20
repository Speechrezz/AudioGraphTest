/*
  ==============================================================================

    FilterProcessor.cpp
    Created: 19 Sep 2022 5:50:11pm
    Author:  thesp

  ==============================================================================
*/

#include "FilterProcessor.h"

namespace xynth
{
FilterProcessor::FilterProcessor()
{
}

void FilterProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec spec{ sampleRate, static_cast<juce::uint32> (samplesPerBlock), 2 };
    filter.prepare(spec);

    *filter.state = *juce::dsp::IIR::Coefficients<float>::makeLowPass(spec.sampleRate, 5000.f, .7f);
}

void FilterProcessor::processBlock(juce::AudioSampleBuffer& buffer, juce::MidiBuffer&)
{
    juce::dsp::AudioBlock<float> block(buffer);
    juce::dsp::ProcessContextReplacing<float> context(block);
    filter.process(context);
}

void FilterProcessor::reset()
{
    filter.reset();
}
} // namespace xynth