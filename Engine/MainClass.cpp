#include "MainClass.hpp"

MainClass::MainClass()
{
    if (_instance != nullptr)
        throw "main class have to have 1 instance";
    _instance = this;
}

void MainClass::onExit(){}

MainClass* MainClass::_instance = nullptr;
