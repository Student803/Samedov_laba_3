#include "Cs.h"
void Cs::Stop()  {
	if (quantityInWork > 0)
		quantityInWork--;
	else
		cout << "Все цехи выключены" << endl;
}
void Cs::Launch() {
		if (quantityInWork < quantity)
			quantityInWork++;
		else
			cout << "Все цехи включены" << endl;
}