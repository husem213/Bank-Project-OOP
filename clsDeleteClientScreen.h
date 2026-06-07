#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsUtil.h"

using namespace std;

class clsDeleteClientScreen : protected clsScreen
{
private:
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
	static void ShowDeleteClientScreen()
	{
		if (!CheckAccessRights(clsBankUser::enPermissions::pDeleteClient))
		{
			return;
		}
		string Title = clsUtil::Tabs(7) + "Delete Client Screen";
		_DrawScreenHeader(Title);

		string AccountNumber = clsInputValidate::ReadString("\tEnter account number of the client you want to delete: ");
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			AccountNumber = clsInputValidate::ReadString("\tAccount does not exist. Enter a new account number: ");
		}
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_Print(Client);

		char Check = 'n';
		cout << "\n\tAre you sure you want to delete this client? Yes [y], No [n] : ";
		cin >> Check;

		if (toupper(Check) == 'Y')
		{
			if (Client.Delete())
			{
				cout << "\n\tClient deleted successfully!";
				_Print(Client);
			}
			else
			{
				cout << "\n\tError! Client was not deleted!";
			}
		}
	}
};

