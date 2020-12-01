#include <iostream>
#include <fstream>
#include <vector>
#include <regex>	
#include "Cs.h"
#include "Tube.h"
using namespace std;




// ? - от 0 до 1
// * - от 0 до +беск
// + - от 1 до +беск
// \ - спец. символ

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
		if (!first) cout << "Некорректный ввод, введите еще раз >> ";
		cout << msg;
		cin >> str;
		first = false;
	} while (!isPositiveFloat(str));
	return atof(str);	// atof возвращает float
}

int inputPositiveInteger(const string& msg) {
	char str[20];
	bool first = true;
	do {
		if (!first) cout << "Некорректный ввод, введите еще раз >> ";
		cout << msg;
		cin >> str;
		first = false;
	} while (!isPositiveInteger(str));
	return atoi(str);	// atoi возвращает int
}

void AddTube(int& idTube, vector<Tube>& arrTube) {
	Tube tube1;
	tube1.id = idTube;
	tube1.length = inputPositiveFloat("Введите длину: ");
	tube1.diam = inputPositiveFloat("Введите диаметр: ");
	arrTube.push_back(tube1);
	idTube++;
}

void AddCs(int& idCs, vector<Cs>& arrCs) {
	Cs cs1;
	cs1.id = idCs;
	cout << "Введите наименование: ";
	cin >> cs1.name;
	cs1.quantity = inputPositiveInteger("Введите количество цехов: ");
	int cur = inputPositiveInteger("Введите количество цехов в работе: ");
	while (cur > cs1.quantity) {
		cout << "Введенное число больше количества цехов! ";
		cur = inputPositiveInteger("Введите количество цехов в работе: ");
	}
	cs1.quantityInWork = cur;
	cs1.efficiency = inputPositiveFloat("Введите показатель эффективности: ");
	cout << endl;
	arrCs.push_back(cs1);
	idCs++;
}

void DeleteTube(vector<Tube>& arrTube) {
	int command = inputPositiveInteger("Введите номер трубы: ");
	if (arrTube.size() < command) {
		cout << "Количество труб меньше " << command << endl;
	}
	else {
		arrTube.erase(arrTube.begin() + command - 1);
	}
}

void View(vector<Tube>& arrTube, vector<Cs>& arrCs) {
	int	idCs = 1;
	int idTube = 1;
	for (auto &it : arrCs) {
		cout << "Компрессорная станция №: " << idCs++ << endl;
		cout << "Наименование: " << it.name << endl;
		cout << "Количество цехов: " << it.quantity << endl;
		cout << "Количество цехов в работе: " << it.quantityInWork << endl;
		cout << "Показатель эффективности: " << it.efficiency << endl << endl;
	}
	for (auto &it : arrTube) {
		cout << "Труба №: " << idTube++ << endl;
		cout << "Длина: " << it.length << endl;
		cout << "Диаметр: " << it.diam << endl;
		if (!it.repaired)
			cout << "В ремонте: нет" << endl << endl;
		else
			cout << "В ремонте: да" << endl << endl;
	}
}

void EditTube(vector<Tube>& arrTube) {
	int id;
	id = inputPositiveInteger("Введите номер трубы: ");
	if (id > arrTube.size() || id < 1)
	{
		cout << "Такой трубы не существует! " << endl;
	}
	else
	{
		id = id - 1;
		arrTube[id].Edit();
	}
}

void EditCs(vector<Cs>& arrCs) {
	int id;
	id = inputPositiveInteger("Введите номер КС: ");
	if (id > arrCs.size() || id < 1)
	{
		cout << "Такой станции не существует! " << endl;
	}
	else
	{
		int n;
		id = id - 1;
		n = inputPositiveInteger("Введите 1, чтобы запустить цех, или 2, чтобы остановить цех: ");
		while (n != 1 && n != 2)
		{
			cout << "Введенное число не равно 1 или 2! ";
			n = inputPositiveInteger("Введите номер команды: ");
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
		cout << "Файл не может быть открыт!\n";
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
		cout << "Файл не может быть открыт!\n";
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
	int n = inputPositiveInteger("Введите 1 для в ремонте: да или 2 для в ремонте: нет: ");
	while (n < 1 || n > 2) {
		int n = inputPositiveInteger("Введите 1 для в ремонте: да или 2 для в ремонте: нет: ");
	}
	if (n == 1) {
		for (auto &it : arrTube) {
			int idTube = 0;
			idTube++;
			if (it.repaired == true) {
				cout << "Труба №: " << idTube << endl;
				cout << "Длина: " << it.length << endl;
				cout << "Диаметр: " << it.diam << endl;
				cout << "В ремонте: да" << endl << endl;
			}
		}
	}
	if (n == 2) {
		for (auto& it : arrTube) {
			int idTube = 0;
			idTube++;
			if (it.repaired == false) {
				cout << "Труба №: " << idTube << endl;
				cout << "Длина: " << it.length << endl;
				cout << "Диаметр: " << it.diam << endl;
				cout << "В ремонте: нет" << endl << endl;
			}
		}
	}
}

void FilterCs(vector<Cs>& arrCs) {
	
	string name;
	cout << "Введите название станции: " << endl;
	cin >> name; 
	int	idCs = 1;
	for (auto it : arrCs) {
		if (name == it.name) {
			cout << "Компрессорная станция №: " << idCs++ << endl;
			cout << "Наименование: " << it.name << endl;
			cout << "Количество цехов: " << it.quantity << endl;
			cout << "Количество цехов в работе: " << it.quantityInWork << endl;
			cout << "Показатель эффективности: " << it.efficiency << endl << endl;
		}
	}
}

void Packet(vector<Tube>& arrTube) {
	vector<int> arr;
	int q;
	q = inputPositiveInteger("Введите количество элементов, которые нужно изменить: ");
	while (q > arrTube.size()) {
		cout << "Элементов меньше, чем введённое количество" << endl;
		q = inputPositiveInteger("Введите количество элементов, которые нужно изменить");
	}
	cout << "Введите номера id: ";
	for (int i = 0; i < q; i++) {
		int n;
		n = inputPositiveInteger("");
		while (n > arrTube.size()) {
			n = inputPositiveInteger("Введите ещё раз: ");
		}
		arr.push_back(n);
	}
	for (auto& it : arr) {
			cout << "Длина: ";
			cin >> arrTube[it-1].length;
			cout << "Диаметр: ";
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
		cout << "1. Добавить трубу" << endl <<
			"2. Добавить КС" << endl <<
			"3. Просмотр всех объектов" << endl <<
			"4. Редактировать трубу" << endl <<
			"5. Редактировать КС" << endl <<
			"6. Сохранить в файл" << endl <<
			"7. Загрузить в файл" << endl <<
			"8. Удалить трубу" << endl <<
			"9. Фильтр труб" << endl <<
			"10. Фильтр станций" << endl <<
			"11. Пакетное редактирование" << endl <<
			"0. Выход" << endl;
		command = inputPositiveInteger("Введите номер команды: ");
		while (command > 11)
		{
			cout << "Введенное число больше 11! ";
			command = inputPositiveInteger("Введите номер команды: ");
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