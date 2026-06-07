#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "clsString.h"
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
#include "clsUtil.h"

using namespace std;

class clsFindCurrencyScreen : protected clsScreen
{
	static void _PrintCurrencyCard(clsCurrency Currency)
	{
		cout << endl;
		cout << clsUtil::Tabs(2) + "Currency card:\n";
		cout << clsUtil::Tabs(2) + "__________________________\n";
		cout << clsUtil::Tabs(2) + "Country: " + Currency.Country() + "\n";
		cout << clsUtil::Tabs(2) + "Code: " + Currency.Code() + "\n";
		cout << clsUtil::Tabs(2) + "Name: " + Currency.Name() + "\n";
		cout << clsUtil::Tabs(2) + "Rate/(1$): " + to_string(Currency.Rate) + "\n";
		cout << clsUtil::Tabs(2) + "__________________________\n";
	}

	static void _ShowResults(clsCurrency Currency)
	{
		if (Currency.IsExist())
		{
			cout << endl << clsUtil::Tabs(2) + "Currency was found!\n";
			_PrintCurrencyCard(Currency);
		}
		else
		{
			cout << endl << clsUtil::Tabs(2) + "Currency was not found!\n";
			return;
		}
	}

public:
	static void ShowFindCurrencyScreen()
	{
		string Title = clsUtil::Tabs(7) + "Find Currency";
		_DrawScreenHeader(Title);

		cout << clsUtil::Tabs(2) + "Find by: [1] Country, [2] Code: ";
		short FindBy = clsInputValidate::ReadNumberBetween<short>(1, 2, clsUtil::Tabs(2) + "Number out of range. Try again: ");

		if (FindBy == 1)
		{
			string Country = clsInputValidate::ReadString(clsUtil::Tabs(2) + "Enter country name: ");
			clsCurrency Currency = clsCurrency::FindByCountry(Country);
			_ShowResults(Currency);
		}
		if (FindBy == 2)
		{
			string Code = clsInputValidate::ReadString(clsUtil::Tabs(2) + "Enter currency code: ");
			clsCurrency Currency = clsCurrency::FindByCode(Code);
			_ShowResults(Currency);
		}
	}
};

