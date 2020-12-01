#include <iostream>
#include <fstream>
#include <vector>
#include <regex>	
#include "Cs.h"
#include "Tube.h"
using namespace std;




// ? - �� 0 �� 1
// * - �� 0 �� +����
// + - �� 1 �� +����
// \ - ����. ������

bool isPositiveFloat(const string& s)	
{
	const regex digit_regex("^[0-9]+(\,[0-9])?[0-9]*$");
	return regex_match(s, digit_regex);
}

bool isPositiveInteger(const string& s)
{
	const regex digit_regex("^[0-9]+$");
	return regex_match(s, digit_regex);
}

float inputPositiveFloat(const string& msg)
{
	char str[20];
	bool first = true;
	do {
		if (!first) cout << "������������ ����, ������� ��� ��� >> ";
		cout << msg;
		cin >> str;
		first = false;
	} while (!isPositiveFloat(str));
	return atof(str);	// atof ���������� float
}

int inputPositiveInteger(const string& msg) {
	char str[20];
	bool first = true;
	do {
		if (!first) cout << "������������ ����, ������� ��� ��� >> ";
		cout << msg;
		cin >> str;
		first = false;
	} while (!isPositiveInteger(str));
	return atoi(str);	// atoi ���������� int
}

void AddTube(int& idTube, vector<Tube>& arrTube) {
	Tube tube1;
	tube1.id = idTube;
	tube1.length = inputPositiveFloat("������� �����: ");
	tube1.diam = inputPositiveFloat("������� �������: ");
	arrTube.push_back(tube1);
	idTube++;
}

void AddCs(int& idCs, vector<Cs>& arrCs) {
	Cs cs1;
	cs1.id = idCs;
	cout << "������� ������������: ";
	cin >> cs1.name;
	cs1.quantity = inputPositiveInteger("������� ���������� �����: ");
	int cur = inputPositiveInteger("������� ���������� ����� � ������: ");
	while (cur > cs1.quantity) {
		cout << "��������� ����� ������ ���������� �����! ";
		cur = inputPositiveInteger("������� ���������� ����� � ������: ");
	}
	cs1.quantityInWork = cur;
	cs1.efficiency = inputPositiveFloat("������� ���������� �������������: ");
	cout << endl;
	arrCs.push_back(cs1);
	idCs++;
}

void DeleteTube(vector<Tube>& arrTube) {
	int command = inputPositiveInteger("������� ����� �����: ");
	if (arrTube.size() < command) {
		cout << "���������� ���� ������ " << command << endl;
	}
	else {
		arrTube.erase(arrTube.begin() + command - 1);
	}
}

void View(vector<Tube>& arrTube, vector<Cs>& arrCs) {
	int	idCs = 1;
	int idTube = 1;
	for (auto &it : arrCs) {
		cout << "������������� ������� �: " << idCs++ << endl;
		cout << "������������: " << it.name << endl;
		cout << "���������� �����: " << it.quantity << endl;
		cout << "���������� ����� � ������: " << it.quantityInWork << endl;
		cout << "���������� �������������: " << it.efficiency << endl << endl;
	}
	for (auto &it : arrTube) {
		cout << "����� �: " << idTube++ << endl;
		cout << "�����: " << it.length << endl;
		cout << "�������: " << it.diam << endl;
		if (!it.repaired)
			cout << "� �������: ���" << endl << endl;
		else
			cout << "� �������: ��" << endl << endl;
	}
}

void EditTube(vector<Tube>& arrTube) {
	int id;
	id = inputPositiveInteger("������� ����� �����: ");
	if (id > arrTube.size() || id < 1)
	{
		cout << "����� ����� �� ����������! " << endl;
	}
	else
	{
		id = id - 1;
		arrTube[id].Edit();
	}
}

void EditCs(vector<Cs>& arrCs) {
	int id;
	id = inputPositiveInteger("������� ����� ��: ");
	if (id > arrCs.size() || id < 1)
	{
		cout << "����� ������� �� ����������! " << endl;
	}
	else
	{
		int n;
		id = id - 1;
		n = inputPositiveInteger("������� 1, ����� ��������� ���, ��� 2, ����� ���������� ���: ");
		while (n != 1 && n != 2)
		{
			cout << "��������� ����� �� ����� 1 ��� 2! ";
			n = inputPositiveInteger("������� ����� �������: ");
		}
		if (n == 1)
			arrCs[id].Launch();
		else
			arrCs[id].Stop();
	}
}

void Save(vector<Tube>& arrTube, vector<Cs>& arrCs) {
	ofstream outf("text.txt", ios::out);
	if (!outf.is_open())
		cout << "���� �� ����� ���� ������!\n";
	else {
		for (auto &it : arrTube) {
			outf << "tube" << endl;
			outf << it.id << endl;
			outf << it.length << endl;
			outf << it.diam << endl;
		}
		for (auto &it : arrCs) {
			outf << "cs" << endl;
			outf << it.id << endl;
			outf << it.name << endl;
			outf << it.quantity << endl;
			outf << it.quantityInWork << endl;
			outf << it.efficiency << endl;
		}
	}
	outf.close();
}

