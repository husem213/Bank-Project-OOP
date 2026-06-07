#pragma once
#include <iostream>
#include <iomanip>
#include "clsCurrency.h"
#include "clsScreen.h"
#include <vector>
#include "clsUtil.h"
#include <string>

using namespace std;

class clsCurrenciesListScreen : protected clsScreen
{
	static void _CurrenciesTableHeader(int CurrenciesNumber)
	{
		string Title = clsUtil::Tabs(7) + "Currencies List", Subtitle = clsUtil::Tabs(6) + "       (" + to_string(CurrenciesNumber) + ") Currency(ies)\n";
		clsScreen::_DrawScreenHeader(Title, Subtitle);
		cout << clsUtil::Tabs(2) << "_____________________________________________________________________________________________________________\n\n";
		cout << clsUtil::Tabs(2) << "| " << left << setw(35) << "Country";
		cout << "| " << left << setw(7) << "Code";
		cout << "| " << left << setw(40) << "Name";
		cout << "| " << left << setw(15) << "Rate\n";
		cout << clsUtil::Tabs(1) << "_____________________________________________________________________________________________________________\n\n";
	}

	static void _PrintCurrencyLine(clsCurrency Currency)
	{
		cout << clsUtil::Tabs(2);
		cout << "| " << left << setw(35) << Currency.Country();
		cout << "| " << left << setw(7) << Currency.Code();
		cout << "| " << left << setw(40) << Currency.Name();
		cout << "| " << left << setw(15) << Currency.Rate;
		cout << endl;
	}

public:

	static void ShowClientsList()
	{
		vector <clsCurrency> vCurrencies = clsCurrency::GetCurrenciesList();
		_CurrenciesTableHeader(static_cast<int>(vCurrencies.size()));
		if (static_cast<int>(vCurrencies.size()) == 0)
		{
			cout << "\nThere are no currencies in the system!";
		}
		else
		{
			for (clsCurrency& Currency : vCurrencies)
			{
				_PrintCurrencyLine(Currency);
			}
		}
		cout << clsUtil::Tabs(2) << "_____________________________________________________________________________________________________________\n\n";
	}
};

