#include <iostream>
#include "../lib/story/Prologo.hpp"
#include "../lib/Class_UserInterface.hpp"

namespace PROLOGO {

    void Contexto(Jugador &Player, int &LEAL){
        bool Evento = false;
        UI.MostrarTexto("...", 100, 100); Sleep(825);
        UI.MostrarTexto("   >> Sientes como te abraza el frio tan intenso de este lugar <<", 25, 25); Sleep(975);
        UI.MostrarTexto("...", 100, 100); Sleep(900);
        UI.MostrarTexto("??? - Recuerdas tu nombre?", 25, 25);
        UI.Input(0, 1, "   | 1: Si | 0: No | ");

        if(UI.GetHistoryOption()){ 
            UI.MostrarTexto("??? - Perfecto. Cual es?", 25, 25);
            Player.EscogerNombre();
        } else {
            UI.MostrarTexto("??? - No te preocupes, esto le puede pasar a cualquiera.", 25, 25);
            UI.MostrarTexto("??? - Acabas de entrar a este lugar. Es normal que no lo recuerdes.", 25, 25);
        }

        if(Player.GetNombre() == "Leonidas" && UI.GetHistoryOption()){
            UI.MostrarTexto("??? - Si. Claro.", 25, 25);
        } else if(UI.GetHistoryOption()) {
            UI.MostrarTexto("??? - Parece que me has mentido.", 25, 25);
            UI.MostrarTexto("??? - No te preocupes. Eso le puede ocurrir a cualquiera. Esta vez lo dejare pasar.", 25, 25);
            Sleep(975); UI.MostrarTexto("??? - Deseas escoger un nombre nuevo?", 25, 25);
            UI.Input(0, 1, "   | 1: Si | 0: No | ");
            if(UI.GetHistoryOption()){
                UI.MostrarTexto("??? - Perfecto. Cual es?", 25, 25);
                Player.EscogerNombre();
                Evento = true;
            } else {
                UI.MostrarTexto("??? - Por su puesto! Tu lo entiendes a la perfeccion.", 25, 25);
            }
        }

        if(Evento){
            UI.MostrarTexto("??? - Para darle una forma a tu nuevo nombre, como quieres que sea tu cuerpo?", 25, 25);
            Evento = false; //Reiniciando la variable para el siguiente evento
        } else UI.MostrarTexto("??? - Para darte una forma, como quieres que sea tu cuerpo?", 25, 25);
        UI.Input(1, 3, "   | 1: Delgado | 2: Fornido | 3: Robusto |");
        UI.MostrarTexto("??? - Perfecto.", 25, 25);

        UI.MostrarTexto("??? - Como describirias a tu nuevo YO?.", 25, 25);
        UI.Input(1, 3, "   | 1: Inteligente | 2: Ocioso | 3: Determinado |");
        UI.MostrarTexto("??? - Muy bien. Muy, muy bien.", 25, 25);

        UI.MostrarTexto("??? - Cual es el sabor que mas te gusta?", 25, 25);
        UI.Input(0, 3, "   | 1: Dulce | 2: Amargo | 3: Salado | 0: Dolor |");

        if(!UI.GetHistoryOption()) {
            UI.MostrarTexto("??? - Si. Lo sabes muy bien! Demasiado bien.", 25, 25);
            LEAL++;
        } else UI.MostrarTexto("??? - Perfecto. Claro!", 25, 25);

        UI.MostrarTexto("??? - Finalmente, preferirias una plena vida llena de PODER, sin ningun ser real al cual amar...?", 25, 25); Sleep(975);
        UI.MostrarTexto("??? - O una simplista existencia HUMILDE, pero rodeado de los que mas amas?", 25, 25); Sleep(975);
        UI.Input(0, 2, "   | 0: PODER | 1: HUMILDAD | 2: NO LO SE (?) |");
        if(!UI.GetHistoryOption()){
            UI.MostrarTexto("??? - Exacto.", 25, 25);
            LEAL++;
        } else UI.MostrarTexto("??? - Si. Muy bien.", 25, 25);
        Sleep(975);

        UI.MostrarTexto("??? - Ahora...", 25, 100); Sleep(875);
        system("cls");

        UI.MostrarTexto(". . .", 25, 500); Sleep(500);
        std::cout << std::endl;
        UI.MostrarTexto("T O D O   E S O   S E   I R A   A   L A   B A S U R A.", 25, 1000);
        std::cout << std::endl;
        UI.MostrarTexto("N O   P U E D E S.", 25, 1000);
        std::cout << std::endl;
        UI.MostrarTexto("N U N C A   P O D R A S   E S C O G E R   Q U I E N   E R E S.", 25, 1000);
        std::cout << std::endl;
        UI.MostrarTexto("Q U E.   I D E A.   T A N.   A B S U R D A!", 25, 1000);
        std::cout << std::endl;
        UI.MostrarTexto("S E A S   Q U I E N   S E A S.   E S T E S   D O N D E   E S T E S.   C R E A S   E N   L O   Q U E   C R E A S.", 25, 500);
        std::cout << std::endl;
        UI.MostrarTexto(". . .", 25, 500); Sleep(500);
        std::cout << std::endl;
        UI.MostrarTexto("Tendras que ingeniartelas en este mundo tan cruel. :D", 25, 1000); Sleep(1000);
        UI.MostrarTexto("En este mundo...", 25, 500); Sleep(500);
        std::cout << std::endl;
        UI.MostrarTexto("P E L E A S   P O R   S O B R E V I V I R,   O   T E   R E S I G N A S   H A S T A   M O R I R.", 25, 1000);
        std::cout << std::endl;
        if(LEAL > 1) {
            UI.MostrarTexto("...Aunque tu ya entiendes esto perfectamente, verdad?", 25, 500);
            std::cout << std::endl;
            UI.MostrarTexto("T E   D E S E O   M U C H A   S U E R T E,   M I   D I S C I P U L O.", 25, 1000);
            std::cout << std::endl;
        }
    }

