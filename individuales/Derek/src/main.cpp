/* Librerias Internas/Externas */
#include <iostream>
#include <string>
#include <cstdlib>
#include <windows.h>
#include <limits>
#include <chrono>
#include <cmath>
#include <vector>

/* L I B R E R I A S   P R O P I A S */
/* Clases Creadas (C L A S S) */
#include "../lib/Class_Criatura.hpp"
#include "../lib/Class_UserInterface.hpp"
#include "../lib/Class_Jugador.hpp"

/* Namespaces creados (N A M E S P A C E S)*/
#include "../lib/story/Prologo.hpp"

/* Enemigos Creados (E N E M Y S) */
#include "../lib/enemys/Enemy_Slime.hpp"

/* Jefes Creados (B O S S E S) */
#include "../lib/bosses/Boss_GiganteDeHierro.hpp" 

// J U G A D O R   J U G A D O R   J U G A D O R

// E N E M I G O S   E N E M I G O S   E N E M I G O S

// S I S T E M A   D E   B A T A L L A
class Batalla { //Batalla es una clase dedicada para almacenar las funciones relacionadas a las batallas entre dos criaturas
public:

    //CursoDeBatalla() es el cerebro de todas las batallas del juego
    //Aqui es donde se desarrolla toda la logica del combate por turnos tomando las funciones ya creadas en la clase
    void CursoDeBatalla(Jugador &Uno, Criatura &Dos){
        Iniciar(Uno, Dos);
        while((Uno.EstaVivo() && Dos.EstaViva()) && !Dos.GetFuePerdonado()){
            TurnoJugador(Uno, Dos);
            if((Uno.EstaVivo() && Dos.EstaViva()) && !Dos.GetFuePerdonado()) TurnoCriatura(Dos, Uno);
        }
        if(Uno.EstaVivo() && (!Dos.EstaViva() || Dos.GetEsJefe())){ 
            Uno.AumentarExperiencia(Dos.SoltarExperiencia()); 
            Uno.AumentarNivel(); 
        }
    }

private:

    //Iniciar() es el metodo que da inicio a la batalla, mostrando los atributos y decidiendo quien comienza
    void Iniciar(Jugador &A, Criatura &B){
        if(!B.GetEsJefe()) {
            std::cout << "Has entrado en una batalla!\n";
        } else {
            system("cls");
            UI.MostrarTexto("!!!  C U I D A D O  !!!   !!!  C U I D A D O  !!!   !!!  C U I D A D O  !!!", 25, 25);
            UI.MostrarTexto("!!!      Estas frente a un enemigo mucho mas fuerte que el habitual     !!!", 20, 20);
            std::cout << std::endl;
        }
        std::cout << "=== " << A.GetNombre() << " vs. " << B.GetNombre() << " ===\n" << std::endl;
        A.MostrarAtributos(); B.MostrarAtributos();
        std::cout << "= Comienza " << A.GetNombre() << " =" << std::endl;
    }

    //Mediante esta funcion, el jugador podra realizar sus ataques, actos o acciones
    void TurnoJugador(Jugador &A, Criatura &B){

        //Se llama a los metodos necesarios para que la batalla siga
        A.MostrarVida(); A.MostrarEnergia(); 
        OpcionesDeBatalla(A, B);

        //Se comprueba si la criatura sigue viva: si si, se cambia de turno; sino, termina la batalla
        if(!B.EstaViva()) {
            std::cout << B.GetNombre() << " ha muerto! Has ganado la batalla.\n" << std::endl;
            Sleep(1000); 
            return;
        }
        if(B.GetFuePerdonado()){
            std::cout << B.GetNombre() << " fue perdonado! Has ganado la batalla.\n" << std::endl;
            Sleep(1000); 
            return;
        }
        CambioDeTurno(B, false);
    }

    //Maneja la logica del turno de la criatura
    void TurnoCriatura(Criatura &A, Jugador &B){
        //Se llama a los metodos necesarios para que la batalla siga
        B.RecibirDanio(A.Atacar());
        std::cout << "   -> Te ha quitado " << B.GetDanioRecibido() << " de vida\n"; 
        Sleep(500);
        //Se comprueba si la criatura sigue viva: si si, se cambia de turno; sino, termina la batalla
        if(!B.EstaVivo()) {
            std::cout << std::endl << "Has muerto! " << A.GetNombre() << " ha ganado la batalla.\n" << std::endl; 
            return;
        }
        CambioDeTurno(A, true);
    }

    //Si la criatura no muere, se llama a esta funcion
    void CambioDeTurno(Criatura &B, bool PlayerTurn){
        std::cout << std::endl;
        if (PlayerTurn){
            UI.MostrarTexto("= Ahora es tu turno =", 20, 20);
        }else {
            UI.MostrarTexto("= Ahora es turno de " + B.GetNombre() + " =", 20, 20);
        }
    }

