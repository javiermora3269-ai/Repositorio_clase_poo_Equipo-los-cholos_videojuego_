/* L I B R E R I A S   S T A N D A R D / E X T E R N A S */
#include <iostream>
#include <string>

/* L I B R E R I A S   P R O P I A S */
/* 
   En este apartado, iran todas las librerias que se vayan implementando conforme avance el desarrollo del juego.
   Un ejemplo de esto es la clase Class_UserInterface.hpp, que se movio a un archivo a parte para limpiar el main.
   Esto se debera hacer con cada una de las demas funciones agregadas al proyecto para mantener un orden dentro del proyecto.
   Si necesitan agregar librerias externas, agreguenlas directamente a la parte superior junto a <iostream> y las demas.
*/
#include "../lib/Class_UserInterface.hpp"

/* N A M E S P A C E S */

/* F U N C I O N E S */
void DisplayMenu(int Uno_Dos){
    if(Uno_Dos == 1) std::cout << "\n1: Modo Historia\n2: Modo Batalla\n0: Salir" << std::endl;
    if(Uno_Dos == 2) std::cout << "\n1: Modalidad PvP\n2: Modalidad PvE [BOT]\n3: Regresar" << std::endl;
}

/* M A I N   /   J U E G O   P R I N C I P A L */
int main(){

    /* Se crea la interfaz de usuario UI */
    std::string texto = "Bienvenido al juego.";
    bool Termino = false; //ESTA VARIABLE SOLO EXISTE POR AHORA PARA NO TENER UN BUCLE INFINITO INESCESARIO DENTRO DEL PROYECTO

    // AQUI ES DONDE COMIENZA EL JUEGO DE VERDAD
    do{
        UI.Output("== BIENVENIDO A JUEGUITO ==", 25, 25);
        DisplayMenu(1);
        UI.Input(0, 2, "");
        switch(UI.GetOption()){
            case 0: 
                Termino = true; 
                break;
            case 1:

                // CREAR FUNCION DONDE SE DESARROLLE LA TOTALIDAD DE LA HISTORIA
                std::cout << "Estas dentro del modo historia" << std::endl;
                Termino = true;
                break;

            case 2: 

                // CREAR FUNCIONES DONDE SE DESARROLLEN CADA UNO DE LOS MODOS DE JUEGO
                DisplayMenu(2);
                UI.Input(1, 3, "");

                // EJEMPLO DE IMPLEMENTACION DE LOS MODOS DE JUEGO 
                switch(UI.GetOption()){
                    case 1:

                        std::cout << "Estas dentro del modo PvP" << std::endl;
                        Termino = true;
                        break;

                    case 2:

                        std::cout << "Estas dentro del modo PvE" << std::endl;
                        Termino = true;
                        break;

                    default: break;
                }

                break;
            default: break;
        }
    }while(!Termino);

    return 0;
}

