#include <ftxui/dom/elements.hpp>   // Para elementos de interfaz
#include <ftxui/screen/screen.hpp>  // Para renderizado
#include <thread>                   // Para sleep
#include <chrono>                   // Para duración
#include <iostream>                 // Para std::cout
#include <vector>                   // Para std::vector
using namespace std;
using namespace ftxui;

int main() {
    // Árboles del fondo (estáticos)
    vector<string> trees = {
        "  .-°°°-.           .-°°°-.            .-°°°-. ",
        " /* * * *\\         /* * * *\\          /* * * *\\ ",
        ":_.-:`:-._;       :_.-:`:-._;        :_.-:`:-._; ",
        "    (_)               (_)                (_) ",
        " \\|/(_)\\|/         \\|/(_)\\|/          \\|/(_)\\|/ "
    };
    
    // Frames de cada conejo 
    vector<string> left_bunny = {
        
    };

    vector<string> right_bunny = {
        " (\\_/) ",
        " (•_• )",
        "  <  \\ "
    };

    // Escena cuando se encuentran con la galleta entre ellos
    vector<string> meet_bunnies = {
        " (\\_/)          (\\_/) ",
        " ( •_•)   🍪   (•_• ) ",
        " /   \\          /   \\ "
    };

    // Escena con el corazón
    vector<string> heart_scene = {
        "         ❤️       ",
        " (\\_/)        (\\_/) ",
        " ( •_•)      (•_• ) ",
        " /   \\        /   \\ "
    };

    // Animación: los conejos se acercan en la misma línea horizontal
    for (int step = 0; step <= 15; ++step) {
        auto screen = Screen::Create(Dimension::Full(), Dimension::Full());

        int left_space = step;          // izquierda avanza a la derecha
        int right_space = 30 - step*2;  // derecha avanza a la izquierda
        if (right_space < 0) right_space = 0;

        vector<Element> lines;

        // Fondo con árboles
        for (auto& line : trees)
        lines.push_back(text(line));

        // Conejos
        for (int i = 0; i < 3; ++i) {
            string frame_line =
                string(left_space, ' ') + left_bunny[i] +
                string(right_space, ' ') + right_bunny[i];
            lines.push_back(text(frame_line));
        }

        Render(screen, vbox(lines) | center);
        screen.Print();
        this_thread::sleep_for(chrono::milliseconds(200));
        screen.Clear();
    }

        // Pausa: se encuentran
    {
        auto screen = Screen::Create(Dimension::Full(), Dimension::Full());
        vector<Element> lines;

        int left_space = 12;  // misma posición final del bucle
        int right_space = 0;

        for (auto& line : trees)
            lines.push_back(text(line));

        for (int i = 0; i < 3; ++i) {
            string frame_line =
                string(left_space, ' ') + meet_bunnies[i];  // mantener alineación
            lines.push_back(text(frame_line));
        }

        Render(screen, vbox(lines) | center);
        screen.Print();
        this_thread::sleep_for(chrono::milliseconds(900));
    }

    // Escena final con el corazón ❤️
    {
        auto screen = Screen::Create(Dimension::Full(), Dimension::Full());
        vector<Element> lines;
        
        int left_space = 12;  // misma posición final del bucle
        int right_space = 0;

        for (auto& line : trees)
            lines.push_back(text(line));

        for (int i = 0; i < 4; ++i) {
            string frame_line =
                string(left_space, ' ') + heart_scene[i];  // mantener alineación
            lines.push_back(text(frame_line));
        }
        
        Render(screen, vbox(lines) | center);
        screen.Print();
        this_thread::sleep_for(chrono::milliseconds(1200));
    }

    // Mensaje final
    {
        auto screen = Screen::Create(Dimension::Full(), Dimension::Full());
        Render(screen, text("¡Animación finalizada!") | center);
        screen.Print();
    }
}