

// =====================================================================
// Version del Jueguito Actualizada
// =====================================================================

#include <iostream>
#include <string>
#include <cstdlib> // Para rand()
#include <ctime>   // Para time()

using namespace std;

// ---------------------------------------------------------------------
// Estructura auxiliar para definir los ataques de cada criatura
// ---------------------------------------------------------------------
struct Ataque
{
    string nombre;
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
    string nombre;
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
    void setVida(int v)
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

    void setEnergia(int e)
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
    Criatura()
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
    Criatura(string nombre, int vida, int energia, Ataque listaAtaques[4])
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
    ~Criatura()
    {
        // Libera los recursos/estado de la instancia
    }

    // -----------------------------------------------------------------
    // METODOS DE CONSULTA (Getters)
    // -----------------------------------------------------------------
    string obtenerNombre() const { return nombre; }
    int obtenerVida() const { return vida; }
    int obtenerVidaMaxima() const { return vidaMaxima; }
    int obtenerEnergia() const { return energia; }
    int obtenerEnergiaMaxima() const { return energiaMaxima; }
    bool estaVolando() const { return volando; }

    // -----------------------------------------------------------------
    // METODO REQUERIDO: estaViva
    // -----------------------------------------------------------------
    bool estaViva() const
    {
        return this->vida > 0;
    }

    // METODO: estaBloqueada (Verifica si se quedó sin ninguna opción)
   //Javier Mora Gutierrez
    bool estaBloqueada() const
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
    bool descansar()
    {
        if (this->usosDescansar >= 3)
        {
            cout << "   [x] Limite de descansos excedido, intente con otra opcion" << endl;
            return false; // No se pudo realizar la acción
        }

        int energiaRecuperada = 20;

        setEnergia(this->energia + energiaRecuperada);
        this->usosDescansar++;

        cout << "   [+] " << this->nombre << " descansa y recupera "
             << energiaRecuperada << " pts de energia. (Energia: "
             << this->energia << "/" << this->energiaMaxima << ")" << endl;
        return true; // Acción realizada con éxito
    }

    // -----------------------------------------------------------------
    // METODO REQUERIDO: curar
    // -----------------------------------------------------------------
    bool curar()
    {
        if (this->usosCurar >= 2)
        {
            cout << "   [x] Limite de curaciones excedido, intente con otra opcion" << endl;
            return false; // No se pudo realizar la acción
        }

        int vidaRecuperada = 20;

        setVida(this->vida + vidaRecuperada);
        this->usosCurar++;

        cout << "   [+] " << this->nombre << " se cura y recupera "
             << vidaRecuperada << " pts de vida. (Vida: "
             << this->vida << "/" << this->vidaMaxima << ")" << endl;
        return true; // Acción realizada con éxito
    }

    // -----------------------------------------------------------------
    // METODO: recibirDanio
    // -----------------------------------------------------------------
    void recibirDanio(int danioRecibido, string tipoAtacante)
    {
        // Regla especial del VUELO
        if (this->volando)
        {
            if (tipoAtacante != "Dragon")
            {
                cout << "   [!]" << this->nombre << " esta en VUELO y esquivo por completo el ataque" << endl;
                this->volando = false; // El vuelo se consume al esquivar
                return;
            }
            else
            {
                cout << "   [!] El atacante tambien es un Dragon. El vuelo fue inutil para esquivar." << endl;
            }
        }

        this->volando = false; // Se reinicia el estado de vuelo si recibe el impacto

        int danioAplicado = danioRecibido;
        setVida(this->vida - danioAplicado);

        cout << "   [-] " << this->nombre << " recibe " << danioAplicado
             << " pts de danio. (Vida: " << this->vida << "/" << this->vidaMaxima << ")" << endl;
    }

    // -----------------------------------------------------------------
    // METODOS DE ATAQUE
    // -----------------------------------------------------------------
    void mostrarAtaques() const
    {
        cout << "\n--- ATAQUES DISPONIBLES DE " << nombre << " ---" << endl;
        for (int i = 0; i < 4; i++)
        {
            cout << i + 1 << ". " << ataques[i].nombre
                 << " (Danio: " << ataques[i].danio
                 << " | Costo Energia: " << ataques[i].costoEnergia << ")" << endl;
        }
    }

    Ataque obtenerAtaque(int indice) const
    {
        if (indice >= 0 && indice < 4)
            return ataques[indice];
        return ataques[0];
    }

