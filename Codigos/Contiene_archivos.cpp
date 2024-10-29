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

vector<int> calcularFuncionZ(vector<string>& Arreglo,  int Pos_inicio) {
    
    vector<int> Z;
    Z.resize(Arreglo.size());

    for (int i = Pos_inicio; i < Arreglo.size(); i++) {
        int j = 0;
        while (i + j < Arreglo.size() && Arreglo[i + j] == Arreglo[j]) {
            if(Arreglo[j] == "$") break;
            else j++;
        }
        Z[i] = j;
    }
    return Z;
}

void Search(string transmission, string mcode, string transmissionName, string mcodeName) {
    string S = mcode + "$" + transmission;
    vector<string> Arreglo(S.size());
    for (int i = 0; i < S.size(); i++) {
        Arreglo[i] = S[i];
    }
    vector<int> Z=calcularFuncionZ(Arreglo,  mcode.size() + 1);
    int m = mcode.size();
    bool found = false;
    for (int i = 0; i < Z.size(); i++) {
        if (Z[i] == m-1) {
           found = true;
        }
    }
    if (found) {
        cout << "(True) El archivo " << transmissionName << " contiene el codigo " << mcode <<" del archivo "<<mcodeName << endl;
    } else {
        cout << "(False) El archivo " << transmissionName << " no contiene el codigo " << mcode <<" del archivo "<< mcodeName << endl;
    }
}

int main() {
    string transmission1, transmission2, mcode1, mcode2, mcode3;

    string fileNames[] = {
        "../../Archivos/transmission1.txt",
        "../../Archivos/transmission2.txt",
        "../../Archivos/mcode1.txt",
        "../../Archivos/mcode2.txt",
        "../../Archivos/mcode3.txt"
    };

    for (int i = 0; i < 5; ++i) {
        ifstream file(fileNames[i]); 
        if (file.is_open()) {
            string line;
            string content;
            while (getline(file, line)) {
                content += line + "\n"; 
            }
            file.close(); 
            switch (i) {
                case 0: transmission1 = content; break;
                case 1: transmission2 = content; break;
                case 2: mcode1 = content; break;
                case 3: mcode2 = content; break;
                case 4: mcode3 = content; break;
            }
        } else {
            cerr << "No se pudo abrir el archivo: " << fileNames[i] << endl;
        }
    }


    Search(transmission1, mcode1, "transmission1", "mcode1");
    Search(transmission1, mcode2, "transmission1", "mcode2");
    Search(transmission1, mcode3, "transmission1", "mcode3");
    Search(transmission2, mcode1, "transmission2", "mcode1");
    Search(transmission2, mcode2, "transmission2", "mcode2");
    Search(transmission2, mcode3, "transmission2", "mcode3");

    return 0;
}

