#include <iostream>
#include <vector>
#include <ctime>
using namespace std;
#include <limits>
#include <cmath>

const int Infinity = numeric_limits<int>::max() / 2;

struct Edge
{
    int from;
    int to;
    int weight;
    Edge(int from, int to, int weight)
    {
        this->from = from;
        this->to = to;
        this->weight = weight;
    }
};

vector<vector<int>>
generate_matrix(int min_v, int max_v, int size);
void print_matrix(vector<vector<int>> matrix);
void print_vector(vector<int> v);
vector<Edge> generate_edges(vector<vector<int>> links, vector<vector<int>> weights);
vector<vector<int>> generate_pair_dist(vector<vector<int>> links, vector<vector<int>> weights);
vector<int> BellmanFord(vector<Edge> edges, int src, int size, float &time);
vector<int> Dijsktra(vector<Edge> edges, int src, int size, float &time);
vector<vector<int>> FloydWarshall(vector<vector<int>> weights, int size, float &time);
vector<vector<int>> Johnson(vector<Edge> edges, int size, float &time);

int main()
{
    srand(time(NULL));
    vector<vector<int>> links = generate_matrix(0, 1, 32);
    vector<vector<int>> weights = generate_matrix(0, 100, 32);
    vector<Edge> edges = generate_edges(links, weights);
    vector<vector<int>> pair_dist = generate_pair_dist(links, weights);

    // print_matrix(links);
    // print_matrix(weights);
    float time;
    vector<int> dist;

    dist = BellmanFord(edges, 0, 32, time);
    cout << "Bellman Ford time: " << time << "s" << endl;
    print_vector(dist);
    cout << endl;

    dist = Dijsktra(edges, 0, 32, time);
    cout << "Dijsktra time: " << time << "s" << endl;
    print_vector(dist);
    cout << endl;

    dist = FloydWarshall(pair_dist, 32, time)[0];
    cout << "Floyd Warshall time: " << time << "s" << endl;
    print_vector(dist);
    cout << endl;

    dist = Johnson(edges, 32, time)[0];
    cout << "Johnson time: " << time << "s" << endl;
    print_vector(dist);
    cout << endl;
}

vector<vector<int>> generate_matrix(int min_v, int max_v, int size)
{
    vector<vector<int>> matrix;
    for (int i = 0; i < size; i++)
    {
        vector<int> row;
        for (int j = 0; j < size; j++)
        {
            row.push_back(min_v + rand() % (max_v + 1));
        }
        matrix.push_back(row);
    }
    return matrix;
}

void print_matrix(vector<vector<int>> matrix)
{
    for (int i = 0; i < matrix.size(); i++)
    {
        printf("| ");
        for (int j = 0; j < matrix[i].size(); j++)
        {
            printf("%3d ", matrix[i][j]);
        }
        printf("|\n");
    }
}

void print_vector(vector<int> v)
{
    cout << "[ ";
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << " ";
    }
    cout << "]" << endl;
}

vector<Edge> generate_edges(vector<vector<int>> links, vector<vector<int>> weights)
{
    vector<Edge> edges;
    for (int i = 0; i < links.size(); i++)
    {
        for (int j = 0; j < links[i].size(); j++)
        {
            if (links[i][j] != 0)
                edges.push_back(Edge(i, j, weights[i][j]));
        }
    }
    return edges;
}

vector<vector<int>> generate_pair_dist(vector<vector<int>> links, vector<vector<int>> weights)
{
    vector<vector<int>> pair_dist = weights;
    for (int i = 0; i < links.size(); i++)
    {
        for (int j = 0; j < links[i].size(); j++)
        {
            if (links[i][j] == 0)
                pair_dist[i][j] = Infinity;
        }
    }
    return pair_dist;
}

vector<int> BellmanFord(vector<Edge> edges, int src, int size, float &time)
{
    vector<int> dist;
    for (int i = 0; i < size; i++)
        dist.push_back(Infinity);

    dist[src] = 0;

    clock_t start = clock();

    for (int i = 0; i < edges.size() - 1; i++)
    {
        for (int j = 0; j < edges.size(); j++)
        {
            Edge e = edges[j];
            if (dist[e.from] != Infinity && dist[e.from] + e.weight < dist[e.to])
            {
                dist[e.to] = dist[e.from] + e.weight;
            }
        }
    }

    clock_t end = clock();
    time = (float(end - start)) / CLOCKS_PER_SEC;

    return dist;
}

vector<int> Dijsktra(vector<Edge> edges, int src, int size, float &time)
{
    vector<int> dist;
    vector<int> unseen;
    for (int i = 0; i < size; i++)
    {
        dist.push_back(Infinity);
        unseen.push_back(i);
    }
    dist[src] = 0;

    clock_t start = clock();

    while (unseen.size() > 0)
    {
        int min_dist = dist[unseen[0]];
        int min_index = unseen[0];
        int unseen_index = 0;

        for (int i = 0; i < unseen.size(); i++)
        {
            if (min_dist > dist[unseen[i]])
            {
                min_dist = dist[unseen[i]];
                min_index = unseen[i];
                unseen_index = i;
            }
        }
        unseen.erase(unseen.begin() + unseen_index);

        for (int i = 0; i < edges.size(); i++)
        {
            if (edges[i].from != min_index)
                continue;

            if (edges[i].weight + min_dist < dist[edges[i].to])
                dist[edges[i].to] = edges[i].weight + min_dist;
        }
    }
    clock_t end = clock();
    time = (float(end - start)) / CLOCKS_PER_SEC;
    return dist;
}

vector<vector<int>> FloydWarshall(vector<vector<int>> weights, int size, float &time)
{
    vector<vector<int>> dist = weights;

    clock_t start = clock();

    for (int k = 0; k < size; k++)
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                if (i == j)
                {
                    dist[i][j] = 0;
                }
            }
        }
    }
    clock_t end = clock();
    time = (float(end - start)) / CLOCKS_PER_SEC;
    return dist;
}

vector<vector<int>> Johnson(vector<Edge> edges, int size, float &time)
{
    vector<vector<int>> dist;
    clock_t start = clock();

    for (int i = 0; i < size; i++)
    {
        dist.push_back(Dijsktra(edges, i, size, time));
    }
    clock_t end = clock();
    time = (float(end - start)) / CLOCKS_PER_SEC;
    return dist;
}