void Load(vector<Tube>& arrTube, vector<Cs>& arrCs) {
	ifstream fin("text.txt");
	if (!fin.is_open())
		cout << "���� �� ����� ���� ������!\n";
	else
	{
		string buff;
		while (fin >> buff) {
			if (buff == "tube") {
				Tube tube1;
				fin >> tube1.id >> tube1.length >> tube1.diam;
				arrTube.push_back(tube1);
			}
			if (buff == "cs") {
				Cs cs1;
				fin >> cs1.id >> cs1.name >> cs1.quantity >> cs1.quantityInWork >> cs1.efficiency;
				arrCs.push_back(cs1);
			}
		}
	}
	fin.close();
}

void FilterTube(vector<Tube>& arrTube) {
	int n = inputPositiveInteger("������� 1 ��� � �������: �� ��� 2 ��� � �������: ���: ");
	while (n < 1 || n > 2) {
		int n = inputPositiveInteger("������� 1 ��� � �������: �� ��� 2 ��� � �������: ���: ");
	}
	if (n == 1) {
		for (auto &it : arrTube) {
			int idTube = 0;
			idTube++;
			if (it.repaired == true) {
				cout << "����� �: " << idTube << endl;
				cout << "�����: " << it.length << endl;
				cout << "�������: " << it.diam << endl;
				cout << "� �������: ��" << endl << endl;
			}
		}
	}
	if (n == 2) {
		for (auto& it : arrTube) {
			int idTube = 0;
			idTube++;
			if (it.repaired == false) {
				cout << "����� �: " << idTube << endl;
				cout << "�����: " << it.length << endl;
				cout << "�������: " << it.diam << endl;
				cout << "� �������: ���" << endl << endl;
			}
		}
	}
}

void FilterCs(vector<Cs>& arrCs) {
	
	string name;
	cout << "������� �������� �������: " << endl;
	cin >> name; 
	int	idCs = 1;
	for (auto it : arrCs) {
		if (name == it.name) {
			cout << "������������� ������� �: " << idCs++ << endl;
			cout << "������������: " << it.name << endl;
			cout << "���������� �����: " << it.quantity << endl;
			cout << "���������� ����� � ������: " << it.quantityInWork << endl;
			cout << "���������� �������������: " << it.efficiency << endl << endl;
		}
	}
}

void Packet(vector<Tube>& arrTube) {
	vector<int> arr;
	int q;
	q = inputPositiveInteger("������� ���������� ���������, ������� ����� ��������: ");
	while (q > arrTube.size()) {
		cout << "��������� ������, ��� �������� ����������" << endl;
		q = inputPositiveInteger("������� ���������� ���������, ������� ����� ��������");
	}
	cout << "������� ������ id: ";
	for (int i = 0; i < q; i++) {
		int n;
		n = inputPositiveInteger("");
		while (n > arrTube.size()) {
			n = inputPositiveInteger("������� ��� ���: ");
		}
		arr.push_back(n);
	}
	for (auto& it : arr) {
			cout << "�����: ";
			cin >> arrTube[it-1].length;
			cout << "�������: ";
			cin >> arrTube[it-1].diam;
			cout << endl;
	}
}

int main() {
	setlocale(LC_ALL, "Russian");
	vector<Cs> arrCs;
	vector<Tube> arrTube;
	int	idCs = 1;
	int idTube = 1;
	for (;;) {
		int command;
		cout << "1. �������� �����" << endl <<
			"2. �������� ��" << endl <<
			"3. �������� ���� ��������" << endl <<
			"4. ������������� �����" << endl <<
			"5. ������������� ��" << endl <<
			"6. ��������� � ����" << endl <<
			"7. ��������� � ����" << endl <<
			"8. ������� �����" << endl <<
			"9. ������ ����" << endl <<
			"10. ������ �������" << endl <<
			"11. �������� ��������������" << endl <<
			"0. �����" << endl;
		command = inputPositiveInteger("������� ����� �������: ");
		while (command > 11)
		{
			cout << "��������� ����� ������ 11! ";
			command = inputPositiveInteger("������� ����� �������: ");
		}
		switch (command) {
		case 1:
		{
			AddTube(idTube, arrTube);
			break;
		}
		case 2:
		{
			AddCs(idCs, arrCs);
			break;
		}
		case 3:
		{
			View(arrTube, arrCs);
			break;
		}
		case 4:
		{
			EditTube(arrTube);
			break;
		}
		case 5:
		{
			EditCs(arrCs);
			break;
		}
		case 6:
		{
			Save(arrTube, arrCs);
			break;
		}
		case 7:
		{
			Load(arrTube, arrCs);
			break;
		}
		case 8:
		{
			DeleteTube(arrTube);
			break;
		}
		case 9:
		{
			FilterTube(arrTube);
			break;
		}
		case 10:
		{
			FilterCs(arrCs);
			break;
		}
		case 11:
		{
			Packet(arrTube);
			break;
		}
		case 0:
			return 0;
		}
	}
}