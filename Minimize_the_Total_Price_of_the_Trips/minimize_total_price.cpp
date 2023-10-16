#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

class Solution {
private:
    // Estrutura para representar um par (nó, distância)
    struct Pair {
        int at;
        int dist;
        
        Pair(int at, int dist) : at(at), dist(dist) {}
        
        bool operator<(const Pair& other) const {
            return dist > other.dist;
        }
    };
    
    // Tamanho máximo para o grafo
    static const int MAX = 51;
    // Valor infinito para distâncias
    const int INF = 1e9;

    // Lista de adjacência para representar o grafo
    vector<int> graph[MAX];
    // Vetor para armazenar distâncias
    vector<int> distance;
    // Vetor para rastrear o nó pai de cada nó na árvore de busca
    vector<int> parent;
    // Matriz para memorização de soluções intermediárias (programação dinâmica)
    vector<vector<int>> dp;
    
public:
    int minimumTotalPrice(int n, vector<vector<int>>& edges, vector<int>& price, vector<vector<int>>& trips) {
        // Limpa o grafo
        for (int i = 0; i < n; i++) {
            graph[i].clear();
        }
        
        // Constrói o grafo a partir das arestas fornecidas
        for (const auto& e : edges) {
            graph[e[0]].push_back(e[1]);
            graph[e[1]].push_back(e[0]);
        }
        
        // Vetor para rastrear a frequência de nós visitados
        vector<int> freq(n, 0);
        
        // Calcula o caminho mais curto e atualiza a frequência para as viagens especificadas
        for (const auto& trip : trips) {
            shortestPath(price, freq, trip[0], trip[1]);
        }
        
        // Inicializa a matriz de programação dinâmica com valores -1
        dp.assign(n, vector<int>(2, -1));
        
        // Retorna o mínimo entre duas possíveis soluções iniciais
        return min(dfs(freq, price, 0, -1, 1), dfs(freq, price, 0, -1, 0));
    }

private:
    // Função recursiva para calcular o custo mínimo
    int dfs(vector<int>& freq, vector<int>& price, int currNode, int parent, int halved) {
        // Se já calculamos a solução para este nó com o mesmo estado, retornamos o valor memorizado
        if (dp[currNode][halved] != -1) {
            return dp[currNode][halved];
        }
        
        // Cálculo do custo total
        int total = freq[currNode] * (halved == 1 ? price[currNode] / 2 : price[currNode]);
        
        // Percorre os nós adjacentes
        for (int adj : graph[currNode]) {
            if (adj != parent) {
                if (halved == 1) {
                    total += dfs(freq, price, adj, currNode, 1 - halved);
                } else {
                    total += min(dfs(freq, price, adj, currNode, halved), dfs(freq, price, adj, currNode, 1 - halved));
                }
            }
        }
        
        // Armazena o valor calculado na matriz de programação dinâmica
        dp[currNode][halved] = total;
        
        return total;
    }

    // Função para calcular o caminho mais curto entre dois nós
    void shortestPath(vector<int>& price, vector<int>& freq, int node1, int node2) {
        // Se os nós de início e fim forem iguais, aumentamos a frequência do nó
        if (node1 == node2) {
            freq[node1]++;
            return;
        }

        // Inicializa as distâncias com INF e configuração da fila de prioridade (min-heap)
        distance.assign(MAX, INF);
        priority_queue<Pair> pq;
        
        distance[node1] = price[node1];
        parent.assign(MAX, -1);
        pq.push(Pair(node1, distance[node1]));
        
        // Algoritmo de busca do caminho mais curto (Dijkstra)
        while (!pq.empty()) {
            Pair currPair = pq.top();
            pq.pop();
            
            int at = currPair.at;
            int dist = currPair.dist;
            
            // Se atingirmos o nó de destino, rastreamos o caminho e atualizamos a frequência
            if (at == node2) {
                int curr = node2;
                while (curr != node1) {
                    freq[curr]++;
                    curr = parent[curr];
                }
                freq[curr]++;
            }
            
            // Ignora nós onde a distância já é maior
            if (distance[at] < dist) {
                continue;
            }
            
            // Relaxamento das arestas
            for (int adj : graph[at]) {
                if (distance[adj] > dist + price[adj]) {
                    distance[adj] = dist + price[adj];
                    pq.push(Pair(adj, distance[adj]));
                    parent[adj] = at;
                }
            }
        }
    }
};
