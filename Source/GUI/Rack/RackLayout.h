/*
  ==============================================================================

    RackLayout.h
    Created: 14 Sep 2022 6:49:33pm
    Author:  thesp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Utils/MovableComponent.h"

class RackLayout  : public juce::Component
{ 
public:
    RackLayout(xynth::GuiData&);
    ~RackLayout() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void updatePositions();

    void mouseDrag(const juce::MouseEvent& e) override;

    void startMoving(MovableComponent* curMoving);
    void stopMoving();

private:
    template <typename t> void move(std::vector<t>& v, size_t oldIndex, size_t newIndex)
    {
        if (oldIndex > newIndex)
            std::rotate(v.rend() - oldIndex - 1, v.rend() - oldIndex, v.rend() - newIndex);
        else
            std::rotate(v.begin() + oldIndex, v.begin() + oldIndex + 1, v.begin() + newIndex + 1);
    }

    xynth::GuiData& guiData;

    std::vector<std::unique_ptr<MovableComponent>> comps;

    // Holds the currently moving component
    MovableComponent* curMoving  { nullptr };
    MovableComponent* newPosition{ nullptr };


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RackLayout)
};
