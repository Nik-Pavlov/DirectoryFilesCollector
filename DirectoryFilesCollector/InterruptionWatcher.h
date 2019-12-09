#pragma once

class InterruptionWatcher
{
public:
    InterruptionWatcher();
    bool isInterrupted() const;

private:

    const unsigned long m_timeoutMs;
    bool isKeyPressed(unsigned long timeoutMs) const;
};