#pragma once

#include <Algorithms/TabuSearch/LocalSearch.hpp>
#include <Algorithms/TabuSearch/Utils/TabuConfiguration.hpp>


class TabuSearch
{
    public:
    TabuSearch(const TabuConfiguration& tabuConfig);
    ~TabuSearch() = default;

    


    private:
    LocalSearch localSearch;
    const TabuConfiguration& tabuConfiguration;
};
