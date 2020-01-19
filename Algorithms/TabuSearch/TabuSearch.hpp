#pragma once

#include <Algorithms/TabuSearch/LocalSearch.hpp>
#include <Algorithms/TabuSearch/Utils/TabuConfiguration.hpp>
#include <Algorithms/TabuSearch/Utils/TabuMove.hpp>
#include <Miscellanous/Timer.hpp>


class GraphMatrix;

class TabuSearch
{
    private:
    using PathWithCost = std::pair<uint32_t, std::vector<uint32_t>>;

    public:
    TabuSearch(const TabuConfiguration& tabuConfig);
    ~TabuSearch() = default;

    PathWithCost findBestPossibleRoute(std::unique_ptr<GraphMatrix>& graphMatrix);


    private:
    LocalSearch localSearch;
    std::vector<TabuMove> tabuList;
    Timer timer;
    const TabuConfiguration& tabuConfiguration;
    const int32_t INFINITY;
};
