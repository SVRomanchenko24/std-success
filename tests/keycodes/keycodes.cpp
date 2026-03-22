#include <iostream>
#include "../../include/ui.h"

using namespace std;

int main()
{
	int keycode;
	while ((keycode = term_getch())!= CONTROL('C')) cout << keycode << '\n';
	return 0;
}
