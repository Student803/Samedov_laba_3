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
	out << "Id �: " << tube.id << endl;
	out << "�����: " << tube.length << endl;
	out << "�������: " << tube.diam << endl;
	if (!tube.repaired)
		out << "� �������: ���" << endl << endl;
	else
		out << "� �������: ��" << endl << endl;
	return out;
}

std::ifstream& operator >> (std::ifstream& fin, Tube& tube)
{
	fin >> tube.id >> tube.length >> tube.diam;
	return fin;
}

std::ofstream& operator << (std::ofstream& fout, Tube& tube)
{
	fout << "tube" << " ";
	fout << tube.id << " ";
	fout << tube.length << " ";
	fout << tube.diam<< endl;
	return fout;
}

istream& operator >> (istream& in, Tube& tube)
{
	tube.length = inputPositiveFloat("������� �����: ");
	tube.diam = inputPositiveFloat("������� �������: ");
	return in;
}