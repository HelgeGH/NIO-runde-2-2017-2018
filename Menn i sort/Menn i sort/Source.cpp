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

	//jeg må bruke en struct for å få med vekten til hver kant
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

	//gjør enn bfs søk fra node A for å finne distanse
	while (!nextA.empty()) {
		int pos = nextA.front();
		nextA.pop();

		for (int i = 0; i != graph[pos].size(); ++i) {
			int nghbr = graph[pos][i].index;
			if (!visitedA[nghbr]) {
				//legg til naboen i køen
				nextA.push(nghbr);
				visitedA[nghbr] = true;
				//og finn avstanden til denne noden
				distance_agent[nghbr] = distance_agent[pos] + graph[pos][i].weight;
			}
		}
	}

	//nå repeter dette for B ------
	vector<bool> visitedB(N, false);
	queue<int> nextB;

	//starter der brukeren står
	nextB.push(B);
	visitedB[B] = true;

	//avstand
	vector<int> distance_user(N, 0);
	distance_user[B] = 0;

	//gjør bfs søk fra B
	while (!nextB.empty()) {
		int pos = nextB.front();
		nextB.pop();

		for (int i = 0; i != graph[pos].size(); ++i) {
			int nghbr = graph[pos][i].index;
			if (!visitedB[nghbr]) {
				visitedB[nghbr] = true;
				//finn distanse først
				distance_user[nghbr] = distance_user[pos] + graph[pos][i].weight;
				nextB.push(nghbr);
			}
		}
	}

	//vi finner svaret
	int result = 0;

	//sjekk hvilken node som er best å stoppe på
	for (int i = 0; i != N; ++i) {
		if (!(distance_user[i] > distance_agent[i]))
			result = max(result, distance_agent[i]);
	}

	//og print resultatet!
	cout << result << endl;
	system("pause");
	return 0;
}