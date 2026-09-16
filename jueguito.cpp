#include <iostream>
#include <string>

class UserInterface{
private:
    /* Variable encargada de almacenar las opciones del usuario/jugador.
       Es privada para que no se pueda modificar de ninguna manera fuera de la clase en si */
    int Option;
public:

    /* Constructor que inicializa la variable 'Option' a 0 por default */
    UserInterface(){
        Option = 0;
    }

    /* Metodo que imprime texto desde una variable o string */
    void Output(const std::string& Text){
        std::cout << Text << "\n";
        /* NOTA: La variable 'text' se pasa por referencia ('&' es un puntero) para que solo agarre el texto 
           y no lo copie en la funcion, evitando sobrecarga de rendimiento innecesaria. Asi mismo, se coloca 
           como 'const' (constante) ya que el string no cambia nunca dentro de la funcion. 
           Lo mismo se aplica en 'void Input()' */
    }

    /* Metodo para recibir las opciones del jugador */
    void Input(int InferiorLimit, int SuperiorLimit, const std::string& Question){
        do{
            /* Se imprime el texto de la pregunta con una sangria */
            std::cout << "   " << Question << std::endl << "  ";
            
            /* Se imprimen/muestran las opciones a escoger en forma de matriz lineal */
            for(int i=InferiorLimit; i<=SuperiorLimit; i++){
                std::cout << " | " << i << "";
            }
            std::cout << " | ->  ";

            /* Se pide la opcion a escoger */
            std::cin >> Option;

            /* Si el usuario mete alguna letra o numero indeseado, se ejecutara el "if" para evitar errores futuros */
            if(std::cin.fail() || std::cin.peek() != '\n'){ 
                std::cin.clear();
                std::cin.ignore(100 /* Rango de limpieza de 100 caracteres */, '\n');
                Option = InferiorLimit-1;
            }

        /* Se repetira el ciclo hasta que se introduzca alguno de los valores del rango */
        }while(Option < InferiorLimit || Option > SuperiorLimit); 
    }

    /* Metodo 'get' para obtener la opcion del jugador */
    int GetOption(){
        return Option;
    }
};

int main(){

    /* Se crea la interfaz de usuario UI */
    UserInterface UI;

    /* Codigo de prueba. Los testers pueden jugar con las funciones de UI como quieran para encontrar errores */
    UI.Output("Estas dentro del juego.");
    UI.Input(1, 3, "Que opcion deseas escojer?");
    std::cout << UI.GetOption() << std::endl; /* Ejemplo para poner a prueba 'UI.GetOption()' */
    UI.Output("Has escogido la opcion!");
    UI.Input(-1, 2, "Que opcion deseas escojer?");

    return 0;
}
