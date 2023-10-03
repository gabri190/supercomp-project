// Implementação com Threads OpenMP
// A implementação de uma solução com OpenMP para encontrar cliques em um grafo usando a heurística gulosa envolve a 
// paralelização das iterações do algoritmo em diferentes threads. O OpenMP simplifica a criação de threads e a coordenação 
// entre elas.

// Nessa implementação você deve apresentar o código-fonte modificado, justificar a alteração feita, e mostrar também o 
// speed up obtido. Faça uso de gráficos e tabelas para mostrar que sua implementação em openMP valeu a pena. Observe que 
// mesmo assim você não vai conseguir resolver exaustivamente o problema, mas o tamanho do grafo será maior, e o tempo de 
// processamento para um mesmo tamanho deve ser preferencialmente menor.
//solucao aqui
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <mpi.h>

#define MAX_VERTICES 1000

int graph[MAX_VERTICES][MAX_VERTICES]; // Matriz de adjacência
int numVertices; // Número de vértices no grafo
int maxCliqueSize; // Tamanho máximo da clique
int clique[MAX_VERTICES]; // Conjunto de vértices na clique máxima

// Função para verificar se um vértice pode ser adicionado à clique atual
bool isSafe(int v, int clique[], int size) {
    for (int i = 0; i < size; i++) {
        if (graph[v][clique[i]])
            return false;
    }
    return true;
}

// Função recursiva para encontrar a clique máxima em uma parte do grafo
void findMaxClique(int clique[], int size, int v) {
    if (v == numVertices) {
        if (size > maxCliqueSize) {
            maxCliqueSize = size;
            // Atualizar a clique máxima encontrada
            for (int i = 0; i < size; i++) {
                clique[i] = clique[i];
            }
        }
        return;
    }

    // Verifique se o vértice pode ser adicionado à clique
    if (isSafe(v, clique, size)) {
        // Inclua o vértice na clique e explore recursivamente
        clique[size] = v;
        findMaxClique(clique, size + 1, v + 1);
    }

    // Explore recursivamente sem incluir o vértice na clique
    findMaxClique(clique, size, v + 1);
}

int main(int argc, char *argv[]) {
    // Inicialize o ambiente MPI
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Distribua o trabalho entre os processadores aqui
    int verticesPerProcessor = numVertices / size;
    int startVertex = rank * verticesPerProcessor;
    int endVertex = (rank == size - 1) ? numVertices : startVertex + verticesPerProcessor;

    maxCliqueSize = 0;

    // Cada processador encontra a clique máxima em sua parte do grafo
    int clique_private[MAX_VERTICES];
    for (int i = startVertex; i < endVertex; i++) {
        findMaxClique(clique_private, 0, i);
    }

    // Combina os resultados para encontrar a clique máxima global
    // Use funções MPI para fazer isso

    // Imprima o resultado aqui

    // Finalize o ambiente MPI
    MPI_Finalize();

    return 0;
}
