#pragma once

#include <vector>
#include <Network/SyncedEntity.h>

class Clock
{
public:
    static Clock& getInstance()
    {
        static Clock instance;

        return instance;
    }
    int getTick();
    void tick();
private:
    Clock() {}

    int tock;

    

public:
    Clock(Clock const&) = delete;
    void operator=(Clock const&) = delete;

};