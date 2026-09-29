#pragma once
#include <string>

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
    void EscogerNombre();

    void MostrarAtributos();

    float EjecutarAtaque();

    bool EstaVivo();

    void RecibirDanio(float _Ataque);

    void Curar(float _VidaAumentada);

    void AumentarNivel();

    void AumentarExperiencia(int Aumento);

    void AumentarAtributos();

    void MostrarVida();

    void MostrarEnergia();

    //Funciones GET

    const std::string& GetNombre() const { return Nombre; }

    float GetDanioRecibido() const { return DanioRecibido; }

    float GetVida() const { return VidaActual; }

    int GetEnergia() const { return Energia; }

    unsigned int GetNivel() const { return Nivel; }

    //Funciones SET
    void SetEnergia(int _CambioEnergia) { Energia += _CambioEnergia; }
};