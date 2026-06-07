#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUtil.h"
#include "clsInputValidate.h"
#include "clsMainScreen.h"
#include "clsUsersListScreen.h"
#include "clsAddNewUser.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"

using namespace std;

class clsManageUsersScreen : protected clsScreen
{
private:
	enum enManageUsers {
		eUsersList = 1, eAddNewUser = 2, eDeleteUser = 3,
		eUpdateUser = 4, eFindUser = 5, eBackToMainMenu = 6
	};

	static void _ShowUsersListScreen()
	{
		system("cls");
		clsUsersListScreen::ShowUsersList();
	}

	static void _AddNewUserScreen()
	{
		system("cls");
		clsAddNewUser::ShowAddNewClientScreen();
	}

	static void _DeleteUserScreen()
	{
		system("cls");
		clsDeleteUserScreen::ShowDeleteUserScreen();
	}

	static void _UpdateUserScreen()
	{
		system("cls");
		clsUpdateUserScreen::ShowUpdateUserScreen();
	}

	static void _FindUserScreen()
	{
		system("cls");
		clsFindUserScreen::ShowFindUserScreen();
	}

	static void _ManageUsers(enManageUsers Choice)
	{
		switch (Choice)
		{
		case eUsersList:
			_ShowUsersListScreen();
			_BackToManageUsersScreen();
			break;
		case eAddNewUser:
			_AddNewUserScreen();
			_BackToManageUsersScreen();
			break;
		case eDeleteUser:
			_DeleteUserScreen();
			_BackToManageUsersScreen();
			break;
		case eUpdateUser:
			_UpdateUserScreen();
			_BackToManageUsersScreen();
			break;
		case eFindUser:
			_FindUserScreen();
			_BackToManageUsersScreen();
			break;
		case eBackToMainMenu:
			//clsMainScreen::MainScreen();
			break;
		}
	}

	static void _BackToManageUsersScreen()
	{
		cout << "\n" << clsUtil::Tabs(2) << "Press any key to go back to manage users menu...";
		system("pause>0");
		system("cls");
		ShowManageUsersScreen();
	}

	static short _ReadChoice(string Text, short from, short to)
	{
		cout << endl << Text;
		string ErrorMessage = "Enter a number between " + to_string(from) + " and " + to_string(to) + ": ";
		return clsInputValidate::ReadNumberBetween<short>(from, to, ErrorMessage);
	}

public:
	static void ShowManageUsersScreen()
	{
		if (!CheckAccessRights(clsBankUser::enPermissions::pManageUsers))
		{
			return;
		}
		string Title = clsUtil::Tabs(7) + "Manage Users";
		_DrawScreenHeader(Title);

		cout << clsUtil::Tabs(4) << "==========================================================\n";
		cout << clsUtil::Tabs(6) << "[1] Show Users List\n";
		cout << clsUtil::Tabs(6) << "[2] Add New User\n";
		cout << clsUtil::Tabs(6) << "[3] Delete User\n";
		cout << clsUtil::Tabs(6) << "[4] Update User Info\n";
		cout << clsUtil::Tabs(6) << "[5] Find User\n";
		cout << clsUtil::Tabs(6) << "[6] Main Menu\n";
		cout << clsUtil::Tabs(4) << "==========================================================\n";

		_ManageUsers((enManageUsers)_ReadChoice(clsUtil::Tabs(4) + "Choose what you want to do [1 to 6]: ", 1, 6));
	}
};

