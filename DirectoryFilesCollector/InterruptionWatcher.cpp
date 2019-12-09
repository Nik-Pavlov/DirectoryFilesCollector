#include "pch.h"
#include "InterruptionWatcher.h"

#include <windows.h>


InterruptionWatcher::InterruptionWatcher()
    : m_timeoutMs(100)
{

}

bool InterruptionWatcher::isInterrupted() const
{
    return isKeyPressed(m_timeoutMs);
}

bool InterruptionWatcher::isKeyPressed(unsigned long timeout_ms) const
{
    return WaitForSingleObject(GetStdHandle(STD_INPUT_HANDLE), timeout_ms) == WAIT_OBJECT_0;
}
