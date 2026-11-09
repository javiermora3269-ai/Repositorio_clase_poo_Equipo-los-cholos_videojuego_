#pragma once
#include "Class_Jugador.hpp"
#include "Class_Entity.hpp"

// S I S T E M A   D E   B A T A L L A
class Batalla { //Batalla es una clase dedicada para almacenar las funciones relacionadas a las batallas entre dos Entitys
public:

    //CursoDeBatalla() es el cerebro de todas las batallas del juego
    //Aqui es donde se desarrolla toda la logica del combate por turnos tomando las funciones ya creadas en la clase
    void CursoDeBatalla(Jugador &Uno, Entity &Dos);

private:

    //Iniciar() es el metodo que da inicio a la batalla, mostrando los atributos y decidiendo quien comienza
    void Iniciar(Jugador &A, Entity &B);

    //Mediante esta funcion, el jugador podra realizar sus ataques, actos o acciones
    void TurnoJugador(Jugador &A, Entity &B);

    //Maneja la logica del turno de la Entity
    void TurnoEntity(Entity &A, Jugador &B);

    //Si la Entity no muere, se llama a esta funcion
    void CambioDeTurno(Entity &B, bool PlayerTurn);

    //Controla todas las opciones que puede realizar el jugador durante una batalla
    void OpcionesDeBatalla(Jugador &Player, Entity &Enemigo);

    //Controla los actos/acciones pasivas que puede realizar el jugador durante una batalla
    void OpcionesDeActo(Jugador &Player, Entity &Enemigo);
};
