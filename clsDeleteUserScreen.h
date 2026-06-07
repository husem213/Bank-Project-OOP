#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankUser.h"
#include "clsInputValidate.h"
#include "clsUtil.h"

using namespace std;

class clsDeleteUserScreen : protected clsScreen
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

	static void ShowDeleteUserScreen()
	{
		string Title = clsUtil::Tabs(7) + "Delete User Screen";
		_DrawScreenHeader(Title);

		string Username = clsInputValidate::ReadString("\tEnter username of the user you want to delete: ");
		while (!clsBankUser::IsUserExist(Username))
		{
			Username = clsInputValidate::ReadString("\tUser does not exist. Enter a new username: ");
		}
		clsBankUser User = clsBankUser::Find(Username);
		_Print(User);

		char Check = 'n';
		cout << "\n\tAre you sure you want to delete this User? Yes [y], No [n] : ";
		cin >> Check;

		if (toupper(Check) == 'Y')
		{
			if (User.Delete())
			{
				cout << "\n\tUser deleted successfully!";
				_Print(User);
			}
			else
			{
				cout << "\n\tError! User was not deleted!";
			}
		}
	}
};

