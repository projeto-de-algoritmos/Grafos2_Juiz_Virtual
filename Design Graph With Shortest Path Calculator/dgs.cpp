#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

class Graph {
public:
    vector<vector<pair<int,int>>> graph;

    Graph(int n, vector<vector<int>>& edges) {
        // Inicializa o grafo com n nós
        graph.resize(n,vector<pair<int,int>>());

        // Adiciona arestas a partir do vetor de entrada
        for(int i=0;i<edges.size();i++){
            graph[edges[i][0]].push_back({edges[i][1],edges[i][2]});
        }
    }

    // Adiciona uma aresta ao grafo
    void addEdge(vector<int> edge) {
        graph[edge[0]].push_back({edge[1],edge[2]});
    }
    
    // dijkstra - Encontra o caminho mais curto de node1 para node2
    int shortestPath(int node1, int node2) {

        vector<int> distancia(graph.size(),INT_MAX);
        distancia[node1]=0;

        queue<pair<int,int>> q;
        q.push({node1,0});

        while(!q.empty()){
            pair<int,int> temp = q.front();
            q.pop();

            if(distancia[temp.first]<temp.second) continue;

            for(int i=0; i<graph[temp.first].size(); i++){

                int nova_distancia = distancia[temp.first]+graph[temp.first][i].second;

                if(nova_distancia >= distancia[graph[temp.first][i].first]) continue;

                distancia[graph[temp.first][i].first] = nova_distancia;

                q.push({graph[temp.first][i].first,nova_distancia});
            }
        }
        if (distancia[node2] == INT_MAX) {
            return -1; // Se o nó de destino não for alcançado, retorna -1
        } else {
            return distancia[node2]; /// Retorna a distância mínima
        }
    }
};

