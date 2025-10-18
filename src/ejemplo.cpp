#include <iostream>
#include <string>
#include <sstream>
#include <thread> //manejar hilos de la computadora
#include <chrono> //manejar el tiempo
using namespace std;
#include <ftxui/screen/screen.hpp>
#include <ftxui/screen/color.hpp>
// #include <ftxui/component/component.hpp>
// #include <ftxui/component/screen_interactive.hpp>
using namespace ftxui;

string nave =
string("     ___      \n")+ 
string(" ___/   \___  \n")+ 
string("/   '---'   \ \n")+ 
string("'--_______--' \n")+ 
string("     / \      \n")+ 
string("    /   \     \n")+ 
string("    /\O/\     \n")+ 
string("    / | \     \n")+ 
string("    // \\     \n");

int main(int argc, char const *argv[])
{
    auto pantalla = Screen::Create(
        Dimension::Full(),
        Dimension::Fixed(10));
    int x = 0;
    int y = 0;

    while (true)
    {
        x++;
        stringstream ss(nave);
        string linea;
        int noLinea = 0;
        while (getline(ss, linea))
        {
            int columna = 0;
            for (auto &&letra : linea)
            {
            // obtener referencia de pixel y modeficacion
            auto &pixel = pantalla.PixelAt(x +columna, y + columna);
            pixel.character = letra;
            columna++;
            }
            noLinea++;
        }

        // imprimir pantalla

        pantalla.Print();
        pantalla.Clear();
        cout << ResetPosition();
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    return 0;
}
