/*
Объект – таблетированное лекарство в аптеке.
Известны наименование лекарства, количество таблеток в упаковке,
вес одной таблетки, дата выпуска, срок годности. Выдать список лекарств,
срок годности которых истекает на момент заданной даты.
*/

#include <iostream>
#include <string>
#include <random>

using namespace std;

int rand_(int t)
{
	random_device rd;
	mt19937 gen(rd());
	switch (t)
	{
	case 1:
	{
		uniform_int_distribution<> n(0, 4);
		return n(gen);
	}
	case 2:
	{
		uniform_int_distribution<> l(1, 10);
		return l(gen);
	}
	case 3:
	{
		uniform_int_distribution<> k(10, 250);
		return k(gen);
	}
	case 4:
	{
		uniform_int_distribution<> w(100, 1000);
		return w(gen);
	}
	default:
		return 0;
	}
}

struct Data
{
	int year;
	int mon;
	int day;

	void in()
	{
		cin >> this->day
			>> this->mon
			>> this->year;
	}

	int sr_god(Data& now)
	{
		int year = this->year - now.year;
		int mon = this->mon - now.mon;
		int day = this->day - now.day;
		if (!year)
		{
			if (!mon)
			{
				if (day > 0)
				{
					return 0;

				}
				return 1;
			}
			if (mon > 0)
			{
				return 0;
			}
			return 1;
		}
		if (year > 0)
		{
			return 0;

		}
		return 1;
	}

	void out(bool n)
	{
		if (!n)
		{
			cout << "Введите дату изготовления в формате: дд мм гггг\t";
			return;
		}
		cout << this->day << '.'
			<< this->mon << '.'
			<< this->year;
	}

};

struct Drug
{
	int kol_p;
	int weight;
	int sr;
	string name;
	Data date;
	Data l_date;

	void in()
	{
		string name_[] = { "Гексарал", "Граммедин", "Терафлю", "Аспирин", "Парацетамол" };
		this->name = name_[rand_(1)];
		this->kol_p = rand_(3);
		this->weight = rand_(4);
		this->sr = rand_(2);

		bool n = 0;
		bool& n_ = n;
		date.out(n_);
		date.in();
		l_date = date;
		l_date.year += sr;
	}

	void out(bool& i)
	{
		bool n = 1;
		bool& n_ = n;
		if (i) {
			cout << this->name << ' '
				<< this->kol_p << ' '
				<< this->weight << ' ';
			this->date.out(n_);
			cout << ' ' << this->sr << endl;
			cout << "Дата истечения срока годности: ";
			this->l_date.out(n_);
			cout << "\n";
			return;
		}
		cout << "Name: " << this->name
			<< "\nKol: " << this->kol_p
			<< "\nWeight: " << this->weight
			<< "\nDate: ";
		this->date.out(n_);
		cout << "\nSrok godnosty: " << this->sr << " years";
		cout << "\n___\n";
	}
};

int main()
{
	system("chcp 1251");
	size_t n;
	cout << "Введите количество лекарств: ";
	cin >> n;

	if (!n)
	{
		cerr << "Ошибка! Недопустимое значение\n";
		return 1;
	}

	Drug* arr = new Drug[n];
	for (size_t i = 0; i < n; i++) {
		bool n = 0;
		bool& n_ = n;
		arr[i].in();
		arr[i].out(n_);
	}

	Data y_date;
	cout << "Введите сегодняшнее число в формате дд мм гггг: ";
	y_date.in();
	Data& y = y_date;
	int k = 0;
	bool out_i = 1;
	bool& out_ii = out_i;
	for (size_t i = 0; i < n; i++) {
		if (arr[i].l_date.sr_god(y))
		{
			arr[i].out(out_ii);
			k++;
		}
	}
	if (!k)
	{
		cout << "Просроченных лекартсв нет\n";
	}
	else
	{
		cout << "Просроченных лекарств: " << k << endl;
	}
	delete[] arr;
}