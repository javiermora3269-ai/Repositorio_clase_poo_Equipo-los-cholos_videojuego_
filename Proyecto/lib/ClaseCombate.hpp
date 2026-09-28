#pragma once
#include <string>
#include "ClaseCriatura.hpp"

class Combate{
private:

    int opcionJugador;
    int dificultad;
    int modoJuego;

protected:

    int opcionOponente;
    int ronda;

public:

    
    Combate(){
        opcionJugador = 0;
        opcionOponente = 0;
        dificultad = 1; //Variable para escoger la dificultad Javier Mora Gutierrez
        modoJuego = 1;
        ronda = 1;
    }

    //MENU PARA EL JUGADOR
    void MenuDeJuego();

    //MUESTRA LAS OPCIONES DE CRIATURAS DISPONIBLES
    void mostrarMenuCriaturas();

    //DEJAR AL JUGADOR GENERAR UNA OPCION
    Criatura crearCriaturaPorOpcion(int opcion);

    void GenerarOpcionJugador();

    void GenerarOpcionOponente();

    void MostrarPantallaFinal(Criatura &jugador, Criatura &oponente);

    int GetDificultad() const { return dificultad; }

    int GetModoDeJuego() const { return modoJuego; }

    int GetOpcionJugador() const { return opcionJugador; }

    int GetOpcionOponente() const { return opcionOponente; }

};