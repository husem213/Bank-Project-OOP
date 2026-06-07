#pragma once
#include <iostream>
#include "clsScreen.h"
#include "Global.h"
#include "clsBankUser.h"
#include "clsUtil.h"
#include "clsInputValidate.h"
#include "clsMainScreen.h"
#include "clsDate.h"

using namespace std;

class clsLoginScreen : protected clsScreen
{
public:

	static bool ShowLoginScreen()
	{
		string Title = clsUtil::Tabs(7) + "Login";
		system("cls");
		_DrawScreenHeader(Title);
		string Username, Password;
		short Trials = 3;
		bool LoginFailed = false;

		do
		{
			if (LoginFailed)
			{
				Trials--;
				cout << "\n\tInvalid username/password!\n";
				cout << "\tYou have " << Trials << " trials left\n";
				if (Trials == 0)
				{
					cout << "\n\tYou are locked after 3 failed trials.";
					return false;
				}
			}
			Username = clsInputValidate::ReadString("\tEnter username:");
			Password = clsInputValidate::ReadString("\tEnter password:");
			CurrentUser = clsBankUser::Find(Username, Password);
			LoginFailed = CurrentUser.IsEmpty();
		} while (LoginFailed);
		CurrentUser.RegisterLogin();
		clsMainScreen::MainScreen();
		return true;
	}
};