    // Intenta ejecutar el ataque seleccionado. Devuelve true si pudo atacar.
    bool ejecutarAtaque(int indiceAtaque, Criatura &objetivo)
    {
        if (indiceAtaque < 0 || indiceAtaque >= 4)
            return false;

        Ataque atq = ataques[indiceAtaque];

        // Verificar si cuenta con la energia requerida
        if (this->energia < atq.costoEnergia)
        {
            cout << "   [x] " << this->nombre << " no tiene suficiente energia para usar "
                 << atq.nombre << " (Requiere: " << atq.costoEnergia
                 << " | Tienes: " << this->energia << ")" << endl;
            return false;
        }

        // Restar costo de energia
        setEnergia(this->energia - atq.costoEnergia);
        cout << "\n   [>] " << this->nombre << " usa " << atq.nombre << endl;

        // Efecto especial: Vuelo del Dragon
        if (this->nombre == "Dragon" && atq.nombre == "Vuelo")
        {
            this->volando = true;
            cout << "   [!] El Dragon emprende el vuelo." << endl;
        }

        // Aplicar daño a la criatura objetivo
        objetivo.recibirDanio(atq.danio, this->nombre);
        return true;
    }

    // -----------------------------------------------------------------
    // METODO: mostrar
    // -----------------------------------------------------------------
    void mostrar() const
    {
        cout << "    -> " << nombre << " | Vida: " << vida << "/" << vidaMaxima
             << " | Energia: " << energia << "/" << energiaMaxima
             << " | Estado: " << (estaViva() ? "VIVA" : "DERROTADA");
        if (volando)
            cout << " [EN VUELO]";
        cout << endl;
    }
};



// =====================================================================
// FUNCIONES DE FABRICA Y SELECCION
// =====================================================================

void mostrarMenuCriaturas()
{
    cout << "1. Dragon     (Vida: 120 | Energia: 50)" << endl;
    cout << "2. Goblin     (Vida: 70  | Energia: 60)" << endl;
    cout << "3. Caballero  (Vida: 100 | Energia: 50)" << endl;
    cout << "4. Orco       (Vida: 110 | Energia: 45)" << endl;
    cout << "5. Fenix      (Vida: 95  | Energia: 65)" << endl;
}

Criatura crearCriaturaPorOpcion(int opcion)
{
    if (opcion == 1)
    {
        Ataque atqs[4] = {
            {"Llamarada", 25, 15},
            {"Garrazada", 15, 5},
            {"Vuelo", 10, 10}, // Ataque especial que activa esquivar
            {"Coletazo", 18, 8}};
        return Criatura("Dragon", 120, 50, atqs);
    }
    else if (opcion == 2)
    {
        Ataque atqs[4] = {
            {"Navajazo", 12, 5},
            {"Lanzar piedra", 15, 8},
            {"Mordisco", 18, 10},
            {"Emboscada", 22, 15}};
        return Criatura("Goblin", 70, 60, atqs);
    }
    else if (opcion == 3)
    {
        Ataque atqs[4] = {
            {"Estocada", 16, 5},
            {"Golpe de escudo", 20, 10},
            {"Carga de lanza", 25, 15},
            {"Espadazo sagrado", 28, 20}};
        return Criatura("Caballero", 100, 50, atqs);
    }
    else if (opcion == 4)
    {
        Ataque atqs[4] = {
            {"Punetazo", 14, 5},
            {"Hachazo", 22, 12},
            {"Aplastar", 26, 16},
            {"Grito de guerra", 18, 8}};
        return Criatura("Orco", 110, 45, atqs);
    }
    else if (opcion == 5)
    {
        Ataque atqs[4] = {
            {"Picotazo", 14, 5},
            {"Pluma de Fuego", 20, 10},
            {"Rafaga Solar", 26, 16},
            {"Explosion Fenix", 32, 22}};
        return Criatura("Fenix", 95, 65, atqs);
    }
    else
    {
        cout << "\nOpcion no valida. Se asigna criatura por defecto.\n";
        return Criatura();
    }
}

//
// FUNCION PARA EL TURNO DE LA IA (1 JUGADOR)
// Aportacion Javier Mora Gutierrez
void ejecutarTurnoIA(Criatura &oponente, Criatura &jugador, int dificultad)
{
    cout << "\n--- TURNO DEL OPONENTE [BOT] (" << oponente.obtenerNombre() << ") ---" << endl;

    // 1. FACIL: Decisiones al azar
    if (dificultad == 1)
    {
        if (rand() % 2 == 0)
        {
            if (!oponente.ejecutarAtaque(rand() % 4, jugador))
                oponente.descansar();
        }
        else
        {
            if (!oponente.curar())
                oponente.descansar();
        }
        return;
    }

    // 2. MEDIO: Se cura si tiene poca vida (<30%), de lo contrario ataca al azar
    if (dificultad == 2)
    {
        if (oponente.obtenerVida() < (oponente.obtenerVidaMaxima() * 0.30))
        {
            if (oponente.curar())
                return;
        }
        if (!oponente.ejecutarAtaque(rand() % 4, jugador))
            oponente.descansar();
        return;
    }

    // 3. DIFICIL: Se cura en estado crítico o selecciona el ataque con mayor daño
    if (dificultad == 3)
    {
        if (oponente.obtenerVida() < (oponente.obtenerVidaMaxima() * 0.25))
        {
            if (oponente.curar())
                return;
        }

        int mejorAtaque = -1;
        int maxDanio = -1;

        for (int i = 0; i < 4; i++)
        {
            Ataque a = oponente.obtenerAtaque(i);
            if (oponente.obtenerEnergia() >= a.costoEnergia && a.danio > maxDanio)
            {
                maxDanio = a.danio;
                mejorAtaque = i;
            }
        }

        if (mejorAtaque != -1)
        {
            oponente.ejecutarAtaque(mejorAtaque, jugador);
        }
        else
        {
            oponente.descansar();
        }
    }
}

