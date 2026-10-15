#include <iostream>
#include <string>
#include <cstdlib>
#include <new>
#include <ctime>

using namespace std;

class Criatura {
private: // ==================== ENCAPSULAMIENTO ====================
    string nombre;
    int vida;
    int energia;

    // MIEMBRO DE CLASE (static): Variable compartida por todas las instancias
    static int contadorCriaturas;

public:
    // ================================================================
    // SOBRECARGA DE CONSTRUCTORES
    // ================================================================

    // 1. Constructor vacío (valores por defecto)
    Criatura() {
        this->nombre = "Criatura";
        this->vida = 100;
        this->energia = 50;
        
        // MIEMBRO DE CLASE: Incrementa el contador global al crear una instancia
        contadorCriaturas++;
    }

    // 2. Constructor con todos los datos (Sobrecarga)
    Criatura(string nombre, int vida, int energia) {
        this->nombre = nombre;
        this->vida = vida;
        this->energia = energia;
        
        // MIEMBRO DE CLASE: Incrementa el contador global al crear una instancia
        contadorCriaturas++;
    }

    // DESTRUCTOR: Mantiene actualizado el contador cuando una instancia se destruye
    ~Criatura() {
        contadorCriaturas--;
    }

    // ================================================================
    // GETTERS Y SETTERS (Encapsulamiento)
    // ================================================================
    string getNombre() const { return nombre; }
    int getVida() const { return vida; }
    int getEnergia() const { return energia; }

    // ================================================================
    // MÉTODOS ESTÁTICOS (Miembro de clase)
    // ================================================================
    // Devuelve la cantidad de criaturas vivas en memoria sin requerir un objeto específico
    static int cuantasHay() {
        return contadorCriaturas;
    }

    // ================================================================
    // SOBRECARGA DE MÉTODOS (atacar)
    // ================================================================

    // Versión 1: Ataque normal con daño aleatorio base
    void atacar(Criatura &enemigo) {
        int dano = 10 + rand() % 16;
        cout << this->nombre << " ataca a " << enemigo.nombre << endl;
        cout << "Daño realizado: " << dano << endl;
        enemigo.recibirDanio(dano);
    }

    // Versión 2: Ataque con bono extra de daño (Sobrecarga)
    void atacar(Criatura &enemigo, int extra) {
        int danoBase = 10 + rand() % 16;
        int danoTotal = danoBase + extra;
        cout << this->nombre << " realiza un ATAQUE POTENCIADO a " << enemigo.nombre << " (Extra: +" << extra << ")" << endl;
        cout << "Daño total realizado: " << danoTotal << endl;
        enemigo.recibirDanio(danoTotal);
    }

    // ================================================================
    // SOBRECARGA DE MÉTODOS (curar)
    // ================================================================

    // Versión 1: Curación fija (+10)
    void curar() {
        int vidaResultante = this->vida + 10;
        if (vidaResultante > 100) vidaResultante = 100;
        this->vida = vidaResultante;
        cout << this->nombre << " se curó 10 puntos de vida." << endl;
    }

    // Versión 2: Curación personalizada (Sobrecarga)
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
// DEFINICIÓN DEL ATRIBUTO STATIC (Fuera de la clase)
// Requisito técnico obligatorio de C++
// ================================================================
int Criatura::contadorCriaturas = 0;


// ==========================================
// MALLOC Y PLACEMENT NEW
// ==========================================
Criatura* crear_criatura(const string& nombre, int vida, int energia) {
    Criatura* c = (Criatura*) malloc(sizeof(Criatura));
    if (c == nullptr) return nullptr;

    // Placement new: llama al constructor sobre la memoria reservada
    new (c) Criatura(nombre, vida, energia);
    return c;
}

void liberar_criatura(Criatura* c) {
    if (c == nullptr) return;

    // Destructor explícito necesario por Placement New (disminuye el contador static)
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
                // Uso del método atacar() normal
                jugador.atacar(enemigo);
                if (enemigo.estaViva()) {
                    cout << "\nTurno del enemigo..." << endl;
                    enemigo.atacar(jugador);
                }
                break;

            case 2:
                // Uso de la SOBRECARGA: atacar(enemigo, extra)
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
    Criatura criatura3("Goblin", 50, 30);              // Constructor completo

    // Comprobación del contador static
    cout << "Criaturas activas después de instanciar 3: " << Criatura::cuantasHay() << endl;

    // 3. Demostración de sobredosis de ataque (Sobrecarga de métodos)
    cout << "\n--- Prueba de Sobrecarga de atacar() ---" << endl;
    criatura2.atacar(criatura3);       // versión normal
    criatura2.atacar(criatura3, 20);   // versión con extra (+20 de daño)

    // 4. Creación dinámica de objeto
    cout << "\n--- Creando criatura dinámica ---" << endl;
    Criatura* orco = crear_criatura("Orco", 100, 70);
    
    if (orco == nullptr) {
        cerr << "Error al reservar memoria." << endl;
        return 1;
    }

    cout << "Criaturas activas tras crear Orco dinámicamente: " << Criatura::cuantasHay() << endl;

    // 5. Destrucción de un objeto mediante ámbito bloque para verificar decrecimiento del contador static
    cout << "\n--- Destruyendo criatura1 (por salida de ámbito) ---" << endl;
    {
        Criatura criaturaTemporal("Temporal", 10, 10);
        cout << "  [Bloque interno] Criaturas activas con 'Temporal': " << Criatura::cuantasHay() << endl;
    } // Aquí se llama automáticamente el destructor de criaturaTemporal
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