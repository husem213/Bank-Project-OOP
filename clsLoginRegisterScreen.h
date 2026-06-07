#pragma once
#include <iostream>
#include "clsScreen.h"
#include "Global.h"
#include "clsBankUser.h"
#include "clsUtil.h"
#include "clsDate.h"

using namespace std;

class clsLoginRegisterScreen : protected clsScreen
{
	static void _TableHeader()
	{
		cout << clsUtil::Tabs(3) << "________________________________________________________________________\n\n";
		cout << clsUtil::Tabs(3) << "| " << left << setw(25) << "Date & Time";
		cout << "| " << left << setw(12) << "Username";
		cout << "| " << left << setw(12) << "Password";
		cout << "| " << left << setw(12) << "Permissions\n";
		cout << clsUtil::Tabs(3) << "________________________________________________________________________\n\n";
	}

	static void _PrintUserLine(clsBankUser::stLoginRegister User)
	{
		cout << clsUtil::Tabs(3) << "| " << left << setw(25) << User.DateAndTimeString;
		cout << "| " << left << setw(12) << User.Username;
		cout << "| " << left << setw(12) << User.Password;
		cout << "| " << left << setw(12) << User.Permissions;
	}

	static void _PrintTable(vector <clsBankUser::stLoginRegister>& vUsers)
	{
		_TableHeader();
		for (clsBankUser::stLoginRegister& User : vUsers)
		{
			_PrintUserLine(User);
			cout << endl;
		}
		cout << clsUtil::Tabs(3) << "________________________________________________________________________\n\n";
	}

public:
	static void ShowLoginRegisterScreen()
	{
		if (!CheckAccessRights(clsBankUser::enPermissions::pLoginRegister))
		{
			return;
		}
		vector <clsBankUser::stLoginRegister> vUsers = clsBankUser::GetLoginRegisterList();
		string Title = clsUtil::Tabs(7) + "Login Register";
		string Subtitle = clsUtil::Tabs(7) + "(" + to_string(static_cast<int>(vUsers.size())) + ") Records";
		_DrawScreenHeader(Title, Subtitle);
		_PrintTable(vUsers);
	}
};

