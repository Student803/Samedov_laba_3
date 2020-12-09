#include <regex>	
inline bool isPositiveFloat(const string& s)
{
	const regex digit_regex("^[0-9]+(\,[0-9])?[0-9]*$");
	return regex_match(s, digit_regex);
}

inline bool isPositiveInteger(const string& s)
{
	const regex digit_regex("^[0-9]+$");
	return regex_match(s, digit_regex);
}

inline float inputPositiveFloat(const string& msg)
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

inline int inputPositiveInteger(const string& msg) {
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