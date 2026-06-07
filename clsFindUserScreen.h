#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankUser.h"
#include "clsInputValidate.h"
#include "clsUtil.h"

using namespace std;

class clsFindUserScreen : protected clsScreen
{
	static void _Print(clsBankUser User)
	{
		cout << "\n" << clsUtil::Tabs(2) << "User Card:\n";
		cout << clsUtil::Tabs(2) << "________________________________\n";
		cout << clsUtil::Tabs(2) << left << setw(12) << "First Name" << ": " << User.FirstName << "\n";
		cout << clsUtil::Tabs(2) << left << setw(12) << "Last Name" << ": " << User.LastName << "\n";
		cout << clsUtil::Tabs(2) << left << setw(12) << "Full Name" << ": " << User.FullName() << "\n";
		cout << clsUtil::Tabs(2) << left << setw(12) << "Email" << ": " << User.Email << "\n";
		cout << clsUtil::Tabs(2) << left << setw(12) << "Phone" << ": " << User.PhoneNumber << "\n";
		cout << clsUtil::Tabs(2) << left << setw(12) << "Username" << ": " << User.Username << "\n";
		cout << clsUtil::Tabs(2) << left << setw(12) << "Password" << ": " << User.Password << "\n";
		cout << clsUtil::Tabs(2) << left << setw(12) << "Permissions" << ": " << User.Permissions << "\n";
		cout << clsUtil::Tabs(2) << "________________________________\n";
	}
public:
	static void ShowFindUserScreen()
	{
		string Title = clsUtil::Tabs(7) + "Find User";
		_DrawScreenHeader(Title);

		string Username = clsInputValidate::ReadString("\tEnter Username: ");

		while (!clsBankUser::IsUserExist(Username))
		{
			Username = clsInputValidate::ReadString("\tUser was not found, enter different Username: ");
		}
		clsBankUser User = clsBankUser::Find(Username);

		if (!User.IsEmpty())
		{
			cout << "\n\tUser is found!\n";
			_Print(User);
		}
		else
		{
			cout << "\n\tUser was not found!";
		}
	}
};

