#include <iostream>
#include <string>
#include "../lib/ModoBatalla/ClaseCriatura.hpp"

    // -----------------------------------------------------------------
    // ENCAPSULAMIENTO: Setters con validación de límites (0 a Máximo)
    // -----------------------------------------------------------------
void Criatura::setVida(int v)
{
    if (v < 0)
    {
        this->vida = 0;
    }
    else if (v > this->vidaMaxima)
    {
        this->vida = this->vidaMaxima;
    }
    else
    {
        this->vida = v;
    }
}

void Criatura::setEnergia(int e)
{
    if (e < 0)
    {
        this->energia = 0;
    }
    else if (e > this->energiaMaxima)
    {
        this->energia = this->energiaMaxima;
    }
    else
    {
        this->energia = e;
    }
}

// -----------------------------------------------------------------
// 1. CONSTRUCTOR POR DEFECTO
// -----------------------------------------------------------------
Criatura::Criatura()
{
    this->nombre = "Criatura Misteriosa";
    this->vidaMaxima = 50;
    this->energiaMaxima = 30;
    this->volando = false;
    this->usosCurar = 0;
    this->usosDescansar = 0;

    setVida(50);
    setEnergia(30);

    // Ataques por defecto
    this->ataques[0] = {"Golpe Basico", 10, 5};
    this->ataques[1] = {"Ataque Fuerte", 15, 10};
    this->ataques[2] = {"Ataque Rapido", 8, 3};
    this->ataques[3] = {"Golpe Cargado", 20, 15};
}

// -----------------------------------------------------------------
// 2. CONSTRUCTOR CON PARAMETROS
// -----------------------------------------------------------------
Criatura::Criatura(std::string nombre, int vida, int energia, Ataque listaAtaques[4])
{
    this->nombre = nombre;
    this->vidaMaxima = vida;
    this->energiaMaxima = energia;
    this->volando = false;
    this->usosCurar = 0;
    this->usosDescansar = 0;

    setVida(vida);
    setEnergia(energia);

    for (int i = 0; i < 4; i++)
    {
        this->ataques[i] = listaAtaques[i];
    }
}

// -----------------------------------------------------------------
// DESTRUCTOR
// -----------------------------------------------------------------

// -----------------------------------------------------------------
// METODOS DE CONSULTA (Getters)
// -----------------------------------------------------------------

// -----------------------------------------------------------------
// METODO REQUERIDO: estaViva
// -----------------------------------------------------------------
bool Criatura::estaViva() const
{
    return this->vida > 0;
}

// METODO: estaBloqueada (Verifica si se quedó sin ninguna opción)
//Javier Mora Gutierrez
bool Criatura::estaBloqueada() const
{
    // El ataque más barato cuesta 3 o 5 de energía
    bool sinEnergia = (this->energia < 3);
    bool sinDescansos = (this->usosDescansar >= 3);
    bool sinCuraciones = (this->usosCurar >= 2);

    // Retorna true solo si NO puede atacar, NI descansar, NI curarse
    return (sinEnergia && sinDescansos && sinCuraciones);
}
// -----------------------------------------------------------------
// METODO REQUERIDO: descansar
// -----------------------------------------------------------------
bool Criatura::descansar()
{
    if (this->usosDescansar >= 3)
    {
        std::cout << "   [x] Limite de descansos excedido, intente con otra opcion" << std::endl;
        return false; // No se pudo realizar la acción
    }

    int energiaRecuperada = 20;

    setEnergia(this->energia + energiaRecuperada);
    this->usosDescansar++;

    std::cout << "   [+] " << this->nombre << " descansa y recupera "
            << energiaRecuperada << " pts de energia. (Energia: "
            << this->energia << "/" << this->energiaMaxima << ")" << std::endl;
    return true; // Acción realizada con éxito
}

