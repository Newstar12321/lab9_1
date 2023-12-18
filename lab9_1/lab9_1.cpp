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

struct MyDate
{
	int year;
	int mon;
	int day;

	void in()
	{
		cin >> this->day >> this->mon >> this->year;
		//validate
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
		return year >= 0 || mon >= 0 || day >= 0;
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
		this->date.in();
	}

	void print()
	{
		cout << "Name: " << this->name
			<< "\nKol: " << this->kol_p
			<< "\nWeight: " << this->weight
			<< "\nDate: ";
		this->date.print();
		cout << "\nSrok godnosty: " << this->sr << " days";
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
		arr[i].in();
		arr[i].print();
	}

	MyDate now;
	cout << "Введите сегодняшнее число в формате дд мм гггг: ";
	now.in();

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