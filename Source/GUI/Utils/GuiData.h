/*
  ==============================================================================

    GuiData.h
    Created: 5 Sep 2022 3:56:01pm
    Author:  thesp

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../../PluginProcessor.h"
#include "../CustomLooks/CustomLook.h"

namespace xynth
{
struct DefaultLookAndFeel
{
    DefaultLookAndFeel()  { /*juce::LookAndFeel::setDefaultLookAndFeel(lnf);*/    }
    ~DefaultLookAndFeel() { juce::LookAndFeel::setDefaultLookAndFeel(nullptr); }

    void updateLnf() { juce::LookAndFeel::setDefaultLookAndFeel(lnf); }

    //juce::HellLook   hellLook;

    // Change to desired LookAndFeel
    juce::CustomLook* lnf; //= &hellLook;
};

struct GuiData
{
    GuiData(AudioGraphTestAudioProcessor& p, DefaultLookAndFeel& defLnf, double& s, juce::ApplicationProperties& props)
        : audioProcessor(p), scale(s), defaultLnf(defLnf), properties(props) 
    {}

    void updateLnf(int skin) 
    { 
        //if (skin == first)
        //    defaultLnf.lnf = &defaultLnf.hellLook;
        //else
        //    jassertfalse; // wrong index (too many items?)

        defaultLnf.updateLnf(); 

        properties.getUserSettings()->setValue("Skin", skin);
        properties.saveIfNeeded();
    }

    AudioGraphTestAudioProcessor& audioProcessor;
    double& scale;
    DefaultLookAndFeel& defaultLnf;
    juce::ApplicationProperties& properties;

    juce::CustomLook& getLnf() { return *defaultLnf.lnf; }
    std::function<void()> showAbout;

private:
    enum skinEnum { first };

};
} //namespace xynth