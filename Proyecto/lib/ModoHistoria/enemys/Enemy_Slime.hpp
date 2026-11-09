#pragma once
#include "../Class_Entity.hpp"

constexpr bool ES_JEFE = false;

class Slime : public Entity {
public:
    Slime(std::string c_Nombre, int c_Exp) : Entity(c_Nombre, 50.0f, 30, 0.0f, 1.0f, "Mojar", ES_JEFE, 1, c_Exp){};

    void MostrarDescripcion() override;

    void AccionEspecial() override;

    float Atacar() override;
};