#include <string>
#include <chrono>
#include <iostream>
#include <fstream>
#include <math.h>
#include <omp.h>

const int NUMBER_OF_THREADS = 1;
const int CHAR_A = 97;
const int CHAR_Z = 122;
const int BASE_10 = 10;
const int BASE_26 = 26;
const int HIGHEST_PASSWORD = 11881376;

using namespace std;

int _26to10(string in26) {
	int out10 = 0;
	int power = 0;
	while (in26.length() > 0) {
		char s = in26[in26.length() - 1];
		out10 += (int(s) - CHAR_A) * pow(BASE_26, power);
		in26 = in26.substr(0, in26.length() - 1);
		power++;
	}
	return out10;
}

string _10to26(int in10) {
	string out26 = "";
	string out_reversed;
	while (in10 > 0) {
		out_reversed.push_back(char(CHAR_A + in10 % BASE_26));
		in10 /= BASE_26;
	}
	for (int l = out_reversed.length() - 1; l >= 0; l--) {
		out26.push_back(out_reversed[l]);
	}
	return out26;
}

void divide_ (int start, int finish, int password, bool* p_found, chrono::high_resolution_clock::time_point* p_end) {
	for (int i = start; i < finish; i++) {
		if (!*p_found) {
			if (i == password) {
				*p_end = chrono::high_resolution_clock::now();
				*p_found = 1;
			}
		}
		else {
			return;
		}
	}
}

void divide(int i, int password, bool* p_found, chrono::high_resolution_clock::time_point* p_end) {
	if (!*p_found) {
		if (i == password) {
			*p_end = chrono::high_resolution_clock::now();
			*p_found = 1;
		}
	}
	else {
		return;
	}
}

void findPassword(string password) {
	bool found = 0;
	chrono::high_resolution_clock::time_point end;
	chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
#pragma omp parallel for num_threads(NUMBER_OF_THREADS)
	for (int i = 0; i < HIGHEST_PASSWORD; i++) {
		divide(i, _26to10(password), &found, &end);
	}
	chrono::duration<double> time = end - start;
	cout << time.count() << "s" << endl;
}

int main() { //a=97 z=122

	ifstream file;
	file.open("password.txt");
	if (!file.is_open()) {
		cout << "error" << endl;
		exit(-1);
	}

	string password;

	file >> password;
	file.close();
	findPassword(password);
}