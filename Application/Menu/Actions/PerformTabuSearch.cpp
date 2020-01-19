#include <iostream>
#include <vector>
#include <cstdint>
#include <Application/Menu/Actions/PerformTabuSearch.hpp>
#include <Graph/GraphMatrix.hpp>


PerformTabuSearch::PerformTabuSearch(const std::string& actionName, const TabuConfiguration& tabuConfig)
    : BaseAction(actionName)
    , graph(nullptr)
    , tabuSearch(tabuConfig)
    , timer()
{ }

void PerformTabuSearch::init(std::unique_ptr<GraphMatrix>& graphMatrix)
{
    graph = &graphMatrix;
}

void PerformTabuSearch::run()
{
    if(graph->get())
    {
        timer.start();
        PathWithCost result = tabuSearch.findBestPossibleRoute(*graph);
        timer.stop();

        printResults(result);
    }
    else
    {
        std::cout << "Graf jest pusty!" << std::endl << std::endl;
    }
}

void PerformTabuSearch::printResults(const PerformTabuSearch::PathWithCost& result)
{
    std::cout << "Algorytm wykonal sie w czasie: " << timer.getTime() << " [s]" << std::endl << std::endl;

    printPath(result.second);
    std::cout << "Koszt trasy: " << result.first << std::endl;

    std::cout << std::endl;
}

void PerformTabuSearch::printPath(const std::vector<uint32_t>& resultPath)
{
    std::cout << "Minimalna trasa: ";
    for(auto& vertex : resultPath)
    {
        std::cout << vertex << " ";

        if(&vertex != &resultPath.back())
        {
            std::cout << "-> ";
        }
    }
    std::cout << std::endl;
}
