#include <iostream>
#include <string>
#include "../lib/ModoBatalla/ClaseCriatura.hpp"
#include "../lib/ModoBatalla/ModoDePVE.hpp"


void ModoDeJuegoPVE::ejecutarTurnoIA(Criatura &oponente, Criatura &jugador, int dificultad)
{
    std::cout << "\n--- TURNO DEL OPONENTE [BOT] (" << oponente.obtenerNombre() << ") ---" << std::endl;

    // 1. FACIL: Decisiones al azar
    if (dificultad == 1)
    {
        if (rand() % 2 == 0)
        {
            if (!oponente.ejecutarAtaque(rand() % 4, jugador))
                oponente.descansar();
        }
        else
        {
            if (!oponente.curar())
                oponente.descansar();
        }
        return;
    }

    // 2. MEDIO: Se cura si tiene poca vida (<30%), de lo contrario ataca al azar
    if (dificultad == 2)
    {
        if (oponente.obtenerVida() < (oponente.obtenerVidaMaxima() * 0.30))
        {
            if (oponente.curar())
                return;
        }
        if (!oponente.ejecutarAtaque(rand() % 4, jugador))
            oponente.descansar();
        return;
    }

    // 3. DIFICIL: Se cura en estado crítico o selecciona el ataque con mayor daño
    if (dificultad == 3)
    {
        if (oponente.obtenerVida() < (oponente.obtenerVidaMaxima() * 0.25))
        {
            if (oponente.curar())
                return;
        }

        int mejorAtaque = -1;
        int maxDanio = -1;

        for (int i = 0; i < 4; i++)
        {
            Ataque a = oponente.obtenerAtaque(i);
            if (oponente.obtenerEnergia() >= a.costoEnergia && a.danio > maxDanio)
            {
                maxDanio = a.danio;
                mejorAtaque = i;
            }
        }

        if (mejorAtaque != -1)
        {
            oponente.ejecutarAtaque(mejorAtaque, jugador);
        }
        else
        {
            oponente.descansar();
        }
    }
}

// LOGICA DE BATALLA PARA EL PLAYER VS ENEMY (BOT)
void ModoDeJuegoPVE::CursoDeBatallaPVE(){
    std::cout << "\n--- SELECCIONA TU CRIATURA ---" << std::endl;
    mostrarMenuCriaturas();
    GenerarOpcionJugador();
    Criatura jugador = crearCriaturaPorOpcion(GetOpcionJugador());

    opcionOponente = (rand() % 5) + 1;
    std::cout << "\nSE HA SELECCIONADO EL OPONENTE DE MANERA ALEATORIA." << std::endl;
    Criatura oponente = crearCriaturaPorOpcion(GetOpcionOponente());


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

        ejecutarTurnoIA(oponente, jugador, GetDificultad());

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
