#pragma once

#include <iostream>
#include <string>
#include "clsDate.h"

class clsUtil
{
public:
	static void Srand()
	{
		srand((unsigned)time(NULL));
	}

	static int RandomNumber(int from, int to)
	{
		return (rand() % (to - from + 1) + from);
	}

	static string EncryptText(string Text, short EncryptionKey)
	{
		for (int i = 0; i <= Text.length(); i++)
		{
			Text[i] = char((int)Text[i] + EncryptionKey);
		}

		return Text;
	}

	static string DecryptText(string Text, short EncryptionKey)
	{
		for (int i = 0; i <= Text.length(); i++)
		{
			Text[i] = char((int)Text[i] - EncryptionKey);
		}

		return Text;
	}

	enum enCharType {
		SamallLetter = 1, CapitalLetter = 2,
		Digit = 3, MixChars = 4, SpecialCharacter = 5
	};

	static char GetRandomCharacter(enCharType CharType)
	{
		if (CharType == MixChars)
			CharType = (enCharType)RandomNumber(1, 3);

		switch (CharType)
		{
		case SamallLetter:
			return char(RandomNumber(97, 122));

		case CapitalLetter:
			return char(RandomNumber(65, 90));

		case Digit:
			return char(RandomNumber(48, 57));

		case SpecialCharacter:
			return char(RandomNumber(33, 47));

		default:
			return char(RandomNumber(97, 122));
		}
	}

	static string GenerateWord(enCharType CharType, short Length)
	{
		string Word;

		for (int i = 1; i <= Length; i++)
		{
			Word = Word + GetRandomCharacter(CharType);
		}

		return Word;
	}

	static string GenerateKey(enCharType CharType)
	{
		string Key = "";

		Key = GenerateWord(CharType, 4) + "-";
		Key = Key + GenerateWord(CharType, 4) + "-";
		Key = Key + GenerateWord(CharType, 4) + "-";
		Key = Key + GenerateWord(CharType, 4);

		return Key;
	}

	static void GenerateKeys(short NumberOfKeys, enCharType CharType)
	{
		for (int i = 1; i <= NumberOfKeys; i++)
		{
			cout << "Key [" << i << "] : ";
			cout << GenerateKey(CharType) << endl;
		}
	}

	static int TimesRepeated(int Number, int arr[100], int arrLength)
	{
		int count = 0;

		for (int i = 0; i <= arrLength - 1; i++)
		{
			if (Number == arr[i])
			{
				count++;
			}
		}

		return count;
	}

	static int MaxNumberInArray(int arr[100], int arrLength)
	{
		int Max = 0;

		for (int i = 0; i < arrLength; i++)
		{
			if (arr[i] > Max)
			{
				Max = arr[i];
			}
		}

		return Max;
	}

	static int MinNumberInArray(int arr[100], int arrLength)
	{
		int Min = 0;
		Min = arr[0];

		for (int i = 0; i < arrLength; i++)
		{
			if (arr[i] < Min)
			{
				Min = arr[i];
			}
		}

		return Min;
	}

	static int SumArray(int arr[100], int arrLength)
	{
		int Sum = 0;

		for (int i = 0; i < arrLength; i++)
		{
			Sum += arr[i];
		}

		return Sum;
	}

	static float ArrayAverage(int arr[100], int arrLength)
	{
		return (float)SumArray(arr, arrLength) / arrLength;
	}

	static void CopyArray(int arrSource[100], int arrDestination[100], int arrLength)
	{
		for (int i = 0; i < arrLength; i++)
			arrDestination[i] = arrSource[i];
	}

	enum enPrimeNotPrime { Prime = 1, NotPrime = 2 };

	static enPrimeNotPrime CheckPrime(int Number)
	{
		int M = round(Number / 2);

		for (int Counter = 2; Counter <= M; Counter++)
		{
			if (Number % Counter == 0)
				return enPrimeNotPrime::NotPrime;
		}

		return enPrimeNotPrime::Prime;
	}

	static void CopyOnlyPrimeNumbers(int arrSource[100], int arrDestination[100], int arrLength, int& arr2Lenght)
	{
		int Counter = 0;

		for (int i = 0; i < arrLength; i++)
		{
			if (CheckPrime(arrSource[i]) == enPrimeNotPrime::Prime)
			{
				arrDestination[Counter] = arrSource[i];
				Counter++;
			}
		}
		arr2Lenght = --Counter;
	}

	static void FillArrayWithRandomKeys(string arr[100], int arrLength, enCharType CharType)
	{
		for (int i = 0; i < arrLength; i++)
			arr[i] = GenerateKey(CharType);
	}

	static void PrintStringArray(string arr[100], int arrLength)
	{
		cout << "\nArray elements:\n\n";
		for (int i = 0; i < arrLength; i++)
		{
			cout << "Array[" << i << "] : ";
			cout << arr[i] << "\n";
		}
		cout << "\n";
	}

	static void ReadArray(int arr[100], int& arrLength)
	{
		cout << "\nEnter number of elements:\n";
		cin >> arrLength;
		cout << "\nEnter array elements: \n";

		for (int i = 0; i < arrLength; i++)
		{
			cout << "Element [" << i + 1 << "] : ";
			cin >> arr[i];
		}

		cout << endl;
	}

	static void PrintArray(int arr[100], int arrLength)
	{
		for (int i = 0; i < arrLength; i++)
			cout << arr[i] << " ";

		cout << "\n";
	}

