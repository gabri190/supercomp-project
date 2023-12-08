#include <iostream>
#include <vector>
#include <algorithm>
#include <omp.h>
#include "grafo.h"  

// Variáveis globais para armazenar cliques maximais
std::vector<std::vector<int>> cliquesMaximaisGlobal;
std::vector<int> cliqueMaximaGlobal;

// Função recursiva para encontrar cliques maximais a partir de um vértice
void EncontrarCliqueMaximalRecursivo(const std::vector<std::vector<int>>& grafo, std::vector<int>& cliqueAtual, std::vector<bool>& visitados, int vertice) {
    // Adiciona o vértice atual ao clique e marca como visitado
    cliqueAtual.push_back(vertice);
    visitados[vertice] = true;

    // Encontra os possíveis vizinhos que podem ser adicionados ao clique
    std::vector<int> possiveisVertices;
    for (int i = 0; i < grafo.size(); ++i) {
        if (!visitados[i]) {
            // Verifica se o vizinho pode ser adicionado ao clique
            bool podeAdicionar = true;
            for (int j : cliqueAtual) {
                if (grafo[i][j] == 0) {
                    podeAdicionar = false;
                    break;
                }
            }
            if (podeAdicionar) {
                possiveisVertices.push_back(i);
            }
        }
    }

    // Chama recursivamente a função para cada vizinho possível
    for (int vizinho : possiveisVertices) {
        EncontrarCliqueMaximalRecursivo(grafo, cliqueAtual, visitados, vizinho);
    }

    // Se não houver mais vizinhos e o clique atual tiver mais de um vértice, adiciona-o à lista global
    if (possiveisVertices.empty() && cliqueAtual.size() > 1) {
        #pragma omp critical
        {
            cliquesMaximaisGlobal.push_back(cliqueAtual);
            // Atualiza a clique máxima global se a clique atual for maior
            if (cliqueAtual.size() > cliqueMaximaGlobal.size()) {
                cliqueMaximaGlobal = cliqueAtual;
            }
        }
    }

    // Remove o vértice atual do clique e marca como não visitado
    cliqueAtual.pop_back();
    visitados[vertice] = false;
}

// Função para encontrar cliques maximais usando OpenMP
void EncontrarCliquesMaximaisOpenMP(const std::vector<std::vector<int>>& grafo, int numVertices) {
    // Executa em paralelo utilizando OpenMP
    #pragma omp parallel
    {
        // Cada thread tem sua própria cópia destas variáveis
        std::vector<bool> visitados(numVertices, false);
        std::vector<int> cliqueAtual;

        // Cada thread itera sobre uma parte diferente dos vértices sem esperar pelas outras
        #pragma omp for nowait
        for (int i = 0; i < numVertices; ++i) {
            EncontrarCliqueMaximalRecursivo(grafo, cliqueAtual, visitados, i);
        }
    }

    // Ordena as cliques maximais globalmente com base no tamanho
    std::sort(cliquesMaximaisGlobal.begin(), cliquesMaximaisGlobal.end(), [](const std::vector<int>& a, const std::vector<int>& b) {
        return a.size() > b.size(); // Ordena do maior para o menor
    });

    // Remove subconjuntos (cliques não maximais)
    cliquesMaximaisGlobal.erase(std::unique(cliquesMaximaisGlobal.begin(), cliquesMaximaisGlobal.end()), cliquesMaximaisGlobal.end());
}

int main(int argc, char* argv[]) {
    // Verifica se o número de argumentos está correto
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " <nome_do_arquivo_de_entrada>" << std::endl;
        return 1;
    }

    // Obtém o nome do arquivo de entrada a partir dos argumentos da linha de comando
    std::string nome_arquivo_entrada = argv[1];

    // Variáveis para armazenar o número de vértices e o grafo lido do arquivo
    int numVertices;
    std::vector<std::vector<int>> grafo = LerGrafo(nome_arquivo_entrada, numVertices);

    // Encontra cliques maximais usando OpenMP
    EncontrarCliquesMaximaisOpenMP(grafo, numVertices);

    // Saída do resultado
    std::cout << "Cliques maximais encontradas:" << std::endl;
    for (const auto& clique : cliquesMaximaisGlobal) {
        std::cout << "[";
        for (int i = 0; i < clique.size(); ++i) {
            std::cout << clique[i] + 1;  // Ajuste para índices baseados em 1
            if (i < clique.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]" << std::endl;
    }

    // Saída da clique máxima encontrada
    std::cout << "Clique máxima encontrada: [";
    for (int i = 0; i < cliqueMaximaGlobal.size(); ++i) {
        std::cout << cliqueMaximaGlobal[i] + 1;  // Ajuste para índices baseados em 1
        if (i < cliqueMaximaGlobal.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;

    return 0;
}