    //Controla todas las opciones que puede realizar el jugador durante una batalla
    void OpcionesDeBatalla(Jugador &Player, Criatura &Enemigo){
        do{
            UI.EjecutarAccion();
            switch(UI.GetBattleOption()){
                case UI.OpcBatalla::Atacar: 
                    Enemigo.RecibirDanio(Player.EjecutarAtaque());
                    std::cout << "   -> Le has quitado " << Enemigo.GetDanioRecibido() << " de vida\n";
                    Enemigo.MostrarVidaRestante();
                    break;
                case UI.OpcBatalla::Actuar: 
                    OpcionesDeActo(Player, Enemigo);
                    break;
                case UI.OpcBatalla::Perdonar:
                    if(Enemigo.GetEsPerdonable()) {
                        Enemigo.SetFuePerdonado(true);
                    } else std::cout << "   -> No se pudo perdonar\n";
                    break;
                default: std::cout << "\n\nERROR\n\n"; break;
            }
        }while(UI.GetBattleOption() == UI.OpcActuar::Regresar);
    }

    //Controla los actos/acciones pasivas que puede realizar el jugador durante una batalla
    void OpcionesDeActo(Jugador &Player, Criatura &Enemigo){
        UI.EjecutarActo(Enemigo, Enemigo.GetNumeroActos());
        switch(UI.GetBattleOption()){
            case UI.OpcActuar::Regresar: break;
            case UI.OpcActuar::Descripcion:
                Enemigo.MostrarDescripcion();
                break;
            case UI.OpcActuar::Objeto:
                Player.Curar(20);
                break;
            default:
                Enemigo.AccionEspecial();
                break;
        }
    }
};

/* N A M E S P A C E S   P R O P I O S */
namespace GenerarEntidades{

    /* Esta funcion se basa en el uso de rand() y Chapter para crear la aparicion de enemigos distintos, 
       favoreciendo asi las partidas aleatorias dentro del juego */
    Criatura* GenerarCriatura(int Chapter){
        int r_Enemy = rand()%3;
        switch(Chapter){
            case 0:
                // ENEMIGOS SENCILLOS PARA PROLOGO
                switch(r_Enemy){
                case 0: return new Slime("Slime de Hielo", 10);
                case 1: return new Slime("Slime Solidario", 0);
                case 2: return new Criatura("Oso de Nieve", 75, 40, 14, 1.0f, "Dormir", false, 1, 30);
                default: break;
                }
                break;
            case 1: return new Criatura();
            default: break;
        }
        return new Slime("Bubble", 0);
    }

    /* Esta funcion se basa en el uso del nivel actual del jugador para hacer aparecer los jefes 
       del juego para, asi, si el jugador tiene un nivel superior a l especificado, no se pueda enfrentar
       a un jefe que no podra derrotar */
    Criatura* GenerarBoss(int Chapter){
        switch(Chapter){
            case 0: return new BossIronGiant();
            default: break;
        }
        return new Criatura();
    }

    /* Esta funcion se basa en el uso de punteros llamados por referencia (*&) para hacer modificacion
       de los nuevos objetos creados y asi poder eliminarlos del juego con la palabra reservada -delete-.
       Esto es equivalente al doble puntero en C (**) */
    void EliminarEntidad(Criatura* &p_Entidad){
        delete p_Entidad;
        p_Entidad = nullptr;
    }
}
//Para no escribir el nombre completo del Namespace, se uso la nomenclatura Gen::
namespace Gen = GenerarEntidades;

// C A P I T U L O S   C A P I T U L O S   C A P I T U L O S


// J U E G O   P R I N C I P A L   J U E G O   P R I N C I P A L
int main(){

    srand(time(NULL));

    Criatura Dragon("Dragon", 200, 50, 70, 0.6f, "Enfrentar", false, 1, 100), Goblin; 
    Batalla Battle;
    Jugador Player;
    BossIronGiant GiganteDeHierro;
    Criatura *Enemy = nullptr; //Variable creada para la Actividad 9 y 10
    Criatura *Boss = nullptr; //Variable creada para la Actividad 9 y 10
    int /*LEALTAD{0},*/ Capitulo{0};
    //bool DEBUG = false;
    

    //IGNORAR ESTE APARTADO EN CADA RESVISION. NO CUMPLE NINGUNA FUNCION ESPECIAL POR AHORA
    system("cls");
    /*if(!DEBUG){ 
    PROLOGO::Contexto(Player, LEALTAD);
    PROLOGO::Etapa_0();

    Enemy = Gen::GenerarCriatura(Capitulo); 
    Battle.CursoDeBatalla(Player, *Enemy);
    Gen::EliminarEntidad(Enemy);

    PROLOGO::Etapa_Final();

    Boss = Gen::GenerarBoss(Player);
    Battle.CursoDeBatalla(Player, *Boss);
    Gen::EliminarEntidad(Boss);
    }*/

    Enemy = Gen::GenerarCriatura(Capitulo); 
    Battle.CursoDeBatalla(Player, *Enemy);
    Gen::EliminarEntidad(Enemy);


    /* Actividades 9 y 10 aplicadas en tiempo real | Tarea Destructores y Encapsulamiento */
    for(int i=0; i < 2 && Player.EstaVivo(); i++){
        Enemy = Gen::GenerarCriatura(Capitulo);
        Battle.CursoDeBatalla(Player, *Enemy);
        Gen::EliminarEntidad(Enemy);
    }

    Boss = Gen::GenerarBoss(Capitulo);
    Battle.CursoDeBatalla(Player, *Boss);
    Gen::EliminarEntidad(Boss);

    return 0;
}
