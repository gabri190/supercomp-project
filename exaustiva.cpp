#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <set>
#include <algorithm>

std::set<std::set<int>> encontrarCliquesMaximais(const std::vector<std::vector<int>>& grafo, int numVertices) {
    std::set<std::set<int>> cliques;
    std::set<int> candidatos;

    for (int i = 0; i < numVertices; ++i) {
        candidatos.insert(i);
    }

    while (!candidatos.empty()) {
        int v = *candidatos.begin();
        std::set<int> cliqueAtual{v};
        candidatos.erase(v);

        auto candidatosRestantes = candidatos;
        for (int u : candidatosRestantes) {
            bool adjacenteATodos = true;

            for (int c : cliqueAtual) {
                if (grafo[u][c] == 0) {
                    adjacenteATodos = false;
                    break;
                }
            }

            if (adjacenteATodos) {
                cliqueAtual.insert(u);
            }
        }

        cliques.insert(cliqueAtual);
        std::set<int> intersecao;
        std::set_intersection(candidatos.begin(), candidatos.end(),
                              cliqueAtual.begin(), cliqueAtual.end(),
                              std::inserter(intersecao, intersecao.begin()));

        candidatos = intersecao;
    }

    return cliques;
}

std::vector<std::vector<int>> LerGrafo(const std::string& filename, int& numVertices) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        exit(EXIT_FAILURE);
    }

    file >> numVertices;
    std::vector<std::vector<int>> grafo(numVertices, std::vector<int>(numVertices, 0));

    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numVertices; ++j) {
            file >> grafo[i][j];
        }
    }

    return grafo;
}

int main() {
    int numVertices;
    std::vector<std::vector<int>> grafo = LerGrafo("grafo.txt", numVertices);

    auto start = std::chrono::high_resolution_clock::now();
    std::set<std::set<int>> cliquesMaximais = encontrarCliquesMaximais(grafo, numVertices);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Cliques maximais encontradas:" << std::endl;

    for (const auto& clique : cliquesMaximais) {
        std::cout << '[';
        for (auto v : clique) {
            std::cout << v + 1 << ' '; // +1 to convert to 1-based indexing
        }
        std::cout << ']' << std::endl;
    }

    // Print the maximum clique
    if (!cliquesMaximais.empty()) {
        auto maxClique = *std::max_element(cliquesMaximais.begin(), cliquesMaximais.end(),
                                           [](const auto& a, const auto& b) {
                                               return a.size() < b.size();
                                           });
        std::cout << "Clique máxima encontrada: [";
        for (auto v : maxClique) {
            std::cout << v + 1 << ' '; // +1 to convert to 1-based indexing
        }
        std::cout << ']' << std::endl;
    } else {
        std::cout << "Nenhuma clique encontrada." << std::endl;
    }

    std::cout << "Tempo de execução: " << elapsed.count() << "s" << std::endl;

    return 0;
}
