#pragma once

#include <cstdint>


class TabuConfiguration
{
    public:
    TabuConfiguration();
    ~TabuConfiguration() = default;

    void setTabuInterval(uint32_t intervalInSeconds);
    void enableDiversification();
    void disableDiversification();
    void setDiversificationCriteria(uint32_t numberOfIterations);
    void setTabuCadencyLength(uint32_t cadency);

    bool isDiversificationEnabled();
    uint32_t getTabuInterval();
    uint32_t getNumberOfIterations();
    uint32_t getCadencyLength();


    private:
    uint32_t tabuInterval;
    bool tabuDiversification;
    uint32_t tabuNumberOfIterations;
    uint32_t tabuCadencyLength;
};
