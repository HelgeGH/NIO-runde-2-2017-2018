#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

//kant
struct Edge {
	int index;
	int weight;
	Edge(int, int);
};

//constructor til kant
Edge::Edge(int a, int w) {
	index = a;
	weight = w;
}

int main() {
	//les inn
	int N, K;
	cin >> N >> K;

	//jeg må bruke en struct for å få med vekten til hver kant
	vector< vector<Edge> > graph(N);

	//avstander fra enhver node
	const int INF = numeric_limits<int>::max() / 2 - 1;
	vector<vector<int> > distance(N, vector<int>(N, INF));

	//basistilfeller
	for (int i = 0; i != N; ++i) {
		distance[i][i] = 0;
	}

	//det er K veier. Resten av basistilfellene er avstanden fra en by til en naboby
	for (int i = 0; i != K; ++i) {
		int a, b, weight;
		cin >> a >> b >> weight;
		graph[a].push_back(Edge(b, weight));
		graph[b].push_back(Edge(a, weight));
		//fyll inn vekt.
		distance[a][b] = weight;
		distance[b][a] = weight;
	}

	//her har jeg implementert Floyd Warshalls algortime for avstand mellom noder (O(n^3))
	for (int k = 0; k != N; ++k)
		for (int i = 0; i != N; ++i)
			for (int j = 0; j != N; ++j) {
				distance[i][j] = min(distance[i][j], distance[i][k] + distance[k][j]);
			}

	//så finner vi lengste avstand fra hver node
	vector<int> ecc(N, 0);

	for (int i = 0; i != N; ++i)
		for (int j = 0; j != N; ++j)
			ecc[i] = max(ecc[i], distance[i][j]);

	//hovedstaden må da være plassert der den lengste avstanden er kortest
	int result = -1;
	int min_ecc = INF;
	for (int i = 0; i != N; ++i)
		if (ecc[i] < min_ecc) {
			min_ecc = ecc[i];
			result = i;
		}

	cout << result << endl;
	system("pause");
	return 0;
}