#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <fstream> // Para leer el archivo
#include <sstream> // Para procesar líneas del archivo

using namespace std;
// Codigo basado en las precentaciones 0.3 paginas 94 - 103
// Complejidad O(N^2)(2^N) donde N es el numero de nodos


#define INF 1000000000 // Valor grande para representar infinito

int tspDP(int n, const vector<vector<int>>& grafo) {
    int N = 1 << n; // Total de subconjuntos
    vector<vector<int>> dp(n, vector<int>(N, INF));
    dp[0][1] = 0; // Caso base: empezar en el nodo 0 con el subconjunto {0}

    // Llenar la tabla DP
    for (int subset = 1; subset < N; subset++) {
        for (int j = 0; j < n; j++) {
            if (!(subset & (1 << j))) continue; // j no está en el subconjunto

            for (int k = 0; k < n; k++) {
                if (k != j && (subset & (1 << k))) {
                    dp[j][subset] = min(dp[j][subset], dp[k][subset ^ (1 << j)] + grafo[k][j]);
                }
            }
        }
    }

    // Encontrar el costo mínimo
    int minCost = INF;
    int lastNode = -1;
    int S = N - 1; // Subconjunto completo

    for (int j = 1; j < n; j++) {
        int costo = dp[j][S] + grafo[j][0];
        if (costo < minCost) {
            minCost = costo;
            lastNode = j;
        }
    }

    // Reconstruir la ruta
    vector<int> path;
    path.push_back(0); // Nodo inicial
    int subset = S;
    int current = lastNode;

    while (current != -1) {
        path.push_back(current); // Agregar nodo actual
        int prev = current;
        current = -1;

        for (int k = 0; k < n; k++) {
            if ((subset & (1 << k)) && dp[k][subset ^ (1 << prev)] + grafo[k][prev] == dp[prev][subset]) {
                current = k;
                break;
            }
        }

        subset ^= (1 << prev); // Eliminar nodo del subconjunto
    }

    // Eliminar nodo inicial extra si está duplicado
    if (path.back() == 0 && path.size() > static_cast<size_t>(n + 1)) {
        path.pop_back();
    }

    // Imprimir resultados
    cout << "Costo mínimo: " << minCost << endl;
    cout << "Ruta: ";
    for (int nodo : path) {
        cout << char('A' + nodo) << " ";
    }
    cout << endl;

    return minCost;
}

// Función para leer el archivo
vector<vector<int>> readGraphFromFile(const string& filename, int& n) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "No se pudo abrir el archivo." << endl;
        exit(1);
    }

    file >> n; // Leer el número de colonias

    vector<vector<int>> grafo(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            file >> grafo[i][j]; // Leer cada valor de la matriz de adyacencia
        }
    }

    file.close();
    return grafo;
}

int main() {
    int n;
    string filename = "../Grafo.txt";

    // Leer el grafo desde el archivo
    vector<vector<int>> grafo = readGraphFromFile(filename, n);

    // Resolver el problema del TSP
    tspDP(n, grafo);

    return 0;
}
