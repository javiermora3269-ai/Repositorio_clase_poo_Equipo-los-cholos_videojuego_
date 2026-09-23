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
    Opcion = -1;
    do{
        std::cout << "1: Atacar  |  2: Actuar  |  3: Perdonar  -> ";
        std::cin >> Opcion;
        if(std::cin.fail() || std::cin.peek() != '\n'){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }while(Opcion < OpcBatalla::Atacar || Opcion > OpcBatalla::Perdonar);
}

void UserInterface::EjecutarActo(Criatura &A, int NumeroActos){
    int MaxLimit = !A.GetEsJefe() ? OpcActuar::Especial : (NumeroActos+3);
    Opcion = -1;
    do{
        std::cout << "1: Descripcion  |  2: Curar  |  " << A.ImprimirActos() << "  |  0: Regresar -> ";
        std::cin >> Opcion;
        if(std::cin.fail() || std::cin.peek() != '\n'){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }while(Opcion < OpcActuar::Regresar || Opcion > MaxLimit);
}

UserInterface UI;