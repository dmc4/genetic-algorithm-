#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include "Source.h"
using namespace std;

GA::GA()
{
	size = 0;
	member = NULL;
}

void GA::get_cityFile(ifstream  &in)
{
	int i, j;
	in >> size;
	member = new city[size];
	for (i = 0; i < size; i++)
	{
		in >> member[i].x >> member[i].y >> member[i].rank;
	}
}

void GA::ini()
{
	int i, j;
	city *temp;

	temp = new city[size];
	for (i = 0; i < size; i++)
	{
		temp[i] = member[i];
		
	}

	for (i = 0; i < 2000; i++)
	{
		pop[i] = new city[size];
	}
	for (i = 0; i < 2000; i++)
	{
		for (j = 0; j < 50; j++)
		{
			swap(temp[get_random(100)], temp[get_random(100)]);
		}
		deepCopy(i, temp);
	}

	delete[] temp;
}

void GA::get_expence()
{
	int i = 0, j = 0;
	double dis;

	for (i = 0; i < 2000; i++)
	{
		expence[i] = 0;//ini
		for (j = 0; j < size - 1; j++)
		{
			dis = sqrt(pow((pop[i][j].x - pop[i][j + 1].x), 2) + pow((pop[i][j].y - pop[i][j + 1].y), 2));
			if (pop[i][j].rank == 1)			//look up
			{
				if (pop[i][j + 1].rank == 1)
				{
					expence[i] = expence[i] + dis * 10;
				}
				else if (pop[i][j + 1].rank == 2)
				{
					expence[i] = expence[i] + dis * 7.5;
				}
				else if (pop[i][j + 1].rank == 3)
				{
					expence[i] = expence[i] + dis * 5;
				}
			}
			else if (pop[i][j].rank == 2)
			{
				if (pop[i][j + 1].rank == 1)
				{
					expence[i] = expence[i] + dis * 7.5;
				}
				else if (pop[i][j + 1].rank == 2)
				{
					expence[i] = expence[i] + dis * 5;
				}
				else if (pop[i][j + 1].rank == 3)
				{
					expence[i] = expence[i] + dis * 2.5;
				}
			}
			else if (pop[i][j].rank == 3)
			{
				if (pop[i][j + 1].rank == 1)
				{
					expence[i] = expence[i] + dis * 5;
				}
				else if (pop[i][j + 1].rank == 2)
				{
					expence[i] = expence[i] + dis * 2.5;
				}
				else if (pop[i][j + 1].rank == 3)
				{
					expence[i] = expence[i] + dis * 1;
				}
			}
		}

		fx[i] = 1 / expence[i];

		if (expence[i] > worst)
		{
			worst = expence[i];
			worst_index = i;
			worst_fx = 1 / expence[i];
		}

		if (expence[i] < best)
		{
			best = expence[i];
			best_index = i;
			best_fx = 1 / expence[i];
		}
	}
}

void GA::make_love()
{
	int i, j, k, l;
	city *temp[2000];

	for (i = 0; i < 2000; i++)
	{
		temp[i] = new city[size];
	}

	i = 0;
	while (i < 1999)
	{
		for (j = 0; j < size; j++)
		{
			temp[i][j] = pop[i][j];
			temp[1 + i][j] = pop[i + 1][j];
		}

		for (l = 0; l < 51; l++)
		{
			for (k = 51; k < 100; k++)
			{
				if (temp[i][l].x == temp[i + 1][k].x && temp[i][l].y == temp[i + 1][k].y)
					;
			}
		}

		i = i + 2;
	}
}


int GA::pick_up()
{
	int i;
	double val;
	double sum_fx = 0, tempVal = 0;

	for (i = 0; i < 2000; i++)
		sum_fx += (1000 / expence[i]);
	
	val = get_random((int)(pow(sum_fx, 2) + 1)) / sum_fx;
	
	for (i = 0; i < 2000; i++)
	{
		tempVal += 1000 / expence[i];
		if (tempVal > val)
			return i;
	}

	return -1;
}

void GA::deepCopy(int i, city *input)
{
	for (int j = 0; j < size; j++)
	{
		pop[i][j].x = input[j].x;
		pop[i][j].y = input[j].y;
		pop[i][j].rank = input[j].rank;
	}
}

int GA::get_random(int size)
{
	return rand() % size;
}
