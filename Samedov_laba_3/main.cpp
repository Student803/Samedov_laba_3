#include <iostream>
#include <fstream>
#include <vector>
#include <regex>	
#include "Cs.h"
#include "Tube.h"
#include <unordered_map>
#include "utils.h"
using namespace std;



// ? - от 0 до 1
// * - от 0 до +беск
// + - от 1 до +беск
// \ - спец. символ



void AddTube(unordered_map<int, Tube>& mapTube) {
	Tube tube1;
	tube1.length = inputPositiveFloat("Введите длину: ");
	tube1.diam = inputPositiveFloat("Введите диаметр: ");
	mapTube.insert(make_pair(tube1.GetId(), tube1));
}

void AddCs(unordered_map<int, Cs>& mapCs) {
	Cs cs1;
	cin >> cs1;
	mapCs.insert(make_pair(cs1.GetId(), cs1));
}

void DeleteTube(unordered_map<int, Tube>& mapTube) {
	int id;
	id = inputPositiveInteger("Введите id трубы: ");
	if (mapTube.find(id) == mapTube.end())
	{
		cout << "Такой трубы не существует! ";
	}
	else {
		mapTube.erase(mapTube.find(id));
	}						
}

void DeleteCs(unordered_map<int, Cs>& mapCs) {
	int id;
	id = inputPositiveInteger("Введите id станции: ");
	if (mapCs.find(id) == mapCs.end())
	{
		cout << "Такой станции не существует! ";
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
	id = inputPositiveInteger("Введите id трубы: ");
	if (mapTube.find(id) == mapTube.end())
	{
		cout << "Такой трубы не существует! ";
	}
	else
	{
		mapTube[id].Edit();
	}
}

void EditCs(unordered_map<int, Cs>& mapCs) {
	int id;
	id = inputPositiveInteger("Введите id КС: ");
	if (mapCs.find(id) == mapCs.end())
	{
		cout << "Такой станции не существует! ";
	}
	else
	{
		int n;
		n = inputPositiveInteger("Введите 1, чтобы запустить цех, или 2, чтобы остановить цех: ");
		while (n != 1 && n != 2)
		{
			cout << "Введенное число не равно 1 или 2! ";
			n = inputPositiveInteger("Введите номер команды: ");
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
		cout << "Файл не может быть открыт!\n";
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
		cout << "Файл не может быть открыт!\n";
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
	int n = inputPositiveInteger("Введите 1 для в ремонте: да или 2 для в ремонте: нет: ");
	while (n < 1 || n > 2) {
		int n = inputPositiveInteger("Введите 1 для в ремонте: да или 2 для в ремонте: нет: ");
	}
	if (n == 1) {
		for (auto &it : mapTube) {
			if (it.second.repaired == true) {
				cout << "Длина: " << it.second.length << endl;
				cout << "Диаметр: " << it.second.diam << endl;
				cout << "В ремонте: да" << endl << endl;
			}
		}
	}
	if (n == 2) {
		for (auto& it : mapTube) {
			if (it.second.repaired == false) {
				cout << "Длина: " << it.second.length << endl;
				cout << "Диаметр: " << it.second.diam << endl;
				cout << "В ремонте: нет" << endl << endl;
			}
		}
	}
}

void FilterCs(unordered_map<int, Cs>& mapCs) {
	
	string name;
	cout << "Введите название станции: " << endl;
	cin >> name; 
	for (auto it : mapCs) {
		if (name == it.second.name) {
			cout << "Наименование: " << it.second.name << endl;
			cout << "Количество цехов: " << it.second.quantity << endl;
			cout << "Количество цехов в работе: " << it.second.quantityInWork << endl;
			cout << "Показатель эффективности: " << it.second.efficiency << endl << endl;
		}
	}
}

void Packet(unordered_map<int, Tube>& mapTube) {
	vector<int> arr;
	int q;
	q = inputPositiveInteger("Введите количество элементов, которые нужно изменить: ");
	while (q > mapTube.size()) {
		cout << "Элементов меньше, чем введённое количество" << endl;
		q = inputPositiveInteger("Введите количество элементов, которые нужно изменить");
	}
	cout << "Введите номера id: ";
	for (int i = 0; i < q; i++) {
		int id;
		id = inputPositiveInteger("");
		while (mapTube.find(id) == mapTube.end()) {
			id = inputPositiveInteger("Введите ещё раз: ");
		}
		arr.push_back(id);
	}
	for (auto& it : arr) {
			cout << "Длина: ";
			cin >> mapTube[it].length;
			cout << "Диаметр: ";
			cin >> mapTube[it].diam;
			cout << endl;
	}
}

void Graph(vector<Tube>& arrTube, vector<Cs>& arrCs, vector<vector<int>>& arr) {
	int n = inputPositiveInteger("Нажмите 1, чтобы обнулить матрицу смежности: ");
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
		i1 = inputPositiveInteger("Введите номер id кс, от которого идёт труба: ");
		i2 = inputPositiveInteger("Введите номер id кс, к которому идёт труба: ");
		if (i1 > arrCs.size() || i2 > arrCs.size()) {
			cout << "Количество труб меньше" << endl;
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
		cout << "1. Добавить трубу" << endl <<
			"2. Добавить КС" << endl <<
			"3. Просмотр всех объектов" << endl <<
			"4. Редактировать трубу" << endl <<
			"5. Редактировать КС" << endl <<
			"6. Сохранить в файл" << endl <<
			"7. Загрузить в файл" << endl <<
			"8. Удалить трубу" << endl <<
			"9. Удалить КС" << endl <<
			"10. Фильтр труб" << endl <<
			"11. Фильтр станций" << endl <<
			"12. Пакетное редактирование" << endl <<
			"0. Выход" << endl;
		command = inputPositiveInteger("Введите номер команды: ");
		while (command > 12)
		{
			cout << "Введенное число больше 12! ";
			command = inputPositiveInteger("Введите номер команды: ");
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

// Перегрузка операторов
// id сделать private
// векторы поменять на мапы