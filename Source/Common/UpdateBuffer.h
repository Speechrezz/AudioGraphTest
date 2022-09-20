/*
  ==============================================================================

    UpdateBuffer.h
    Created: 16 Sep 2022 10:06:48am
    Author:  thesp

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "Constants.h"
#include "../GUI/Utils/MovableComponent.h"

namespace xynth
{
/// <summary>
/// Designed to update the audio thread when changes are made in the visual thread
/// </summary>
class UpdateBuffer
{
public:
    UpdateBuffer() = default;
    ~UpdateBuffer() = default;

    void pushState(std::vector<std::unique_ptr<MovableComponent>>& comps);
    std::vector<int>& readState();

    bool isUnread() const;

private:
    std::atomic<int> stateAtomic = idle;
    std::vector<int> compIds;

    enum states
    {
        idle, unread
    };

};
} // namespace xynth