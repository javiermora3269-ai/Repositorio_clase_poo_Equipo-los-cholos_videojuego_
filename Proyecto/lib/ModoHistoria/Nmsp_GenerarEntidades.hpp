#pragma once
#include "Class_Entity.hpp"

/* N A M E S P A C E S   P R O P I O S */
namespace GenerarEntidades{

    /* Esta funcion se basa en el uso de rand() y Chapter para crear la aparicion de enemigos distintos, 
       favoreciendo asi las partidas aleatorias dentro del juego */
    Entity* GenerarCriatura(int Chapter);

    /* Esta funcion se basa en el uso del nivel actual del jugador para hacer aparecer los jefes 
       del juego para, asi, si el jugador tiene un nivel superior a l especificado, no se pueda enfrentar
       a un jefe que no podra derrotar */
    Entity* GenerarBoss(int Chapter);

    /* Esta funcion se basa en el uso de punteros llamados por referencia (*&) para hacer modificacion
       de los nuevos objetos creados y asi poder eliminarlos del juego con la palabra reservada -delete-.
       Esto es equivalente al doble puntero en C (**) */
    void EliminarEntidad(Entity* &p_Entidad);
}