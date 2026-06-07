#pragma once
#include <iostream>
#include <iomanip>
#include "clsBankUser.h"
#include "clsScreen.h"
#include <vector>
#include "clsUtil.h"
#include <string>

using namespace std;

class clsUsersListScreen : protected clsScreen
{
	static void _UsersTableHeader(int UsersNumber)
	{
		string Title = clsUtil::Tabs(7) + "Users List", Subtitle = clsUtil::Tabs(6) + "       (" + to_string(UsersNumber) + ") user(s)\n";
		clsScreen::_DrawScreenHeader(Title, Subtitle);
		cout << clsUtil::Tabs(2) << "_____________________________________________________________________________________________________________\n\n";
		cout << clsUtil::Tabs(2) << "| " << left << setw(20) << "Username";
		cout << "| " << left << setw(12) << "Password";
		cout << "| " << left << setw(20) << "Full Name";
		cout << "| " << left << setw(20) << "Email";
		cout << "| " << left << setw(15) << "Phone Number";
		cout << "| " << left << setw(10) << "Permissions\n";
		cout << clsUtil::Tabs(2) << "_____________________________________________________________________________________________________________\n\n";
	}

	static void _PrintUserLine(clsBankUser User)
	{
		cout << clsUtil::Tabs(2);
		cout << "| " << left << setw(20) << User.Username;
		cout << "| " << left << setw(12) << User.Password;
		cout << "| " << left << setw(20) << User.FullName();
		cout << "| " << left << setw(20) << User.Email;
		cout << "| " << left << setw(15) << User.PhoneNumber;
		cout << "| " << left << setw(10) << User.Permissions;
		cout << endl;
	}

public:
	static void ShowUsersList()
	{
		vector <clsBankUser> vUsers = clsBankUser::GetUsersList();
		_UsersTableHeader(static_cast<int>(vUsers.size()));
		if (static_cast<int>(vUsers.size()) == 0)
		{
			cout << "\nThere are no users in the system!";
		}
		else
		{
			for (clsBankUser& User : vUsers)
			{
				_PrintUserLine(User);
			}
		}
		cout << clsUtil::Tabs(2) << "_____________________________________________________________________________________________________________\n\n";
	}
};

