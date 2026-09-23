#pragma once
#include "../Class_Criatura.hpp"

class BossIronGiant : public Criatura{
private:

    int AtaqueRandom;
    std::string AccionExlcusivaNombre;
    std::string AccionParticularNombre;
    int AccionIntentosEspecial;
    int AccionIntentosExclusiva;

public:

    BossIronGiant();

    void MostrarDescripcion() override;

    void AccionEspecial() override;

    float Atacar() override;

    void PerdonableVidaBaja() override { return; }

    std::string ImprimirActos() const;

    const std::string GetAccionExclusivaNombre() const { return AccionExlcusivaNombre; }
    const std::string GetAccionParticularNombre() const { return AccionParticularNombre; }
    
};
