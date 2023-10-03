#include <iostream>
#include <vector>

using namespace std;

// Função para encontrar a Clique Máxima
vector<int> EncontrarCliqueMaxima(vector<vector<int>>& grafo, int numVertices) {
    vector<int> cliqueMaxima;
    vector<int> candidatos;

    // Inicialmente, todos os nós são candidatos
    for (int i = 0; i < numVertices; i++) {
        candidatos.push_back(i);
    }

    while (!candidatos.empty()) {
        int v = candidatos.back();
        candidatos.pop_back();
        bool podeAdicionar = true;

        for (int u : cliqueMaxima) {
            if (grafo[u][v] == 0) {
                podeAdicionar = false;
                break;
            }
        }

        if (podeAdicionar) {
            cliqueMaxima.push_back(v);
            vector<int> novosCandidatos;

            for (int u : candidatos) {
                bool adjacenteATodos = true;

                for (int c : cliqueMaxima) {
                    if (grafo[u][c] == 0) {
                        adjacenteATodos = false;
                        break;
                    }
                }

                if (adjacenteATodos) {
                    novosCandidatos.push_back(u);
                }
            }

            candidatos = novosCandidatos;
        }
    }

    return cliqueMaxima;
}

int main() {
    // Exemplo de uso da função EncontrarCliqueMaxima
    int numVertices = 5;
    vector<vector<int>> grafo = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 1, 0},
        {1, 1, 0, 1, 1},
        {0, 1, 1, 0, 1},
        {0, 0, 1, 1, 0}
    };

    vector<int> cliqueMaxima = EncontrarCliqueMaxima(grafo, numVertices);

    cout << "Clique Máxima: ";
    for (int node : cliqueMaxima) {
        cout << node << " ";
    }
    cout << endl;

    return 0;
}
