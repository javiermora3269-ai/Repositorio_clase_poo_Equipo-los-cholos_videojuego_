#include <iostream>
#include <string>
#include <cstdlib>
#include <new>
#include <ctime>

using namespace std;

// ================================================================
// CLASE BASE: CRIATURA
// ================================================================
class Criatura {
protected: // Modificado a 'protected' para permitir acceso directo a las clases derivadas
    string nombre;
    int vida;
    int energia;

    // MIEMBRO DE CLASE (static): Variable compartida por todas las instancias y sus derivadas
    static int contadorCriaturas;

public:
    // Constructores
    Criatura() {
        this->nombre = "Criatura";
        this->vida = 100;
        this->energia = 50;
        contadorCriaturas++;
    }

    Criatura(string nombre, int vida, int energia) {
        this->nombre = nombre;
        this->vida = vida;
        this->energia = energia;
        contadorCriaturas++;
    }

    // Destructor
    ~Criatura() {
        contadorCriaturas--;
    }

    // Getters
    string getNombre() const { return nombre; }
    int getVida() const { return vida; }
    int getEnergia() const { return energia; }

    // Método estático
    static int cuantasHay() {
        return contadorCriaturas;
    }

    // Métodos de acción (HEREDABLES por Guerrero y Mago)
    void atacar(Criatura &enemigo) {
        int dano = 10 + rand() % 16;
        cout << this->nombre << " ataca a " << enemigo.nombre << endl;
        cout << "Daño realizado: " << dano << endl;
        enemigo.recibirDanio(dano);
    }

    void atacar(Criatura &enemigo, int extra) {
        int danoBase = 10 + rand() % 16;
        int danoTotal = danoBase + extra;
        cout << this->nombre << " realiza un ATAQUE POTENCIADO a " << enemigo.nombre << " (Extra: +" << extra << ")" << endl;
        cout << "Daño total realizado: " << danoTotal << endl;
        enemigo.recibirDanio(danoTotal);
    }

    void curar() {
        int vidaResultante = this->vida + 10;
        if (vidaResultante > 100) vidaResultante = 100;
        this->vida = vidaResultante;
        cout << this->nombre << " se curó 10 puntos de vida." << endl;
    }

    void curar(int cantidad) {
        int vidaResultante = this->vida + cantidad;
        if (vidaResultante > 100) vidaResultante = 100;
        this->vida = vidaResultante;
        cout << this->nombre << " se curó " << cantidad << " puntos de vida." << endl;
    }

    void recibirDanio(int dano) {
        this->vida -= dano;
        if (this->vida < 0) this->vida = 0;
    }

    void descansar() {
        this->energia += 20;
        if (this->energia > 100) this->energia = 100;
        cout << this->nombre << " descansó y recuperó energía." << endl;
    }

    void mostrar() const {
        cout << "Nombre: " << this->nombre 
             << " | Vida: " << this->vida 
             << " | Energía: " << this->energia << endl;
    }

    bool estaViva() const {
        return this->vida > 0;
    }
};

// ================================================================
// CLASE DERIVADA 1: GUERRERO (Hereda de Criatura)
// ================================================================
class Guerrero : public Criatura {
private:
    int fuerza; // ATRIBUTO PROPIO: Exclusivo de Guerrero

public:
    // Llamada al constructor de la base usando lista de inicialización
    Guerrero(string nombre, int vida, int energia, int fuerza) 
        : Criatura(nombre, vida, energia) {
        this->fuerza = fuerza;
    }

    // MÉTODOS HEREDADOS UTILIZADOS DIRECTAMENTE:
    // - mostrar(), estaViva(), recibirDanio(), curar(), etc. son de Criatura.
    // - Atributos 'nombre', 'vida' y 'energia' son HEREDADOS de Criatura.

    // MÉTODO PROPIO: Habilidad exclusiva del Guerrero
    void golpePotente(Criatura &enemigo) {
        int danoTotal = 15 + this->fuerza; // Accede a 'fuerza' (propio) y 'nombre' (heredado protected)
        cout << this->nombre << " asesta un GOLPE POTENTE a " << enemigo.getNombre() 
             << " usando su fuerza de " << this->fuerza << "!" << endl;
        cout << "Daño realizado: " << danoTotal << endl;
        enemigo.recibirDanio(danoTotal);
    }
};

// ================================================================
// CLASE DERIVADA 2: MAGO (Hereda de Criatura)
// ================================================================
class Mago : public Criatura {
private:
    int mana; // ATRIBUTO PROPIO: Exclusivo de Mago

public:
    // Llamada al constructor de la base usando lista de inicialización
    Mago(string nombre, int vida, int energia, int mana) 
        : Criatura(nombre, vida, energia) {
        this->mana = mana;
    }

    // MÉTODOS HEREDADOS UTILIZADOS DIRECTAMENTE:
    // - mostrar(), estaViva(), recibirDanio(), curar(), etc. son de Criatura.
    // - Atributos 'nombre', 'vida' y 'energia' son HEREDADOS de Criatura.

