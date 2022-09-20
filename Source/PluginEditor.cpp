/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#define WIDTH 600
#define HEIGHT 300
#define MAX_SCALE 4
#define WINDOW_SCALE_ID "WindowScale"
#define APPLICATION_NAME "AudioGraphTest"
#define FILENAME_SUFFIX ".settings"
#define FILENAME_SUFFIX_KEY ".info"
#define FOLDER_NAME "Xynth"

#include "PluginProcessor.h"
#include "PluginEditor.h"

AudioGraphTestAudioProcessorEditor::AudioGraphTestAudioProcessorEditor (AudioGraphTestAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), guiData(p, *defaultLnf, scale, properties), windowLayout(guiData)
{
    // Setup global plugin settings
    juce::PropertiesFile::Options fileOptions;
    fileOptions.applicationName = APPLICATION_NAME;
    fileOptions.filenameSuffix = FILENAME_SUFFIX;
    fileOptions.folderName = FOLDER_NAME;
    fileOptions.osxLibrarySubFolder = "Application Support"; // Recommended by Apple
    fileOptions.commonToAllUsers = false;
    fileOptions.ignoreCaseOfKeyNames = false;
    fileOptions.storageFormat = juce::PropertiesFile::storeAsXML;
    properties.setStorageParameters(fileOptions);

    // Load global plugin scale
    auto* propertiesFile = properties.getUserSettings();
    if (propertiesFile)
        scale = propertiesFile->getDoubleValue(WINDOW_SCALE_ID, scale);

    // Set plugin window dimensions and scale
    setSize(double(WIDTH) * scale, double(HEIGHT) * scale);
    juce::Rectangle<int> defaultSize(WIDTH, HEIGHT);
    windowLayout.setBounds(defaultSize);

    // Allow for window to be resizable
    setResizable(true, true);
    const double aspectRatio = double(WIDTH) / double(HEIGHT);
    getConstrainer()->setFixedAspectRatio(aspectRatio);
    setResizeLimits(WIDTH / 2, HEIGHT / 2, WIDTH * MAX_SCALE, HEIGHT * MAX_SCALE);

    const int skin = properties.getUserSettings()->getIntValue("Skin", 0);
    //guiData.updateLnf(skin);

    addAndMakeVisible(windowLayout);
}

AudioGraphTestAudioProcessorEditor::~AudioGraphTestAudioProcessorEditor()
{
    properties.closeFiles();
}

//==============================================================================
void AudioGraphTestAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void AudioGraphTestAudioProcessorEditor::resized()
{
    // Calculate, store and apply window scale
    scale = (double)getWidth() / double(WIDTH);
    properties.getUserSettings()->setValue(WINDOW_SCALE_ID, scale);
    properties.saveIfNeeded();
    windowLayout.setTransform(juce::AffineTransform::scale(scale));
}
