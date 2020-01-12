#include <Algorithms/TabuSearch/Utils/TabuConfiguration.hpp>


// default values for Tabu Search algorithm
TabuConfiguration::TabuConfiguration()
    : tabuInterval(60)
    , tabuDiversification(true)
    , tabuNumberOfIterations(10000)
    , tabuCadencyLength(0)
{ }

void TabuConfiguration::setTabuInterval(uint32_t intervalInSeconds)
{
    tabuInterval = intervalInSeconds;
}

void TabuConfiguration::enableDiversification()
{
    tabuDiversification = true;
}

void TabuConfiguration::disableDiversification()
{
    tabuDiversification = false;
}

void TabuConfiguration::setDiversificationCriteria(uint32_t numberOfIterations)
{
    tabuNumberOfIterations = numberOfIterations;
}

void TabuConfiguration::setTabuCadencyLength(uint32_t cadency)
{
    tabuCadencyLength = cadency;
}

bool TabuConfiguration::isDiversificationEnabled()
{
    return tabuDiversification;
}

uint32_t TabuConfiguration::getTabuInterval()
{
    return tabuInterval;
}

uint32_t TabuConfiguration::getNumberOfIterations()
{
    return tabuNumberOfIterations;
}

uint32_t TabuConfiguration::getCadencyLength()
{
    return tabuCadencyLength;
}
