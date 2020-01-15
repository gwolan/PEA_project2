#pragma once

#include <vector>
#include <cstdint>
#include <memory>


class GraphMatrix;

class GreedyLocalSearch
{
    public:
    GreedyLocalSearch();
    ~GreedyLocalSearch() = default;

    std::vector<uint32_t> findStartingPathGreedyStyle(std::unique_ptr<GraphMatrix>& graphMatrix, uint32_t startingVertex);


    private:
    template<class Iterator>
    bool wasVertexAlreadyChecked(Iterator begin, Iterator end, const uint32_t vertex);
    bool isGivenEdgePromising(const uint32_t edgeWeight, const uint32_t upperBound);

    const int32_t INFINITY;
};
