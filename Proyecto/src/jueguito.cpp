#include <iostream>
#include <string>
#include <limits>
#include "../lib/Class_UserInterface.hpp"

int main(){

    /* Se crea la interfaz de usuario UI */
    std::string texto = "Bienvenido al juego.";

    /* Codigo de prueba. Los testers pueden jugar con las funciones de UI como quieran para encontrar errores */
    UI.Output(texto);
    UI.Input(1, 3, "Elije una opcion para continuar: ");
    std::cout << UI.GetOption() << std::endl; /* Ejemplo para poner a prueba 'UI.GetOption()' */
    UI.Output("Has escogido la opcion!");
    UI.Input(-1, 2, "Que opcion deseas escojer?");

    return 0;
}
