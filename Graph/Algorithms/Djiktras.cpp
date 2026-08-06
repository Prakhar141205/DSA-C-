class Djiktras {    
public:
    Djiktras(int vertices) {
        this->vertices = vertices;
        graph = new int*[vertices];
        for (int i = 0; i < vertices; i++) {
            graph[i] = new int[vertices];
            for (int j = 0; j < vertices; j++) {
                graph[i][j] = 0;
            }
        }
    }

    void addEdge(int u, int v, int weight) {
        graph[u][v] = weight;
        graph[v][u] = weight; // For undirected graph
    }

    void dijkstra(int start) {
        int* dist = new int[vertices];
        bool* sptSet = new bool[vertices];

        for (int i = 0; i < vertices; i++) {
            dist[i] = INT_MAX;
            sptSet[i] = false;
        }

        dist[start] = 0;

        for (int count = 0; count < vertices - 1; count++) {
            int u = minDistance(dist, sptSet);
            sptSet[u] = true;

            for (int v = 0; v < vertices; v++) {
                if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                    dist[v] = dist[u] + graph[u][v];
                }
            }
        }

        printSolution(dist);
    }