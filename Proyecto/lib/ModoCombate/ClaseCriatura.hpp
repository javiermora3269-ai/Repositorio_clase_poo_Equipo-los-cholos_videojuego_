#pragma once
#include <string>

struct Ataque
{
    std::string nombre;
    int danio;
    int costoEnergia;
};

// =====================================================================
// DEFINICION DE LA CLASE: Criatura
// =====================================================================
class Criatura
{
private:
    // -----------------------------------------------------------------
    // ENCAPSULAMIENTO: Atributos privados
    // -----------------------------------------------------------------
    std::string nombre;
    int vida;
    int vidaMaxima;
    int energia;
    int energiaMaxima;
    Ataque ataques[4]; // Arreglo miembro con los 4 ataques de la criatura
    bool volando;      // Estado especial para la habilidad de Vuelo del Dragon

    // Contadores para controlar los límites de uso
    int usosCurar;
    int usosDescansar;

public:
    // -----------------------------------------------------------------
    // ENCAPSULAMIENTO: Setters con validación de límites (0 a Máximo)
    // -----------------------------------------------------------------
    void setVida(int v);

    void setEnergia(int e);

    // -----------------------------------------------------------------
    // 1. CONSTRUCTOR POR DEFECTO
    // -----------------------------------------------------------------
    Criatura();

    // -----------------------------------------------------------------
    // 2. CONSTRUCTOR CON PARAMETROS
    // -----------------------------------------------------------------
    Criatura(std::string nombre, int vida, int energia, Ataque listaAtaques[4]);

    // -----------------------------------------------------------------
    // DESTRUCTOR
    // -----------------------------------------------------------------
    ~Criatura()
    {
        // Libera los recursos/estado de la instancia
    }

    // -----------------------------------------------------------------
    // METODOS DE CONSULTA (Getters)
    // -----------------------------------------------------------------
    std::string obtenerNombre() const { return nombre; }
    int obtenerVida() const { return vida; }
    int obtenerVidaMaxima() const { return vidaMaxima; }
    int obtenerEnergia() const { return energia; }
    int obtenerEnergiaMaxima() const { return energiaMaxima; }
    bool estaVolando() const { return volando; }

    // -----------------------------------------------------------------
    // METODO REQUERIDO: estaViva
    // -----------------------------------------------------------------
    bool estaViva() const;

    // METODO: estaBloqueada (Verifica si se quedó sin ninguna opción)
   //Javier Mora Gutierrez
    bool estaBloqueada() const;
    // -----------------------------------------------------------------
    // METODO REQUERIDO: descansar
    // -----------------------------------------------------------------
    bool descansar();

    // -----------------------------------------------------------------
    // METODO REQUERIDO: curar
    // -----------------------------------------------------------------
    bool curar();

    // -----------------------------------------------------------------
    // METODO: recibirDanio
    // -----------------------------------------------------------------
    void recibirDanio(int danioRecibido, std::string tipoAtacante);

    // -----------------------------------------------------------------
    // METODOS DE ATAQUE
    // -----------------------------------------------------------------
    void mostrarAtaques() const;

    Ataque obtenerAtaque(int indice) const;

    // Intenta ejecutar el ataque seleccionado. Devuelve true si pudo atacar.
    bool ejecutarAtaque(int indiceAtaque, Criatura &objetivo);

    // -----------------------------------------------------------------
    // METODO: mostrar
    // -----------------------------------------------------------------
    void mostrar() const;
};