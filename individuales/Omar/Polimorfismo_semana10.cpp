#include <iostream>
#include <string>
#include <cstdlib>
#include <new>
#include <ctime>
#include <vector> 

using namespace std;

// ================================================================
// INTERFAZ: INTERCAMBIABLE
// ================================================================
class Intercambiable {
public:
    virtual int valorDeIntercambio() const = 0;
    virtual ~Intercambiable() {}
};

class Criatura {
protected:
    string nombre;
    int vida;
    int energia;
    int ataque;

    static int contadorCriaturas;

public:
    Criatura() : nombre("Criatura"), vida(100), energia(50), ataque(10) {
        contadorCriaturas++;
    }

    Criatura(const string& nom, int vid, int ene, int atq = 10) {
        this->nombre = nom;
        this->vida = vid;
        this->energia = ene;
        this->ataque = atq;
        contadorCriaturas++;
    }

    // Destructor virtual: Fundamental para evitar fugas de memoria y asegurar
    // que se invoque el destructor de las clases derivadas al eliminar a través 
    // de un puntero de la clase base.
    virtual ~Criatura() {
        contadorCriaturas--;
    }

    // Métodos virtuales puros (Parte del Contrato)
    virtual string tipo() const = 0;
    virtual void atacar(Criatura& enemigo) = 0;
    virtual void habilidadEspecial() const = 0;

    string getNombre() const { return nombre; }
    int getVida() const { return vida; }
    int getEnergia() const { return energia; }
    int getAtaque() const { return ataque; }

    void setNombre(const string& nom) { this->nombre = nom; }
    void setVida(int vid) { this->vida = (vid < 0) ? 0 : vid; }
    void setEnergia(int ene) { this->energia = (ene < 0) ? 0 : ene; }

    static int cuantasHay() {
        return contadorCriaturas;
    }

    void atacar() const {
        cout << nombre << " realiza una accion de ataque." << endl;
    }

    void atacar(Criatura &enemigo, int extra) {
        int danoBase = ataque + rand() % 16;
        int danoTotal = danoBase + extra;
        cout << this->nombre << " realiza un ATAQUE POTENCIADO a " << enemigo.nombre << " (Extra: +" << extra << ")" << endl;
        cout << "Danio total realizado: " << danoTotal << endl;
        enemigo.recibirDanio(danoTotal);
    }

    void curar() {
        int vidaResultante = this->vida + 10;
        if (vidaResultante > 100) vidaResultante = 100;
        this->vida = vidaResultante;
        cout << this->nombre << " se curo 10 puntos de vida." << endl;
    }

    void curar(int cantidad) {
        int vidaResultante = this->vida + cantidad;
        if (vidaResultante > 100) vidaResultante = 100;
        this->vida = vidaResultante;
        cout << this->nombre << " se curo " << cantidad << " puntos de vida." << endl;
    }

    void recibirDanio(int dano) {
        this->vida -= dano;
        if (this->vida < 0) this->vida = 0;
    }

    void descansar() {
        this->energia += 20;
        if (this->energia > 100) this->energia = 100;
        cout << this->nombre << " descanso y recupero energia." << endl;
    }

    void mostrar() const {
        cout << "[" << tipo() << "] Nombre: " << this->nombre 
             << " | Vida: " << this->vida 
             << " | Energia: " << this->energia 
             << " | Ataque Base: " << this->ataque << endl;
    }

    bool estaViva() const {
        return this->vida > 0;
    }
};

int Criatura::contadorCriaturas = 0;

// ================================================================
// CLASE CAPACIDAD: VOLADOR
// ================================================================
class Volador {
public:
    virtual ~Volador() {}
    void volar() const {
        cout << "!Despliega sus alas y emprende el vuelo surcando los cielos!" << endl;
    }
};

// ================================================================
// CLASES DERIVADAS
// ================================================================

class Dragon : public Criatura, public Volador {
public:
    using Criatura::atacar;

    Dragon(const string& nom = "Dragon Base", int vid = 100, int ene = 80, int atq = 25) 
        : Criatura(nom, vid, ene, atq) {}

    string tipo() const override {
        return "Dragon";
    }

    void atacar(Criatura& enemigo) override {
        volar();
        int dano = ataque + 15;
        cout << nombre << " desciende en picada y ataca a " << enemigo.getNombre() 
             << " infligiendo " << dano << " de danio." << endl;
        enemigo.recibirDanio(dano);
    }

