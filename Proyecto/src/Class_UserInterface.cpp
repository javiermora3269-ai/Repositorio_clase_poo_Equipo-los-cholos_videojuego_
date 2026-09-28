#include <iostream>
#include <windows.h>
#include <limits>
#include "../lib/Class_UserInterface.hpp"

//Funciones de UI
void UserInterface::Output(const std::string& texto, unsigned long VelocidadT, unsigned long VelocidadTM){
    for(unsigned int i = 0; i < texto.length(); i++){
        char c = texto[i];
        std::cout << c;
        if(c == '.' || c == '?' || c == '!'){
            Sleep(VelocidadTM);
        } else Sleep(VelocidadT);
    }
    std::cout << std::endl;
}

void UserInterface::Input(int InferiorLimit, int SuperiorLimit, const std::string& Question){
    Option = InferiorLimit-2;
    do{
        std::cout << Question << " -> ";
        std::cin >> Option;
        if(std::cin.fail() || std::cin.peek() != '\n'){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            Option = InferiorLimit-2;
        }
    }while(Option < InferiorLimit || Option > SuperiorLimit);
}

UserInterface UI;