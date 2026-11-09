#include "../lib/ModoHistoria/Nmsp_GenerarEntidades.hpp"
#include "../lib/ModoHistoria/All_Entities.hpp"

/* N A M E S P A C E S   P R O P I O S */
namespace GenerarEntidades{

    /* Esta funcion se basa en el uso de rand() y Chapter para crear la aparicion de enemigos distintos, 
       favoreciendo asi las partidas aleatorias dentro del juego */
    Entity* GenerarCriatura(int Chapter){
        int r_Enemy = rand()%3;
        switch(Chapter){
            case 0:
                // ENEMIGOS SENCILLOS PARA PROLOGO
                switch(r_Enemy){
                case 0: return new Slime("Slime de Hielo", 10);
                case 1: return new Slime("Slime Solidario", 0);
                case 2: return new Entity("Oso de Nieve", 75, 40, 14, 1.0f, "Dormir", false, 1, 30);
                default: break;
                }
                break;
            case 1: return new Entity();
            default: break;
        }
        return new Slime("Bubble", 0);
    }

    /* Esta funcion se basa en el uso del nivel actual del jugador para hacer aparecer los jefes 
       del juego para, asi, si el jugador tiene un nivel superior a l especificado, no se pueda enfrentar
       a un jefe que no podra derrotar */
    Entity* GenerarBoss(int Chapter){
        switch(Chapter){
            case 1: return new BossIronGiant();
            default: break;
        }
        return new Entity();
    }

    /* Esta funcion se basa en el uso de punteros llamados por referencia (*&) para hacer modificacion
       de los nuevos objetos creados y asi poder eliminarlos del juego con la palabra reservada -delete-.
       Esto es equivalente al doble puntero en C (**) */
    void EliminarEntidad(Entity* &p_Entidad){
        delete p_Entidad;
        p_Entidad = nullptr;
    }
}