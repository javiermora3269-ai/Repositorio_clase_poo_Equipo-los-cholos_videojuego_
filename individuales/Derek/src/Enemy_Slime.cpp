#include <iostream>
#include "../lib/enemys/Enemy_Slime.hpp"

void Slime::MostrarDescripcion() {
    std::cout << "   >> Estas frente a una bola de agua <<\n   >> No sabe que hace ahi... <<\n";
}

void Slime::AccionEspecial() {
    /* Si la vida de la criatura esta por debajo del 20%, se podra perdonar;
    Si las condiciones del Acto cumplen los requisitos, tambien se podra perdonar */
    AccionIntentos++;
    if(AccionIntentos < 2){
        std::cout << "   -> " << GetNombre() << " se inflo un poco mas." << std::endl;
    } else if(AccionIntentos < 3){
        std::cout << "   -> " << GetNombre() << " se ha inflado muchisimo!" << std::endl;
    } else {
        std::cout << "   -> " << GetNombre() << " se inflo tanto que se derritio!\n" << std::endl;
        SetEsPerdonable(true);
        SetFuePerdonado(true);
    }
}

float Slime::Atacar() {
    std::cout << "   -> El Slime no pudo alcanzarte." << std::endl;
    return Ataque;
}
