// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <string>
#include <chrono>
#include <iostream>
#include <thread>
#include <fstream>

const int N = 1;

using namespace std;

void divide(int i, int p, string password, bool* p_found, chrono::high_resolution_clock::time_point* p_end) {
	for (int a = i; a < i + p; a++) {
		for (int b = i; b < i + p; b++) {
			for (int c = i; c < i + p; c++) {
				for (int d = i; d < i + p; d++) {
					for (int e = i; e < i + p; e++) {
						if (!*p_found) {
							string passwd = { char(a), char(b), char(c), char(d), char(e) };
							if (passwd == password) {
								*p_end = chrono::high_resolution_clock::now();
								*p_found = 1;
							}
						}
						else {
							return;
						}
					}
				}
			}
		}
	}
}

void findPassword(string password) {

	thread threadObj[N];
	bool found = 0;
	chrono::high_resolution_clock::time_point end;
	chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
	
	for (int i = 0; i < N; i++){
		threadObj[i] = thread(divide, 97 + 26 * i / N, (26 * (i + 1) / N) - (26 * i / N), password, &found, &end);
	}

	for (int i = 0; i < N; i++) {
		threadObj[i].join();
	}
	chrono::duration<double> time = end - start;
	cout << time.count() << endl;
}

int main() { //a=97 z=122
	//int i = 97;
	//char c = 'a';
	//cout << c << c << endl;
	

	ifstream file;
	file.open("password.txt");
	if (!file.is_open()) {
		cout << "error" << endl;
		exit;
	}

	string password;

	file >> password;
	file.close();
	findPassword(password);
}