	static void FillArrayWithRandomNumbers(int arr[100], int arrLength, int From, int To)
	{
		for (int i = 0; i < arrLength; i++)
			arr[i] = RandomNumber(From, To);
	}
	
	static void FillArrayWithRandomWords(string arr[100], int arrLength, enCharType CharType, short WordLength)
	{
		for (int i = 0; i < arrLength; i++)
			arr[i] = GenerateWord(MixChars, WordLength);
	}

	static void SumOf2Arrays(int arr1[100], int arr2[100], int arrSum[100], int arrLength)
	{
		for (int i = 0; i < arrLength; i++)
		{
			arrSum[i] = arr1[i] + arr2[i];
		}
	}

	static void Swap(int& A, int& B)
	{
		int Temp;
		Temp = A;
		A = B;
		B = Temp;
	}
	
	static void Swap(string& A, string& B)
	{
		string Temp;
		Temp = A;
		A = B;
		B = Temp;
	}
	
	static void Swap(double& A, double& B)
	{
		double Temp;
		Temp = A;
		A = B;
		B = Temp;
	}

	static void Swap(bool& A, bool& B)
	{
		bool Temp;
		Temp = A;
		A = B;
		B = Temp;
	}

	static void Swap(char& A, char& B)
	{
		char Temp;
		Temp = A;
		A = B;
		B = Temp;
	}

	static void Swap(clsDate& A, clsDate& B)
	{
		clsDate Temp;
		Temp = A;
		A = B;
		B = Temp;
	}

	static void FillArrayWith1toN(int arr[100], int arrLength)
	{
		for (int i = 0; i < arrLength; i++)
			arr[i] = i + 1;
	}

	static void ShuffleArray(int arr[100], int arrLength)
	{
		for (int i = 0; i < arrLength; i++)
		{
			Swap(arr[RandomNumber(1, arrLength) - 1], arr[RandomNumber(1, arrLength) - 1]);
		}
	}

	static  void ShuffleArray(string arr[100], int arrLength)
	{
		for (int i = 0; i < arrLength; i++)
			Swap(arr[RandomNumber(1, arrLength) - 1], arr[RandomNumber(1, arrLength) - 1]);
	}

	static void CopyArrayInReverseOrder(int arrSource[100], int arrDestination[100], int arrLength)
	{
		for (int i = 0; i < arrLength; i++) 
			arrDestination[i] = arrSource[arrLength - 1 - i];
	}

	static short FindNumberPositionInArray(int Number, int arr[100], int arrLength)
	{
		for (int i = 0; i < arrLength; i++)
		{
			if (arr[i] == Number)
				return i;
		}

		return -1;
	}

	static void PrintNumberPosition(int Number, int arr[100], int arrLength)
	{
		short NumberPosition = FindNumberPositionInArray(Number, arr, arrLength);

		if (NumberPosition == -1)
			cout << "The number is not found :-(\n";
		else
		{
			cout << "The number found at position: ";
			cout << NumberPosition << endl;
			cout << "The number found its order: ";
			cout << NumberPosition + 1 << endl;
		}
	}

	static bool IsNumberInArray(int Number, int arr[100], int arrLength)
	{
		return FindNumberPositionInArray(Number, arr, arrLength) != -1;
	}

	static void AddArrayElement(int Number, int arr[100], int& arrLength)
	{
		arrLength++;
		arr[arrLength - 1] = Number;
	}

	static void CopyDistinctNumbersToArray(int arrSource[100], int arrDestination[100], int SourceLength, int& DestinationLength)
	{
		for (int i = 0; i < SourceLength; i++)
		{
			if (!IsNumberInArray(arrSource[i], arrDestination, DestinationLength))
			{
				AddArrayElement(arrSource[i], arrDestination,
					DestinationLength);
			}
		}
	}

	static string Tabs(short NumberOfTabs)
	{
		string temp = "";

		for (short i = 0; i < NumberOfTabs; i++)
			temp += "\t";

		return temp;
	}

	string NumberToText(int Number)
	{
		if (Number >= 0 && Number <= 19)
		{
			string arr[] = { "", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Elven"
			, "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen" };

			return arr[Number] + " ";
		}

		if (Number >= 20 && Number <= 99)
		{
			string arr[] = { "", "", "Twenty", "Thirty", "Fourty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety" };

			return arr[Number / 10] + " " + NumberToText(Number % 10);
		}

		if (Number >= 100 && Number <= 199)
		{
			return "One hundred " + NumberToText(Number % 100);
		}

		if (Number >= 200 && Number <= 999)
		{
			return NumberToText(Number / 100) + "Hundreds " + NumberToText(Number % 100);
		}

		if (Number >= 1000 && Number <= 1999)
		{
			return "One thousand " + NumberToText(Number % 1000);
		}

		if (Number >= 2000 && Number <= 999999)
		{
			return NumberToText(Number / 1000) + "Thousands " + NumberToText(Number % 1000);
		}

		if (Number >= 1000000 && Number <= 1999999)
		{
			return "One million " + NumberToText(Number % 1000000);
		}

		if (Number >= 2000000 && Number <= 9999999)
		{
			return NumberToText(Number / 1000000) + "Millions " + NumberToText(Number % 1000000);
		}

		if (Number >= 10000000 && Number <= 19999999)
		{
			return "One Billion " + NumberToText(Number % 10000000);
		}

		if (Number >= 20000000 && Number <= 99999999)
		{
			return NumberToText(Number / 10000000) + "Billions " + NumberToText(Number % 10000000);
		}
	}
};

