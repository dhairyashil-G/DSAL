/*
Represent a given graph using adjacency matrix/list to perform DFS and using adjacency list
to perform BFS. Use the map of the area around the college as the graph. Identify the prominent
land marks as nodes and perform DFS and BFS on that.
*/

#include <bits/stdc++.h>
using namespace std;

class graph
{
    int **adj_matrix;
    int num_vertices;
    bool *visited;

public:
    graph(int num_vertices)
    {
        this->num_vertices = num_vertices;
        adj_matrix = new int *[num_vertices];
        for (int i = 0; i < num_vertices; i++)
        {
            adj_matrix[i] = new int[num_vertices];
            for (int j = 0; j < num_vertices; j++)
                adj_matrix[i][j] = 0;
        }
        visited = new bool[num_vertices];
        for (int i = 0; i < num_vertices; i++)
            visited[i] = false;
    }

    void add_edge(int i, int j, int weight = 1)
    {
        adj_matrix[i][j] = weight;
        adj_matrix[j][i] = weight;
    }

    void remove_edge(int i, int j)
    {
        adj_matrix[i][j] = 0;
        adj_matrix[j][i] = 0;
    }

    void BFS(int s)
    {
        list<int> queue;
        // mark the current node as visited and enqueue it
        visited[s] = true;
        queue.push_back(s);
        while (!queue.empty())
        {
            // dequeue a vertex from queue and print it
            s = queue.front();
            cout << s << " ";
            queue.pop_front();
            // get all adjacent vertices of the dequeued vertex s if a adjacent has not been visited, then mark it visited and enqueue it
            for (int d = 0; d < num_vertices; d++)
            {
                if ((adj_matrix[s][d] != 0) && (visited[d] == false))
                {
                    visited[d] = true;
                    queue.push_back(d);
                }
            }
        }
    }

    void DFS_recursive(int v)
    {
        // mark the current node as visited and print it
        visited[v] = true;
        cout << v << " ";
        // recur for all the vertices adjacent to this vertex
        for (int d = 0; d < num_vertices; d++)
            if ((adj_matrix[v][d] != 0) && (visited[d] == false))
                DFS_recursive(d);
    }

    void DFS_iterative(int v)
    {
        // similar to BFS just replace queue by stack
        stack<int> stack;
        stack.push(v);
        while (!stack.empty())
        {
            // pop a vertex from stack and print it
            int s = stack.top();
            stack.pop();
            // stack may contain same vertex twice so we need to print the popped item only if it is not visited
            if (!visited[s])
            {
                cout << s << " ";
                visited[s] = true;
            }
            // get all adjacent vertices of the popped vertex s if a adjacent has not been visited, then mark it visited and push it
            for (int d = 0; d < num_vertices; d++)
            {
                if ((adj_matrix[s][d] != 0) && (visited[d] == false))
                {
                    visited[d] = true;
                    stack.push(d);
                }
            }
        }
    }

    void print_graph()
    {
        for (int i = 0; i < num_vertices; i++)
        {
            cout << i << " : ";
            for (int j = 0; j < num_vertices; j++)
                cout << adj_matrix[i][j] << " ";
            cout << "\n";
        }
    }

    ~graph()
    {
        for (int i = 0; i < num_vertices; i++)
            delete[] adj_matrix[i];
        delete[] adj_matrix;
    }
};

int main()
{
    graph g(4);

    g.add_edge(0, 1);
    g.add_edge(0, 2);
    g.add_edge(1, 2);
    g.add_edge(2, 0);
    g.add_edge(2, 3);
    g.add_edge(3, 3);

    g.BFS(2);
    g.DFS_iterative(2);
    g.DFS_recursive(2);

    g.print_graph();

    g.remove_edge(0, 2);
    g.remove_edge(2, 3);

    g.print_graph();
}