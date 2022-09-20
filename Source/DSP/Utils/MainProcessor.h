/*
  ==============================================================================

    MainProcessor.h
    Created: 19 Sep 2022 5:27:14pm
    Author:  thesp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Processors/ProcessorHeader.h"

namespace xynth
{
class MainProcessor
{
public:
    MainProcessor();
    ~MainProcessor() = default;

    void prepare(double sampleRate, int samplesPerBlock, int inChannels, int outChannels);
    void releaseResources();
    void updateGraph(std::vector<int>& compIds);

    void processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages);

private:
    using AudioGraphIOProcessor = juce::AudioProcessorGraph::AudioGraphIOProcessor;
    using Node = juce::AudioProcessorGraph::Node;

    void initialiseGraph();
    void connectAudioNodes();
    void connectMidiNodes();

    DistortionProcessor distortionProcessor;
    ReverbProcessor reverbProcessor;
    FilterProcessor filterProcessor;
    GainProcessor gainProcessor;

    std::unique_ptr<ProcessorBase> selectSwitch(int i) {
        switch (i) {
        case 0: return std::make_unique<ProcessorBase>();
        case 1: return std::make_unique<DistortionProcessor>();
        case 2: return std::make_unique<ReverbProcessor>();
        case 3: return std::make_unique<FilterProcessor>();
        case 4: return std::make_unique<GainProcessor>();
        default: jassertfalse; return 0;
        }
    }

    std::array<ProcessorBase*, 5> processors{ nullptr, &distortionProcessor, 
        &reverbProcessor, &filterProcessor, &gainProcessor };

    std::unique_ptr<juce::AudioProcessorGraph> mainProcessor;

    Node::Ptr audioInputNode;
    Node::Ptr audioOutputNode;
    Node::Ptr midiInputNode;
    Node::Ptr midiOutputNode;

    double sampleRate; 
    int samplesPerBlock;

};
} // namespace xynth