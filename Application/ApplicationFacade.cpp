#include <Application/ApplicationFacade.hpp>


ApplicationFacade::ApplicationFacade(const std::string& menuContent)
    : ioHandler(menuContent)
    , graph(nullptr)
{ }

void ApplicationFacade::printMenu()
{
    ioHandler.printMenu();
}

bool ApplicationFacade::readMenuSelection()
{
    return ioHandler.readMenuSelection();
}

char ApplicationFacade::getCurrentMenuSelection()
{
    return ioHandler.getCurrentMenuSelection();
}

BaseAction* ApplicationFacade::getSelectedAction()
{
    return ioHandler.getSelectedAction();
}
