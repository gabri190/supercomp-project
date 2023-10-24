// Implementação com Threads OpenMP
// A implementação de uma solução com OpenMP para encontrar cliques em um grafo usando a heurística gulosa envolve a 
// paralelização das iterações do algoritmo em diferentes threads. O OpenMP simplifica a criação de threads e a coordenação 
// entre elas.

// Nessa implementação você deve apresentar o código-fonte modificado, justificar a alteração feita, e mostrar também o 
// speed up obtido. Faça uso de gráficos e tabelas para mostrar que sua implementação em openMP valeu a pena. Observe que 
// mesmo assim você não vai conseguir resolver exaustivamente o problema, mas o tamanho do grafo será maior, e o tempo de 
// processamento para um mesmo tamanho deve ser preferencialmente menor.
//solucao aqui
#include "grafo.h"
#include <iostream>
#include <omp.h>

std::vector<int> encontrarCliqueMaxima(const std::vector<std::vector<int>>& grafo, int numVertices) {
    std::vector<int> cliqueMaxima;
    std::vector<int> candidatos;

    for(int i = 0; i < numVertices; ++i) {
        candidatos.push_back(i);
    }

    #pragma omp parallel
    {
        #pragma omp single nowait
        {
            while(!candidatos.empty()) {
                int v = candidatos.back();
                candidatos.pop_back();

                bool podeAdicionar = true;

                #pragma omp critical
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

