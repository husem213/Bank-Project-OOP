#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankUser.h"
#include "clsInputValidate.h"
#include "clsUtil.h"

using namespace std;

class clsAddNewUser : protected clsScreen
{
	static int _ReadPermissions()
	{
		cout << "\n" << clsUtil::Tabs(2) << "Enter permissions:\n";
		string Check = "n";
		int Permissions = 0;

		Check = clsInputValidate::ReadCharacter(clsUtil::Tabs(2) + "Do you want to give full access? [Y/N] ");
		if (Check == "Y" || Check == "y")
			return -1;

		Check = clsInputValidate::ReadCharacter(clsUtil::Tabs(2) + "Show clients list? [Y/N] ");
		if (Check == "Y" || Check == "y")
			Permissions += 1;

		Check = clsInputValidate::ReadCharacter(clsUtil::Tabs(2) + "Add new clients? [Y/N] ");
		if (Check == "Y" || Check == "y")
			Permissions += 2;

		Check = clsInputValidate::ReadCharacter(clsUtil::Tabs(2) + "Delete clients? [Y/N] ");
		if (Check == "Y" || Check == "y")
			Permissions += 4;

		Check = clsInputValidate::ReadCharacter(clsUtil::Tabs(2) + "Update clients? [Y/N] ");
		if (Check == "Y" || Check == "y")
			Permissions += 8;

		Check = clsInputValidate::ReadCharacter(clsUtil::Tabs(2) + "Find clients? [Y/N] ");
		if (Check == "Y" || Check == "y")
			Permissions += 16;

		Check = clsInputValidate::ReadCharacter(clsUtil::Tabs(2) + "Transactions? [Y/N] ");
		if (Check == "Y" || Check == "y")
			Permissions += 32;

		Check = clsInputValidate::ReadCharacter(clsUtil::Tabs(2) + "Manage users? [Y/N] ");
		if (Check == "Y" || Check == "y")
			Permissions += 64;

		Check = clsInputValidate::ReadCharacter(clsUtil::Tabs(2) + "Login register? [Y/N] ");
		if (Check == "Y" || Check == "y")
			Permissions += 128;

		Check = clsInputValidate::ReadCharacter(clsUtil::Tabs(2) + "Currency exchange? [Y/N] ");
		if (Check == "Y" || Check == "y")
			Permissions += 256;

		return Permissions;
	}

	static void _ReadUserInfo(clsBankUser& User)
	{
		User.Password = clsInputValidate::ReadString("\tEnter password: ");
		User.FirstName = clsInputValidate::ReadString("\tEnter first name: ");
		User.LastName = clsInputValidate::ReadString("\tEnter last name: ");
		User.Email = clsInputValidate::ReadString("\tEnter email: ");
		User.PhoneNumber = clsInputValidate::ReadString("\tEnter phone number: ");
		User.Permissions = _ReadPermissions();
	}

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

	static void ShowAddNewClientScreen()
	{
		string Title = clsUtil::Tabs(7) + "Add New User";
		_DrawScreenHeader(Title);

		string Username = clsInputValidate::ReadString("\tEnter Username: ");

		while (clsBankUser::IsUserExist(Username))
		{
			Username = clsInputValidate::ReadString("\User already exists, enter different username: ");
		}

		clsBankUser NewUser = clsBankUser::NewUserObject(Username);
		_ReadUserInfo(NewUser);
		clsBankUser::enSaveResult SavingResult = NewUser.Save();
		switch (SavingResult)
		{
		case clsBankUser::svAddedSuccessfully:
			cout << "\n\tNew user added successfully!";
			_Print(NewUser);
			break;
		case clsBankUser::svFailed:
			cout << "\n\tAdding new user has been failed!";
			break;
		default:
			cout << "\n\tAdding new user has been failed!";
			break;
		}
	}
};

