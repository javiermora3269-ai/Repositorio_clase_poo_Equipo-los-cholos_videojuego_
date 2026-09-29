#pragma once
#include "../Class_Criatura.hpp"

class Slime : public Criatura {
public:
    Slime(std::string c_Nombre, int c_Exp) : Criatura(c_Nombre, 50.0f, 30, 0.0f, 1.0f, "Mojar", false, 1, c_Exp){};

    void MostrarDescripcion() override;

    void AccionEspecial() override;

    float Atacar() override;
};
