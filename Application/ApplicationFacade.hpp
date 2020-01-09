#pragma once

#include <string>
#include <memory>
#include <Graph/GraphMatrix.hpp>
#include <Application/Menu/IOhandler.hpp>
#include <Application/Menu/ActionStrategy.hpp>


class ApplicationFacade
{
    public:
    ApplicationFacade(const std::string& menuContent);
    ~ApplicationFacade() = default;

    void run();
    void printMenu();
    bool readMenuSelection();
    char getCurrentMenuSelection();


    private:
    IOhandler ioHandler;
    ActionStrategy actionStrategy;
    std::unique_ptr<GraphMatrix> graph;
};
