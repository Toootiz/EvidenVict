#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

// Función para leer el contenido de un archivo y devolverlo como un vector de strings
vector<string> leerArchivo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    vector<string> lineas;
    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            lineas.push_back(linea);
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo: " << nombreArchivo << "\n";
    }
    return lineas;
}

int main() {
    // Mapa para asociar el nombre de cada vector con el contenido del archivo correspondiente
    map<string, vector<string>> contenidoArchivos;

    // Nombres de archivo y sus nombres de vector correspondientes
    vector<pair<string, string>> nombresArchivos = {
        {"../../Archivos/mcode1.txt", "mcode1"},
        {"../../Archivos/mcode2.txt", "mcode2"},
        {"../../Archivos/mcode3.txt", "mcode3"},
        {"../../Archivos/transmission1.txt", "transmission1"},
        {"../../Archivos/transmission2.txt", "transmission2"}
    };

    // Leer cada archivo y almacenar su contenido en el map con el nombre correspondiente
    for (const auto& archivo : nombresArchivos) {
        vector<string> contenidoActual = leerArchivo(archivo.first);
        contenidoArchivos[archivo.second] = contenidoActual;  // Asignar el contenido al nombre del vector
    }

    // Mostrar el contenido de cada archivo usando su nombre de vector
    for (const auto& archivo : nombresArchivos) {
        const string& nombreVector = archivo.second;
        cout << "Contenido de " << nombreVector << ":\n";
        for (const string& linea : contenidoArchivos[nombreVector]) {
            cout << linea << '\n';
        }
        cout << "\n";
    }

    return 0;
}

