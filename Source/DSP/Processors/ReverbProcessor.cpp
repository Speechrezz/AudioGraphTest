/*
  ==============================================================================

    ReverbProcessor.cpp
    Created: 19 Sep 2022 5:50:41pm
    Author:  thesp

  ==============================================================================
*/

#include "ReverbProcessor.h"

xynth::ReverbProcessor::ReverbProcessor()
{
}

void xynth::ReverbProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec spec{ sampleRate, static_cast<juce::uint32> (samplesPerBlock), 2 };
    reverb.prepare(spec);
}

void xynth::ReverbProcessor::processBlock(juce::AudioSampleBuffer& buffer, juce::MidiBuffer&)
{
    juce::dsp::AudioBlock<float> block(buffer);
    juce::dsp::ProcessContextReplacing<float> context(block);
    reverb.process(context);
}

void xynth::ReverbProcessor::reset()
{
    reverb.reset();
}
