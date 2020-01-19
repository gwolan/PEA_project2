#include <Algorithms/TabuSearch/TabuSearch.hpp>


TabuSearch::TabuSearch(const TabuConfiguration& tabuConfig)
    : localSearch()
    , tabuConfiguration(tabuConfig)
{ }
