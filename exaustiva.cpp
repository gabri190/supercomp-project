#include "grafo.h"
#include <iostream>
#include <chrono>

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
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<int> cliqueMaxima = encontrarCliqueMaxima(grafo, numVertices);
    auto end = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Clique máxima: ";
    for(int v : cliqueMaxima) {
        std::cout << v << " ";
    }
    std::cout << std::endl;

    std::cout << "Tempo de execução: " << elapsed.count() << "s" << std::endl;

    return 0;
}