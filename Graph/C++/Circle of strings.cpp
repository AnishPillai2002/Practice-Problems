// Problem link: https://practice.geeksforgeeks.org/problems/circle-of-strings4530/1


// A C++ program to check if a given
// directed graph is Eulerian or not
#include<iostream>
#include <list>
#define CHARS 26
using namespace std;

// A class that represents an undirected graph
class Graph
{
	int V; // No. of vertices
	list<int> *adj; // A dynamic array of adjacency lists
	int *in;
public:
	// Constructor and destructor
	Graph(int V);
	~Graph() { delete [] adj; delete [] in; }

	// function to add an edge to graph
	void addEdge(int v, int w) { adj[v].push_back(w); (in[w])++; }

	// Method to check if this graph is Eulerian or not
	bool isEulerianCycle();

	// Method to check if all non-zero degree
	// vertices are connected
	bool isSC();

	// Function to do DFS starting from v. Used in isConnected();
	void DFSUtil(int v, bool visited[]);

	Graph getTranspose();
};

Graph::Graph(int V)
{
	this->V = V;
	adj = new list<int>[V];
	in = new int[V];
	for (int i = 0; i < V; i++)
	in[i] = 0;
}

/* This function returns true if the directed
graph has an eulerian cycle, otherwise returns
false */
bool Graph::isEulerianCycle()
{
	// Check if all non-zero degree vertices are connected
	if (isSC() == false)
		return false;

	// Check if in degree and out degree
	// of every vertex is same
	for (int i = 0; i < V; i++)
		if (adj[i].size() != in[i])
			return false;

	return true;
}

// A recursive function to do DFS starting from v
void Graph::DFSUtil(int v, bool visited[])
{
	// Mark the current node as visited and print it
	visited[v] = true;

	// Recur for all the vertices adjacent to this vertex
	list<int>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); ++i)
		if (!visited[*i])
			DFSUtil(*i, visited);
}

// Function that returns reverse (or transpose) of this graph
// This function is needed in isSC()
Graph Graph::getTranspose()
{
	Graph g(V);
	for (int v = 0; v < V; v++)
	{
		// Recur for all the vertices adjacent to this vertex
		list<int>::iterator i;
		for(i = adj[v].begin(); i != adj[v].end(); ++i)
		{
			g.adj[*i].push_back(v);
			(g.in[v])++;
		}
	}
	return g;
}

bool Graph::isSC()
{
	// Mark all the vertices as not visited (For first DFS)
	bool visited[V];
	for (int i = 0; i < V; i++)
		visited[i] = false;

	// Find the first vertex with non-zero degree
	int n;
	for (n = 0; n < V; n++)
		if (adj[n].size() > 0)
		break;

	// Do DFS traversal starting from first non zero degree vertex.
	DFSUtil(n, visited);

	// If DFS traversal doesn’t visit all vertices, then return false.
	for (int i = 0; i < V; i++)
		if (adj[i].size() > 0 && visited[i] == false)
			return false;

	// Create a reversed graph
	Graph gr = getTranspose();

	// Mark all the vertices as not visited (For second DFS)
	for (int i = 0; i < V; i++)
		visited[i] = false;

	// Do DFS for reversed graph starting from first vertex.
	// Starting Vertex must be same starting point of first DFS
	gr.DFSUtil(n, visited);

	// If all vertices are not visited in second DFS, then
	// return false
	for (int i = 0; i < V; i++)
		if (adj[i].size() > 0 && visited[i] == false)
			return false;

	return true;
}

bool canBeChained(string arr[], int n)
{

	Graph g(CHARS);


	for (int i = 0; i < n; i++)
	{
		string s = arr[i];
		g.addEdge(s[0]-'a', s[s.length()-1]-'a');
	}

	return g.isEulerianCycle();
}


int main()
{
	string arr1[] = {"for", "geek", "rig", "kaf"};
	int n1 = sizeof(arr1)/sizeof(arr1[0]);
	canBeChained(arr1, n1)? cout << "Can be chained \n" :
						cout << "Can't be chained \n";

	string arr2[] = {"aab", "abb"};
	int n2 = sizeof(arr2)/sizeof(arr2[0]);
	canBeChained(arr2, n2)? cout << "Can be chained \n" :
						cout << "Can't be chained \n";

	return 0;
}
