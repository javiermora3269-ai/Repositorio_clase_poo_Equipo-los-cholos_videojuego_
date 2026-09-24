/* Librerias Internas/Externas */
#include <iostream>
#include <string>
#include <cstdlib>
#include <windows.h>
#include <limits>
#include <chrono>
#include <memory>
#include <cmath>
#include <vector>

/* L I B R E R I A S   P R O P I A S */
/* Clases Creadas (C L A S S) */
#include "../lib/Class_Criatura.hpp"
#include "../lib/Class_UserInterface.hpp"

/* Enemigos Creados (E N E M Y S) */
#include "../lib/enemys/Enemy_Slime.hpp"

/* Jefes Creados (B O S S E S) */
#include "../lib/bosses/Boss_GiganteDeHierro.hpp" 

// J U G A D O R   J U G A D O R   J U G A D O R
class Jugador{
private:
    float DanioRecibido; //Almacena el total del golpe recibido
    float VidaMaxima;
    float VidaActual;
    int EnergiaMaxima;
    int Energia; 
    float AtaqueMaximo;
    float Ataque;
    float Defenza; //Es un valor porcentual que multiplica al danio recibido
    std::string Nombre;
    float BuffAtaque; //Es un valor porcentual que multiplica al ataque provocado
    int Experiencia;
    unsigned int Nivel;

public:

    //CONSTRUCTORES
    Jugador();
    Jugador(float _VidaMaxima, int _Energia, float _Ataque, float _Defenza);

    //METODOS
    void EscogerNombre(){
        bool IsCapable = true;
        std::string _Nombre = "";
        do{
            UI.MostrarTexto("Escoje tu nombre ", 80, 480);
            std::cout << "   -> ";
            std::cin >> _Nombre;

            if(std::cin.fail()){
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                IsCapable = false;
                std::cout << "Este nombre no es valido.\n";

            } else IsCapable = true;
            std::cout << std::endl;
        Nombre = _Nombre;
        }while(!IsCapable);
    }

    void MostrarAtributos(){
        //Muestra todos y cada uno de los atributos de la criatura
        std::cout << "  Nivel: <" << Nivel << ">" << std::endl;
        std::cout << "  Nombre: <" << Nombre << ">" << std::endl;
        std::cout << "  Vida: <" << VidaActual << ">" << std::endl;
        std::cout << "  Ataque: <" << Ataque << ">" << std::endl;
        std::cout << "  Defenza: <" << Defenza << ">" << std::endl;
        std::cout << "  Energia: <" << Energia << ">\n" << std::endl;
    }

    float EjecutarAtaque(){
        return Ataque*BuffAtaque;
    }

    bool EstaVivo(){
        if(VidaActual <= 0){
            return false;
        }
        return true;
    }

    void RecibirDanio(float _Ataque){
        //El dano recibido esta calculado multiplicando el ataque del enemigo por la defenza del defensor
        DanioRecibido = _Ataque*Defenza;

        //El resultante se le resta a la vida actual
        VidaActual -= DanioRecibido;
        
        if(VidaActual < 0){
            VidaActual = 0; //La vida no puede ser menor que 0. Si es 0 o menor, murio
        }
    }

    void Curar(float _VidaAumentada){
        if (GetEnergia() >= 15){
            float NewVida = VidaActual;
            NewVida += _VidaAumentada;
            if(NewVida > VidaMaxima) NewVida = VidaMaxima;
            VidaActual = NewVida;
            std::cout << "   -> Se curo un total de " << _VidaAumentada << "." << std::endl;
            std::cout << "   -> La -Energia- disminuyo en 15 puntos." << std::endl;
            SetEnergia(-15);
        } else std::cout << "   -> La cura no pudo efectuarse\n";
    }

    void AumentarNivel(){
        std::vector<int> ExpNecesaria = {0, 100, 300, 900, 1800, 3600, 7200, 14400, 28800};
        unsigned int NivelAnterior = Nivel;
        while(Nivel < ExpNecesaria.size() && Experiencia >= ExpNecesaria[Nivel]){
            Nivel++;
            AumentarAtributos();
        }
        if (NivelAnterior != Nivel) { 
            std::cout << std::endl;
            UI.MostrarTexto("!!!   H A S   S U B I D O   D E   N I V E L   !!!", 30, 30);
            std::cout << std::endl;
            Sleep(1000);
        } 
    }

    void AumentarExperiencia(int Aumento){
        Experiencia += Aumento;
        std::cout << "\r   -> Has ganado " << Aumento << " de experiencia!" << std::endl;
        Sleep(1000);
    }

