#include <iostream>
#include <vector>

using namespace std;

int main() {
	//les inn
	long long K;
	int N;
	cin >> N >> K;

	vector<int> values;

	//fyll vector
	for (int i = 0; i != N; ++i) {
		int record;
		cin >> record;
		values.push_back(record);
	}

	//antall blippcoins
	long long blipps = 0;

	for (int i = 0; i != N; ++i) {
		//selg p� den siste, hvis mulig
		if (i == N - 1) {
			K += blipps * values[i];
		}
		//kj�p n�r prisen kommer til � stige, og hvis man har r�d
		else if (values[i] < values[i + 1] && K > values[i]) {
			blipps += K / values[i];
			K -= blipps * values[i];
		}
		//selg hvis den skal synke
		else if (values[i] > values[i + 1]) {
			K += blipps * values[i];
			blipps = 0;
		}
	}

	//print resultat
	cout << K << endl;
	system("pause");
	return 0;
}