// -----------------------------------------------------------------
// METODO REQUERIDO: curar
// -----------------------------------------------------------------
bool Criatura::curar()
{
    if (this->usosCurar >= 2)
    {
        std::cout << "   [x] Limite de curaciones excedido, intente con otra opcion" << std::endl;
        return false; // No se pudo realizar la acción
    }

    int vidaRecuperada = 20;

    setVida(this->vida + vidaRecuperada);
    this->usosCurar++;

    std::cout << "   [+] " << this->nombre << " se cura y recupera "
            << vidaRecuperada << " pts de vida. (Vida: "
            << this->vida << "/" << this->vidaMaxima << ")" << std::endl;
    return true; // Acción realizada con éxito
}

// -----------------------------------------------------------------
// METODO: recibirDanio
// -----------------------------------------------------------------
void Criatura::recibirDanio(int danioRecibido, std::string tipoAtacante)
{
    // Regla especial del VUELO
    if (this->volando)
    {
        if (tipoAtacante != "Dragon")
        {
            std::cout << "   [!]" << this->nombre << " esta en VUELO y esquivo por completo el ataque" << std::endl;
            this->volando = false; // El vuelo se consume al esquivar
            return;
        }
        else
        {
            std::cout << "   [!] El atacante tambien es un Dragon. El vuelo fue inutil para esquivar." << std::endl;
        }
    }

    this->volando = false; // Se reinicia el estado de vuelo si recibe el impacto

    int danioAplicado = danioRecibido;
    setVida(this->vida - danioAplicado);

    std::cout << "   [-] " << this->nombre << " recibe " << danioAplicado
            << " pts de danio. (Vida: " << this->vida << "/" << this->vidaMaxima << ")" << std::endl;
}

// -----------------------------------------------------------------
// METODOS DE ATAQUE
// -----------------------------------------------------------------
void Criatura::mostrarAtaques() const
{
    std::cout << "\n--- ATAQUES DISPONIBLES DE " << nombre << " ---" << std::endl;
    for (int i = 0; i < 4; i++)
    {
        std::cout << i + 1 << ". " << ataques[i].nombre
                << " (Danio: " << ataques[i].danio
                << " | Costo Energia: " << ataques[i].costoEnergia << ")" << std::endl;
    }
}

Ataque Criatura::obtenerAtaque(int indice) const
{
    if (indice >= 0 && indice < 4)
        return ataques[indice];
    return ataques[0];
}

// Intenta ejecutar el ataque seleccionado. Devuelve true si pudo atacar.
bool Criatura::ejecutarAtaque(int indiceAtaque, Criatura &objetivo)
{
    if (indiceAtaque < 0 || indiceAtaque >= 4)
        return false;

    Ataque atq = ataques[indiceAtaque];

    // Verificar si cuenta con la energia requerida
    if (this->energia < atq.costoEnergia)
    {
        std::cout << "   [x] " << this->nombre << " no tiene suficiente energia para usar "
                << atq.nombre << " (Requiere: " << atq.costoEnergia
                << " | Tienes: " << this->energia << ")" << std::endl;
        return false;
    }

    // Restar costo de energia
    setEnergia(this->energia - atq.costoEnergia);
    std::cout << "\n   [>] " << this->nombre << " usa " << atq.nombre << std::endl;

    // Efecto especial: Vuelo del Dragon
    if (this->nombre == "Dragon" && atq.nombre == "Vuelo")
    {
        this->volando = true;
        std::cout << "   [!] El Dragon emprende el vuelo." << std::endl;
    }

    // Aplicar daño a la criatura objetivo
    objetivo.recibirDanio(atq.danio, this->nombre);
    return true;
}

// -----------------------------------------------------------------
// METODO: mostrar
// -----------------------------------------------------------------
void Criatura::mostrar() const
{
    std::cout << "    -> " << nombre << " | Vida: " << vida << "/" << vidaMaxima
            << " | Energia: " << energia << "/" << energiaMaxima
            << " | Estado: " << (estaViva() ? "VIVA" : "DERROTADA");
    if (volando)
        std::cout << " [EN VUELO]";
    std::cout << std::endl;
}
