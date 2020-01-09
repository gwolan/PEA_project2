#include <iostream>
#include <Application/Menu/IOhandler.hpp>
#include <Application/Menu/Actions/ExitProgram.hpp>
#include <Application/Menu/Actions/ReadGraphFromFile.hpp>
#include <Application/Menu/Actions/DisplayGraph.hpp>
#include <Application/Menu/Actions/GenerateRandomGraph.hpp>
#include <Application/Menu/Actions/PerformBruteForce.hpp>
#include <Application/Menu/Actions/PerformBranchAndBound.hpp>
#include <Application/Menu/Actions/MeasureBruteForce.hpp>
#include <Application/Menu/Actions/MeasureBranchAndBound.hpp>


IOhandler::IOhandler(const std::string& menuContent)
    : selectedAction(nullptr)
    , currentSelection(0)
    , menu(menuContent)
{ }

void IOhandler::printMenu()
{
    std::cout << menu;
}

char IOhandler::getCurrentMenuSelection()
{
    return currentSelection;
}

BaseAction* IOhandler::getSelectedAction()
{
    return selectedAction.get();
}

bool IOhandler::readMenuSelection()
{
    std::cin >> currentSelection;

    return validateInput();
}

bool IOhandler::validateInput()
{
    switch(currentSelection)
    {
        case '0':
        {
            selectedAction = std::make_unique<ExitProgram>("Wyjście z programu");
        }
        break;
        case '1':
        {
            selectedAction = std::make_unique<ReadGraphFromFile>("Wczytanie grafu z pliku");
        }
        break;
        case '2':
        {
            selectedAction = std::make_unique<GenerateRandomGraph>("Wygenerowanie losowego grafu");
        }
        break;
        case '3':
        {
            selectedAction = std::make_unique<DisplayGraph>("Wyświetlenie grafu (macierz sasiedztwa)");
        }
        break;
        case '4':
        {
            selectedAction = std::make_unique<PerformBruteForce>("Wykonanie przeglądu zupelnego metoda Brute Force");
        }
        break;
        case '5':
        {
            selectedAction = std::make_unique<PerformBranchAndBound>("Znalezienie optymalnej sciezki algorytmem B&B");
        }
        break;
        case '6':
        {
            selectedAction = std::make_unique<MeasureBruteForce>("Pomiary dla przegladu zupelnego");
        }
        break;
        case '7':
        {
            selectedAction = std::make_unique<MeasureBranchAndBound>("Pomiary dla Branch&Bound");
        }
        break;
        default:
        {
            std::cout << "Wybrana opcja nie istnieje." << std::endl << std::endl;
            return false;
        }
    }

    std::cout << "Wybrano - " << selectedAction->getActionName() << std::endl << std::endl;
    return true;
}
