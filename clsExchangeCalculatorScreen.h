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

class clsExchangeCalculatorScreen : protected clsScreen
{
	static clsCurrency _ReadCurrencyCode(string FromTo)
	{
		string Code = clsInputValidate::ReadString(clsUtil::Tabs(2) + "Enter currency code you want to convert " + FromTo + ": ");;
		while (!clsCurrency::IsExist(Code))
		{
			cout << endl << clsUtil::Tabs(2) + "Currency was not found!\n";
			Code = clsInputValidate::ReadString(clsUtil::Tabs(2) + "Enter currency code you want to convert " + FromTo + ": ");
		}
		return clsCurrency::FindByCode(Code);
	}

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

	static float _ReadAmount()
	{
		float Amount = clsInputValidate::ReadNumber<float>(clsUtil::Tabs(2) + "Enter amount to exchange: ");
		while (Amount <= 0)
		{
			cout << endl << clsUtil::Tabs(2) + "Amount has to be postitive!\n";
			Amount = clsInputValidate::ReadNumber<float>(clsUtil::Tabs(2) + "Enter amount to exchange: ");
		}
		return Amount;
	}

	static void _ShowResults(float Amount, clsCurrency CurrencyFrom, clsCurrency CurrencyTo)
	{
		_PrintCurrencyCard(CurrencyFrom);
		cout << "\n" + clsUtil::Tabs(2) + to_string(Amount) + " " + CurrencyFrom.Code() + "  =  " << CurrencyFrom.ConvertToUSD(Amount) << " USD";
		if (CurrencyTo.Code() != "USD")
		{
			cout << "\n\n" << clsUtil::Tabs(2) + "To:\n";
			_PrintCurrencyCard(CurrencyTo);
			cout << endl << clsUtil::Tabs(2) + to_string(Amount) + " " + CurrencyFrom.Code() + "  =  " << CurrencyFrom.ConvertToOtherCurrency(Amount, CurrencyTo) << " " + CurrencyTo.Code();
		}
	}

public:
	static void ShowExchangeCalculatorScreen()
	{
		char Check = 'Y';
		while (toupper(Check) == 'Y')
		{
			system("cls");
			string Title = clsUtil::Tabs(7) + "Exchange calculator";
			_DrawScreenHeader(Title);
		
			clsCurrency CurrencyFrom = _ReadCurrencyCode("from");
			clsCurrency CurrencyTo = _ReadCurrencyCode("to");
			float Amount = _ReadAmount();

			_ShowResults(Amount, CurrencyFrom, CurrencyTo);

			Check = clsInputValidate::ReadCharacter("\n" + clsUtil::Tabs(2) + "Do you want to perform another calculation? y/n: ");
		}
	}
};

