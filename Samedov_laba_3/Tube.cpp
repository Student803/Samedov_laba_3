#include "Tube.h"
#include <fstream>
#include <string>
#include "utils.h"

void Tube::Edit() {
	this->repaired = !this->repaired;
}

int Tube::GetId() {
	return id;
}
void Tube::SetId(int id) {
	this->id = id;
}

int Tube::MAX_ID = 1;

Tube::Tube() {
	id = MAX_ID++;
}

Tube::Tube(int needed)
{
	if (needed != -1)
		id = ++MAX_ID;
}

std::ostream& operator << (std::ostream& out, const Tube& tube)
{
	out << "Id №: " << tube.id << endl;
	out << "Длина: " << tube.length << endl;
	out << "Диаметр: " << tube.diam << endl;
	if (!tube.repaired)
		out << "В ремонте: нет" << endl << endl;
	else
		out << "В ремонте: да" << endl << endl;
	return out;
}

std::ifstream& operator >> (std::ifstream& fin, Tube& tube)
{
	fin >> tube.id >> tube.length >> tube.diam;
	return fin;
}

std::ofstream& operator << (std::ofstream& fout, Tube& tube)
{
	fout << "tube" << endl;
	fout << tube.id << endl;
	fout << tube.length << endl;
	fout << tube.diam<< endl;
	return fout;
}

istream& operator >> (istream& in, Tube& tube)
{
	tube.length = inputPositiveFloat("Введите длину: ");
	tube.diam = inputPositiveFloat("Введите диаметр: ");
	return in;
}