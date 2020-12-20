#pragma once
#include <iostream>

using namespace std;
class Tube
{
private: 
	int id;
public:
	Tube();
	Tube(int needed);
	static int MAX_ID;
	float length;
	float diam;
	bool repaired = false;
	void Edit();
	int GetId();
	void SetId(int id);
	bool used = false;
	friend std::ostream& operator << (std::ostream& out, const Tube& tube);
	friend std::ifstream& operator >> (std::ifstream& fin, Tube& tube);
	friend std::ofstream& operator << (std::ofstream& fout, Tube& tube);
	friend std::istream& operator >> (std::istream& in, Tube& tube);
};
