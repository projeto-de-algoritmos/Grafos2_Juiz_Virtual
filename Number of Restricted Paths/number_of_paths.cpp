#include <vector>
#include <unordered_map>
#include <queue>
#include <climits>

class Solution {
public:
    int countRestrictedPaths(int n, std::vector<std::vector<int>>& edges) {
        if (n == 1) return 0;

        // Cria um mapa não ordenado para representar o grafo com nós e arestas ponderadas
        std::unordered_map<int, std::vector<std::pair<int, int>> > graph;

        // Preenche o grafo com arestas e pesos
        for (auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];
            graph[u].push_back(std::make_pair(w, v));
            graph[v].push_back(std::make_pair(w, u));
        }

        // Calcula as menores distâncias de nó n para todos os outros nós
        std::vector<long long> dist = dijkstra(n, graph);
        
        // Vetor para armazenar resultados da programação dinâmica
        std::vector<int> dp(n + 1, -1);

        // Encontra o número de caminhos restritos de 1 até n
        return dfs(1, n, dist, graph, dp); // Passa 'graph' e 'dp' para dfs
    }

private:
    // Algoritmo de Dijkstra para calcular as menores distâncias
    std::vector<long long> dijkstra(int n, std::unordered_map<int, std::vector<std::pair<int, int>>>& graph) {
        std::vector<long long> dist(n + 1, LLONG_MAX); // Inicializa as distâncias com valores máximos
        dist[n] = 0; // A distância de n para ele mesmo é 0
        std::priority_queue<std::pair<long long, int>> minHeap; // Usa uma fila de prioridade para travessia eficiente
        minHeap.push(std::make_pair(0, n)); // Começa de n

        while (!minHeap.empty()) {
            long long d = -minHeap.top().first; // Extrai a distância (negativa porque priority_queue é um max-heap)
            int u = minHeap.top().second; // Extrai o nó
            minHeap.pop();

            if (d != dist[u]) continue; // Ignora se um caminho mais curto já foi encontrado

            for (auto& edge : graph[u]) {
                int w = edge.first; // Peso da aresta
                int v = edge.second; // Nó vizinho
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w; // Atualiza a distância se um caminho mais curto for encontrado
                    minHeap.push(std::make_pair(-dist[v], v)); // Adiciona o vizinho à fila de prioridade
                }
            }
        }

        return dist;
    }

    // Busca em profundidade para contar o número de caminhos restritos
    int dfs(int src, int n, std::vector<long long>& dist, std::unordered_map<int, std::vector<std::pair<int, int>>>& graph, std::vector<int>& dp) {
        if (src == n) return 1; // Encontrou um caminho para chegar ao destino
        if (dp[src] != -1) return dp[src]; // Verifica se o resultado já foi calculado

        int ans = 0;

        for (auto& edge : graph[src]) { // Usa 'graph' dos parâmetros
            int w = edge.first; // Peso da aresta
            int nei = edge.second; // Nó vizinho
            if (dist[src] > dist[nei]) {
                ans = (ans + dfs(nei, n, dist, graph, dp)) % 1000000007; // Explora o vizinho recursivamente
            }
        }

        dp[src] = ans; // Armazena o resultado para evitar repetições
        return ans;
    }
};
