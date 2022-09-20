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

void MainProcessor::prepare(double _sampleRate, int _samplesPerBlock, int inChannels, int outChannels)
{
    sampleRate = _sampleRate;
    samplesPerBlock = _samplesPerBlock;

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

    connectAudioNodes();
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

void MainProcessor::updateGraph(std::vector<int>& compIds)
{
    for (auto connection : mainProcessor->getConnections())
        mainProcessor->removeConnection(connection);

    const int size = compIds.size();

    for (int i = 0; i < compIds.size(); ++i)
    {
        nodes[i] = mainProcessor->addNode(selectSwitch(compIds[i]));
        nodes[i]->getProcessor()->prepareToPlay(sampleRate, samplesPerBlock);
    }

    // Connect nodes
    for (int i = 0; i < compIds.size() - 1; ++i)
        for (int channel = 0; channel < 2; ++channel)
            mainProcessor->addConnection({ {nodes[i]->nodeID,     channel},
                                           {nodes[i + 1]->nodeID, channel} });

    // Connect input and output nodes to system
    for (int channel = 0; channel < 2; ++channel)
    {
        mainProcessor->addConnection({ {audioInputNode->nodeID,  channel},
                                       {nodes[0]->nodeID,        channel} });
        mainProcessor->addConnection({ {nodes[size - 1]->nodeID, channel},
                                       {audioOutputNode->nodeID, channel} });
    }

    connectMidiNodes();
}
} // namespace xynth