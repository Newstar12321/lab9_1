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
	case 5:
	{
		uniform_int_distribution<> d(1, 31);
		return d(gen);
	}
	case 6:
	{
		uniform_int_distribution<> m(1, 12);
		return m(gen);
	}
	case 7:
	{
		uniform_int_distribution<> g(2000, 2050);
		return g(gen);
	}
	default:
		return 0;
	}
}

struct MyDate
{
	size_t year;
	size_t mon;
	size_t day;

	bool in()
	{
		cin >> this->day >> this->mon >> this->year;
		//validate
		if (this->day && this->day <= 31 &&
			this->mon && this->mon <= 12 &&
			this->year >= 1000 &&
			this->year <= 9999)
		{
			return 0;
		}
		return 1;
	}

	//bool operator>=(MyDate& other);  // dat >= dat2
	//MyDate& operator+(int days);     // dat + 32

	/**
	 * @brief Сравнить даты
	 * @param now
	 * @return Дата ещё не наступила
	*/
	bool cmp(MyDate& now)
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

	void print()
	{
		cout << this->day << '.' << this->mon << '.' << this->year;
	}
};

struct Drug
{
	int kol_p;
	int weight;
	string name;
	MyDate date;
	// срок годности в днях
	int sr;

	void in()
	{
		string name_[] = { "Гексарал", "Граммедин", "Терафлю", "Аспирин", "Парацетамол" };
		this->name = name_[rand_(1)];
		this->kol_p = rand_(3);
		this->weight = rand_(4);
		this->sr = rand_(2);
		this->date.day = rand_(5);
		this->date.mon = rand_(6);
		this->date.year = rand_(7);
	}

	void print()
	{
		cout << "___\n";
		cout << "Name: " << this->name
			<< "\nKol: " << this->kol_p
			<< "\nWeight: " << this->weight
			<< "\nDate: ";
		this->date.print();
		cout << "\nSrok godnosty: " << this->sr << " days\n\n";
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
		arr[i].in();
		arr[i].print();
	}

	MyDate now;
	cout << "Введите сегодняшнее число в формате дд мм гггг: ";
	if (now.in())
	{
		cerr << "Ошибка!";
		return 1;
	}

	int k = 0;
	for (size_t i = 0; i < n; i++) {
		// дата истечения
		MyDate l_date = arr[i].date;
		l_date.day += arr[i].sr; // (!)
		if (l_date.cmp(now))
		{
			arr[i].print();
			cout << "Дата истечения срока годности: ";
			l_date.print();
			cout << endl;
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