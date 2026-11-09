/* L I B R E R I A S   S T A N D A R D / E X T E R N A S  */
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

/* L I B R E R I A S   P R O P I A S */
/* 
   En este apartado, iran todas las librerias que se vayan implementando conforme avance el desarrollo del juego.
   Un ejemplo de esto es la clase Class_UserInterface.hpp, que se movio a un archivo a parte para limpiar el main.
   Esto se debera hacer con cada una de las demas funciones agregadas al proyecto para mantener un orden dentro del proyecto.
   Si necesitan agregar librerias externas, agreguenlas directamente a la parte superior junto a <iostream> y las demas.
*/
#include "../lib/ModoHistoria/Class_UserInterface.hpp"
#include "../lib/ModoHistoria/All_Entities.hpp"
#include "../lib/ModoHistoria/Class_Batalla.hpp"
#include "../lib/ModoHistoria/Nmsp_GenerarEntidades.hpp"
#include "../lib/ModoHistoria/story/Prologo.hpp"

#include "../lib/ModoCombate/ClaseCombate.hpp"
#include "../lib/ModoCombate/ClaseCriatura.hpp"
#include "../lib/ModoCombate/ModoDePVE.hpp"
#include "../lib/ModoCombate/ModoDePVP.hpp"

/* N A M E S P A C E S */
namespace Gen = GenerarEntidades;

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
    ModoDeJuegoPVE PVE;
    ModoDeJuegoPVP PVP;

    // AQUI ES DONDE COMIENZA EL JUEGO DE VERDAD
    do{
        UI.MostrarTexto("== BIENVENIDO A JUEGUITO ==", 25, 25);
        DisplayMenu(1);
        UI.Input(0, 2, "");
        switch(UI.GetHistoryOption()){
            case 0: 
                Termino = true; 
                break;
            case 1: // MODO HISTORIA
            {
                srand(time(NULL));

                //Criatura Dragon("Dragon", 200, 50, 70, 0.6f, "Enfrentar", false, 1, 100); 
                Entity *Enemy = nullptr; 
                Entity *Boss = nullptr; //Variable creada para la Actividad 9 y 10
                Batalla *Battle = new Batalla();
                int LEALTAD{0}, Capitulo{0};
                Jugador Player;

                /* SAVE FILE MANAGER */
                std::string current_file{};
                {
                    std::ifstream saved_file{};

                    UI.MostrarTexto("Que partida deseas iniciar? Escribe solo el numero:\n", 20, 20);
                    UI.Input(1, 3, "   Archivo 1 | Archivo 2 | Archivo 3");
                    switch(UI.GetHistoryOption()){
                        case 1: current_file = "../saved/file1.dat"; saved_file.open("../saved/file1.dat"); break;
                        case 2: current_file = "../saved/file2.dat"; saved_file.open("../saved/file2.dat"); break;
                        case 3: current_file = "../saved/file3.dat"; saved_file.open("../saved/file3.dat"); break;
                        default: std::cout << "Could not open";
                    }

                    if(saved_file.fail()) std::cout << "Could not open";
                    else {
                        int new_experiencia{};
                        std::string new_nombre{};

                        saved_file >> new_experiencia;
                        saved_file >> new_nombre;
                        saved_file >> Capitulo;

                        if(!(new_experiencia == 0 && Capitulo == 0)){
                            Player.SetExperiencia(new_experiencia);
                            Player.SetNombre(new_nombre);
                            Player.Textless_AumentarNivel();
                        }
                    }

                    saved_file.close();
                }

                //IGNORAR ESTE APARTADO EN CADA RESVISION. NO CUMPLE NINGUNA FUNCION ESPECIAL POR AHORA
                system("cls");
                if(Capitulo == 0){
                PROLOGO::Contexto(Player, LEALTAD);
                PROLOGO::Etapa_0();
                Enemy = Gen::GenerarCriatura(Capitulo); 
                Battle->CursoDeBatalla(Player, *Enemy);
                Gen::EliminarEntidad(Enemy);

                Enemy = Gen::GenerarCriatura(Capitulo); 
                Battle->CursoDeBatalla(Player, *Enemy);
                Gen::EliminarEntidad(Enemy);
                Capitulo = 1;
                }

                if(Capitulo == 1){
                PROLOGO::Etapa_Final();

                Boss = Gen::GenerarBoss(Capitulo);
                Battle->CursoDeBatalla(Player, *Boss);
                Gen::EliminarEntidad(Boss);
                }

                delete Battle;
                break;
            }
            case 2: // MODO COMBATE

                // CREAR FUNCIONES DONDE SE DESARROLLEN CADA UNO DE LOS MODOS DE JUEGO
                DisplayMenu(2);
                UI.Input(1, 3, "");

                // EJEMPLO DE IMPLEMENTACION DE LOS MODOS DE JUEGO 
                switch(UI.GetBattleOption()){
                    case 1:

                        PVP.CursoDeCombatePVP();
                        break;

                    case 2:

                        PVE.CursoDeBatallaPVE();
                        break;

                    default: break;
                }

                break;
            default: break;
        }
    }while(!Termino);

    return 0;
}
