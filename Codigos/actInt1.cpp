#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

vector<int> calcularFuncionZ(vector<string>& Arreglo, int Pos_inicio) {
    vector<int> Z;
    Z.resize(Arreglo.size());

    for (int i = Pos_inicio; i < Arreglo.size(); i++) {
        int j = 0;
        while (i + j < Arreglo.size() && Arreglo[i + j] == Arreglo[j]) {
            if (Arreglo[j] == "$") break;
            else j++;
        }
        Z[i] = j;
    }
    return Z;
}

void search(string transmission, string mcode, string transmissionName, string mcodeName) {
    string S = mcode + "$" + transmission;
    vector<string> Arreglo(S.size());
    for (int i = 0; i < S.size(); i++) {
        Arreglo[i] = S[i];
    }
    vector<int> Z = calcularFuncionZ(Arreglo, mcode.size() + 1);
    int m = mcode.size();
    bool found = false;
    for (int i = 0; i < Z.size(); i++) {
        if (Z[i] == m - 1) {
            found = true;
        }
    }
    if (found) {
        cout << "(True) El archivo " << transmissionName << " contiene el codigo " << mcode <<" del archivo "<<mcodeName << endl;
    } else {
        cout << "(False) El archivo " << transmissionName << " no contiene el codigo " << mcode <<" del archivo "<< mcodeName << endl;
    }
}

// Función para preprocesar la cadena para el algoritmo de Manacher
string preprocesarCadena(const string& s) {
    if (s.empty()) return "^$";
    string ret = "^"; 

    for (char c : s) {
        ret += "#" + string(1, c);
    }

    ret += "#$"; 
    return ret;
}

// Función para encontrar el palindromo más largo usando el algoritmo de Manacher
pair<int, int> manacher(const string& s) {
    string cadena = preprocesarCadena(s);
    int n = cadena.length();
    vector<int> positions(n, 0);

    int center = 0, right = 0; // Centro y límite derecho del palíndromo actual más grande
    for (int i = 1; i < n - 1; ++i) {
        int i_mirror = 2 * center - i; // Índice reflejado de i con respecto al centro

        if (right > i) {
            positions[i] = min(right - i, positions[i_mirror]);
        }

        // Intentar expandir el palíndromo centrado en i
        while (cadena[i + 1 + positions[i]] == cadena[i - 1 - positions[i]]) {
            positions[i]++;
        }

        // Actualizar el centro y límite derecho si el palíndromo expandido va más allá del límite derecho
        if (i + positions[i] > right) {
            center = i;
            right = i + positions[i];
        }
    }

    // Encontrar el palíndromo más largo
    int maxLongitud = 0;
    int centroIndex = 0;
    for (int i = 1; i < n - 1; ++i) {
        if (positions[i] > maxLongitud) {
            maxLongitud = positions[i];
            centroIndex = i;
        }
    }

    // Convertir el índice de centro del palíndromo encontrado a posiciones originales
    int inicio = (centroIndex - 1 - maxLongitud) / 2;
    int fin = inicio + maxLongitud - 1;
    return {inicio + 1, fin + 1}; // Regresar posiciones
}

// Función para encontrar el Longest Common Substring
void longestCommonSubstring(const string s1, const string s2) {
    int n = s1.length();
    int m = s2.length();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    int maxLength = 0;  
    int endPos1 = 0;   

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] > maxLength) {
                    maxLength = dp[i][j];
                    endPos1 = i; 
                }
            }
        }
    }

    int startPos1 = endPos1 - maxLength + 1;

    cout << "Substring común más largo entre las transmisiones: " << startPos1 << " " << endPos1 << endl;
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
    // Lectura de archivos
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

    // Parte 1: Buscar código malicioso en transmisiones
    search(transmission1, mcode1, "transmission1", "mcode1");
    search(transmission1, mcode2, "transmission1", "mcode2");
    search(transmission1, mcode3, "transmission1", "mcode3");
    search(transmission2, mcode1, "transmission2", "mcode1");
    search(transmission2, mcode2, "transmission2", "mcode2");
    search(transmission2, mcode3, "transmission2", "mcode3");
    cout << endl;

    // Parte 2: Encontrar el palíndromo más largo en cada transmisión utilizando Manacher
    pair<int, int> palindromo1 = manacher(transmission1);
    cout << "Palíndromo más largo en transmission1: " << endl << "Posición inicial: " << palindromo1.first << ", Posición final: " << palindromo1.second << endl << endl;

    pair<int, int> palindromo2 = manacher(transmission2);
    cout << "Palíndromo más largo en transmission2: " << endl << "Posición inicial: " << palindromo2.first << ", Posición final: " << palindromo2.second << endl << endl;

    // Parte 3: Encontrar Longest Common Substring entre transmisiones
    longestCommonSubstring(transmission1, transmission2);

    return 0;
}
