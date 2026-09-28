#pragma once
#include <string>

//Funciones de UI
class UserInterface{
private:

    int Option;

public:

    UserInterface() { Option = 0; }

    void Output(const std::string& texto, unsigned long VelocidadT, unsigned long VelocidadTM);

    void Input(int InferiorLimit, int SuperiorLimit, const std::string& Question);

    int GetOption() const { return Option; }

};

extern UserInterface UI;
