#include <iostream>
#include <string>
#include <limits>
#include "../lib/Class_UserInterface.hpp"

int main(){

    /* Se crea la interfaz de usuario UI */
    std::string texto = "Bienvenido al juego.";

    /* Codigo de prueba. Los testers pueden jugar con las funciones de UI como quieran para encontrar errores */
    UI.Output(texto);
    UI.Output("Elije una opcion para continuar");
    UI.Input(1, 3, "   | 1 | 2 | 3 |");
    std::cout << UI.GetOption() << std::endl; /* Ejemplo para poner a prueba 'UI.GetOption()' */
    UI.Output("Has escogido la opcion!");
    UI.Output("Que opcion deseas escojer?");
    UI.Input(-1, 2, "   | -1 | 0 | 1 | 2 |");
    std::cout << UI.GetOption() << std::endl;

    return 0;
}
