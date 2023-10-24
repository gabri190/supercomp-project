// Paralelização e Distribuição do Processamento com MPI
// Nesta implementação, você deve dividir o problema em várias partes e distribuí-las para diferentes processadores usando a 
// biblioteca MPI (Message Passing Interface). Cada processador será responsável por encontrar cliques em uma parte do grafo, e 
// os resultados serão combinados no final para encontrar todas as cliques no grafo.
//solucao aqui 

// Paralelização e Distribuição do Processamento com MPI
// Nesta implementação, você deve dividir o problema em várias partes e distribuí-las para diferentes processadores usando a 
// biblioteca MPI (Message Passing Interface). Cada processador será responsável por encontrar cliques em uma parte do grafo, e 
// os resultados serão combinados no final para encontrar todas as cliques no grafo.
//solucao aqui 
#include <mpi.h>
#include "grafo.h"
#include <iostream>
#include <vector>

std::vector<int> encontrarCliqueMaxima(const std::vector<std::vector<int>>& grafo, int numVertices, int start, int end) {
    std::vector<int> cliqueMaxima;
    std::vector<int> candidatos;

    for(int i = start; i < end; ++i) {
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


int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int numVertices;
    std::vector<std::vector<int>> grafo = LerGrafo("grafo.txt", numVertices);

    // Divida o espaço de busca entre os processos.
    int verticesPorProcesso = numVertices / size;
    int start = rank * verticesPorProcesso;
    int end = (rank == size - 1) ? numVertices : start + verticesPorProcesso;

    // Encontre a clique máxima localmente em cada processo.
    std::vector<int> cliqueMaximaLocal = encontrarCliqueMaxima(grafo, numVertices, start, end);

    // Comunique os tamanhos das cliques máximas locais ao processo 0.
    int tamanhoCliqueMaximaLocal = cliqueMaximaLocal.size();
    std::vector<int> tamanhosCliqueMaxima(size);
    MPI_Gather(&tamanhoCliqueMaximaLocal, 1, MPI_INT, tamanhosCliqueMaxima.data(), 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Determine a clique máxima global no processo 0.
    if(rank == 0) {
        int maxIdx = 0;
        for(int i = 1; i < size; i++) {
            if(tamanhosCliqueMaxima[i] > tamanhosCliqueMaxima[maxIdx]) {
                maxIdx = i;
            }
        }

        // Se a clique máxima não foi encontrada pelo processo 0, receba-a do processo que a encontrou.
        if(maxIdx != 0) {
            cliqueMaximaLocal.resize(tamanhosCliqueMaxima[maxIdx]);
            MPI_Recv(cliqueMaximaLocal.data(), tamanhosCliqueMaxima[maxIdx], MPI_INT, maxIdx, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
    }
    // Se um processo diferente do 0 encontrou a clique máxima, envie-a para o processo 0.
    else if(tamanhoCliqueMaximaLocal == *max_element(tamanhosCliqueMaxima.begin(), tamanhosCliqueMaxima.end())) {
        MPI_Send(cliqueMaximaLocal.data(), tamanhoCliqueMaximaLocal, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    // O processo 0 imprime a clique máxima global.
    if(rank == 0) {
        std::cout << "Clique máxima: ";
        for(int v : cliqueMaximaLocal) {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }

    MPI_Finalize();
    return 0;
}
