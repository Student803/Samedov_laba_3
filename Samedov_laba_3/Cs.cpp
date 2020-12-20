#pragma once
#include "Cs.h"
#include <fstream>
#include <string>
#include "utils.h"

void Cs::Stop()  {
	if (quantityInWork > 0)
		quantityInWork--;
	else
		cout << "��� ���� ���������" << endl;
}
void Cs::Launch() {
		if (quantityInWork < quantity)
			quantityInWork++;
		else
			cout << "��� ���� ��������" << endl;
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
	out << "Id �: " << cs.id << endl;
	out << "������������: " << cs.name << endl;
	out << "���������� �����: " << cs.quantity << endl;
	out << "���������� ����� � ������: " << cs.quantityInWork << endl;
	out << "���������� �������������: " << cs.efficiency << endl << endl;
	return out;
}

std::ifstream& operator >> (std::ifstream& fin, Cs& cs)
{
	fin >> cs.id >> cs.name >> cs.quantity >> cs.quantityInWork >> cs.efficiency;
	return fin;
}

std::ofstream& operator << (std::ofstream& fout, Cs& cs)
{
	fout << "cs" << " ";
	fout << cs.id << " ";
	fout << cs.name << " ";
	fout << cs.quantity << " ";
	fout << cs.quantityInWork << " ";
	fout << cs.efficiency << endl;
	return fout;
}

istream& operator >> (istream& in, Cs& cs)
{
	cout << "������� ������������: ";
	cin >> cs.name;
	cs.quantity = inputPositiveInteger("������� ���������� �����: ");
	int cur = inputPositiveInteger("������� ���������� ����� � ������: ");
	while (cur > cs.quantity) {
		cout << "��������� ����� ������ ���������� �����! ";
		cur = inputPositiveInteger("������� ���������� ����� � ������: ");
	}
	cs.quantityInWork = cur;
	cs.efficiency = inputPositiveFloat("������� ���������� �������������: ");
	cout << endl;
	return in;
}