    // MÉTODO PROPIO: Habilidad exclusiva del Mago
    void hechizo(Criatura &enemigo) {
        if (this->mana >= 20) {
            this->mana -= 20; // Reduce su propio recurso de maná
            int danoMagico = 35;
            cout << this->nombre << " lanza un HECHIZO DE FUEGO a " << enemigo.getNombre() 
                 << " consumiendo 20 de maná (Maná restante: " << this->mana << ")." << endl;
            cout << "Daño mágico realizado: " << danoMagico << endl;
            enemigo.recibirDanio(danoMagico);
        } else {
            cout << this->nombre << " intentó lanzar un hechizo pero no tiene suficiente maná (" 
                 << this->mana << "/20)." << endl;
        }
    }
};

// Definición del miembro static obligatorio
int Criatura::contadorCriaturas = 0;


// ==========================================
// MALLOC Y PLACEMENT NEW
// ==========================================
Criatura* crear_criatura(const string& nombre, int vida, int energia) {
    Criatura* c = (Criatura*) malloc(sizeof(Criatura));
    if (c == nullptr) return nullptr;

    new (c) Criatura(nombre, vida, energia);
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
                cout << "Cuántos puntos quieres curar: ";
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
                cout << "\nOpción no válida." << endl;
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
    srand(time(nullptr));

    cout << "========================================" << endl;
    cout << "  PRACTICA DE SOBRECARGA Y STATIC C++   " << endl;
    cout << "========================================" << endl;

    // 1. Verificación inicial del contador static
    cout << "\nCriaturas activas al inicio: " << Criatura::cuantasHay() << endl;

    // 2. Creación con distintos constructores (Sobrecarga)
    cout << "\n--- Creando criaturas en el stack ---" << endl;
    Criatura criatura1;                                // Constructor vacío
    Criatura criatura2("Dragón", 100, 80);             // Constructor completo
    Criatura criatura3("Goblin", 100, 30);             // Constructor completo

    cout << "Criaturas activas después de instanciar 3: " << Criatura::cuantasHay() << endl;

    // 3. Demostración de sobredosis de ataque (Sobrecarga de métodos)
    cout << "\n--- Prueba de Sobrecarga de atacar() ---" << endl;
    criatura2.atacar(criatura3);       // versión normal
    criatura2.atacar(criatura3, 20);   // versión con extra (+20 de daño)

    // ================================================================
    // DEMOSTRACIÓN DE HERENCIA SIMPLE (Guerrero y Mago)
    // ================================================================
    cout << "\n--- Prueba de Herencia: Instanciando Guerrero y Mago ---" << endl;
    
    // Instanciación invocando constructores que llaman a la base
    Guerrero guerrero("Thorin", 120, 60, 25); // Atributo propio 'fuerza' = 25
    Mago mago("Gandalf", 90, 100, 50);        // Atributo propio 'mana' = 50

    cout << "\n1. Uso de método heredado (mostrar):" << endl;
    cout << "  [Guerrero] "; guerrero.mostrar(); // Método heredado de Criatura
    cout << "  [Mago]     "; mago.mostrar();     // Método heredado de Criatura

    cout << "\n2. Uso de métodos propios:" << endl;
    cout << "  -> Golpe del Guerrero:" << endl;
    guerrero.golpePotente(criatura3); // Método propio de Guerrero

    cout << "  -> Hechizo del Mago:" << endl;
    mago.hechizo(criatura3);          // Método propio de Mago

    cout << "\nCriaturas activas (incluyendo Guerrero y Mago): " << Criatura::cuantasHay() << endl;

    // 4. Creación dinámica de objeto
    cout << "\n--- Creando criatura dinámica ---" << endl;
    Criatura* orco = crear_criatura("Orco", 100, 70);
    
    if (orco == nullptr) {
        cerr << "Error al reservar memoria." << endl;
        return 1;
    }

    cout << "Criaturas activas tras crear Orco dinámicamente: " << Criatura::cuantasHay() << endl;

    // 5. Destrucción de un objeto mediante ámbito bloque para verificar decrecimiento
    cout << "\n--- Destruyendo criatura1 (por salida de ámbito) ---" << endl;
    {
        Criatura criaturaTemporal("Temporal", 10, 10);
        cout << "  [Bloque interno] Criaturas activas con 'Temporal': " << Criatura::cuantasHay() << endl;
    } 
    cout << "  [Fuera del bloque] Criaturas activas tras destruir 'Temporal': " << Criatura::cuantasHay() << endl;

    // 6. Batalla interactiva entre Dragon y Orco
    cout << "\n--- Iniciar Batalla ---" << endl;
    menuBatalla(criatura2, *orco);

    // 7. Liberación de memoria dinámica y revisión final del contador
    cout << "\n--- Liberando memoria del Orco ---" << endl;
    liberar_criatura(orco);
    cout << "Criaturas activas tras liberar al Orco: " << Criatura::cuantasHay() << endl;

    cout << "\nPrograma finalizado correctamente." << endl;
    return 0;
}