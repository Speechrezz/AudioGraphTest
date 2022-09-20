/*
  ==============================================================================

    MovableComponent.h
    Created: 15 Sep 2022 10:53:02am
    Author:  thesp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class MovableComponent  : public juce::Component
{
public:
    MovableComponent(int width = 100);
    ~MovableComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void mouseDown(const juce::MouseEvent& e) override;
    void mouseDrag(const juce::MouseEvent& e) override;
    void mouseUp  (const juce::MouseEvent& e) override;

    inline int getIdx() { return idx; }
    void setIdx(int _idx) { idx = _idx; }

    inline int getId() { return id; }
    void setId(int _id) { id = _id; }

    inline int getDesiredWidth() const { return width; }

private:
    int idx = 0, id = 0, width = 100;
    const int headerHeight = 20;

    bool isMoving = false;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MovableComponent)
};
