#include "grafo.h"
#include <iostream>

std::vector<int> encontrarCliqueMaxima(const std::vector<std::vector<int>>& grafo, int numVertices) {
    std::vector<int> cliqueMaxima;
    std::vector<int> candidatos;

    for(int i = 0; i < numVertices; ++i) {
        candidatos.push_back(i);
    }

    while(!candidatos.empty()) {
        int v = candidatos.back();
        candidatos.pop_back();

        bool podeAdicionar = true;

        for(int u : cliqueMaxima) {
            if(grafo[u][v] == 0) {
                podeAdicionar = false;
                break;
            }
        }

        if(podeAdicionar) {
            cliqueMaxima.push_back(v);
            std::vector<int> novosCandidatos;

            for(int u : candidatos) {
                bool adjacenteATodos = true;

                for(int c : cliqueMaxima) {
                    if(grafo[u][c] == 0) {
                        adjacenteATodos = false;
                        break;
                    }
                }

                if(adjacenteATodos) {
                    novosCandidatos.push_back(u);
                }
            }

            candidatos = novosCandidatos;
        }
    }

    return cliqueMaxima;
}

int main() {
    int numVertices;
    std::vector<std::vector<int>> grafo = LerGrafo("grafo.txt", numVertices);

    std::vector<int> cliqueMaxima = encontrarCliqueMaxima(grafo, numVertices);

    std::cout << "Clique máxima: ";
    for(int v : cliqueMaxima) {
        std::cout << v << " ";
    }
    std::cout << std::endl;

    return 0;
}