    void habilidadEspecial() const override {
        cout << getNombre() << " exhala un ALIENTO DE FUEGO abrasador!" << endl;
    }
};

class Guerrero : public Criatura, public Intercambiable {
private:
    int fuerza;

public:
    using Criatura::atacar;

    Guerrero(const string& nom = "Guerrero", int vid = 100, int ene = 50, int fsz = 20) 
        : Criatura(nom, vid, ene, 15) {
        this->fuerza = fsz;
    }

    string tipo() const override {
        return "Guerrero";
    }

    void atacar(Criatura& enemigo) override {
        int dano = ataque + (fuerza / 2);
        cout << nombre << " blande su espada contra " << enemigo.getNombre() 
             << " causando " << dano << " de danio." << endl;
        enemigo.recibirDanio(dano);
    }

    void habilidadEspecial() const override {
        cout << getNombre() << " activa su MODO FURIA e incrementa su resistencia fisica." << endl;
    }

    int valorDeIntercambio() const override {
        return getVida() + getEnergia() + (fuerza * 2);
    }

    void golpePotente(Criatura &enemigo) {
        int danoTotal = 15 + this->fuerza;
        cout << getNombre() << " asesta un GOLPE POTENTE a " << enemigo.getNombre() 
             << " usando su fuerza de " << this->fuerza << "!" << endl;
        cout << "Danio realizado: " << danoTotal << endl;
        enemigo.recibirDanio(danoTotal);
    }
};

class Mago : public Criatura {
private:
    int mana;

public:
    using Criatura::atacar;

    Mago(const string& nom = "Mago", int vid = 90, int ene = 100, int mna = 50) 
        : Criatura(nom, vid, ene, 12) {
        this->mana = mna;
    }

    string tipo() const override {
        return "Mago";
    }

    void atacar(Criatura& enemigo) override {
        int dano = ataque + 8;
        cout << nombre << " lanza una descarga arcana a " << enemigo.getNombre() 
             << " causando " << dano << " de danio." << endl;
        enemigo.recibirDanio(dano);
    }

    void habilidadEspecial() const override {
        cout << getNombre() << " canaliza un ESCUDO ARCANO rodeandose de energia magica." << endl;
    }

    void hechizo(Criatura &enemigo) {
        if (this->mana >= 20) {
            this->mana -= 20;
            int danoMagico = 35;
            cout << getNombre() << " lanza un HECHIZO DE FUEGO a " << enemigo.getNombre() 
                 << " consumiendo 20 de mana (Mana restante: " << this->mana << ")." << endl;
            cout << "Danio magico realizado: " << danoMagico << endl;
            enemigo.recibirDanio(danoMagico);
        } else {
            cout << getNombre() << " intento lanzar un hechizo pero no tiene suficiente mana (" 
                 << this->mana << "/20)." << endl;
        }
    }
};

class Arquero : public Criatura {
public:
    using Criatura::atacar;

    Arquero(const string& nom = "Arquero", int vid = 95, int ene = 70) 
        : Criatura(nom, vid, ene, 18) {}

    string tipo() const override {
        return "Arquero";
    }

    void atacar(Criatura& enemigo) override {
        int dano = ataque + 5;
        cout << nombre << " dispara una flecha certera a " << enemigo.getNombre() 
             << " provocando " << dano << " de danio." << endl;
        enemigo.recibirDanio(dano);
    }

    void habilidadEspecial() const override {
        cout << getNombre() << " dispara una LLUVIA DE FLECHAS certeras." << endl;
    }
};

// ==========================================
// FUNCIONES GLOBALES
// ==========================================
void turno(const Criatura& c) {
    c.habilidadEspecial();
}

void combate(Criatura& c1, Criatura& c2) {
    cout << "\n========================================" << endl;
    cout << "    INICIO DE COMBATE POLIMORFICO" << endl;
    cout << "    " << c1.getNombre() << " VS " << c2.getNombre() << endl;
    cout << "========================================" << endl;

    int ronda = 1;
    while (c1.estaViva() && c2.estaViva() && ronda <= 3) {
        cout << "\n--- Ronda " << ronda << " ---" << endl;
        if (c1.estaViva()) c1.atacar(c2); 
        if (c2.estaViva()) c2.atacar(c1);

        c1.mostrar();
        c2.mostrar();
        ronda++;
    }
}

