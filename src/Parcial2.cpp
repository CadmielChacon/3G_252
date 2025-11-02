#include <ftxui/dom/elements.hpp>   // Para elementos de interfaz
#include <ftxui/screen/screen.hpp>  // Para renderizado
#include <thread>                   // Para sleep
#include <chrono>                   // Para duración
#include <iostream>                 // Para std::cout
#include <vector>                   // Para std::vector
using namespace std;
using namespace ftxui;

// Clase que representa una escena (fondo + personajes)
class Escena {
private:
    vector<string> fondo;
    vector<string> personajes;
    int desplazamiento_izq;
    int desplazamiento_der;

public:
    // Constructor
    Escena(const vector<string>& fondo, const vector<string>& personajes, int izq = 0, int der = 0)
        : fondo(fondo), personajes(personajes), desplazamiento_izq(izq), desplazamiento_der(der) {}

    // Método para renderizar la escena
    void Mostrar(int duracion_ms = 300) const {
        auto screen = Screen::Create(Dimension::Full(), Dimension::Full());
        vector<Element> lines;

        // Agrega fondo
        for (auto& line : fondo)
            lines.push_back(text(line));

        // Agrega personajes
        for (auto& line : personajes)
            lines.push_back(text(string(desplazamiento_izq, ' ') + line + string(desplazamiento_der, ' ')));

        Render(screen, vbox(lines) | center);
        screen.Print();
        this_thread::sleep_for(chrono::milliseconds(duracion_ms));
        screen.Clear();
    }
};

// Clase principal que controla toda la animación
class AnimacionConejos {
private:
    vector<string> arboles;
    vector<string> conejo_izq;
    vector<string> conejo_der;
    vector<string> encuentro;
    vector<string> corazon;

public:
    AnimacionConejos() {
        // Árboles
        arboles = {
        "  .-°°°-.           .-°°°-.            .-°°°-. ",
        " /* * * *\\         /* * * *\\          /* * * *\\ ",
        ":_.-:`:-._;       :_.-:`:-._;        :_.-:`:-._; ",
        "    (_)               (_)                (_) ",
        " \\|/(_)\\|/         \\|/(_)\\|/          \\|/(_)\\|/ "
        };

        // Conejos
        conejo_izq = {         
            " (\\_/) ",
            " ( •_•)",
            " / >🍪 "
        };
        conejo_der = {
            " (\\_/) ",
            " (•_• )",
            "  <  \\ "
        };
        encuentro  = { 
            " (\\_/)          (\\_/) ",
            " ( •_•)   🍪   (•_• ) ",
            " /   \\          /   \\ "
        };
        corazon    = { 
            "         ❤️       ",
            " (\\_/)        (\\_/) ",
            " ( •_•)      (•_• ) ",
            " /   \\        /   \\ "
        };
    }

    void Reproducir() {
        // Animación de movimiento
        for (int step = 0; step <= 15; ++step) {
            int left_space = step;
            int right_space = 30 - step * 2;
            if (right_space < 0) right_space = 0;

            vector<string> frame;
            for (int i = 0; i < 3; ++i) {
                frame.push_back(string(left_space, ' ') + conejo_izq[i] + string(right_space, ' ') + conejo_der[i]);
            }

            Escena escena(arboles, frame);
            escena.Mostrar(200);
        }

        // Encuentro
        {
            Escena escena_encuentro(arboles, encuentro, 12, 0);
            escena_encuentro.Mostrar(900);
        }

        // Corazón
        {
            Escena escena_corazon(arboles, corazon, 12, 0);
            escena_corazon.Mostrar(1200);
        }

        // Mensaje final
        auto screen = Screen::Create(Dimension::Full(), Dimension::Full());
        Render(screen, text("¡Animación finalizada!") | center);
        screen.Print();
    }
};

int main() {
    AnimacionConejos animacion;
    animacion.Reproducir();
    return 0;
}
