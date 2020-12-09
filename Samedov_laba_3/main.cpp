#include <iostream>
#include <fstream>
#include <vector>
#include <regex>	
#include "Cs.h"
#include "Tube.h"
#include <unordered_map>
#include "utils.h"
using namespace std;



// ? - �� 0 �� 1
// * - �� 0 �� +����
// + - �� 1 �� +����
// \ - ����. ������



void AddTube(unordered_map<int, Tube>& mapTube) {
	Tube tube1;
	tube1.length = inputPositiveFloat("������� �����: ");
	tube1.diam = inputPositiveFloat("������� �������: ");
	mapTube.insert(make_pair(tube1.GetId(), tube1));
}

void AddCs(unordered_map<int, Cs>& mapCs) {
	Cs cs1;
	cin >> cs1;
	mapCs.insert(make_pair(cs1.GetId(), cs1));
}

void DeleteTube(unordered_map<int, Tube>& mapTube) {
	int id;
	id = inputPositiveInteger("������� id �����: ");
	if (mapTube.find(id) == mapTube.end())
	{
		cout << "����� ����� �� ����������! ";
	}
	else {
		mapTube.erase(mapTube.find(id));
	}						
}

void DeleteCs(unordered_map<int, Cs>& mapCs) {
	int id;
	id = inputPositiveInteger("������� id �������: ");
	if (mapCs.find(id) == mapCs.end())
	{
		cout << "����� ������� �� ����������! ";
	}
	else {
		mapCs.erase(mapCs.find(id));
	}
}

void View(unordered_map<int, Tube>& mapTube, unordered_map<int, Cs>& mapCs) {

	for (auto &it : mapCs) {
		cout << it.second;
	}
	for (auto &it : mapTube) {
		cout << it.second;
	}
}

void EditTube(unordered_map<int, Tube>& mapTube) {
	int id;
	id = inputPositiveInteger("������� id �����: ");
	if (mapTube.find(id) == mapTube.end())
	{
		cout << "����� ����� �� ����������! ";
	}
	else
	{
		mapTube[id].Edit();
	}
}

void EditCs(unordered_map<int, Cs>& mapCs) {
	int id;
	id = inputPositiveInteger("������� id ��: ");
	if (mapCs.find(id) == mapCs.end())
	{
		cout << "����� ������� �� ����������! ";
	}
	else
	{
		int n;
		n = inputPositiveInteger("������� 1, ����� ��������� ���, ��� 2, ����� ���������� ���: ");
		while (n != 1 && n != 2)
		{
			cout << "��������� ����� �� ����� 1 ��� 2! ";
			n = inputPositiveInteger("������� ����� �������: ");
		}
		if (n == 1)
			mapCs[id].Launch();
		else
			mapCs[id].Stop();
	}
}

void Save(unordered_map<int, Tube>& mapTube, unordered_map<int, Cs>& mapCs) {
	ofstream fout("text.txt", ios::out);
	if (!fout.is_open())
		cout << "���� �� ����� ���� ������!\n";
	else {
		for (auto &it : mapTube) {
			fout << it.second;
		}
		for (auto &it : mapCs) {
			fout << it.second;
		}
	}
	fout.close();
}

void Load(unordered_map<int, Tube>& mapTube, unordered_map<int, Cs>& mapCs) {
	ifstream fin("text.txt");
	int id;
	if (!fin.is_open())
		cout << "���� �� ����� ���� ������!\n";
	else
	{
		mapTube.clear();
		mapCs.clear();
		string buff;
		int maxid1 = 1;
		int maxid2 = 1;
		while (fin >> buff) {
			if (buff == "tube") {
				Tube tube1(-1);
				fin >> tube1;
				mapTube.insert(make_pair(tube1.GetId(), tube1));
				if (maxid1 < tube1.GetId()) maxid1 = tube1.GetId() + 1;
			}
			if (buff == "cs") {
				Cs cs1(-1);
				fin >> cs1;
				mapCs.insert(make_pair(cs1.GetId(), cs1));
				if (maxid2 < cs1.GetId()) maxid2 = cs1.GetId() + 1;
			}
		}
		Tube::MAX_ID = maxid1;
		Cs::MAX_ID = maxid2;
	}
	fin.close();
}

