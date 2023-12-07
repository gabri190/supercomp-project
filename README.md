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
g++ -o exaustiva{id} exaustiva.cpp grafo.cpp -std=c++11

```
- gerando executavel
```shell

./exaustiva{id} grafo.txt
```
Se quiser pode colocar numeros ao lado do nome exaustiva pra indicar o numero de vertices do grafo

#### threads.cpp
- compilação

``` shell
g++ -o threads{id} threads.cpp grafo.cpp -fopenmp -O3

```
- gerando executavel
```shell

./threads{id} grafo.txt
```
- Onde o id é o número de vértices do grafo que você pode alterar no input.py

#### paralelizacao.cpp
- a compilação e execucao serão feitas no cluster de cada grupo da disciplina

- compilação

``` shell
mpic++ paralelizacao.cpp -o mpi{id} 

```
- submetendo job

```shell
sbatch paralel.slurm
```
- pegando output

```shell
cat slurm-{jobid}.out
```

Não esquece de criar um arquivo.slurm e modificar o executavel como no exemplo a seguir:

```shell
#!/bin/bash
#SBATCH --job-name=projeto_gabriel
#SBATCH --nodes=1
#SBATCH --partition=express
#SBATCH --mem=500M
echo Output do Job $SLURM_JOB_ID
./executavel
```

Para os três casos serão discutidos os resultados a seguir na seção de resultados 
para diferentes de grafos.

### Resultados

#### exaustiva

- Grafo de 5 vértices:

![image](https://github.com/gabri190/supercomp-project/assets/72319195/7f83db73-f68f-45d9-933d-2a6cbe8383a7)

![image](https://github.com/gabri190/supercomp-project/assets/72319195/e33848f4-76f9-4be4-8867-0d306833a460)

- Grafo de 10 vértices:

![image](https://github.com/gabri190/supercomp-project/assets/72319195/07b7fae7-0f8d-4bee-8169-5c9cf5ca39de)

![image](https://github.com/gabri190/supercomp-project/assets/72319195/8c013453-1c1d-49fc-99dd-99b6c3b236f7)

- Grafo de 15 vértices:

![image](https://github.com/gabri190/supercomp-project/assets/72319195/06faa35b-40c8-4d7a-9082-5f8e30fa3dbb)

![image](https://github.com/gabri190/supercomp-project/assets/72319195/decb5a25-fba2-4084-a08e-4ffc5ce89a57)

- Grafo de 20 vértices
  
![image](https://github.com/gabri190/supercomp-project/assets/72319195/64b35175-aa9e-4e98-b43c-f48edf472ad4)

![image](https://github.com/gabri190/supercomp-project/assets/72319195/feb851d1-ac14-4b09-8804-0d3da385b82c)

- Grafo de 25 vértices

![image](https://github.com/gabri190/supercomp-project/assets/72319195/c607947b-8427-40c9-ae02-3d07ee811b0b)

![image](https://github.com/gabri190/supercomp-project/assets/72319195/ed536218-df46-41ea-9f6f-895448d5df8d)
  
Para cada tamanho de grafo as primeiras imagens são o arquivo de verificação.py e as imagens subquentes são o resultado do arquivo exaustiva.cpp 

#### threads

- Grafo de 5 vértices:

![image](https://github.com/gabri190/supercomp-project/assets/72319195/95d6ceb4-7269-499d-ab04-b5ec15f44165)

- Grafo de 10 vértices:

![image](https://github.com/gabri190/supercomp-project/assets/72319195/88fd52b9-957c-42b4-bf6b-6451c80f6fae)

- Grafo de 15 vértices:

![image](https://github.com/gabri190/supercomp-project/assets/72319195/f5de4c52-e704-4a06-93e5-d9932df29dc3)

- Grafo de 20 vértices:

![image](https://github.com/gabri190/supercomp-project/assets/72319195/a2ccac2c-7ca2-4b16-beb1-ba065d49de8a)

- Grafo de 25 vértices:

![image](https://github.com/gabri190/supercomp-project/assets/72319195/8c880676-a9a1-4a2f-be89-4d6db30ddeb7)

### MPI-paralelizacao

Para cada tamanho de grafo com os vértices a primeira imagem e a clique máxima da busca_exaustiva(serial) e a 
segunda imagem e a paralelização MPI com o tempo da execução

- Grafo de 5 vértices:

![image](https://github.com/gabri190/supercomp-project/assets/72319195/1139471c-83bf-4adb-84c1-5f03ad65850f)

![image](https://github.com/gabri190/supercomp-project/assets/72319195/a55b4dd0-209e-4dda-95c8-347b3442be27)

- Grafo de 10 vértices:

![image](https://github.com/gabri190/supercomp-project/assets/72319195/10a3867c-0d77-4608-805f-6a960de93314)

![image](https://github.com/gabri190/supercomp-project/assets/72319195/4a4470ae-3644-44df-99e7-3eb9c434de81)


- Grafo de 15 vértices:

![image](https://github.com/gabri190/supercomp-project/assets/72319195/7cf2dc01-f7e3-449f-a929-c621d84d176b)

![image](https://github.com/gabri190/supercomp-project/assets/72319195/3f3e3582-468a-4622-8b17-168ffeb2acdd)

- Grafo de 20 vértices
  
![image](https://github.com/gabri190/supercomp-project/assets/72319195/b7aa8327-fa5d-4583-abab-9cf3dcc49b93)

![image](https://github.com/gabri190/supercomp-project/assets/72319195/b7273af2-5ae6-45fb-8191-00204b6f4265)

- Grafo de 25 vértices

![image](https://github.com/gabri190/supercomp-project/assets/72319195/a439ceef-f7e5-4446-8777-44c5cbc5a640)

![image](https://github.com/gabri190/supercomp-project/assets/72319195/10d639f0-918c-4363-a8b8-b6209adbb7dd)
  

### Comparações em relação a speedups:

- Serial e OpenMp

![newplot](https://github.com/gabri190/supercomp-project/assets/72319195/add491f3-a001-48fc-8238-0d968fb8142f)

No primeiro o tempo foi parecido mas o OpenMp ja devia ser mais rápido o que aconteceu para alguns vértices

- Serial e MPI
 
![newplot](https://github.com/gabri190/supercomp-project/assets/72319195/5511cbb4-7019-418e-9deb-1f42a22c28b5)

No segundo caso e muito rápido o MPI e por isso praticamente impercepitível em relação a tempo.
