/*
  ==============================================================================

    MainProcessor.h
    Created: 19 Sep 2022 5:27:14pm
    Author:  thesp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ProcessorBase.h"
#include "../Processors/GainProcessor.h"

namespace xynth
{
class MainProcessor
{
public:
    MainProcessor();
    ~MainProcessor() = default;

    void prepare(double sampleRate, int samplesPerBlock, int inChannels, int outChannels);
    void releaseResources();

    void processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages);

private:
    using AudioGraphIOProcessor = juce::AudioProcessorGraph::AudioGraphIOProcessor;
    using Node = juce::AudioProcessorGraph::Node;

    void initialiseGraph();
    void connectAudioNodes();
    void connectMidiNodes();
    void updateGraph();

    std::unique_ptr<juce::AudioProcessorGraph> mainProcessor;

    Node::Ptr audioInputNode;
    Node::Ptr audioOutputNode;
    Node::Ptr midiInputNode;
    Node::Ptr midiOutputNode;

    Node::Ptr slot1Node;

};
} // namespace xynth