void FilterTube(unordered_map<int, Tube>& mapTube) {
	int n = inputPositiveInteger("������� 1 ��� � �������: �� ��� 2 ��� � �������: ���: ");
	while (n < 1 || n > 2) {
		int n = inputPositiveInteger("������� 1 ��� � �������: �� ��� 2 ��� � �������: ���: ");
	}
	if (n == 1) {
		for (auto &it : mapTube) {
			if (it.second.repaired == true) {
				cout << "�����: " << it.second.length << endl;
				cout << "�������: " << it.second.diam << endl;
				cout << "� �������: ��" << endl << endl;
			}
		}
	}
	if (n == 2) {
		for (auto& it : mapTube) {
			if (it.second.repaired == false) {
				cout << "�����: " << it.second.length << endl;
				cout << "�������: " << it.second.diam << endl;
				cout << "� �������: ���" << endl << endl;
			}
		}
	}
}

void FilterCs(unordered_map<int, Cs>& mapCs) {
	
	string name;
	cout << "������� �������� �������: " << endl;
	cin >> name; 
	for (auto it : mapCs) {
		if (name == it.second.name) {
			cout << "������������: " << it.second.name << endl;
			cout << "���������� �����: " << it.second.quantity << endl;
			cout << "���������� ����� � ������: " << it.second.quantityInWork << endl;
			cout << "���������� �������������: " << it.second.efficiency << endl << endl;
		}
	}
}

void Packet(unordered_map<int, Tube>& mapTube) {
	vector<int> arr;
	int q;
	q = inputPositiveInteger("������� ���������� ���������, ������� ����� ��������: ");
	while (q > mapTube.size()) {
		cout << "��������� ������, ��� �������� ����������" << endl;
		q = inputPositiveInteger("������� ���������� ���������, ������� ����� ��������");
	}
	cout << "������� ������ id: ";
	for (int i = 0; i < q; i++) {
		int id;
		id = inputPositiveInteger("");
		while (mapTube.find(id) == mapTube.end()) {
			id = inputPositiveInteger("������� ��� ���: ");
		}
		arr.push_back(id);
	}
	for (auto& it : arr) {
			cout << "�����: ";
			cin >> mapTube[it].length;
			cout << "�������: ";
			cin >> mapTube[it].diam;
			cout << endl;
	}
}

void Graph(vector<Tube>& arrTube, vector<Cs>& arrCs, vector<vector<int>>& arr) {
	int n = inputPositiveInteger("������� 1, ����� �������� ������� ���������: ");
		if (n == 1) {
			arr.resize(arrCs.size());
			for (int i = 0; i < arrCs.size(); i++) {
				arr[i].resize(arrCs.size());
				for (int k = 0; k < arrCs.size(); k++) {
					arr[i][k] = 0;
				}
			}
		}
		int i1;
		int i2;
		i1 = inputPositiveInteger("������� ����� id ��, �� �������� ��� �����: ");
		i2 = inputPositiveInteger("������� ����� id ��, � �������� ��� �����: ");
		if (i1 > arrCs.size() || i2 > arrCs.size()) {
			cout << "���������� ���� ������" << endl;
		}
		else
		arr[i1 - 1][i2 - 1] = 1;
}

void ViewGraph(vector<vector<int>>& arr) {
	for (int i = 0; i < arr.size(); i++) {
		for (int k = 0; k < arr.size(); k++) {
			cout << arr[i][k] << " ";
		}
		cout << endl;
	}
}



int main() {
	setlocale(LC_ALL, "Russian");
	unordered_map<int, Tube> mapTube;
	unordered_map<int, Cs> mapCs;
	vector<vector<int>> arr;
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
			"9. ������� ��" << endl <<
			"10. ������ ����" << endl <<
			"11. ������ �������" << endl <<
			"12. �������� ��������������" << endl <<
			"0. �����" << endl;
		command = inputPositiveInteger("������� ����� �������: ");
		while (command > 12)
		{
			cout << "��������� ����� ������ 12! ";
			command = inputPositiveInteger("������� ����� �������: ");
		}
		switch (command) {
		case 1:
		{
			AddTube(mapTube);
			break;
		}
		case 2:
		{
			AddCs(mapCs);
			break;
		}
		case 3:
		{
			View(mapTube, mapCs);
			break;
		}
		case 4:
		{
			EditTube(mapTube);
			break;
		}
		case 5:
		{
			EditCs(mapCs);
			break;
		}
		case 6:
		{
			Save(mapTube, mapCs);
			break;
		}
		case 7:
		{
			Load(mapTube, mapCs);
			break;
		}
		case 8:
		{
			DeleteTube(mapTube);
			break;
		}
		case 9:
		{
			DeleteCs(mapCs);
			break;
		}
		case 10:
		{
			FilterTube(mapTube);
			break;
		}
		case 11:
		{
			FilterCs(mapCs);
			break;
		}
		case 12:
		{
			Packet(mapTube);
			break;
		}
		case 0:
			return 0;
		}
	}
}

// ���������� ����������
// id ������� private
// ������� �������� �� ����