    void AumentarAtributos(){
        VidaMaxima *= 2;
        AtaqueMaximo *= 2;
        EnergiaMaxima += 10;
        VidaActual = VidaMaxima;
        Ataque = AtaqueMaximo;
        Energia = EnergiaMaxima;
    }

    void MostrarVida(){
        std::cout << "   >> Vida: " << GetVida() << " <<";
    }

    void MostrarEnergia(){
        std::cout << "   >> Energia: " << GetEnergia() << " <<";
    }

    //Funciones GET

    const std::string& GetNombre() const { return Nombre; }

    float GetDanioRecibido() const { return DanioRecibido; }

    float GetVida() const { return VidaActual; }

    int GetEnergia() const { return Energia; }

    unsigned int GetNivel() const { return Nivel; }

    //Funciones SET
    void SetEnergia(int _CambioEnergia) { Energia += _CambioEnergia; }
};

Jugador::Jugador(){
    VidaMaxima = 175;
    EnergiaMaxima = 50;
    AtaqueMaximo = 13;
    Defenza = 0.9f;
    BuffAtaque = 1.0f;
    VidaActual = VidaMaxima;
    Energia = EnergiaMaxima;
    Ataque = AtaqueMaximo;
    Nivel = 1;
    Experiencia = 0;
}

Jugador::Jugador(float _VidaMaxima, int _Energia, float _Ataque, float _Defenza){
    VidaMaxima = _VidaMaxima;
    EnergiaMaxima = _Energia;
    AtaqueMaximo = _Ataque;
    Defenza = _Defenza;
    BuffAtaque = 1.0f;
    VidaActual = VidaMaxima;
    Ataque = AtaqueMaximo;
    Energia = EnergiaMaxima;
    Nivel = 1;
    Experiencia = 0;
}

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
            switch(UI.GetOpcion()){
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
        }while(UI.GetOpcion() == UI.OpcActuar::Regresar);
    }

    //Controla los actos/acciones pasivas que puede realizar el jugador durante una batalla
    void OpcionesDeActo(Jugador &Player, Criatura &Enemigo){
        UI.EjecutarActo(Enemigo, Enemigo.GetNumeroActos());
        switch(UI.GetOpcion()){
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

    /* Esta funcion se basa en el uso de rand() para crear la aparicion de enemigos distintos, 
       favoreciendo asi las partidas aleatorias dentro del juego */
    Criatura* GenerarCriatura(){
        int Randomizer = rand()%3;
        switch(Randomizer){
            case 0: return new Slime();
            case 1: return new Criatura();
            default: break;
        }
        return new Slime();
    }

    /* Esta funcion se basa en el uso del nivel actual del jugador para hacer aparecer los jefes 
       del juego para, asi, si el jugador tiene un nivel superior a l especificado, no se pueda enfrentar
       a un jefe que no podra derrotar */
    Criatura* GenerarBoss(Jugador &Player){
        if(Player.GetNivel() < 2){
            return new BossIronGiant();
        }
        return new Criatura();
    }

    /* Esta funcion se basa en el uso de punteros llamados por referencia (*&) para hacer modificacion
       de los nuevos objetos creados y asi poder eliminarlos del juego con la palabra reservada -delete-.
       Esto es equivalente al doble puntero en C (**) */
    void EliminarEntidad(Criatura*& pEntidad){
        delete pEntidad;
        pEntidad = nullptr;
    }
}
//Para no escribir el nombre completo del Namespace, se uso la nomenclatura Gen::
namespace Gen = GenerarEntidades;

int main(){

    Criatura Dragon("Dragon", 200, 50, 70, 0.6f, "Enfrentar", false, 1, 100), Goblin; 
    Batalla Battle;
    Jugador Player;
    BossIronGiant GiganteDeHierro;
    Criatura *Enemy = nullptr; //Variable creada para la Actividad 9 y 10
    Criatura *Boss = nullptr; //Variable creada para la Actividad 9 y 10
    srand(time(NULL));

    //Definiendo los atributos de cada Objeto
    Player.EscogerNombre();

    /* Actividades 9 y 10 aplicadas en tiempo real | Tarea Destructores y Encapsulamiento */
    while(Player.EstaVivo()){
        for(int i=0; i < 2 && Player.EstaVivo(); i++){
            Enemy = Gen::GenerarCriatura();
            Battle.CursoDeBatalla(Player, *Enemy);
            Gen::EliminarEntidad(Enemy);
            
        }

        if(!Player.EstaVivo()) break;
        Boss = Gen::GenerarBoss(Player);
        Battle.CursoDeBatalla(Player, *Boss);
        Gen::EliminarEntidad(Boss);
    }

    return 0;
}
