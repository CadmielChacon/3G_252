#include <ftxui/dom/elements.hpp>   // Para elementos de interfaz
#include <ftxui/screen/screen.hpp>  // Para renderizado
#include <thread>                   // Para sleep
#include <chrono>                   // Para duración
#include <iostream>                 // Para std::cout
#include <vector>                   // Para std::vector
using namespace ftxui;
using namespace std;

int main() {
    // === Frames ASCII del conejo ===
    vector<string> bunny_frames = {
        "        (\\_/)      \n"
        "        ( •_•)     \n"
        "        / >🍪      ",
        "        (\\_/)      \n"
        "        ( •_•)     \n"
        "        / >🍩      ",
        "        (\\_/)      \n"
        "        ( •_•)     \n"
        "        / >🍰      "
    };

    for (int i = 0; i < 9; i++) {
        auto screen = Screen::Create(Dimension::Full(), Dimension::Full());
        string frame = bunny_frames[i % bunny_frames.size()];

        // Convertir el texto del frame en líneas separadas
        vector<Element> lines;
        string line;
        for (char c : frame) {
            if (c == '\n') {
                lines.push_back(text(line));
                line.clear();
            } else {
                line += c;
            }
        }
        if (!line.empty()) lines.push_back(text(line));

        auto bunny_element = vbox(lines) | center;
        Render(screen, bunny_element);
        screen.Print();

        this_thread::sleep_for(chrono::milliseconds(400));
        screen.Clear();
    }

    auto screen = Screen::Create(Dimension::Full(), Dimension::Full());
    Render(screen, text("¡Animación finalizada!") | center);
    screen.Print();
}
