#include "field.h"
#include <iostream>
#include <string>
#include <time.h>
#include <memory>

using namespace std;

field::field()
{
	square_ = std::make_unique<int[]>(0);
	size_ = 0;
	N_ = 0;
}

field::field(int n, int f = 0)
{
	switch (f)
	{
	case 0:
		square_ = std::make_unique<int[]>(n*n);
		for (int i = 0; i < n*n; ++i)
		{
			square_[i] = 0;
		}
		N_ = n;
		size_ = n * n;
		break;
	case 1:
		srand(time(NULL));
		square_ = std::make_unique<int[]>(n*n);
		for (int i = 0; i < n*n; ++i)
		{
			square_[i] = rand()%2;
		}
		N_ = n;
		size_ = n * n;
		break;
	case 2:
		cout << "NOT DONE" << endl;//одно из заранее выбранных полей
		break;
	}
}

field::~field()
{

}

void field::next_tick(int born_rule1 = 3, int born_rule2 = 3, int survival_rule1 = 2, int survival_rule2 = 3)
{
	int N = this->N_;
	int size = this->size_;
	int s = 0;
	int i, j;
	int f1 = 0, f2 = 0;
	for (i = 0; i < N; ++i)
	{
		for (j = 0; j < N; ++j)
		{
			s = 0;
			for (int k = -1; k <= 1; ++k)
			{
				for (int p = -1; p <= 1; ++p)
				{
					if ((k == 0) && (p == 0))
					{
						++p;
					}

					if (j + p < 0)
					{
						f1 = N;
					}

					if (i + k < 0)
					{
						f2 = N;
					}

					if (this->square_[((i + k)%N + f2)*N + (j + p)%N + f1] > 0)
					{
						++s;
					}

					f1 = 0;
					f2 = 0;
				}
			}

			if (this->square_[i*N + j] == 1)
			{
				if ((s >= survival_rule1) && (s <= survival_rule2))
				{
					this->square_[i*N + j] = 1;
				}
				else
				{
					this->square_[i*N + j] = 2;
				}
			}
			else
			{
				if ((s >= born_rule1) && (s <= born_rule2))
				{
					this->square_[i*N + j] = -1;
				}
			}
		}
	}


	for (i = 0; i < N; ++i)
	{
		for (j = 0; j < N; ++j)
		{
			if (this->square_[i*N + j] == 2)
			{
				this->square_[i*N + j] = 0;
			}

			if (this->square_[i*N + j] == -1)
			{
				this->square_[i*N + j] = 1;
			}
		}
	}
}

void field::dump(ofstream &f, string name, string rule)
{
	f << "#Life 1.06" << endl;
	f << "#N " << name << endl;
	f << "#R " << rule << endl;
	int N = this->N_;
	int i, j;
	for (i = 0; i < N; ++i)
	{
		for (j = 0; j < N; ++j)
		{
			if (this->square_[i*N + j] == 1)
			{
				f << i << " " << j << endl;
			}
		}
	}
}

void field::printer()
{
	int N = this->N_;
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			if (this->square_[i * N + j] == 1)
			{
				cout << "#";
			}
			else
			{
				cout << " ";
			}
		}
		cout << endl;
	}
}