// ==========================================
// MEMORIA DINÁMICA
// ==========================================
Criatura* crear_criatura(const string& nom, int vid, int ene) {
    Guerrero* c = static_cast<Guerrero*>(malloc(sizeof(Guerrero)));
    if (c == nullptr) return nullptr;

    new (c) Guerrero(nom, vid, ene, 15);
    return c;
}

void liberar_criatura(Criatura* c) {
    if (c == nullptr) return;
    c->~Criatura();
    free(c);
}

void mostrarEstado(const Criatura &c1, const Criatura &c2) {
    cout << "\n================================" << endl;
    cout << "          ESTADO ACTUAL" << endl;
    cout << "================================" << endl;
    c1.mostrar();
    c2.mostrar();
    cout << "================================" << endl;
}

void menuBatalla(Criatura &jugador, Criatura &enemigo) {
    int opcion;

    while (jugador.estaViva() && enemigo.estaViva()) {
        cout << "\n================================" << endl;
        cout << "        BATALLA DE CRIATURAS" << endl;
        cout << "================================" << endl;
        cout << "1. Atacar normal" << endl;
        cout << "2. Atacar con potencia extra (+15)" << endl;
        cout << "3. Curar +10" << endl;
        cout << "4. Curar cantidad personalizada" << endl;
        cout << "5. Descansar" << endl;
        cout << "6. Ver estado" << endl;
        cout << "7. Salir" << endl;
        cout << "\nSelecciona una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                jugador.atacar(enemigo);
                if (enemigo.estaViva()) {
                    cout << "\nTurno del enemigo..." << endl;
                    enemigo.atacar(jugador);
                }
                break;

            case 2:
                jugador.atacar(enemigo, 15);
                if (enemigo.estaViva()) {
                    cout << "\nTurno del enemigo..." << endl;
                    enemigo.atacar(jugador);
                }
                break;

            case 3:
                jugador.curar();
                break;

            case 4: {
                int cantidad;
                cout << "Cuantos puntos quieres curar: ";
                cin >> cantidad;
                jugador.curar(cantidad);
                break;
            }

            case 5:
                jugador.descansar();
                break;

            case 6:
                mostrarEstado(jugador, enemigo);
                break;

            case 7:
                cout << "\nHas salido de la batalla." << endl;
                return;

            default:
                cout << "\nOpcion no valida." << endl;
        }

        if (opcion >= 1 && opcion <= 5) {
            mostrarEstado(jugador, enemigo);
        }
    }

    cout << "\n================================" << endl;
    cout << "         FIN DE BATALLA" << endl;
    cout << "================================" << endl;

    if (jugador.estaViva()) {
        cout << jugador.getNombre() << " ha ganado la batalla!" << endl;
    } else {
        cout << enemigo.getNombre() << " ha ganado la batalla!" << endl;
    }
}

