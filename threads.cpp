#include <iostream>
#include <vector>
#include <algorithm>
#include <omp.h>
#include "grafo.h"

std::vector<std::vector<int>> cliquesMaximaisGlobal;
std::vector<int> cliqueMaximaGlobal;

void EncontrarCliqueMaximalRecursivo(const std::vector<std::vector<int>>& grafo, std::vector<int>& cliqueAtual, std::vector<bool>& visitados, int vertice) {
    cliqueAtual.push_back(vertice);
    visitados[vertice] = true;

    std::vector<int> possiveisVertices;
    for (int i = 0; i < grafo.size(); ++i) {
        if (!visitados[i]) {
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

    for (int vizinho : possiveisVertices) {
        EncontrarCliqueMaximalRecursivo(grafo, cliqueAtual, visitados, vizinho);
    }

    if (possiveisVertices.empty() && cliqueAtual.size() > 1) {
        #pragma omp critical
        {
            cliquesMaximaisGlobal.push_back(cliqueAtual);
            if (cliqueAtual.size() > cliqueMaximaGlobal.size()) {
                cliqueMaximaGlobal = cliqueAtual;
            }
        }
    }

    cliqueAtual.pop_back();
    visitados[vertice] = false;
}

void EncontrarCliquesMaximaisOpenMP(const std::vector<std::vector<int>>& grafo, int numVertices) {
    #pragma omp parallel
    {
        std::vector<bool> visitados(numVertices, false);
        std::vector<int> cliqueAtual;

        #pragma omp for nowait
        for (int i = 0; i < numVertices; ++i) {
            EncontrarCliqueMaximalRecursivo(grafo, cliqueAtual, visitados, i);
        }
    }

    // Ordena as cliques maximais globalmente com base no tamanho
    std::sort(cliquesMaximaisGlobal.begin(), cliquesMaximaisGlobal.end(), [](const std::vector<int>& a, const std::vector<int>& b) {
        return a.size() > b.size(); // Ordena do maior para o menor
    });

    // Removendo subconjuntos (cliques não maximais)
    cliquesMaximaisGlobal.erase(std::unique(cliquesMaximaisGlobal.begin(), cliquesMaximaisGlobal.end()), cliquesMaximaisGlobal.end());
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " <nome_do_arquivo_de_entrada>" << std::endl;
        return 1;
    }

    std::string nome_arquivo_entrada = argv[1];
    int numVertices;
    std::vector<std::vector<int>> grafo = LerGrafo(nome_arquivo_entrada, numVertices);

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
