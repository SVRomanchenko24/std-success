#include "../include/ui.h"

bool drawExitWarning()
{
	term_printCentered("Current progress will not be saved, press Ctrl-C to proceed");
	return term_getch()==CONTROL('C');
}
