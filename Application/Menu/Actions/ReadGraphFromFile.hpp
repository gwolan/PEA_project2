#pragma once

#include <memory>
#include <Application/Menu/Actions/BaseAction.hpp>
#include <Miscellanous/TSPLIBparser.hpp>


class GraphMatrix;

class ReadGraphFromFile : public BaseAction
{
    public:
    ReadGraphFromFile(const std::string& actionName);
    ~ReadGraphFromFile() = default;

    void run();
    void init(std::unique_ptr<GraphMatrix>& graphMatrix);


    private:
    void fillGraphAdjacencyMatrix();

    std::unique_ptr<GraphMatrix>* graph;
    TSPLIBparser parser;
    std::string fileName;
};
