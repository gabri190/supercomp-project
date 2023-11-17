#include <iostream>
#include <vector>
#include <algorithm>
#include <omp.h>
#include "grafo.h"

std::vector<std::vector<int>> cliquesMaximaisGlobal;
std::vector<int> cliqueMaximaGlobal;
bool stop = false;

void EncontrarCliqueMaximalRecursivo(int vertice, const std::vector<std::vector<int>>& grafo, std::vector<int>& cliqueAtual) {
    cliqueAtual.push_back(vertice);

    for (int vizinho : cliqueAtual) {
        if (grafo[vertice][vizinho] == 0) {
            return; // Não é um clique válido
        }
    }

    std::vector<int> vizinhosNaoClicados;
    for (int i = 0; i < grafo.size(); ++i) {
        if (std::find(cliqueAtual.begin(), cliqueAtual.end(), i) == cliqueAtual.end()) {
            vizinhosNaoClicados.push_back(i);
        }
    }

    for (int vizinho : vizinhosNaoClicados) {
        EncontrarCliqueMaximalRecursivo(vizinho, grafo, cliqueAtual);
    }
}

bool ComparaCliques(const std::vector<int>& a, const std::vector<int>& b) {
    return a.size() < b.size();
}

void AdicionarCliqueMaximal(const std::vector<int>& cliqueAtual) {
    #pragma omp critical
    {
        bool cliqueExiste = false;
        for (const auto& clique : cliquesMaximaisGlobal) {
            if (clique.size() == cliqueAtual.size() && std::is_permutation(cliqueAtual.begin(), cliqueAtual.end(), clique.begin())) {
                cliqueExiste = true;
                break;
            }
        }

        if (!cliqueExiste) {
            cliquesMaximaisGlobal.push_back(cliqueAtual);
        }
    }
}

void EncontrarCliquesMaximaisOpenMP(const std::vector<std::vector<int>>& grafo, int numVertices) {
    #pragma omp parallel for
    for (int i = 0; i < numVertices; ++i) {
        std::vector<int> cliqueAtual;
        EncontrarCliqueMaximalRecursivo(i, grafo, cliqueAtual);

        // Verifica se a clique atual é maximal
        bool ehMaximal = true;
        for (const auto& clique : cliquesMaximaisGlobal) {
            if (std::includes(clique.begin(), clique.end(), cliqueAtual.begin(), cliqueAtual.end())) {
                ehMaximal = false;
                break;
            }
        }

        if (ehMaximal) {
            // Adiciona a clique atual às cliques maximais globais
            AdicionarCliqueMaximal(cliqueAtual);
        }

        // Atualiza a clique máxima global
        #pragma omp critical
        {
            if (cliqueAtual.size() > cliqueMaximaGlobal.size()) {
                cliqueMaximaGlobal = cliqueAtual;
            }
        }
    }

    // Ordena as cliques maximais globalmente com base no tamanho
    #pragma omp barrier
    #pragma omp single
    std::sort(cliquesMaximaisGlobal.begin(), cliquesMaximaisGlobal.end(), ComparaCliques);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " <nome_do_arquivo_de_entrada>" << std::endl;
        return 1;
    }

    // Nome do arquivo de entrada passado como argumento
    std::string nome_arquivo_entrada = argv[1];

    // Leitura do grafo
    int numVertices;
    std::vector<std::vector<int>> grafo = LerGrafo(nome_arquivo_entrada, numVertices);

    // Executa a busca paralela usando OpenMP
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

    std::cout << "Clique máxima encontrada:";
    std::cout << "[";
    for (int i = 0; i < cliqueMaximaGlobal.size(); ++i) {
        std::cout << cliqueMaximaGlobal[i] + 1;  // Ajuste para índices baseados em 1
        if (i < cliqueMaximaGlobal.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;

    return 0;
}
