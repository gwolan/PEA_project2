#pragma once

#include <string>
#include <memory>
#include <Application/Menu/IOhandler.hpp>
#include <Graph/GraphMatrix.hpp>


class ApplicationFacade
{
    public:
    ApplicationFacade(const std::string& menuContent);
    ~ApplicationFacade() = default;

    void printMenu();
    bool readMenuSelection();
    char getCurrentMenuSelection();
    BaseAction* getSelectedAction();

    std::unique_ptr<GraphMatrix> graph;

    private:
    IOhandler ioHandler;
};
