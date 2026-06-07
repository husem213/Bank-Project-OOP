#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankUser.h"
#include "clsUtil.h"
#include "clsInputValidate.h"
#include "clsDate.h"
#include "clsBankClient.h"

using namespace std;

class clsTransferScreen : protected clsScreen
{
	static clsBankClient _ReadAccountNumber(string FromTo)
	{
		string AccountNumber = clsInputValidate::ReadString(clsUtil::Tabs(2) + "Enter account number to transfer " + FromTo + " : ");
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			AccountNumber = clsInputValidate::ReadString(clsUtil::Tabs(2) + "Client does not exist. Try again: ");
		}
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		return Client;
	}

	static void _PrintClientCard(clsBankClient Client)
	{
		cout << clsUtil::Tabs(2) + "Client card:\n";
		cout << clsUtil::Tabs(2) + "______________________________________\n";
		cout << clsUtil::Tabs(2) + "Full name: " << Client.FullName() << "\n";
		cout << clsUtil::Tabs(2) + "Acc number: " << Client.AccNumber << "\n";
		cout << clsUtil::Tabs(2) + "Balance: " << Client.Balance << "\n";
		cout << clsUtil::Tabs(2) + "______________________________________\n";
	}

	static double _ReadTransferAmount(clsBankClient Client)
	{
		double Amount = 0;
		bool Check = 0;
		do
		{
			Amount = clsInputValidate::ReadNumber<double>(clsUtil::Tabs(2) + "Enter transfer amount: ");
			Check = Amount > Client.Balance;
			if (Check)
				cout << "\n" + clsUtil::Tabs(2) + "Amount esceeds balance!\n";
		} while (Check);
		return Amount;
	}

public:
	static void ShowTransferScreen()
	{
		string ScreenName = clsUtil::Tabs(7) + "Transfer";
		_DrawScreenHeader(ScreenName);

		clsBankClient ClientFrom = _ReadAccountNumber("from");
		_PrintClientCard(ClientFrom);

		clsBankClient ClientTo = _ReadAccountNumber("to");
		_PrintClientCard(ClientTo);

		double Amount = clsInputValidate::ReadNumber<double>(clsUtil::Tabs(2) + "Enter the amount you want to transfer: ");
		char Check = clsInputValidate::ReadCharacter(clsUtil::Tabs(2) + "Are you sure you want to transfer this amount? Yes [y], No [n] : ");

		if (toupper(Check) == 'Y')
		{
			if (ClientFrom.Transfer(Amount, ClientTo))
			{
				cout << "\n" + clsUtil::Tabs(2) + "Transfer done successfully!\n";
			}
			else
				cout << "\n" + clsUtil::Tabs(2) + "Amount exceeds balance!\n";
		}
		else
		{
			cout << "\n" + clsUtil::Tabs(2) + "Opration cancelled!\n";
		}

		_PrintClientCard(ClientFrom);
		_PrintClientCard(ClientTo);
	}
};

