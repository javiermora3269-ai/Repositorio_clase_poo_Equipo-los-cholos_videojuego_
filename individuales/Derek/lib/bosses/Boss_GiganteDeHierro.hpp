#pragma once
#include "../Class_Criatura.hpp"

class BossIronGiant : public Criatura{
private:

    int AtaqueRandom;
    std::string AccionExNombre[2];
    int AccionIntentosEspecial;
    int AccionIntentosExclusiva;

public:

    BossIronGiant();

    void MostrarDescripcion() override;

    void AccionEspecial() override;

    float Atacar() override;

    void PerdonableVidaBaja() override { return; }

    std::string ImprimirActos() const;

    const std::string GetAccionEx_0() const { return AccionExNombre[0]; }
    const std::string GetAccionEx_1() const { return AccionExNombre[1]; }
    
};