// =====================================================================
// FUNCION PRINCIPAL (main)
// =====================================================================
int main()
{
    srand(time(0));

    // -----------------------------------------------------------------
    // SECCION 1: Bienvenida y Seleccion de Modo de Juego
    // -----------------------------------------------------------------
    cout << "========================================" << endl;
    cout << "         Bienvenido al Jueguito" << endl;
    cout << "========================================" << endl
         << endl;
    int dificultad = 1;//Variable para escoger la dificultad Javier Mora Gutierrez
    int modoJuego = 1;
    cout << "SELECCIONA EL MODO DE JUEGO:" << endl;
    cout << "1. 1 Jugador (Player 1 vs IA)" << endl;
    cout << "2. 2 Jugadores (Player 1 vs Player 2)" << endl;
    cout << "Elige una opcion: ";
    cin >> modoJuego;

    //Seleccion de dificultad Javier Mora Gutierrez
    if (modoJuego == 1) {
    cout << "\nSELECCIONA LA DIFICULTAD DEL BOT:" << endl;
    cout << "1. Facil" << endl;
    cout << "2. Medio" << endl;
    cout << "3. Dificil" << endl;
    cout << "Elige la dificultad: ";
    cin >> dificultad;
    if (dificultad < 1 || dificultad > 3) dificultad = 1;
}

    int opcionJugador = 0;
    int opcionOponente = 0;

    // -----------------------------------------------------------------
    // SECCION 2: Seleccion de Personajes
    // -----------------------------------------------------------------
    if (modoJuego == 2)
    {
        cout << "\n--- PLAYER 1: SELECCIONA TU CRIATURA ---" << endl;
    }
    else
    {
        cout << "\n--- SELECCIONA TU CRIATURA ---" << endl;
    }
    mostrarMenuCriaturas();
    cout << "Elige tu opcion: ";
    cin >> opcionJugador;

    Criatura jugador = crearCriaturaPorOpcion(opcionJugador);

    if (modoJuego == 2)
    {
        cout << "\n--- PLAYER 2: SELECCIONA TU CRIATURA ---" << endl;
        mostrarMenuCriaturas();
        cout << "Elige tu opcion: ";
        cin >> opcionOponente;
    }
    else
    {
        // Seleccion aleatoria para el oponente en modo 1 Jugador
        opcionOponente = (rand() % 5) + 1;
        cout << "\nSE HA SELECCIONADO EL OPONENTE DE MANERA ALEATORIA." << endl;
    }

    Criatura oponente = crearCriaturaPorOpcion(opcionOponente);

    // -----------------------------------------------------------------
    // SECCION 3: Demostracion de metodos requeridos (estaViva, descansar y curar)
    // -----------------------------------------------------------------
    cout << "\n========================================" << endl;
    cout << "        PRUEBA INICIAL DE METODOS" << endl;
    cout << "========================================" << endl;
    cout << "El jugador esta vivo? " << (jugador.estaViva() ? "Si (true)" : "No (false)") << endl;
    cout << "Probando metodo descansar en jugador:" << endl;
    jugador.descansar(); // Invoca descansar()
    cout << "Probando metodo curar en jugador:" << endl;
    jugador.curar(); // Invoca curar()
    cout << "========================================\n"
         << endl;

    // -----------------------------------------------------------------
    // SECCION 4: Bucle del Combate Interactiva por Rondas
    // -----------------------------------------------------------------
    int ronda = 1;

    cout << "========================================" << endl;
    cout << " EMPIEZA EL COMBATE: " << jugador.obtenerNombre()
         << " VS " << oponente.obtenerNombre() << endl;
    cout << "========================================" << endl;

    while (jugador.estaViva() && oponente.estaViva())
    {
        cout << "\n========================================" << endl;
        cout << "                ROUND " << ronda << endl;
        cout << "========================================" << endl;
        jugador.mostrar();
        oponente.mostrar();

        // -------------------------------------------------------------
        // TURNO DEL JUGADOR 1
        // -------------------------------------------------------------
        bool accionTurnoValida = false;

        // VERIFICACIÓN DE SEGURIDAD: Si está sin energía y sin usos restantes
        //Javier Mora Gutierrez
        if (jugador.estaBloqueada())
        {
            cout << "\n   [!] ¡Te has quedado sin energia, descansos y curaciones!" << endl;
            cout << "   [!] Pasas tu turno de emergencia y recuperas 15 pts de energia." << endl;
            jugador.setEnergia(jugador.obtenerEnergia() + 15);
            accionTurnoValida = true; // Activa la bandera para no entrar al menú
        }

        while (!accionTurnoValida && jugador.estaViva())
        {
            cout << "\nQue accion deseas realizar, " << jugador.obtenerNombre() << "?" << endl;
            cout << "1. Atacar" << endl;
            cout << "2. Descansar (Recupera energia)" << endl;
            cout << "3. Curar (Recupera vida)" << endl;
            cout << "Elige tu accion: ";

            int eleccionAccion = 0;
            cin >> eleccionAccion;

            if (eleccionAccion == 1)
            {
                jugador.mostrarAtaques();
                cout << "Elige un ataque: ";
                int numAtaque = 0;
                cin >> numAtaque;

                accionTurnoValida = jugador.ejecutarAtaque(numAtaque - 1, oponente);
            }
            else if (eleccionAccion == 2)
            {
                // Invocacion del metodo descansar() (Retorna false si excede limite)
                accionTurnoValida = jugador.descansar();
            }
            else if (eleccionAccion == 3)
            {
                // Invocacion del metodo curar() (Retorna false si excede limite)
                accionTurnoValida = jugador.curar();
            }
            else
            {
                cout << "Opcion no valida. Intenta de nuevo." << endl;
            }
        }

        // Verificar si el oponente murio tras el ataque del jugador 1
        if (!oponente.estaViva())
        {
            cout << "\n"
                 << oponente.obtenerNombre() << " ha sido derrotado" << endl;
            break;
        }

        // -------------------------------------------------------------
        // TURNO DEL OPONENTE / PLAYER 2
        // -------------------------------------------------------------
        if (modoJuego == 2)
        {
            // TURNO MANUAL PARA PLAYER 2
            bool accionTurnoValida2 = false;

            while (!accionTurnoValida2 && oponente.estaViva())
            {
                cout << "\n--- TURNO DEL PLAYER 2 (" << oponente.obtenerNombre() << ") ---" << endl;
                cout << "Que accion deseas realizar, " << oponente.obtenerNombre() << "?" << endl;
                cout << "1. Atacar" << endl;
                cout << "2. Descansar (Recupera energia)" << endl;
                cout << "3. Curar (Recupera vida)" << endl;
                cout << "Elige tu accion: ";

                int eleccionAccion2 = 0;
                cin >> eleccionAccion2;

                if (eleccionAccion2 == 1)
                {
                    oponente.mostrarAtaques();
                    cout << "Elige un ataque: ";
                    int numAtaque2 = 0;
                    cin >> numAtaque2;

                    accionTurnoValida2 = oponente.ejecutarAtaque(numAtaque2 - 1, jugador);
                }
                else if (eleccionAccion2 == 2)
                {
                    accionTurnoValida2 = oponente.descansar();
                }
                else if (eleccionAccion2 == 3)
                {
                    accionTurnoValida2 = oponente.curar();
                }
                else
                {
                    cout << "Opcion no valida. Intenta de nuevo." << endl;
                }
            }
        }
        else
        {
            // TURNO DEL OPONENTE (IA según la dificultad elegida)
            //Javier Mora Gutierrez
            ejecutarTurnoIA(oponente, jugador, dificultad);
        }

        // Verificar si el jugador murio tras el ataque del oponente / Player 2
        if (!jugador.estaViva())
        {
            cout << "\n"
                 << jugador.obtenerNombre() << " ha sido derrotado" << endl;
            break;
        }

        ronda++;
    }

    // -----------------------------------------------------------------
    // SECCION 5: Resultado Final del Combate
    // -----------------------------------------------------------------
    cout << "\n========================================" << endl;
    cout << "            FIN DEL COMBATE" << endl;
    cout << "========================================" << endl;

    if (jugador.estaViva() && !oponente.estaViva())
    {
        cout << "VICTORIA " << jugador.obtenerNombre() << " es el ganador." << endl;
    }
    else if (!jugador.estaViva() && oponente.estaViva())
    {
        cout << "DERROTA " << oponente.obtenerNombre() << " te ha vencido." << endl;
    }
    else
    {
        cout << "EMPATE. Ambas criaturas cayeron en combate." << endl;
    }

    cout << "\nEstado Final:" << endl;
    jugador.mostrar();
    oponente.mostrar();

    cout << "\nFIN DEL JUEGO" << endl;

    return 0;
}
