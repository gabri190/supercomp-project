# Projeto SuperComputação 2023.2
## Análise de Redes Sociais: encontrando a clique máxima em um grafo.

![Exemplo Clique](https://upload.wikimedia.org/wikipedia/commons/thumb/d/d0/VR_complex.svg/1200px-VR_complex.svg.png)


A análise de redes sociais (ARS) é uma abordagem oriunda de áreas tais como Sociologia, Psicologia Social e Antropologia. Tal abordagem estuda as ligações relacionais (*relational tie*) entre atores sociais. Os atores na ARS podem ser tanto pessoas e empresas, analisadas como unidades individuais, quanto unidades sociais coletivas como, por exemplo, departamentos dentro de uma organização, agências de serviço público em uma cidade, estados-nações de um continente, dentre outras. A ARS difere fundamentalmente de outros estudos pelo fato de que sua ênfase não é nos atributos (características) dos atores, mas nas ligações entre eles.


A idéia de uma clique em um grafo é relativamente simples. No nível mais geral, uma clique é um subconjunto de uma rede no qual os atores são mais próximos entre si do que com outros membros da rede. Em termo de laços de amizade, por exemplo, não é incomum encontrar grupos humanos que formam cliques baseando-se em idade, gênero, raça, etnia, religião, ideologia, e muitas coisas coisas. Uma clique é, portanto, um conjunto de vértices em um grafo em que cada par de vértices está diretamente conectado por uma aresta.

Encontrar a clique máxima em um grafo é uma tarefa computacionalmente desafiadora devido à natureza combinatória do problema.  A dificuldade computacional surge da necessidade de explorar todas as combinações possíveis de vértices para identificar a maior clique, o que se torna exponencial em relação ao número de vértices. Isso resulta em uma complexidade computacional alta, mesmo para grafos moderadamente grandes.

A importância de estudar cliques está notavelmente presente na análise de redes sociais, onde as cliques representam grupos coesos de indivíduos que compartilham interesses, amizades ou conexões em comum. A identificação de cliques ajuda a entender a estrutura de uma rede social, identificar influenciadores e grupos de afinidade, além de auxiliar na detecção de comunidades e na análise de dinâmicas sociais.

As cliques são importantes, pois além de desenvolver em seus membros comportamentos homogêneos, elas têm, por definição, grande proximidade, aumentando a velocidade das trocas. Assim, informações dirigidas a uma clique são rapidamente absorvidas pelos seus membros, que tendem a percebê-las de forma semelhante. Isso é importante, por exemplo, em estratégias de segmentação.


Portanto, a resolução eficiente do problema da clique máxima tem aplicações valiosas em áreas que vão desde a ciência da computação até a análise de dados em redes sociais.

## SUA TAREFA: Encontrar a clique máxima em um grafo.

Seu programa deve receber um grafo a partir de um input de texto (abaixo você vai encontrar o código gerador do input). A partir da leitura do arquivo, você deve armazenar o grafo computacionalmente (matriz de adjacência, por exemplo). E com isso, você deverá executar três implementações:
1. **Abordagem Exaustiva**

A exaustão é uma abordagem que seleciona iterativamente os vértices para formar um clique, geralmente começando com um vértice e adicionando outros que tenham o maior número de vizinhos já na clique. Aqui está um pseudo-código simplificado para detectar cliques em um grafo usando essa abordagem. ATENÇÃO: esse pseudo-codigo **não** é a solução completa dessa abordagem. Você pode se inspirar nele para compreender como resolver o problema, mas é parte de sua tarefa desenvolver a solução.

```
Função EncontrarCliqueMaxima(grafo, numVertices)
    cliqueMaxima = ListaVazia()
    candidatos = ListaDeNós()  # Inicialmente, todos os nós são candidatos

    Para cada i de 0 até numVertices - 1 Faça
        Adicione i à lista de candidatos

    Enquanto candidatos não estiver vazia Faça
        v = Último elemento de candidatos
        Remova o último elemento de candidatos

        podeAdicionar = Verdadeiro

        Para cada u em cliqueMaxima Faça
            Se grafo[u][v] == 0 Então
                podeAdicionar = Falso
                Pare o loop
            Fim Se
        Fim Para

        Se podeAdicionar for Verdadeiro Então
            Adicione v a cliqueMaxima
            novosCandidatos = ListaDeNós()

            Para cada u em candidatos Faça
                adjacenteATodos = Verdadeiro

                Para cada c em cliqueMaxima Faça
                    Se grafo[u][c] == 0 Então
                        adjacenteATodos = Falso
                        Pare o loop
                    Fim Se
                Fim Para

                Se adjacenteATodos for Verdadeiro Então
                    Adicione u a novosCandidatos
                Fim Se
            Fim Para

            candidatos = novosCandidatos
        Fim Se
    Fim Enquanto

    Retorne cliqueMaxima
Fim Função


```

Implemente o código em C++.

Aproveite para pensar se é possível adotar alguma heurística. Por exemplo, ordenar os nós em função do grau de adjacência, ajuda?


**Sua segunda tarefa**: Até qual tamanho de problema você conseguiu obter um resultado em tempo hábil (aprox. 15 min)? Você deve apresentar um pseudo-codigo de uma heurística para otimizar essa tarefa exaustiva. É possível implementar alguma poda? Algum critério que evite calcular um nó, dado que você já descobriu uma clique maior?

2. **Implementação com Threads OpenMP**

A implementação de uma solução com OpenMP para encontrar cliques em um grafo usando a heurística gulosa envolve a paralelização das iterações do algoritmo em diferentes threads. O OpenMP simplifica a criação de threads e a coordenação entre elas.


Nessa implementação você deve apresentar o código-fonte modificado, justificar a alteração feita, e mostrar também o speed up obtido. Faça uso de gráficos e tabelas para mostrar que sua implementação em openMP valeu a pena. Observe que mesmo assim você não vai conseguir resolver exaustivamente o problema, mas o tamanho do grafo será maior, e o tempo de processamento para um mesmo tamanho deve ser preferencialmente menor.


3. **Paralelização e Distribuição do Processamento com MPI**

Nesta implementação, você deve dividir o problema em várias partes e distribuí-las para diferentes processadores usando a biblioteca MPI (*Message Passing Interface*). Cada processador será responsável por encontrar cliques em uma parte do grafo, e os resultados serão combinados no final para encontrar todas as cliques no grafo.

Como apresentar seus resultados:
- Você deverá focar em comparar suas implementações em relação ao speedup. Aumente o tamanho do grafo e das arestas, e busque determinar a clique máxima.

Códigos-fonte de apoio

1. Código-fonte de geração do grafo (em Python)
 - Codigo disponível em input.py
2. Trecho de código-fonte para leitura do grafo e armazenamento como matriz de adjacência
 - Codigo disponível em grafo.cpp
3. Verificar (em Python) se seu programa encontrou a clique correta. Para isso, use a implementação abaixo, ela já está adaptada para ler nosso arquivo de input, ignorando a primeira linha.
 - Codigo disponível em verificacao.py

### Como Compilar 

#### exaustiva.cpp
- compilação

``` shell
g++ -o exaustiva exaustiva.cpp grafo.cpp -std=c++11

```
- gerando executavel
```shell

./exaustiva grafo.txt
```
Se quiser pode colocar numeros ao lado do nome exaustiva pra indicar o numero de vertices do grafo

#### threads.cpp
- compilação

``` shell
g++ -o threads5 threads.cpp grafo.cpp -fopenmp -O3

```
- gerando executavel
```shell

./threads grafo.txt
```
Se quiser pode colocar numeros ao lado do nome exaustiva pra indicar o numero de vertices do grafo

#### paralelizacao.cpp
- a compilação e execucao serão feitas no cluster de cada grupo da disciplina

Para os três casos serão discutidos os resultados a seguir na seção de resultados 
para diferentes de grafos.

### Resultados

#### exaustiva

- Grafo de 5 vértices:

![image](https://github.com/gabri190/supercomp-project/assets/72319195/3aba2896-be8a-4be5-94db-b97735188d2b)

- Grafo de 10 vértices:

  ![image](https://github.com/gabri190/supercomp-project/assets/72319195/e62f5be2-bff7-4f00-bc85-e752dad4dd13)

- Grafo de 50 vértices:

![image](https://github.com/gabri190/supercomp-project/assets/72319195/b37dd0b1-2de7-499c-b58b-ef7974febfe1)

- Grafo de 100 vértices

![image](https://github.com/gabri190/supercomp-project/assets/72319195/3800bf32-42a7-4267-a698-1e76e38b4f57)

  
#### threads

- Grafo de 5 vértices:

![image](https://github.com/gabri190/supercomp-project/assets/72319195/53b8f62d-6670-497b-b9d6-1dc52581c7d8)

- Grafo de 10 vértices:

![image](https://github.com/gabri190/supercomp-project/assets/72319195/7be12b76-a5f1-46f4-83e5-721572991292)

- Grafo de 50 vértices:

![image](https://github.com/gabri190/supercomp-project/assets/72319195/6ffd03b5-f570-4eea-a413-339e9cfa5594)

- Grafo de 100 vértices:

![image](https://github.com/gabri190/supercomp-project/assets/72319195/28dd6700-d615-43aa-ac79-7ab605db8b97)

### Comparações em relação a speedups:

![image](https://github.com/gabri190/supercomp-project/assets/72319195/82146070-88a9-46e5-83f7-8444f2a866f0)


