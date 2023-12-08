// Paralelização e Distribuição do Processamento com MPI
// Nesta implementação, você deve dividir o problema em várias partes e distribuí-las para diferentes processadores usando a 
// biblioteca MPI (Message Passing Interface). Cada processador será responsável por encontrar cliques em uma parte do grafo, e 
// os resultados serão combinados no final para encontrar todas as cliques no grafo.
//solucao aqui 

#include <mpi.h>
#include "grafo.h"  
#include <iostream>
#include <vector>
#include <chrono>

// Função para encontrar a clique máxima em uma parte do grafo
std::vector<int> encontrarCliqueMaxima(const std::vector<std::vector<int>>& grafo, int numVertices, int start, int end) {
    std::vector<int> cliqueMaxima;
    std::vector<int> candidatos;

    // Inicializa candidatos para a parte específica do grafo
    for (int i = start; i < end; ++i) {
        candidatos.push_back(i);
    }

    while (!candidatos.empty()) {
        int v = candidatos.back();
        candidatos.pop_back();

        bool podeAdicionar = true;

        // Verifica se o vértice pode ser adicionado à clique
        for (int u : cliqueMaxima) {
            if (grafo[u][v] == 0) {
                podeAdicionar = false;
                break;
            }
        }

        if (podeAdicionar) {
            cliqueMaxima.push_back(v);

            // Atualiza candidatos para incluir apenas vértices adjacentes aos já adicionados à clique
            std::vector<int> novosCandidatos;
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

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int numVertices;
    std::vector<std::vector<int>> grafo = LerGrafo("grafo.txt", numVertices);

    // Divide o número de vértices igualmente entre os processos
    int verticesPorProcesso = numVertices / size;
    int start = rank * verticesPorProcesso;
    int end = (rank == size - 1) ? numVertices : start + verticesPorProcesso;

    std::chrono::high_resolution_clock::time_point start_time;
    if (rank == 0) {
        start_time = std::chrono::high_resolution_clock::now();
    }

    // Cada processo encontra a clique máxima em sua parte do grafo
    std::vector<int> cliqueMaximaLocal = encontrarCliqueMaxima(grafo, numVertices, start, end);

    int tamanhoCliqueMaximaLocal = cliqueMaximaLocal.size();
    std::vector<int> tamanhosCliqueMaxima(size);

    // Cada processo envia o tamanho de sua clique máxima para o processo raiz
    MPI_Gather(&tamanhoCliqueMaximaLocal, 1, MPI_INT, tamanhosCliqueMaxima.data(), 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        // O processo raiz determina o índice do processo com a maior clique e recebe a clique completa
        int maxIdx = 0;
        for (int i = 1; i < size; i++) {
            if (tamanhosCliqueMaxima[i] > tamanhosCliqueMaxima[maxIdx]) {
                maxIdx = i;
            }
        }

        if (maxIdx != 0) {
            cliqueMaximaLocal.resize(tamanhosCliqueMaxima[maxIdx]);
            MPI_Recv(cliqueMaximaLocal.data(), tamanhosCliqueMaxima[maxIdx], MPI_INT, maxIdx, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
    } else if (tamanhoCliqueMaximaLocal == *max_element(tamanhosCliqueMaxima.begin(), tamanhosCliqueMaxima.end())) {
        // Cada processo envia sua clique máxima completa para o processo raiz
        MPI_Send(cliqueMaximaLocal.data(), tamanhoCliqueMaximaLocal, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    if (rank == 0) {
        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end_time - start_time;

        // Saída do resultado no processo raiz
        std::cout << "Clique máxima: ";
        for (int v : cliqueMaximaLocal) {
            std::cout << v << " ";
        }
        std::cout << std::endl;

        std::cout << "Tempo de execução: " << elapsed.count() << "s" << std::endl;
    }

    MPI_Finalize();
    return 0;
}
