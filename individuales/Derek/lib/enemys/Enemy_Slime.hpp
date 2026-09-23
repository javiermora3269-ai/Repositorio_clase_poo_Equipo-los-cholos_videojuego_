#pragma once
#include "../Class_Criatura.hpp"

class Slime : public Criatura {
public:
    Slime() : Criatura("Bubble", 50.0f, 30, 0.0f, 1.0f, "Mojar", false, 1, 1){};

    void MostrarDescripcion() override;

    void AccionEspecial() override;

    float Atacar() override;
};