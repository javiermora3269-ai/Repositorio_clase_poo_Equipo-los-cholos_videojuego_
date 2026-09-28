#pragma once
#include "ClaseCombate.hpp"

class ModoDeJuegoPVE : public Combate{
public:
    //LOGICA DE COMBATE DE LA IA
    // FUNCION PARA EL TURNO DE LA IA (1 JUGADOR)
    // Aportacion Javier Mora Gutierrez
    void ejecutarTurnoIA(Criatura &oponente, Criatura &jugador, int dificultad);

    // LOGICA DE BATALLA PARA EL PLAYER VS ENEMY (BOT)
    void CursoDeBatallaPVE();
};