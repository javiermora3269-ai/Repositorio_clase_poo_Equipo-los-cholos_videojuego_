#include <iostream>
#include "../lib/Class_Criatura.hpp"

//==  CONSTRUCTORES ==
Criatura::Criatura()
{
    VidaMaxima = 80;
    Energia = 100; 
    AtaqueMaximo = 15;
    Defenza = 0.9f;
    DanioRecibido = 0;
    Nombre = "Goblin";
    AccionNombre = "Dormir";
    AccionIntentos = 0;
    VidaActual = VidaMaxima;
    Ataque = AtaqueMaximo;
    EsPerdonable = false;
    FuePerdonado = false;
    EsJefe = false;
    NumeroDeActos = 1;
    Exp = 40;
}

Criatura::Criatura(std::string _Nombre, float _VidaMaxima, int _Energia, float _Ataque, 
                  float _Defenza, std::string _AccionNombre, bool _EsJefe, int _NumeroDeActos, int _Exp)
{
    Nombre = _Nombre; 
    VidaMaxima = _VidaMaxima;
    Energia = _Energia; 
    AtaqueMaximo = _Ataque;
    Defenza = _Defenza;
    AccionNombre = _AccionNombre;
    AccionIntentos = 0;
    DanioRecibido = 0;
    VidaActual = VidaMaxima;
    Ataque = AtaqueMaximo;
    EsPerdonable = false;
    FuePerdonado = false;
    EsJefe = _EsJefe;
    NumeroDeActos = _NumeroDeActos;
    Exp = _Exp;
}

//== METODOS ==
void Criatura::Descansa(const std::string& Texto){
    std::cout << Texto << "La energia aumento en 15.\n";
    Energia += 15;
}

bool Criatura::EstaViva(){
    if(VidaActual <= 0){
        return false;
    }
    return true;
}

void Criatura::RecibirDanio(float _Ataque){
    //El dano recibido esta calculado multiplicando el ataque del enemigo por la defenza del defensor
    DanioRecibido = _Ataque*Defenza;
    VidaActual -= DanioRecibido;
    
    if(VidaActual < 0){
        VidaActual = 0; //La vida no puede ser menor que 0. Si es 0 o menor, murio
    }
    PerdonableVidaBaja();
}

void Criatura::MostrarVidaRestante(){
    //Muestra la vida restante de la criatura
    std::cout << "   -> La vida restante de " << Nombre << " es de " << VidaActual << std::endl;
}

void Criatura::MostrarAtributos(){
    //Muestra todos y cada uno de los atributos de la criatura
    std::cout << "  Nombre: <" << Nombre << ">" << std::endl;
    std::cout << "  Vida: <" << VidaActual << ">" << std::endl;
    std::cout << "  Ataque: <" << Ataque << ">" << std::endl;
    std::cout << "  Defenza: <" << Defenza << ">" << std::endl;
    std::cout << "  Energia: <" << Energia << ">\n" << std::endl;
}

 void Criatura::Curar(){
    float Cantidad = 5;
    float NuevaVida = VidaActual+Cantidad; //LOCAL
    if(NuevaVida > VidaMaxima) NuevaVida = VidaMaxima;
    VidaActual = NuevaVida; //MIEMBRO
    std::cout << Nombre << " se ha curado " << Cantidad << " puntos\n" << std::endl;
 }

void Criatura::Curar(float Cantidad){
    float NuevaVida = VidaActual+Cantidad; //LOCAL
    if(NuevaVida > VidaMaxima) NuevaVida = VidaMaxima;
    VidaActual = NuevaVida; //MIEMBRO
    std::cout << Nombre << " se ha curado " << Cantidad << " puntos\n" << std::endl;
}

void Criatura::AccionEspecial(){
    /* Si la vida de la criatura esta por debajo del 20%, se podra perdonar;
       Si las condiciones del Acto cumplen los requisitos, tambien se podra perdonar */
    AccionIntentos++;
    if(AccionIntentos < 2){
        std::cout << "   -> " << GetNombre() << " se duerme junto a ti. Cada vez esta mas cansado." << std::endl;
    } else {
        std::cout << "   -> " << GetNombre() << " esta somnoliento!\n   -> Su ataque se ha reducido en 20%" << std::endl;
        SetAtaque((0.8f*AtaqueMaximo));
        SetEsPerdonable(true);
    }
}

void Criatura::MostrarDescripcion(){
    std::cout << "   >> Estas peleando contra un Goblin verde y horrendo <<\n   >> Te esta mirando furiosamente <<\n";
}

void Criatura::PerdonableVidaBaja(){
    if(VidaActual < 0.2f*VidaMaxima){
        SetEsPerdonable(true);
    }
}

float Criatura::Atacar(){
    std::cout << "   -> " << GetNombre() << " te ha atacado!\n";
    return Ataque; 
}

std::string Criatura::ImprimirActos() const {
    return "3: " + GetAccionNombre();
}
