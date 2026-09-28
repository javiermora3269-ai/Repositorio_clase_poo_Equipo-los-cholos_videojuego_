#include <iostream>
#include <string>
#include "../lib/ModoBatalla/ClaseCriatura.hpp"
#include "../lib/ModoBatalla/ClaseCombate.hpp"

//MENU PARA EL JUGADOR
void Combate::MenuDeJuego(){
    std::cout << "========================================" << std::endl;
    std::cout << "         Bienvenido al Jueguito" << std::endl;
    std::cout << "========================================" << std::endl
        << std::endl;
    std::cout << "SELECCIONA EL MODO DE JUEGO:" << std::endl;
    std::cout << "1. 1 Jugador (Player 1 vs IA)" << std::endl;
    std::cout << "2. 2 Jugadores (Player 1 vs Player 2)" << std::endl;
    std::cout << "Elige una opcion: ";
    std::cin >> modoJuego;

    //Seleccion de dificultad Javier Mora Gutierrez
    if (modoJuego == 1) {
        std::cout << "\nSELECCIONA LA DIFICULTAD DEL BOT:" << std::endl;
        std::cout << "1. Facil" << std::endl;
        std::cout << "2. Medio" << std::endl;
        std::cout << "3. Dificil" << std::endl;
        std::cout << "Elige la dificultad: ";
        std::cin >> dificultad;
        if (dificultad < 1 || dificultad > 3) dificultad = 1;
    }
}

//MUESTRA LAS OPCIONES DE CRIATURAS DISPONIBLES
void Combate::mostrarMenuCriaturas()
{
    std::cout << "1. Dragon     (Vida: 120 | Energia: 50)" << std::endl;
    std::cout << "2. Goblin     (Vida: 70  | Energia: 60)" << std::endl;
    std::cout << "3. Caballero  (Vida: 100 | Energia: 50)" << std::endl;
    std::cout << "4. Orco       (Vida: 110 | Energia: 45)" << std::endl;
    std::cout << "5. Fenix      (Vida: 95  | Energia: 65)" << std::endl;
}

//DEJAR AL JUGADOR GENERAR UNA OPCION
Criatura Combate::crearCriaturaPorOpcion(int opcion)
{
    if (opcion == 1)
    {
        Ataque atqs[4] = {
            {"Llamarada", 25, 15},
            {"Garrazada", 15, 5},
            {"Vuelo", 10, 10}, // Ataque especial que activa esquivar
            {"Coletazo", 18, 8}};
        return Criatura("Dragon", 120, 50, atqs);
    }
    else if (opcion == 2)
    {
        Ataque atqs[4] = {
            {"Navajazo", 12, 5},
            {"Lanzar piedra", 15, 8},
            {"Mordisco", 18, 10},
            {"Emboscada", 22, 15}};
        return Criatura("Goblin", 70, 60, atqs);
    }
    else if (opcion == 3)
    {
        Ataque atqs[4] = {
            {"Estocada", 16, 5},
            {"Golpe de escudo", 20, 10},
            {"Carga de lanza", 25, 15},
            {"Espadazo sagrado", 28, 20}};
        return Criatura("Caballero", 100, 50, atqs);
    }
    else if (opcion == 4)
    {
        Ataque atqs[4] = {
            {"Punetazo", 14, 5},
            {"Hachazo", 22, 12},
            {"Aplastar", 26, 16},
            {"Grito de guerra", 18, 8}};
        return Criatura("Orco", 110, 45, atqs);
    }
    else if (opcion == 5)
    {
        Ataque atqs[4] = {
            {"Picotazo", 14, 5},
            {"Pluma de Fuego", 20, 10},
            {"Rafaga Solar", 26, 16},
            {"Explosion Fenix", 32, 22}};
        return Criatura("Fenix", 95, 65, atqs);
    }
    else
    {
        std::cout << "\nOpcion no valida. Se asigna criatura por defecto.\n";
        return Criatura();
    }
}

void Combate::GenerarOpcionJugador(){
    std::cout << "Elige tu opcion: ";
    std::cin >> opcionJugador;
}

void Combate::GenerarOpcionOponente(){
    std::cout << "Elige tu opcion: ";
    std::cin >> opcionOponente;
}

void Combate::MostrarPantallaFinal(Criatura &jugador, Criatura &oponente){
    std::cout << "\n========================================" << std::endl;
    std::cout << "            FIN DEL COMBATE" << std::endl;
    std::cout << "========================================" << std::endl;

    if (jugador.estaViva() && !oponente.estaViva())
    {
        std::cout << "VICTORIA " << jugador.obtenerNombre() << " es el ganador." << std::endl;
    }
    else if (!jugador.estaViva() && oponente.estaViva())
    {
        std::cout << "DERROTA " << oponente.obtenerNombre() << " te ha vencido." << std::endl;
    }
    else
    {
        std::cout << "EMPATE. Ambas criaturas cayeron en combate." << std::endl;
    }

    std::cout << "\nEstado Final:" << std::endl;
    jugador.mostrar();
    oponente.mostrar();

    std::cout << "\nFIN DEL JUEGO" << std::endl;
}

