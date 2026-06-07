#pragma once

#include <iostream>
#include <typeinfo>
#include <string>
#include "clsDate.h"
#include "clsUtil.h"

using namespace std;

class clsInputValidate
{
public:

	template <typename T> static T IsNumberBetween(T Number, T from, T to)
	{
		return (Number >= from && Number <= to);
	}

	template <typename T> static T ReadNumber(string Message)
	{
		T Number = 0;
		cout << Message;

		while (!(cin >> Number))
		{
			cin.clear();
			cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
			cout << "\nInvalid number. Try again ";
		}

		return Number;
	}

	static string ReadString(string Message)
	{
		string Sentence = "";

		cout << Message;
		getline(cin >> ws, Sentence);

		return Sentence;
	}

	template <typename T> static T ReadNumberBetween(T from, T to, string ErrorMessage = "Number out of range. Try again!\n")
	{
		T Number = ReadNumber<T>("Enter a number between " + to_string(from) + " and " + to_string(to) + ": ");

		while (!IsNumberBetween<T>(Number, from, to))
		{
			cout << ErrorMessage;
			Number = ReadNumber<T>("Enter a number between " + to_string(from) + " and " + to_string(to) + ": ");
		}

		return Number;
	}

	static bool IsValidDate(clsDate Date)
	{
		return clsDate::IsValidDate(Date);
	}

	static char ReadCharacter(string Message)
	{
		char Letter;
		
		cout << endl << Message;
		cin >> Letter;

		return Letter;
	}
};