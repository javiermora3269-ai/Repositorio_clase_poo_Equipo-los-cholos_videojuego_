#pragma once
#include <string>
#include <windows.h>
#include "Class_Criatura.hpp"

//Funciones de UI
class UserInterface{
private:

    int Opcion;

public:

    UserInterface() { Opcion = 0; }

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
        Exclusiva,
        Particular
    };
    
    void EjecutarAccion();

    void EjecutarActo(Criatura &A, int NumeroActos);

    int GetOpcion() const { return Opcion; }
};

extern UserInterface UI;