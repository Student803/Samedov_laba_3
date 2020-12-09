#pragma once
#include "Cs.h"
#include <fstream>
#include <string>
#include "utils.h"

void Cs::Stop()  {
	if (quantityInWork > 0)
		quantityInWork--;
	else
		cout << "Все цехи выключены" << endl;
}
void Cs::Launch() {
		if (quantityInWork < quantity)
			quantityInWork++;
		else
			cout << "Все цехи включены" << endl;
}
int Cs::GetId() {
	return id;
}
void Cs::SetId(int id) {
	this->id = id;
}

int Cs::MAX_ID = 1;

Cs::Cs() {
	id = MAX_ID++;
}

Cs::Cs(int needed)
{
	if (needed != -1)
		id = ++MAX_ID;
}

std::ostream& operator << (std::ostream& out, const Cs& cs)
{
	out << "Id №: " << cs.id << endl;
	out << "Наименование: " << cs.name << endl;
	out << "Количество цехов: " << cs.quantity << endl;
	out << "Количество цехов в работе: " << cs.quantityInWork << endl;
	out << "Показатель эффективности: " << cs.efficiency << endl << endl;
	return out;
}

std::ifstream& operator >> (std::ifstream& fin, Cs& cs)
{
	fin >> cs.id >> cs.name >> cs.quantity >> cs.quantityInWork >> cs.efficiency;
	return fin;
}

std::ofstream& operator << (std::ofstream& fout, Cs& cs)
{
	fout << "cs" << endl;
	fout << cs.id << endl;
	fout << cs.name << endl;
	fout << cs.quantity << endl;
	fout << cs.quantityInWork << endl;
	fout << cs.efficiency << endl;
	return fout;
}

istream& operator >> (istream& in, Cs& cs)
{
	cout << "Введите наименование: ";
	cin >> cs.name;
	cs.quantity = inputPositiveInteger("Введите количество цехов: ");
	int cur = inputPositiveInteger("Введите количество цехов в работе: ");
	while (cur > cs.quantity) {
		cout << "Введенное число больше количества цехов! ";
		cur = inputPositiveInteger("Введите количество цехов в работе: ");
	}
	cs.quantityInWork = cur;
	cs.efficiency = inputPositiveFloat("Введите показатель эффективности: ");
	cout << endl;
	return in;
}