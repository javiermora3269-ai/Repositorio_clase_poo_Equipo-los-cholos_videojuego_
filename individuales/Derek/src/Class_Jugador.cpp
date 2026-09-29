#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include "../lib/Class_UserInterface.hpp"
#include "../lib/Class_Jugador.hpp"

//CONSTRUCTORES
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

//METODOS
void Jugador::EscogerNombre(){
    bool IsCapable = true;
    std::string _Nombre = "";
    do{
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

void Jugador::MostrarAtributos(){
    //Muestra todos y cada uno de los atributos de la criatura
    std::cout << "  Nivel: <" << Nivel << ">" << std::endl;
    std::cout << "  Nombre: <" << Nombre << ">" << std::endl;
    std::cout << "  Vida: <" << VidaActual << ">" << std::endl;
    std::cout << "  Ataque: <" << Ataque << ">" << std::endl;
    std::cout << "  Defenza: <" << Defenza << ">" << std::endl;
    std::cout << "  Energia: <" << Energia << ">\n" << std::endl;
}

float Jugador::EjecutarAtaque(){
    return Ataque*BuffAtaque;
}

bool Jugador::EstaVivo(){
    if(VidaActual <= 0){
        return false;
    }
    return true;
}

void Jugador::RecibirDanio(float _Ataque){
    //El dano recibido esta calculado multiplicando el ataque del enemigo por la defenza del defensor
    DanioRecibido = _Ataque*Defenza;

    //El resultante se le resta a la vida actual
    VidaActual -= DanioRecibido;
        
    if(VidaActual < 0){
        VidaActual = 0; //La vida no puede ser menor que 0. Si es 0 o menor, murio
    }
}

void Jugador::Curar(float _VidaAumentada){
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

void Jugador::AumentarNivel(){
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

void Jugador::AumentarExperiencia(int Aumento){
    Experiencia += Aumento;
    std::cout << "\r   -> Has ganado " << Aumento << " de experiencia!" << std::endl;
    Sleep(1000);
}

void Jugador::AumentarAtributos(){
    VidaMaxima *= 2;
    AtaqueMaximo *= 2;
    EnergiaMaxima += 10;
    VidaActual = VidaMaxima;
    Ataque = AtaqueMaximo;
    Energia = EnergiaMaxima;
}

void Jugador::MostrarVida(){
    std::cout << "   >> Vida: " << GetVida() << " <<";
}

void Jugador::MostrarEnergia(){
    std::cout << "   >> Energia: " << GetEnergia() << " <<";
}