#pragma once
#include <iostream>
#include "clsScreen.h"
#include "Global.h"
#include "clsBankClient.h"
#include "clsUtil.h"
#include "clsInputValidate.h"

using namespace std;

class clsDepositScreen : protected clsScreen
{
	static void _Print(clsBankClient Client)
	{
		cout << "\n" << clsUtil::Tabs(2) << "Client Card:\n";
		cout << clsUtil::Tabs(2) << "________________________________\n";
		cout << clsUtil::Tabs(2) << left << setw(12) << "First Name" << ": " << Client.FirstName << "\n";
		cout << clsUtil::Tabs(2) << left << setw(12) << "Last Name" << ": " << Client.LastName << "\n";
		cout << clsUtil::Tabs(2) << left << setw(12) << "Full Name" << ": " << Client.FullName() << "\n";
		cout << clsUtil::Tabs(2) << left << setw(12) << "Email" << ": " << Client.Email << "\n";
		cout << clsUtil::Tabs(2) << left << setw(12) << "Phone" << ": " << Client.PhoneNumber << "\n";
		cout << clsUtil::Tabs(2) << left << setw(12) << "Acc. Number" << ": " << Client.AccNumber << "\n";
		cout << clsUtil::Tabs(2) << left << setw(12) << "Pin Code" << ": " << Client.PinCode << "\n";
		cout << clsUtil::Tabs(2) << left << setw(12) << "Balance" << ": " << Client.Balance << "\n";
		cout << clsUtil::Tabs(2) << "________________________________\n";
	}
public:
	static void ShowDepositScreen()
	{
		string Title = clsUtil::Tabs(7) + "Deposit", AccountNumber = "";
		_DrawScreenHeader(Title);
		do
		{
			AccountNumber = clsInputValidate::ReadString(clsUtil::Tabs(2) + "Enter client's account number: ");
		} while (!clsBankClient::IsClientExist(AccountNumber));

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_Print(Client);

		cout << "\n" << clsUtil::Tabs(2) + "Enter the amount you want to deposit: ";
		double Amount = clsInputValidate::ReadNumber<double>("Invalid number. Try again ");
		char Check = clsInputValidate::ReadCharacter("Are you sure you want to deposit this amount? Yes[y], No[n]: ");
		if (toupper(Check) == 'Y')
		{
			Client.Deposit(Amount);
			cout << "\n" << clsUtil::Tabs(2) + "Amount deposited successfully!";
			cout << "\n" << clsUtil::Tabs(2) + "New balance is: " << Client.Balance;
		}
		else
		{
			cout << "\n" << clsUtil::Tabs(2) + "Operation cancelled!";
		}
	}
};

