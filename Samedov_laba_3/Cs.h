#pragma once
#include <iostream>
using namespace std;
class Cs
{
private:
	int id;
public:
	Cs();
	Cs(int needed);
	static int MAX_ID;
	string name;
	int quantity;
	int quantityInWork;
	float efficiency;
	void Stop();
	void Launch();
	int GetId();
	void SetId(int id);
	friend std::ostream& operator << (std::ostream& out, const Cs& cs);
	friend std::ifstream& operator >> (std::ifstream& fin, Cs& cs);
	friend std::ofstream& operator << (std::ofstream& fout, Cs& cs);
	friend std::istream& operator >> (std::istream& in, Cs& cs);
};