    void Etapa_0(){
        system("cls");
        UI.MostrarTexto("...", 100, 100); Sleep(825);
        UI.MostrarTexto("   >> El frio tan intenso de este lugar lo comienzas a sentir con aun mas fuerza <<", 25, 25); Sleep(975);
        UI.MostrarTexto("   >> Al estar acostado de lado, sientes una humedad insolitamente seca en tu costado <<", 25, 25); Sleep(975);
        UI.MostrarTexto("   >> Mientras mas tiempo pasas ahi, mas obvia es la sensacion de las particulas de hielo cayendo continuamente sobre ti <<", 25, 25); Sleep(975);
        UI.MostrarTexto("   >> Claramente esto es normal <<", 40, 25); Sleep(475);
        UI.MostrarTexto("...", 100, 100); Sleep(825);
        UI.MostrarTexto("   >> Te levantas. Hacia donde quieres ir? <<", 25, 25); Sleep(475);
        UI.Input(1, 1, "   | 1: No se |");
        UI.MostrarTexto("   >> Ves un refujio a unos metros delante de ti. Deseas ir? <<", 40, 25); Sleep(475);
        UI.Input(1, 2, "   | 1: Ir hacia el refujio | 2: Ir hacia la muralla en el horizonte |");
        if(UI.GetHistoryOption() == 2) { 
            UI.MostrarTexto("   >> Esta a kilometros de ti <<", 40, 25); Sleep(475); 
            UI.MostrarTexto("   >> Realisticamente, solo llegarias a caminar 100 metros antes de desmayarte de nuevo <<", 40, 25); Sleep(475);
            UI.MostrarTexto("   >> Hacia donde deseas ir? <<", 40, 25); Sleep(475);
            UI.Input(1, 1, "   | 1: Ir hacia el refujio |");
        }
        UI.MostrarTexto("...", 100, 100); Sleep(825);
        UI.MostrarTexto("   >> Ahora mismo, estas muy cansado, pero para tu propio bien, deseas ir hacia delante <<", 40, 25); Sleep(475);
        UI.MostrarTexto("...", 100, 100); Sleep(825);
        UI.MostrarTexto("   >> Ahora mismo, estas en el extremo de este reino nevado <<", 25, 25); Sleep(475);
        UI.MostrarTexto("   >> El llamado Muro Acerado de los Gigantes Plateados. Los que alguna vez fueron la ultima defensa de estas tierras... <<", 25, 200); Sleep(475);
        UI.MostrarTexto("   >> Antes de la llegada de La Laceracion <<", 25, 200); Sleep(475);
        UI.MostrarTexto("...", 100, 100); Sleep(825);
        UI.MostrarTexto("   >> C U I D A D O <<", 15, 25); Sleep(475);
        std::cout << std::endl;
        
    }

    void Etapa_Final(){
        UI.MostrarTexto("   >> Has llegado hasta el Muro Acerado <<", 50, 200); Sleep(475);
        UI.MostrarTexto("   >> En frente tuyo, solo queda el ultimo rastro de lo que alguna vez fueron los Gigantes Plateados <<", 50, 200); Sleep(475);
        UI.MostrarTexto("   >> Deseas seguir adelante? <<", 50, 200); Sleep(475);
        UI.Input(0, 1, "   | 1: Seguir adelante | 0: Esperar |");
        while(!UI.GetHistoryOption()){
            UI.MostrarTexto("...", 100, 100); Sleep(825);
            UI.MostrarTexto("   >> Se que es algo intimidante haber llegado hasta aqui <<", 50, 200); Sleep(475);
            UI.MostrarTexto("   >> Te enfrentaras con una criatura que marco un antes y un despues en la historia <<", 50, 200); Sleep(475);
            UI.MostrarTexto("...", 100, 100); Sleep(825);
            UI.MostrarTexto("   >> Pero necesitas hacer esto <<", 50, 200); Sleep(475);
            UI.MostrarTexto("...", 100, 100); Sleep(825);
            UI.MostrarTexto("   >> Deseas un tip para poder vencerlo? <<", 50, 200); Sleep(475);
            UI.Input(0, 1, "   | 1: Si | 0: No |");
            if(UI.GetHistoryOption()){
                UI.MostrarTexto("   >> Por mas imponentes que se vean, si tratas de imponerte contra ellos, eventualmente sederan <<", 50, 200); Sleep(475);
                UI.MostrarTexto("   >> No tienen energia infinita <<", 50, 200); Sleep(475);
            }
            UI.MostrarTexto("...", 100, 100); Sleep(825);
            UI.MostrarTexto("   >> Deseas seguir adelante? <<", 50, 200); Sleep(475);
            UI.Input(0, 1, "   | 1: Seguir adelante | 0: Esperar |");
        }
        UI.MostrarTexto("...", 100, 100); Sleep(825);
    }
}