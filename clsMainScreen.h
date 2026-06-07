#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUtil.h"
#include "clsShowClientsListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsManageUsersScreen.h"
#include "Global.h"
#include "clsTransactionsScreen.h"
#include "clsLoginRegisterScreen.h"
#include "clsCurrencyExchangeScreen.h"

using namespace std;

class clsMainScreen : protected clsScreen
{
	enum enMainMenu
	{
		eClientsList = 1, eAddNewClient = 2, eDeleteClient = 3, eUpdateClient = 4,
		eFindClient = 5, eTransactions = 6, eManageUsers = 7, eLoginRegister = 8, eCurrencyExchange = 9, eLogout = 10
	};

	static void _BackToMainMenuScreen()
	{
		cout << "\n" << clsUtil::Tabs(2) << "Press any key to go back to main menu...";
		system("pause>0");
		MainScreen();
	}

	static void _ShowClientsListScreen()
	{
		system("cls");
		clsShowClientsList::ShowClientsList();
	}

	static void _AddNewClientScreen()
	{
		system("cls");
		clsAddNewClientScreen::ShowAddNewClientScreen();
	}

	static void _DeleteClientScreen()
	{
		system("cls");
		clsDeleteClientScreen::ShowDeleteClientScreen();
	}

	static void _UpdateClientScreen()
	{
		system("cls");
		clsUpdateClient::ShowUpdateClientScreen();
	}

	static void _FindClientScreen()
	{
		system("cls");
		clsFindClientScreen::ShowFindClientScreen();
	}

	static void _TransactionsScreen()
	{
		system("cls");
		clsTransactionsScreen::ShowTransactionScreen();
	}

	static void _ManageUsersScreen()
	{
		system("cls");
		clsManageUsersScreen::ShowManageUsersScreen();
	}

	static void _LogoutScreen()
	{
		system("cls");
		CurrentUser = clsBankUser::Find("", "");
	}

	static void _LoginRegisterScreen()
	{
		system("cls");
		clsLoginRegisterScreen::ShowLoginRegisterScreen();
	}

	static void _CurrencyExchangeScreen()
	{
		system("cls");
		clsCurrencyExchangeScreen::ShowCurrencyExchangeScreen();
	}

	static void _MainMenu(enMainMenu Choice)
	{
		switch (Choice)
		{
		case eClientsList:
			_ShowClientsListScreen();
			_BackToMainMenuScreen();
			break;
		case eAddNewClient:
			_AddNewClientScreen();
			_BackToMainMenuScreen();
			break;
		case eDeleteClient:
			_DeleteClientScreen();
			_BackToMainMenuScreen();
			break;
		case eUpdateClient:
			_UpdateClientScreen();
			_BackToMainMenuScreen();
			break;
		case eFindClient:
			_FindClientScreen();
			_BackToMainMenuScreen();
			break;
		case eTransactions:
			_TransactionsScreen();
			_BackToMainMenuScreen();
			break;
		case eManageUsers:
			_ManageUsersScreen();
			_BackToMainMenuScreen();
			break;
		case eLoginRegister:
			_LoginRegisterScreen();
			_BackToMainMenuScreen();
			break;
		case eCurrencyExchange:
			_CurrencyExchangeScreen();
			_BackToMainMenuScreen();
			break;
		case eLogout:
			_LogoutScreen();
			break;
		}
	}

	static short _ReadChoice(string Text, short from, short to)
	{
		cout << endl << Text;
		string ErrorMessage = "Enter a number between " + to_string(from) + " and " + to_string(to) + ": ";
		return clsInputValidate::ReadNumberBetween<short>(from, to, ErrorMessage);
	}

public:

	static void MainScreen()
	{
		string ScreenName = clsUtil::Tabs(7) + "Main Menu";
		system("cls");
		_DrawScreenHeader(ScreenName);
		cout << clsUtil::Tabs(5) << "===========================================\n";
		cout << clsUtil::Tabs(6) << "[1] Show Client List\n";
		cout << clsUtil::Tabs(6) << "[2] Add New Client\n";
		cout << clsUtil::Tabs(6) << "[3] Delete Client\n";
		cout << clsUtil::Tabs(6) << "[4] Update Client Info\n";
		cout << clsUtil::Tabs(6) << "[5] Find Client\n";
		cout << clsUtil::Tabs(6) << "[6] Transactions\n";
		cout << clsUtil::Tabs(6) << "[7] Manage Users\n";
		cout << clsUtil::Tabs(6) << "[8] Login Register\n";
		cout << clsUtil::Tabs(6) << "[9] Currency Exchange\n";
		cout << clsUtil::Tabs(6) << "[10] Logout\n";
		cout << clsUtil::Tabs(5) << "===========================================\n";

		_MainMenu((enMainMenu)_ReadChoice(clsUtil::Tabs(4) + "Choose what you want to do [1 to 10]: ", 1, 10));
	}
};

