#include <iostream>
#include <windows.h>
#include <limits>
#include "../lib/Class_UserInterface.hpp"

//Funciones de UI
void UserInterface::MostrarTexto(const std::string& texto, unsigned long VelocidadT, unsigned long VelocidadTM){
    for(unsigned int i = 0; i < texto.length(); i++){
        char c = texto[i];
        std::cout << c;
        if(c == '.' || c == '?' || c == '!'){
            Sleep(VelocidadTM);
        } else Sleep(VelocidadT);
    }
    std::cout << std::endl;
}

void UserInterface::EjecutarAccion(){
    std::cout << std::endl;
    Battle_Option = -1;
    do{
        std::cout << "1: Atacar  |  2: Actuar  |  3: Perdonar  -> ";
        std::cin >> Battle_Option;
        if(std::cin.fail() || std::cin.peek() != '\n'){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }while(Battle_Option < OpcBatalla::Atacar || Battle_Option > OpcBatalla::Perdonar);
}

void UserInterface::EjecutarActo(Criatura &A, int NumeroActos){
    int MaxLimit = !A.GetEsJefe() ? OpcActuar::Especial : (NumeroActos+3);
    Battle_Option = -1;
    do{
        std::cout << "1: Descripcion  |  2: Curar  |  " << A.ImprimirActos() << "  |  0: Regresar -> ";
        std::cin >> Battle_Option;
        if(std::cin.fail() || std::cin.peek() != '\n'){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }while(Battle_Option < OpcActuar::Regresar || Battle_Option > MaxLimit);
}

void UserInterface::Input(int InferiorLimit, int SuperiorLimit, const std::string& Question){
    History_Option = InferiorLimit-2;
    do{
        std::cout << Question << " -> ";
        std::cin >> History_Option;
        if(std::cin.fail() || std::cin.peek() != '\n'){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            History_Option = InferiorLimit-2;
        }
    }while(History_Option < InferiorLimit || History_Option > SuperiorLimit);
}

UserInterface UI;
