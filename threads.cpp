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
#include <chrono>  

std::vector<int> encontrarCliqueMaxima(const std::vector<std::vector<int>>& grafo, int numVertices) {
    std::vector<int> cliqueMaxima;
    std::vector<int> candidatos;

    for(int i = 0; i < numVertices; ++i) {
        candidatos.push_back(i);
    }

    int exitLoop = 0;

    #pragma omp parallel
    {
        #pragma omp single nowait
        {
            while(!candidatos.empty() && !exitLoop) {
                int v;
                #pragma omp critical
                {
                    v = candidatos.back();
                    candidatos.pop_back();
                }

                bool podeAdicionar = true;

                #pragma omp parallel for
                for(int u = 0; u < cliqueMaxima.size(); ++u) {
                    if(grafo[cliqueMaxima[u]][v] == 0) {
                        #pragma omp critical
                        {
                            podeAdicionar = false;
                            exitLoop = 1;  // Set the exitLoop variable to terminate the outer loop
                        }
                    }
                }

                if(podeAdicionar) {
                    #pragma omp critical
                    {
                        cliqueMaxima.push_back(v);
                    }
                    
                    std::vector<int> novosCandidatos;

                    #pragma omp parallel for
                    for(int u = 0; u < candidatos.size(); ++u) {
                        bool adjacenteATodos = true;

                        for(int c : cliqueMaxima) {
                            if(grafo[candidatos[u]][c] == 0) {
                                adjacenteATodos = false;
                                break;
                            }
                        }

                        if(adjacenteATodos) {
                            #pragma omp critical
                            {
                                novosCandidatos.push_back(candidatos[u]);
                            }
                        }
                    }

                    #pragma omp critical
                    {
                        candidatos = novosCandidatos;
                    }
                }
            }
        }
    }

    return cliqueMaxima;
}

int main() {
    int numVertices;
    std::vector<std::vector<int>> grafo = LerGrafo("grafo.txt", numVertices);

    auto start_time = std::chrono::high_resolution_clock::now();

    std::vector<int> cliqueMaxima = encontrarCliqueMaxima(grafo, numVertices);

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time;

    std::cout << "Clique máxima: ";
    for(int v : cliqueMaxima) {
        std::cout << v << " ";
    }
    std::cout << std::endl;

    std::cout << "Tempo de execução: " << elapsed.count() << "s" << std::endl;

    return 0;
}
