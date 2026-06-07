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

class clsUpdateRateScreen : protected clsScreen
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

public:
	static void ShowUpdateRateScreen()
	{
		string Title = clsUtil::Tabs(6) + "  Update Currency Rate";
		_DrawScreenHeader(Title);
		string Code = clsInputValidate::ReadString(clsUtil::Tabs(2) + "Enter currency code: ");

		
		while (!clsCurrency::IsExist(Code))
		{
			cout << clsUtil::Tabs(2) + "Currency was not found! Try again\n";
			Code = clsInputValidate::ReadString(clsUtil::Tabs(2) + "Enter currency code: ");
		}

		clsCurrency Currency = clsCurrency::FindByCode(Code);
		_PrintCurrencyCard(Currency);

		char Check = clsInputValidate::ReadCharacter(clsUtil::Tabs(2) + "Are you sure you want to update this currency rate? y/n: ");
		if (toupper(Check) == 'Y')
		{
			float NewRate = clsInputValidate::ReadNumber<float>(clsUtil::Tabs(2) + "Enter the new rate: ");
			Currency.Rate = NewRate;
			cout << endl << clsUtil::Tabs(2) + "Currency rate was updated successfully!\n";
			_PrintCurrencyCard(Currency);
			return;
		}
		else
		{
			cout << endl << clsUtil::Tabs(2) + "Operation was cancelled!\n";
			return;
		}
	}
};

