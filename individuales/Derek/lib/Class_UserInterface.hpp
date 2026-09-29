#pragma once
#include <string>
#include <windows.h>
#include "Class_Criatura.hpp"

//Funciones de UI
class UserInterface{
private:

    int Battle_Option;
    int History_Option;

public:

    UserInterface() { Battle_Option = 0; History_Option = 0; }

    void MostrarTexto(const std::string& texto, unsigned long VelocidadT, unsigned long VelocidadTM);

    //Acciones de Batalla
    enum OpcBatalla{
        Default,
        Atacar,
        Actuar,
        Perdonar
    };

    //Acciones al Actuar
    enum OpcActuar{
        Regresar,
        Descripcion,
        Objeto,
        Especial,
        ExZero,
        ExOne
    };
    
    void EjecutarAccion();

    void EjecutarActo(Criatura &A, int NumeroActos);

    void Input(int InferiorLimit, int SuperiorLimit, const std::string& Question);

    int GetBattleOption() const { return Battle_Option; }

    int GetHistoryOption() const { return History_Option; }
};

extern UserInterface UI;
