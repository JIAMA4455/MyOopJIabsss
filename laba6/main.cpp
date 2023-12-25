#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <unordered_set>

class Graph {
public:
    std::vector<std::list<int>> adjacencyList;

    Graph(int vertices) : adjacencyList(vertices) {}

    void addEdge(int src, int dest) {
        adjacencyList[src].push_back(dest);
    }
};

class GraphTraversal {
protected:
    Graph& graph;

    virtual void beginTraversal() {}
    virtual void endTraversal() {}
    virtual void visitNode(int node) {}
    virtual void visitEdge(int src, int dest) {}

public:
    GraphTraversal(Graph& g) : graph(g) {}

    virtual void traverse(int startVertex) = 0;
};

class DepthFirstSearch : public GraphTraversal {
public:
    DepthFirstSearch(Graph& g) : GraphTraversal(g) {}

    void visitNode(int node) override {
        std::cout << "DFS - Visited node: " << node << std::endl;
    }

    void visitEdge(int src, int dest) override {
        std::cout << "DFS - Visited edge: " << src << " -> " << dest << std::endl;
    }

    void traverse(int startVertex) override {
        std::stack<int> stack;
        std::unordered_set<int> visited;

        stack.push(startVertex);

        while (!stack.empty()) {
            int current = stack.top();
            stack.pop();

            if (visited.find(current) == visited.end()) {
                visitNode(current);
                visited.insert(current);

                for (auto it = graph.adjacencyList[current].rbegin(); it != graph.adjacencyList[current].rend(); ++it) {
                    if (visited.find(*it) == visited.end()) {
                        stack.push(*it);
                        visitEdge(current, *it);
                    }
                }
            }
        }
    }
};

class BreadthFirstSearch : public GraphTraversal {
public:
    BreadthFirstSearch(Graph& g) : GraphTraversal(g) {}

    void visitNode(int node) override {
        std::cout << "BFS - Visited node: " << node << std::endl;
    }

    void visitEdge(int src, int dest) override {
        std::cout << "BFS - Visited edge: " << src << " -> " << dest << std::endl;
    }

    void traverse(int startVertex) override {
        std::queue<int> queue;
        std::unordered_set<int> visited;

        queue.push(startVertex);

        while (!queue.empty()) {
            int current = queue.front();
            queue.pop();

            if (visited.find(current) == visited.end()) {
                visitNode(current);
                visited.insert(current);

                for (int neighbor : graph.adjacencyList[current]) {
                    if (visited.find(neighbor) == visited.end()) {
                        queue.push(neighbor);
                        visitEdge(current, neighbor);
                    }
                }
            }
        }
    }
};

// Example usage:
int main() {
    Graph g(5); // Create a graph with 5 vertices
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);

    DepthFirstSearch dfs(g);
    dfs.traverse(0); // Perform DFS starting from vertex 0

    BreadthFirstSearch bfs(g);
    bfs.traverse(0); // Perform BFS starting from vertex 0

    return 0;
}
