#include <iostream>
#include <windows.h>
#include "../lib/ModoHistoria/Class_Batalla.hpp"
#include "../lib/ModoHistoria/Class_UserInterface.hpp"


//CursoDeBatalla() es el cerebro de todas las batallas del juego
//Aqui es donde se desarrolla toda la logica del combate por turnos tomando las funciones ya creadas en la clase
void Batalla::CursoDeBatalla(Jugador &Uno, Entity &Dos){
    Iniciar(Uno, Dos);
    while((Uno.EstaVivo() && Dos.EstaViva()) && !Dos.GetFuePerdonado()){
        TurnoJugador(Uno, Dos);
        if((Uno.EstaVivo() && Dos.EstaViva()) && !Dos.GetFuePerdonado()) TurnoEntity(Dos, Uno);
    }
    if(Uno.EstaVivo() && (!Dos.EstaViva() || Dos.GetEsJefe())){ 
        Uno.AumentarExperiencia(Dos.SoltarExperiencia()); 
        Uno.AumentarNivel(); 
    }
}



//Iniciar() es el metodo que da inicio a la batalla, mostrando los atributos y decidiendo quien comienza
void Batalla::Iniciar(Jugador &A, Entity &B){
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
void Batalla::TurnoJugador(Jugador &A, Entity &B){

    //Se llama a los metodos necesarios para que la batalla siga
    A.MostrarVida(); A.MostrarEnergia(); 
    OpcionesDeBatalla(A, B);

    //Se comprueba si la Entity sigue viva: si si, se cambia de turno; sino, termina la batalla
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

//Maneja la logica del turno de la Entity
void Batalla::TurnoEntity(Entity &A, Jugador &B){
    //Se llama a los metodos necesarios para que la batalla siga
    B.RecibirDanio(A.Atacar());
    std::cout << "   -> Te ha quitado " << B.GetDanioRecibido() << " de vida\n"; 
    Sleep(500);
    //Se comprueba si la Entity sigue viva: si si, se cambia de turno; sino, termina la batalla
    if(!B.EstaVivo()) {
        std::cout << std::endl << "Has muerto! " << A.GetNombre() << " ha ganado la batalla.\n" << std::endl; 
        return;
    }
    CambioDeTurno(A, true);
}

//Si la Entity no muere, se llama a esta funcion
void Batalla::CambioDeTurno(Entity &B, bool PlayerTurn){
    std::cout << std::endl;
    if (PlayerTurn){
        UI.MostrarTexto("= Ahora es tu turno =", 20, 20);
    }else {
        UI.MostrarTexto("= Ahora es turno de " + B.GetNombre() + " =", 20, 20);
    }
}

//Controla todas las opciones que puede realizar el jugador durante una batalla
void Batalla::OpcionesDeBatalla(Jugador &Player, Entity &Enemigo){
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
void Batalla::OpcionesDeActo(Jugador &Player, Entity &Enemigo){
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

