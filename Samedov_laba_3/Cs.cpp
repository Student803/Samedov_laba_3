#include "Cs.h"
void Cs::Stop()  {
	if (quantityInWork > 0)
		quantityInWork--;
	else
		cout << "��� ���� ���������" << endl;
}
void Cs::Launch() {
		if (quantityInWork < quantity)
			quantityInWork++;
		else
			cout << "��� ���� ��������" << endl;
}