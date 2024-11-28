#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

#define INF INT_MAX
// Codigo inspirado en https://www.mycompiler.io/view/JV06mkzT2k9
//Complejidad O(NlogN) donde N es el numero de nodos
void Prim(vector<vector<int>>& Grafo){
   int n = Grafo.size();
    //Creamos la PQ y un vector MST para indicar que nodos ya fueron visitados
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> colaPrioridad;
    vector<bool> MST(n, false);

    //En nodos vamos a guardar el peso de cada indice hasta ese momento
    vector<int> Nodos(n, INF);
    //Y en Padres el antecesor de cada nodo
    vector<int> Padres(n, -1);

    
    int Nodo_Inicial = 0;
    Nodos[Nodo_Inicial] = 0;
    //Formato (peso, nodo)
    colaPrioridad.push({Nodos[Nodo_Inicial], Nodo_Inicial});

    while (!colaPrioridad.empty()) {
        int u = colaPrioridad.top().second;
        colaPrioridad.pop();

        if (MST[u]) continue;

        MST[u] = true; //Declaramos que ese nodo ya fue visitado

        
        for (int i = 0; i < Grafo[u].size(); i++) {
            int peso = Grafo[u][i];

            
            if (peso != 0 && !MST[i] && peso < Nodos[i]) {
                Nodos[i] = peso;    
                Padres[i] = u;  // Guardamos el nodo padre en el indice del hijo    
                colaPrioridad.push({peso, i}); 
            }
        }
    }

    //Formato con ayuda de chat
    cout << "Arista   Peso\n";
    int costoTotal = 0;
    for (int i = 1; i < n; i++) { // Comenzamos en 1 porque 0 no tiene padre
        if (Padres[i] != -1) {
            cout << Padres[i] << " - " << i << "    " << Nodos[i] << "\n";
            costoTotal += Nodos[i];
        }
    }
    cout << "Costo total del MST: " << costoTotal << endl;
}

vector<vector<int>> Translate(string Grafo){
    vector<vector<int>> matrix; 
    stringstream ss(Grafo); 
    string line;

    // Procesar cada línea del string
    while (getline(ss, line)) {
        vector<int> row; 
        stringstream lineStream(line); 
        int number;

        // Extraer números del flujo
        while (lineStream >> number) {
            row.push_back(number);
        }

        // Agregar el vector de la línea a la matriz
        matrix.push_back(row);
    }

    

    return matrix;
}

int main(){
    string Grafo;

    string fileNames[] = {
        "../Grafo.txt"
    };
    // Lectura de archivos
    
    ifstream file(fileNames[0]); 
    if (file.is_open()) {
        string line;
        string content;
        while (getline(file, line)) {
            content += line + "\n"; 
        }
        file.close(); 
        Grafo=content;
    } else {
        cerr << "No se pudo abrir el archivo: " << fileNames[0] << endl;
    }

    vector<vector<int>> grafo=Translate(Grafo);
    
    vector<vector<int>> grafo_prueba = {
        {0, 12, 10, 0,  0,  0,  0, 14},
    {12, 0,  8, 13, 0,  0,  0,  0},
    {10, 8,  0,  9,  7,  0,  0,  0},
    {0,  13, 9,  0,  11, 15, 0,  0},
    {0,  0,  7,  11, 0,  6,  9,  0},
    {0,  0,  0,  15, 6,  0,  8,  5},
    {0,  0,  0,  0,  9,  8,  0, 10},
    {14, 0,  0,  0,  0,  5,  10, 0}
    };

    Prim(grafo_prueba);
    return 0;
}