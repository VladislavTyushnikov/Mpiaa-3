/*

*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <conio.h>
#include <cstdlib>
#include<string.h>
#include <windows.h>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <vector>
#include "timer.h"
using namespace std;

#define  size_hash_table 10513

using namespace std;

class human
{
public:
	char * name;
	char * surname;
	short day;
	char * month;
	short year;
	human(char * name, char * surname, short day, char * month, short year)
	{
		this->name = new char[strlen(name) + 1];
		this->month = new char[strlen(month) + 1];
		this->surname = new char[strlen(surname) + 1];

		strcpy(this->name, name);
		strcpy(this->surname, surname);
		this->day = day;
		strcpy(this->month, month);
		this->year = year;
	}
	human(char * input_str)
	{

		char name[50];
		char surname[50];
		short day;
		char month[50];
		short year;

		name[0] = '\0';
		surname[0] = '\0';
		month[0] = '\0';

		sscanf(input_str, "%s %s %hd %s %hd", name, surname, &day, month, &year);
		*this = human(name, surname, day, month, year);
	}
	human(){}

	
	int get_age()
	{
		// сегодня 31 декабря 2016 года. т.е. родился в 2015 - 0 лет; в 2014 - 1 год 
		return 2016 - this->year;
	}
	/*~human()
	{
		delete this->name;
		delete this->surname;
		delete this->month;
	}*/
};

bool const operator == (const human &hum1, const human &hum2)
{
	if (strcmp(hum2.name, hum1.name) != 0 ||
		strcmp(hum2.surname, hum1.surname) != 0 ||
		strcmp(hum2.month, hum1.month) != 0 ||
		hum2.day != hum1.day ||
		hum2.year != hum1.year)
		return false;
	else
		return true;

}

class hash_table
{
public:
	vector<human> *table = new vector <human>[size_hash_table];

	hash_table() {}
	void add_elem(human human)
	{
		int hash_value = hash_func(human.surname, human.get_age());
		int index = find_elem(this->table[hash_value], human.surname, human.get_age());
		if (index == -1)
			this->table[hash_value].push_back(human);
		else
			this->table[hash_value][index] = human;
	}
	human find_elem(char * surname, int age)
	{
		int hash_value = hash_func(surname, age);
		int index = find_elem(this->table[hash_value], surname, age);
		if (index == -1)
			return human("", "", 0, "", 0);
		else
			return table[hash_value][index];
	}
	int min_len_list()
	{
		int min = INT_MAX;
		for (int i = 0; i < size_hash_table; i++)
		{
			int size = table[i].size();
			if (size < min)
				min = size;
		}
		return min;
	}
	int max_len_list()
	{
		int max = -1;
		for (int i = 0; i < size_hash_table; i++)
		{
			int size = table[i].size();
			if (size > max)
				max = size;
		}
		return max;
	}
	int averange_len_list()
	{
		int sum = 0;
		for (int i = 0; i < size_hash_table; i++)
		{
			sum += table[i].size();

		}
		return sum / size_hash_table;
	}
	int hash_func(char * surname, int age)
	{
		return (weight_string(surname) + age) % size_hash_table;
	}

private:
	unsigned long long weight_string(char * str)
	{
		//97 символ - 0
		//122 символ - 25
		//всего символов 26

		int lenght = strlen(str);
		unsigned long long weight = 0;
		for (int i = 0; i < lenght; i++)
			weight += (tolower(str[i]) - 97) * pow(26, i);
		return weight;

	}
	int find_elem(vector <human> vector, char * surname, int age) // -1 не найден; иначе вернуть индекс
	{
		int lenght_vector = vector.size();
		for (int i = 0; i < lenght_vector; i++)
			if (strcmp(surname, vector[i].surname) == 0 && age == vector[i].get_age())
				return i;
		return -1;
	}
};

human generate_human()
{
	char * name = new char[5];
	char * surname = new char[5];
	short day;
	char * month = new char[4];
	short year;

	for (int j = 0; j < 4; j++)
		name[j] = rand() % 26 + 97;
	for (int j = 0; j < 4; j++)
		surname[j] = rand() % 26 + 97;
	for (int j = 0; j < 3; j++)
		month[j] = rand() % 26 + 97;
	day = rand() % 31 + 1;
	year = rand() % 115 + 1900;

	name[4] = '\0';
	surname[4] = '\0';
	month[3] = '\0';

	return human(name, surname, day, month, year);
}

class search_key
{
public:
	char * surname;
	int age;

	search_key()
	{
		this->surname = new char[5];

		for (int j = 0; j < 4; j++)
			this->surname[j] = rand() % 26 + 97;
		this->age = rand() % 500;
		this->surname[4] = '\0';
	}
};

class human_mass
{
public:
	human * mass;
	int lenght;
	human_mass(int size)
	{
		this->mass = new human[size];
		lenght = 0;
	}
	void add_elem(human human)
	{
		mass[lenght] = human;
		lenght++;
	}
	human find_elem(char * surname, int age)
	{
		for (int i = 0; i < this->lenght; i++)
			if (strcmp(surname, this->mass[i].surname) == 0 && age == this->mass[i].get_age())
				return this->mass[i];
		return  human("", "", 0, "", 0);
	}
};

void main()
{
	setlocale(LC_ALL, "ru");
	
	hash_table hash_table;
	for (int i = 0; i < 100'000; i++)
		hash_table.add_elem(generate_human());

	int min_len_list = hash_table.min_len_list();
	int max_len_list = hash_table.max_len_list();
	int averange_len_list = hash_table.averange_len_list();
	cout << "Для хэш таблицы на 100 000 элементов:\nМинимальная длинна списка: " << min_len_list<< "\nМаксимальная длинна списка: " <<
		max_len_list << "\nСредняя длинна списка: " << averange_len_list << endl;

	search_key *mass_keys = new search_key [100'000];
	timer_start();
	for (int i = 0; i < 100'000; i++)
	{
		mass_keys[i] = search_key();
		hash_table.find_elem(mass_keys[i].surname, mass_keys[i].age);
	}
	double time = timer_check();
	cout << "Время поиска 100 000 элементов в хэш таблице: " << time << "сек" << endl;


	human_mass mass = human_mass(100'000);

	for (int i = 0; i < 100'000; i++)
		mass.add_elem(generate_human());

	for (int i = 0; i < 10'000; i++)
	{
		mass_keys[i] = search_key();
		mass.find_elem(mass_keys[i].surname, mass_keys[i].age);
	}

	time = timer_check();
	cout << "Время поиска 10 000 элементов в массиве: " << time << "сек" << endl;

	_getch();

}