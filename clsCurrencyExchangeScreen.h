#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUtil.h"
#include "Global.h"
#include "clsInputValidate.h"
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateRateScreen.h"
#include "clsExchangeCalculatorScreen.h"

using namespace std;

class clsCurrencyExchangeScreen : protected clsScreen
{
	enum enCurrencyExchangeMenu {eCurrenciesList = 1, eFindCurrency = 2, eUpdateRate = 3, eCurrencyCalculator = 4, eMainMenu = 5};

	static void _ShowCurrenciesListScreen()
	{
		system("cls");
		clsCurrenciesListScreen::ShowClientsList();
	}

	static void _ShowFindCurrency()
	{
		system("cls");
		clsFindCurrencyScreen::ShowFindCurrencyScreen();
	}

	static void _ShowUpdateRateScreen()
	{
		system("cls");
		clsUpdateRateScreen::ShowUpdateRateScreen();
	}

	static void _ShowCurrencyCalculatorScreen()
	{
		system("cls");
		clsExchangeCalculatorScreen::ShowExchangeCalculatorScreen();
	}

	static void _BackToCurrencyExchangeScreen()
	{
		cout << "\n" << clsUtil::Tabs(2) << "Press any key to go back to currency exchange menu...";
		system("pause>0");
		ShowCurrencyExchangeScreen();
	}

	static void _CurrencyExchangeMenu(enCurrencyExchangeMenu Choice)
	{
		switch (Choice)
		{
		case eCurrenciesList:
			_ShowCurrenciesListScreen();
			_BackToCurrencyExchangeScreen();
			break;
		case eFindCurrency:
			_ShowFindCurrency();
			_BackToCurrencyExchangeScreen();
			break;
		case eUpdateRate:
			_ShowUpdateRateScreen();
			_BackToCurrencyExchangeScreen();
			break;
		case eCurrencyCalculator:
			_ShowCurrencyCalculatorScreen();
			_BackToCurrencyExchangeScreen();
			break;
		case eMainMenu:
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
	static void ShowCurrencyExchangeScreen()
	{
		if (!CheckAccessRights(clsBankUser::enPermissions::pCurrencyExchange))
		{
			return;
		}
		string ScreenName = clsUtil::Tabs(7) + "Currency Exchange";
		system("cls");
		_DrawScreenHeader(ScreenName);
		cout << clsUtil::Tabs(5) << "===========================================\n";
		cout << clsUtil::Tabs(6) << "[1] Currencies List\n";
		cout << clsUtil::Tabs(6) << "[2] Find Currency\n";
		cout << clsUtil::Tabs(6) << "[3] Update Rate\n";
		cout << clsUtil::Tabs(6) << "[4] Currency Calculator\n";
		cout << clsUtil::Tabs(6) << "[5] Main Menu\n";
		cout << clsUtil::Tabs(5) << "===========================================\n";

		_CurrencyExchangeMenu((enCurrencyExchangeMenu)_ReadChoice(clsUtil::Tabs(4) + "Choose what you want to do [1 to 5]: ", 1, 5));
	}
};

