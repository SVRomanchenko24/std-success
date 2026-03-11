#include <iostream>
#include "../include/ui.h"
#include "../include/keycodes.h"
#include "../include/defines.h"

using namespace std;

int main()
{
	term_init();
	short term_maxx, term_maxy;
	term_getTermSize(term_maxx, term_maxy);

	term_setCursorVisibility(0);

	int keycode = 0;
	while (keycode != CONTROL('C'))
	{
		term_clear();
		term_moveCursor(term_maxx/2-2, term_maxy/2);
		cout << keycode;
		keycode = term_getch();
	}

	term_deinit();
	
	return 0;
}
