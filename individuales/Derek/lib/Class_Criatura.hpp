#pragma once
#include <string>

//C R I A T U R A   C R I A T U R A   C R I A T U R A
class Criatura {
private:

    float DanioRecibido; //Almacena el total del golpe recibido
    float VidaMaxima;
    float AtaqueMaximo;
    std::string Nombre;
    std::string AccionNombre;
    bool EsPerdonable;
    bool FuePerdonado;

protected:

    int Exp;
    float VidaActual;
    int Energia; 
    float Ataque;
    float Defenza; //Es un valor porcentual que multiplica al danio recibido
    int AccionIntentos;
    bool EsJefe;
    int NumeroDeActos;

public:    

    //==  CONSTRUCTORES ==
    Criatura();
    Criatura(std::string _Nombre, float _VidaMaxima, int _Energia, float _Ataque, 
            float _Defenza, std::string _AccionNombre, bool _EsJefe, int _NumeroDeActos, int _Exp);

    //== DESTRUCTORES ==
    virtual ~Criatura() = default;
     
    //== METODOS ==
    void Descansa(const std::string& Texto);

    bool EstaViva();

    void RecibirDanio(float _Ataque);

    void MostrarVidaRestante();

    void MostrarAtributos();

    void Curar();

    void Curar(float Cantidad);

    //Metodos Reescribibles
    virtual void AccionEspecial();

    virtual void MostrarDescripcion();

    virtual void PerdonableVidaBaja();

    virtual float Atacar();

    virtual std::string ImprimirActos() const;

    int SoltarExperiencia() const { return Exp; }

    //Funciones GET
    float GetVidaActual() const { return VidaActual; }

    float GetAtaqueMaximo() const { return AtaqueMaximo; }

    const std::string& GetNombre() const { return Nombre; }

    int GetEnergia() const { return Energia; }

    float GetDanioRecibido() const { return DanioRecibido; }

    bool GetEsPerdonable() const { return EsPerdonable; }

    const std::string GetAccionNombre() const { return AccionNombre; }

    bool GetFuePerdonado() const { return FuePerdonado; }

    int GetAccionIntentos() const { return AccionIntentos; }

    bool GetEsJefe() const { return EsJefe; }

    int GetNumeroActos() const { return NumeroDeActos; }

    //Funciones SET
    void SetNombre(const std::string& _Nombre) { Nombre = _Nombre; }

    void SetFuePerdonado(bool _TorF) { FuePerdonado = _TorF; }

    void SetAtaque(float _Ataque) { Ataque = _Ataque; }

    void SetAccionIntentos(int _AccionIntentos) { AccionIntentos = _AccionIntentos; }

    void SetEsPerdonable(bool _TorF) { EsPerdonable = _TorF; }

    void SetEsJefe(bool _TorF) { EsJefe = _TorF; }

    void SetEnergia(int _Suma) { Energia += _Suma; if(Energia < 0) Energia = 0; }

};
