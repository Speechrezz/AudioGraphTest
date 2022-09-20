/*
  ==============================================================================

    MainProcessor.cpp
    Created: 19 Sep 2022 5:27:14pm
    Author:  thesp

  ==============================================================================
*/

#include "MainProcessor.h"

namespace xynth
{
MainProcessor::MainProcessor() : mainProcessor(new juce::AudioProcessorGraph())
{
}

void MainProcessor::prepare(double sampleRate, int samplesPerBlock, int inChannels, int outChannels)
{
    mainProcessor->setPlayConfigDetails(inChannels, outChannels, sampleRate, samplesPerBlock);
    mainProcessor->prepareToPlay(sampleRate, samplesPerBlock);

    initialiseGraph();
}

void MainProcessor::releaseResources()
{
    mainProcessor->releaseResources();
}

void MainProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    // updateGraph();

    mainProcessor->processBlock(buffer, midiMessages);
}

void MainProcessor::initialiseGraph()
{
    mainProcessor->clear();

    audioInputNode  = mainProcessor->addNode(std::make_unique<AudioGraphIOProcessor>(AudioGraphIOProcessor::audioInputNode));
    audioOutputNode = mainProcessor->addNode(std::make_unique<AudioGraphIOProcessor>(AudioGraphIOProcessor::audioOutputNode));
    midiInputNode   = mainProcessor->addNode(std::make_unique<AudioGraphIOProcessor>(AudioGraphIOProcessor::midiInputNode));
    midiOutputNode  = mainProcessor->addNode(std::make_unique<AudioGraphIOProcessor>(AudioGraphIOProcessor::midiOutputNode));

    //connectAudioNodes();
    updateGraph();
    connectMidiNodes();
}

void MainProcessor::connectAudioNodes()
{
    for (int channel = 0; channel < 2; ++channel)
        mainProcessor->addConnection({ { audioInputNode->nodeID,  channel },
                                       { audioOutputNode->nodeID, channel } });
}

void MainProcessor::connectMidiNodes()
{
    mainProcessor->addConnection({ { midiInputNode->nodeID,  juce::AudioProcessorGraph::midiChannelIndex },
                                   { midiOutputNode->nodeID, juce::AudioProcessorGraph::midiChannelIndex } });
}

void MainProcessor::updateGraph()
{
    slot1Node = mainProcessor->addNode(std::make_unique<xynth::GainProcessor>());


    for (int channel = 0; channel < 2; ++channel)
    {
        mainProcessor->addConnection({ {audioInputNode->nodeID,  channel},
                                       {slot1Node->nodeID,       channel} });
        mainProcessor->addConnection({ {slot1Node->nodeID,       channel},
                                       {audioOutputNode->nodeID, channel} });
    }
}
} // namespace xynth