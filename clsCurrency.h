#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "clsString.h"
#include <fstream>
#include <iomanip>

using namespace std;

class clsCurrency
{
	enum enMode { EmptyMode = 0, UpdateMode = 1 };

	string _Country, _Code, _Name;
	float _Rate;
	enMode _Mode;

	static clsCurrency _ConvertLineToCurrencyObject(string DataLine)
	{
		vector <string> vData = clsString::Split(DataLine, "#//#");

		return clsCurrency(UpdateMode, vData[0], vData[1], vData[2], stof(vData[3]));
	}

	static clsCurrency _GetEmptyCurrencyObject()
	{
		return clsCurrency(EmptyMode, "", "", "", 0);
	}

	static vector <clsCurrency> _LoadCurrenciesFromFile()
	{
		vector <clsCurrency> vCurrencies;
		fstream Currencies;

		Currencies.open("Currencies.txt", ios::in);

		if (Currencies.is_open())
		{
			string Line;
			while (getline(Currencies, Line))
			{
				if (Line.empty())
					continue;
				vCurrencies.push_back(_ConvertLineToCurrencyObject(Line));
			}
			Currencies.close();
		}
		return vCurrencies;
	}

	string _ConvertCurrencyObjectToLine(clsCurrency& Currency, string Deliminator = "#//#")
	{
		string Line = "";
		Line += Currency.Country() + Deliminator;
		Line += Currency.Code() + Deliminator;
		Line += Currency.Name() + Deliminator;
		Line += to_string(Currency.Rate);
		return Line;
	}

	void _SaveCurrenciesToFile(vector <clsCurrency>& vCurrencies)
	{
		string DataLine = "";
		fstream Currencies;

		Currencies.open("Currencies.txt", ios::out);

		if (Currencies.is_open())
		{
			for (clsCurrency& Currency : vCurrencies)
			{
				if (Currency.IsEmpty())
				{
					continue;
				}
				DataLine = _ConvertCurrencyObjectToLine(Currency);
				Currencies << DataLine << endl;
			}
			Currencies.close();
		}
	}

	void _Update()
	{
		vector <clsCurrency> vCurrencies = _LoadCurrenciesFromFile();
		for (clsCurrency& C : vCurrencies)
		{
			if (C.Code() == Code())
			{
				C = *this;
				break;
			}
		}
		_SaveCurrenciesToFile(vCurrencies);
	}

public:
	clsCurrency(enMode Mode, string Country, string Code, string Name, float Rate)
	{
		_Mode = Mode;
		_Country = Country;
		_Code = Code;
		_Name = Name;
		_Rate = Rate;
	};

	string Country()
	{
		return _Country;
	}

	string Code()
	{
		return _Code;
	}

	string Name()
	{
		return _Name;
	}

	void UpdateRate(float Rate)
	{
		_Rate = Rate;
		_Update();
	}

	float GetRate()
	{
		return _Rate;
	}
	__declspec(property(get = GetRate, put = UpdateRate)) float Rate;

	enMode GetMode()
	{
		return _Mode;
	}

	void SetMode(enMode Mode)
	{
		_Mode = Mode;
	}
	__declspec(property(get = GetMode, put = SetMode)) enMode Mode;

	bool IsEmpty()
	{
		return Mode == EmptyMode;
	}

	static clsCurrency FindByCountry(string Country)
	{
		Country = clsString::UpperCaseAllLetters(Country);
		vector <clsCurrency> vCurrencies;
		fstream Currencies;

		Currencies.open("Currencies.txt", ios::in);

		if (Currencies.is_open())
		{
			string Line;
			while (getline(Currencies, Line))
			{
				if (Line.empty())
					continue;
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
				if (clsString::UpperCaseAllLetters(Currency.Country()) == Country)
				{
					Currencies.close();
					return Currency;
				}
			}
		}
		return _GetEmptyCurrencyObject();
	}

	static clsCurrency FindByCode(string Code)
	{
		Code = clsString::UpperCaseAllLetters(Code);
		vector <clsCurrency> vCurrencies;
		fstream Currencies;

		Currencies.open("Currencies.txt", ios::in);

		if (Currencies.is_open())
		{
			string Line;
			while (getline(Currencies, Line))
			{
				if (Line.empty())
					continue;
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
				if (Currency.Code() == Code)
				{
					Currencies.close();
					return Currency;
				}
			}
		}
		return _GetEmptyCurrencyObject();
	}

	static vector <clsCurrency> GetCurrenciesList()
	{
		return _LoadCurrenciesFromFile();
	}

	static bool IsExist(string Code)
	{
		clsCurrency Currency = FindByCode(Code);
		return !Currency.IsEmpty();
	}

	bool IsExist()
	{
		return IsExist(Code());
	}

	float ConvertToUSD(float Amount)
	{
		return (Amount / Rate);
	}

	float ConvertToOtherCurrency(float Amount, clsCurrency CurrencyTo)
	{
		float AmountInUSD = ConvertToUSD(Amount);

		if (CurrencyTo.Code() == "USD")
			return AmountInUSD;

		return AmountInUSD * CurrencyTo.Rate;
	}
};