// ==========================================
// MAIN
// ==========================================
int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    cout << "========================================" << endl;
    cout << "  PRACTICA UNIDAD IV: POO Y POLIMORFISMO " << endl;
    cout << "========================================" << endl;

    cout << "\n[METODO DE CLASE] Criaturas activas al inicio: " << Criatura::cuantasHay() << endl;

    cout << "\n--- Creando criaturas concretas en el stack ---" << endl;
    Guerrero criatura1("Guerrero Novato", 100, 50, 10);                                 
    Dragon criatura2("Dragon Base", 100, 80);            
    Guerrero criatura3("Goblin", 100, 30, 5);            

    cout << "[METODO DE CLASE] Criaturas activas tras instanciar 3: " << Criatura::cuantasHay() << endl;

    cout << "\n--- Prueba de Herencia Multiple (Dragon) ---" << endl;
    Dragon dragon("Smaug", 250, 120);
    cout << "1. Metodo heredado de Criatura: ";
    dragon.mostrar();
    cout << "2. Metodo heredado de Volador: ";
    dragon.volar();

    cout << "\n--- Prueba de Sobrecarga de atacar() ---" << endl;
    criatura2.atacar(criatura3);       
    criatura2.atacar(criatura3, 20);   

    cout << "\n--- Prueba de Herencia y Encapsulamiento ---" << endl;
    Guerrero guerrero("Thorin", 120, 60, 25); 
    Mago mago("Gandalf", 90, 100, 50);       

    cout << "\n1. Uso de Metodos de OBJETO Heredados (mostrar):" << endl;
    cout << "   [Guerrero] "; guerrero.mostrar(); 
    cout << "   [Mago]     "; mago.mostrar();    

    cout << "\n2. Uso de Metodos de OBJETO Propios:" << endl;
    cout << "   -> Golpe del Guerrero:" << endl;
    guerrero.golpePotente(criatura3); 

    cout << "   -> Hechizo del Mago:" << endl;
    mago.hechizo(criatura3);          

    cout << "\n--- Llamadas al metodo habilidadEspecial() ---" << endl;
    cout << "   -> Guerrero: "; guerrero.habilidadEspecial();
    cout << "   -> Mago:     "; mago.Mago::habilidadEspecial();
    cout << "   -> Dragon:   "; dragon.habilidadEspecial();

    cout << "\n[METODO DE CLASE] Criaturas activas: " << Criatura::cuantasHay() << endl;

    cout << "\n--- Creando criatura dinamica ---" << endl;
    Criatura* orco = crear_criatura("Orco", 100, 70);
    
    if (orco == nullptr) {
        cerr << "Error al reservar memoria." << endl;
        return 1;
    }

    cout << "[METODO DE CLASE] Criaturas activas tras crear Orco dinamicamente: " << Criatura::cuantasHay() << endl;

    cout << "\n--- Destruyendo criatura temporal (por salida de ambito) ---" << endl;
    {
        Guerrero criaturaTemporal("Temporal", 10, 10, 5);
        cout << "   [Bloque interno] Criaturas activas con 'Temporal': " << Criatura::cuantasHay() << endl;
    } 
    cout << "   [Fuera del bloque] Criaturas activas tras destruir 'Temporal': " << Criatura::cuantasHay() << endl;

    cout << "\n--- Prueba de Funcion Global de Combate Polimorfico ---" << endl;
    combate(dragon, guerrero);

    cout << "\n--- Iniciar Batalla Interactiva ---" << endl;
    menuBatalla(criatura2, *orco);

    cout << "\n--- Liberando memoria del Orco ---" << endl;
    liberar_criatura(orco);
    cout << "[METODO DE CLASE] Criaturas activas tras liberar al Orco: " << Criatura::cuantasHay() << endl;

    // ================================================================
    // POLIMORFISMO
    // ================================================================
    cout << "\n--- Demostracion de Polimorfismo con vector<Criatura*> ---" << endl;

    // POLIMORFISMO EN VECTOR: Almacenamos punteros a la clase base (Criatura*),
    // permitiendo agrupar objetos de clases derivadas distintas (Guerrero, Mago, etc.)
    vector<Criatura*> equipo = { 
        new Guerrero("Conan"), 
        new Mago("Merlin"), 
        new Arquero("Legolas"),
        new Dragon("Vhagar")
    };

    cout << "\n1. Recorrido del equipo (Polimorfismo con vector):" << endl;
    for (Criatura* c : equipo) {
        cout << "Tipo: " << c->tipo() << " -> ";
        // POLIMORFISMO EN TIEMPO DE EJECUCIÓN: Se invoca la versión de 
        // habilidadEspecial() correspondiente a la clase derivada real apuntada por 'c'.
        c->habilidadEspecial(); 
    }

    cout << "\n2. Uso de la funcion turno(const Criatura&):" << endl;
    for (Criatura* c : equipo) {
        turno(*c); // POLIMORFISMO POR REFERENCIA
    }

    cout << "\n3. Demostracion de Interfaz (Intercambiable):" << endl;
    Guerrero* hercules = new Guerrero("Hercules", 150, 80, 30);
  
    Criatura* ptrCriatura = hercules;
    ptrCriatura->mostrar();
    ptrCriatura->atacar();  

    Intercambiable* ptrIntercambiable = hercules;
    cout << "Valor de intercambio: " << ptrIntercambiable->valorDeIntercambio() << endl;

    delete hercules;

    cout << "\n--- Liberando memoria del vector polimorfico ---" << endl;
    for (Criatura* c : equipo) {
        delete c; 
    }
    equipo.clear();

    cout << "\n[METODO DE CLASE] Criaturas activas al final: " << Criatura::cuantasHay() << endl;
    cout << "Programa finalizado correctamente." << endl;

    return 0;
}