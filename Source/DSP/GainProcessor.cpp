/*
  ==============================================================================

    GainProcessor.cpp
    Created: 13 Sep 2022 1:48:55pm
    Author:  thesp

  ==============================================================================
*/

#include "GainProcessor.h"

xynth::GainProcessor::GainProcessor()
{
    gain.setGainDecibels(-6.f);
}

void xynth::GainProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec spec{ sampleRate, static_cast<juce::uint32> (samplesPerBlock), 2 };
    gain.prepare(spec);
}

void xynth::GainProcessor::processBlock(juce::AudioSampleBuffer& buffer, juce::MidiBuffer&)
{
    juce::dsp::AudioBlock<float> block(buffer);
    juce::dsp::ProcessContextReplacing<float> context(block);
    gain.process(context);
}

void xynth::GainProcessor::reset()
{
    gain.reset();
}
