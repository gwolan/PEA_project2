#pragma once

#include <string>


class IOhandler
{
    public:
    IOhandler(const std::string& menuContent);
    ~IOhandler() = default;

    void printMenu();
    bool readMenuSelection();
    char getCurrentMenuSelection();


    private:
    char currentSelection;
    const std::string menu;
};
