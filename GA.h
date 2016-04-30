#pragma once
#include <fstream>
#include <iostream>
using namespace std;
struct city {
	int x;
	int y;
	int rank;
};


class GA {
private:
	int size;
	city *member;
	city *pop[2000];
	double expence[2000], fx[2000];
	double best = 999999999, best_fx, worst = 0, worst_fx;
	int best_index, worst_index;
	int get_random(int size);
	void deepCopy(int i, city *input);
	int pick_up();
public:
	GA();
	void get_cityFile(ifstream  &in);
	void ini();
	void get_expence();
	void make_love();
};

