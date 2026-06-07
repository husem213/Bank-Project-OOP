#include <iostream>
#include "clsLoginScreen.h"

using namespace std;

int main()
{
	srand((unsigned)time(NULL));
	
	bool Run = true;
	while (Run)
	{
		Run = clsLoginScreen::ShowLoginScreen();
	}

	return 0;
}