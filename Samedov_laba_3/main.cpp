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
	cin >> tube1;
	mapTube.insert(make_pair(tube1.GetId(), tube1));
}

void AddCs(unordered_map<int, Cs>& mapCs) {
	Cs cs1;
	cin >> cs1;
	mapCs.insert(make_pair(cs1.GetId(), cs1));
}

void DeleteTube(unordered_map<int, Tube>& mapTube, unordered_map<int, vector<pair<int, int>>>& graph) {
	int id;
	id = inputPositiveInteger("Введите id трубы: ");
	if (mapTube.find(id) == mapTube.end())
	{
		cout << "Такой трубы не существует!" << endl;
	}
	else {
		mapTube.erase(mapTube.find(id));
		int i = -1;
		int i2;
		int x = 0;
		for (auto& it : graph) {
			i2 = it.first;
			for (auto& it2 : it.second) {
				i++;
				if (it2.second == id) {
					it.second.erase(it.second.begin() + i);
					x = -2;
					break;
				}
			//	i2++;
			}
			if (graph[i2].size() == 0)
				graph.erase(i2);
			if (x == -2) break;
			i = -1;
		}
	}						
}

void DeleteCs(unordered_map<int, Cs>& mapCs,  unordered_map<int, Tube>& mapTube, unordered_map<int, vector<pair<int, int>>>& graph) {
	int id;
	id = inputPositiveInteger("Введите id станции: ");
	if (mapCs.find(id) == mapCs.end())
	{
		cout << "Такой станции не существует!" << endl;
	}
	else 
	{
		mapCs.erase(mapCs.find(id));
		unordered_map<int, vector<pair<int, int>>> arr = graph;
		for (auto& it : arr) {
			int i2 = -1;
			if (it.first == id) {
				cout << "Удаляю кс с id: " << id << endl;
				for (auto& it2 : it.second) {
					graph[it2.first].clear();
					mapTube[it2.second].used = false;
				}
				graph.erase(id);
			}
		}
		arr = graph;
		for (auto& it : arr) {
			int i2 = -1;
			for (auto& it2 : it.second) {
				i2++;
				if (it2.first == id)
				{
					graph[it.first].erase(graph[it.first].begin() + i2);
					mapTube[i2+1].used = false;
				}
			}
		}
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

void EditTube(unordered_map<int, Tube>& mapTube, unordered_map<int, vector<pair<int, int>>>& graph) {
	int id;
	id = inputPositiveInteger("Введите id трубы: ");
	if (mapTube.find(id) == mapTube.end())
	{
		cout << "Такой трубы не существует! ";
	}
	else
	{										
		mapTube[id].Edit();
		if (mapTube[id].repaired == true) {
			mapTube[id].used = false;
			int i = -1;
			int i2;
			int x = 0;
			for (auto& it : graph) {
				i2 = it.first;
				for (auto& it2 : it.second) {
					i++;
					if (it2.second == id) {
						it.second.erase(it.second.begin() + i);
						x = -2;
						break;
					}
					i2++;
				}
				if (graph[i2].size() == 0)
					graph.erase(i2);
				if (x == -2) break;
				i = -1;
			}
			cout << i << endl;
		}
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

void OutputGraphToFile(unordered_map<int, Tube>& mapTube, unordered_map<int, Cs>& mapCs, unordered_map<int, vector<pair<int, int>>>& graph)
{

	ofstream fout;
	fout.open("text.txt");
	if (!fout.is_open())
		cout << "Файл не может быть открыт!\n";
	else
	{
		for (auto& it : mapTube) {
			fout << it.second;
		}
		for (auto& it : mapCs) {
			fout << it.second;
		}
		for (auto& it : graph)
		{
			fout << it.second.size() << " ";
			fout << it.first << " ";
			for (auto& it2 : it.second)
			{
				fout << it2.first << " " << it2.second << " ";
			}
			fout << endl;
		}
		cout << "Вывели в файл данные" << endl;
		fout.close();
	}
}

bool IsNumber(const string& s) {
	return all_of(s.cbegin(), s.cend(), [](const char& c) {
		return isdigit(c);
		});
}

void InputGraphFromFile(unordered_map<int, Tube>& mapTube, unordered_map<int, Cs>& mapCs, unordered_map<int, vector<pair<int, int>>>& graph)
{


	ifstream fin("text.txt");
	if (!fin.is_open())
		cout << "Файл не может быть открыт!\n";
	else
	{
		graph.clear();
		mapTube.clear();
		mapCs.clear();
		int buff;
		string buff2;
		int maxid1 = 1;
		int maxid2 = 1;
		while (fin >> buff2)
		{			
			if (buff2 == "tube") {
				Tube tube1(-1);
				fin >> tube1;
				mapTube.insert(make_pair(tube1.GetId(), tube1));
				if (maxid1 <= tube1.GetId()) maxid1 = tube1.GetId() + 1;
			}
			if (buff2 == "cs") {
				Cs cs1(-1);
				fin >> cs1;
				mapCs.insert(make_pair(cs1.GetId(), cs1));
				if (maxid2 <= cs1.GetId()) maxid2 = cs1.GetId() + 1;
			}
			if (IsNumber(buff2)) {
				buff = atoi(buff2.c_str());
				int Csid1;
				fin >> Csid1;
				for (int i = 0; i < buff; i++)
				{
					int Csid2;
					fin >> Csid2;
					int Tubeid;
					fin >> Tubeid;
					pair<int, int> p(Csid2, Tubeid);
					mapTube[Tubeid].used = true;
					graph[Csid1].push_back(p);
				}
			}
		}

		Tube::MAX_ID = maxid1;
		Cs::MAX_ID = maxid2;
		cout << "Ввели из файла данные" << endl;
		fin.close();
	}

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
	for (auto& it : mapCs) {
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
		q = inputPositiveInteger("Введите количество элементов, которые нужно изменить: ");
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

void Create(unordered_map<int, Tube>& mapTube, unordered_map<int, Cs>& mapCs, unordered_map<int, vector<pair<int, int>>>& graph) {
	int count = 0;
	for (auto& it : mapTube) {
		if (it.second.used == false && it.second.repaired == false)
		{
			count++;
			break;
		}
	}
	if (count == 0) {
		cout << "Свободных труб нет" << endl;
		return;
	} 
	if (mapCs.size() < 2) {
		cout << "Недостаточно станций" << endl;
		return;
	}


	int id1 = inputPositiveInteger("Введите id станции, от которой идёт труба: ");		
	while (mapCs.find(id1) == mapCs.end()) {
		id1 = inputPositiveInteger("Введите ещё раз: ");			
	}

	int id2 = inputPositiveInteger("Введите id станции, к которой идёт труба: ");
	while (mapCs.find(id2) == mapCs.end()) {
		id2 = inputPositiveInteger("Введите ещё раз: ");
	}
	if (id2 == id1) {
		cout << "id станций совпадают" << endl;
		return;
	}

	int id3 = inputPositiveInteger("Введите id трубы, которая соединяет станции: ");
	while (mapTube.find(id3) == mapTube.end()) {
		id3 = inputPositiveInteger("Введите ещё раз: ");
	}
	if (mapTube[id3].used == true)
	{
		cout << "Эта труба уже используется" << endl;
		return;
	}
	mapTube[id3].used = true;
	pair<int, int> p2(id2, id3);

	graph[id1].push_back(p2);
}

void Display(unordered_map<int, vector<pair<int, int>>>& graph) {
	for (auto& it : graph) {
		for (auto& it2 : it.second) {
			cout << it.first << " к " << it2.first << " с id трубы: " << it2.second << endl; // Убрал длины и mapTube
		}
	}
	cout << endl;
}

void dfs(int v, unordered_map<int, vector<pair<int, int>>>& g, unordered_map<int, bool>& count, vector<int>& ans) {
	count[v] = true;
	vector<pair<int, int>> arr;
	if (g.find(v) != g.end()) {

		arr = g[v];
		for (auto& el : arr) {
			int to = el.first;

			if (!count[to])
				dfs(to, g, count, ans);
		}
	}
	ans.push_back(v);
}

unordered_map<int, bool> countCS(unordered_map<int, vector<pair<int, int>>>& g)
{
	unordered_map<int, bool> countArr;
	for (auto& el : g)
	{
		countArr[el.first] = false;
		for (auto& p1 : el.second)
		{
			countArr[p1.first] = false;
		}
	}
	return countArr;
}

void topologicalSort(unordered_map<int, vector<pair<int, int>>>& g, unordered_map<int, bool>& count, vector<int>& ans) {
	count = countCS(g);

	ans.clear();
	for (auto& el : count)
		if (!el.second)
			dfs(el.first, g, count, ans);
	reverse(ans.begin(), ans.end());
}

unordered_map<int, int> visitedCS(unordered_map<int, vector<pair<int, int>>>& g)
{
	unordered_map<int, int> countArr;
	for (auto& el : g)
	{
		countArr[el.first] = 0;
		for (auto& p1 : el.second)
		{
			countArr[p1.first] = 0;
		}
	}
	return countArr;
}

bool dfs2(int v, unordered_map<int, vector<pair<int, int>>>& g, unordered_map<int, int>& cl, int& cycle_st) {
	if (g.find(v) == g.end())
	{
		return false;
	}
	cl[v] = 1;
	for (size_t i = 0; i < g[v].size(); ++i) {
		int to;

		to = g[v][i].first;
		if (cl[to] == 0) {
			if (dfs2(to, g, cl, cycle_st))  return true;
		}
		else if (cl[to] == 1) {
			//cycle_end = v;
			cycle_st = to;
			return true;
		}
	}
	cl[v] = 2;
	return false;
}

bool searchForCycle(unordered_map<int, vector<pair<int, int>>>& graph)
{
	//vector<char> cl;
	unordered_map<int, int> p;
	int cycle_st, cycle_end;
	p = visitedCS(graph);
	//cl.assign(p.size(), 0);
	cycle_st = -1;
	for (auto& el : p)
		if (dfs2(el.first, graph, p, cycle_st)) break;
	if (cycle_st == -1) return false;
	else return true;
}

void DeleteGraph(unordered_map<int, vector<pair<int, int>>>& graph) {
	graph.clear();
}

int main() {
	setlocale(LC_ALL, "Russian");
	unordered_map<int, Tube> mapTube;
	unordered_map<int, Cs> mapCs;
	unordered_map<int, vector<pair<int, int>>> graph;
	vector<int> ans;
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
			"13. Создать граф" << endl <<
			"14. Показать граф" << endl <<
			"15. Топологическая сортировка" << endl <<
			"16. Удалить граф" << endl <<
			"0. Выход" << endl;
		command = inputPositiveInteger("Введите номер команды: ");
		while (command > 16)
		{
			cout << "Введенное число больше 16! ";
			command = inputPositiveInteger("Введите номер команды: ");
		}
		switch (command) {
		case 16: {
			DeleteGraph(graph);
			break;
		}
		case 7:
		{
			InputGraphFromFile(mapTube, mapCs, graph);
			break;
		};
		case 6:
		{
			OutputGraphToFile(mapTube, mapCs, graph);
			break;
		};
		case 15:
		{
			if (!searchForCycle(graph))
			{
				unordered_map<int, bool> count;
			//	vector<int> ans;
				topologicalSort(graph, count, ans);
				for (auto index = ans.begin(); index != ans.end(); index++)
				{
					cout << *index;
					if (index + 1 != ans.end()) cout << " -> ";
				}
			}
			else
			{
				cout << "Граф цикличный!";
			}
			cout << endl;
			break;
		};
		case 14:
		{
			Display(graph);
			break;
		}
		case 13:
		{
			Create(mapTube, mapCs, graph);
			break;
		}
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
			EditTube(mapTube, graph);
			break;
		}
		case 5:
		{
			EditCs(mapCs);
			break;
		}
		case 8:
		{
			DeleteTube(mapTube, graph);
			break;
		}
		case 9:
		{
			DeleteCs(mapCs, mapTube, graph);
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