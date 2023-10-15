#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {
public:
    // Estrutura para representar uma aresta com seu identificador e distância.
    struct Edge {
        int id;
        int dist;

        Edge(int i, int d) : id(i), dist(d) {}

        // Sobrecarga do operador ">" para que a fila de prioridade funcione corretamente.
        bool operator>(const Edge& other) const {
            return dist > other.dist;
        }
    };

    // Função para encontrar a menor soma das distâncias entre pontos.
    int minCostConnectPoints(vector<vector<int>>& points) {
        if (points.empty()) return 0;

        int ans = 0;
        priority_queue<Edge, vector<Edge>, greater<Edge>> pq; // Fila de prioridade para manter as arestas ordenadas por distância.
        set<int> mstPoints; // Conjunto para manter os pontos já incluídos na árvore geradora mínima.

        pq.push(Edge(0, 0)); // Começamos a partir do primeiro ponto.

        while (!pq.empty()) {
            Edge edge = pq.top();
            pq.pop();

            int id = edge.id;
            int dist = edge.dist;

            if (mstPoints.find(id) != mstPoints.end()) continue; // Verificamos se o ponto já está na árvore.

            mstPoints.insert(id);
            ans += dist; // Adicionamos a distância à resposta.

            // Iteramos sobre os pontos não incluídos na árvore e calculamos suas distâncias.
            for (int i = 0; i < points.size(); i++) {
                if (mstPoints.find(i) != mstPoints.end()) continue;

                int newDist = getDist(points, id, i);
                pq.push(Edge(i, newDist)); // Adicionamos a nova aresta à fila de prioridade.
            }
        }

        return ans; 
    }

    // Função para calcular a distância entre dois pontos.
    int getDist(vector<vector<int>>& points, int p, int q) {
        return abs(points[p][0] - points[q][0]) + abs(points[p][1] - points[q][1]);
    }
};
