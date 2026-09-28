#include <iostream>
#include <string>
#include "../lib/ModoBatalla/ClaseCriatura.hpp"
#include "../lib/ModoBatalla/ModoDePVP.hpp"

void ModoDeJuegoPVP::CursoDeCombatePVP(){
    std::cout << "\n--- PLAYER 1: SELECCIONA TU CRIATURA ---" << std::endl;
    mostrarMenuCriaturas();
    GenerarOpcionJugador();
    Criatura jugador = crearCriaturaPorOpcion(GetOpcionJugador());

    std::cout << "\n--- PLAYER 2: SELECCIONA TU CRIATURA ---" << std::endl;
    mostrarMenuCriaturas();
    GenerarOpcionOponente();
    Criatura oponente = crearCriaturaPorOpcion(GetOpcionOponente());

    std::cout << "========================================" << std::endl;
    std::cout << " EMPIEZA EL COMBATE: " << jugador.obtenerNombre()
        << " VS " << oponente.obtenerNombre() << std::endl;
    std::cout << "========================================" << std::endl;

    //TURNO DEL JUGADOR 1
    while (jugador.estaViva() && oponente.estaViva())
    {
        std::cout << "\n========================================" << std::endl;
        std::cout << "                ROUND " << ronda << std::endl;
        std::cout << "========================================" << std::endl;
        jugador.mostrar();
        oponente.mostrar();

        // -------------------------------------------------------------
        // TURNO DEL JUGADOR 1
        // -------------------------------------------------------------
        bool accionTurnoValida = false;

        // VERIFICACIÓN DE SEGURIDAD: Si está sin energía y sin usos restantes
        //Javier Mora Gutierrez
        if (jugador.estaBloqueada())
        {
            std::cout << "\n   [!] ¡Te has quedado sin energia, descansos y curaciones!" << std::endl;
            std::cout << "   [!] Pasas tu turno de emergencia y recuperas 15 pts de energia." << std::endl;
            jugador.setEnergia(jugador.obtenerEnergia() + 15);
            accionTurnoValida = true; // Activa la bandera para no entrar al menú
        }

        while (!accionTurnoValida && jugador.estaViva())
        {
            std::cout << "\nQue accion deseas realizar, " << jugador.obtenerNombre() << "?" << std::endl;
            std::cout << "1. Atacar" << std::endl;
            std::cout << "2. Descansar (Recupera energia)" << std::endl;
            std::cout << "3. Curar (Recupera vida)" << std::endl;
            std::cout << "Elige tu accion: ";

            int eleccionAccion = 0;
            std::cin >> eleccionAccion;

            if (eleccionAccion == 1)
            {
                jugador.mostrarAtaques();
                std::cout << "Elige un ataque: ";
                int numAtaque = 0;
                std::cin >> numAtaque;

                accionTurnoValida = jugador.ejecutarAtaque(numAtaque - 1, oponente);
            }
            else if (eleccionAccion == 2)
            {
                // Invocacion del metodo descansar() (Retorna false si excede limite)
                accionTurnoValida = jugador.descansar();
            }
            else if (eleccionAccion == 3)
            {
                // Invocacion del metodo curar() (Retorna false si excede limite)
                accionTurnoValida = jugador.curar();
            }
            else
            {
                std::cout << "Opcion no valida. Intenta de nuevo." << std::endl;
            }
        }

        // Verificar si el oponente murio tras el ataque del jugador 1
        if (!oponente.estaViva())
        {
            std::cout << "\n"
                << oponente.obtenerNombre() << " ha sido derrotado" << std::endl;
            break;
        }

        // TURNO MANUAL PARA PLAYER 2
        bool accionTurnoValida2 = false;

        while (!accionTurnoValida2 && oponente.estaViva())
        {
            std::cout << "\n--- TURNO DEL PLAYER 2 (" << oponente.obtenerNombre() << ") ---" << std::endl;
            std::cout << "Que accion deseas realizar, " << oponente.obtenerNombre() << "?" << std::endl;
            std::cout << "1. Atacar" << std::endl;
            std::cout << "2. Descansar (Recupera energia)" << std::endl;
            std::cout << "3. Curar (Recupera vida)" << std::endl;
            std::cout << "Elige tu accion: ";

            int eleccionAccion2 = 0;
            std::cin >> eleccionAccion2;

            if (eleccionAccion2 == 1)
            {
                oponente.mostrarAtaques();
                std::cout << "Elige un ataque: ";
                int numAtaque2 = 0;
                std::cin >> numAtaque2;

                accionTurnoValida2 = oponente.ejecutarAtaque(numAtaque2 - 1, jugador);
            }
            else if (eleccionAccion2 == 2)
            {
                accionTurnoValida2 = oponente.descansar();
            }
            else if (eleccionAccion2 == 3)
            {
                accionTurnoValida2 = oponente.curar();
            }
            else
            {
                std::cout << "Opcion no valida. Intenta de nuevo." << std::endl;
            }
        }

        if (!jugador.estaViva())
        {
            std::cout << "\n"
                << jugador.obtenerNombre() << " ha sido derrotado" << std::endl;
            break;
        }
        ronda++;
    }

    MostrarPantallaFinal(jugador, oponente);
    ronda = 0;
}
