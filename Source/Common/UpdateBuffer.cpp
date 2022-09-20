/*
  ==============================================================================

    UpdateBuffer.cpp
    Created: 16 Sep 2022 10:06:48am
    Author:  thesp

  ==============================================================================
*/

#include "UpdateBuffer.h"

namespace xynth
{
void UpdateBuffer::pushState(std::vector<std::unique_ptr<MovableComponent>>& comps)
{
    compIds.resize(comps.size());
    
    for (int i = 0; i < comps.size(); ++i)
    {
        auto& comp = *comps[i];
        compIds[i] = comp.getId();
    }

    stateAtomic.store(unread, std::memory_order_release);
}

std::vector<int>& UpdateBuffer::readState()
{
    int state = stateAtomic.load(std::memory_order_acquire);
    stateAtomic.store(idle, std::memory_order_relaxed);

    return compIds;
}
bool UpdateBuffer::isUnread() const
{
    return stateAtomic.load(std::memory_order_relaxed) == unread;
}
} // namespace xynth