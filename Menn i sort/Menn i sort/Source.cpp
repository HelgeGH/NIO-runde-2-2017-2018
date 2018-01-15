#include <queue>
#include <iostream>
#include <vector>
#include <algorithm>

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
	int N, A, B;
	cin >> N >> A >> B;

	//jeg m� bruke en struct for � f� med vekten til hver kant
	vector< vector<Edge> > graph(N);

	//det er N - 1 veier
	for (int i = 0; i != N - 1; ++i) {
		int a, b, weight;
		cin >> a >> b >> weight;
		graph[a].push_back(Edge(b, weight));
		graph[b].push_back(Edge(a, weight));
	}

	vector<bool> visitedA(N, false);
	queue<int> nextA;

	//vi starter bfs der agenten er
	nextA.push(A);
	visitedA[A] = true;

	//og setter en verdi for avstanden han til hver node
	vector<int> distance_agent(N, 0);
	distance_agent[A] = 0;

	//gj�r enn bfs s�k fra node A for � finne distanse
	while (!nextA.empty()) {
		int pos = nextA.front();
		nextA.pop();

		for (int i = 0; i != graph[pos].size(); ++i) {
			int nghbr = graph[pos][i].index;
			if (!visitedA[nghbr]) {
				//legg til naboen i k�en
				nextA.push(nghbr);
				visitedA[nghbr] = true;
				//og finn avstanden til denne noden
				distance_agent[nghbr] = distance_agent[pos] + graph[pos][i].weight;
			}
		}
	}

	//n� repeter dette for B ------
	vector<bool> visitedB(N, false);
	queue<int> nextB;

	//starter der brukeren st�r
	nextB.push(B);
	visitedB[B] = true;

	//avstand
	vector<int> distance_user(N, 0);
	distance_user[B] = 0;

	//gj�r bfs s�k fra B
	while (!nextB.empty()) {
		int pos = nextB.front();
		nextB.pop();

		for (int i = 0; i != graph[pos].size(); ++i) {
			int nghbr = graph[pos][i].index;
			if (!visitedB[nghbr]) {
				visitedB[nghbr] = true;
				//finn distanse f�rst
				distance_user[nghbr] = distance_user[pos] + graph[pos][i].weight;
				nextB.push(nghbr);
			}
		}
	}

	//vi finner svaret
	int result = 0;

	//sjekk hvilken node som er best � stoppe p�
	for (int i = 0; i != N; ++i) {
		if (!(distance_user[i] > distance_agent[i]))
			result = max(result, distance_agent[i]);
	}

	//og print resultatet!
	cout << result << endl;
	system("pause");
	return 0;
}