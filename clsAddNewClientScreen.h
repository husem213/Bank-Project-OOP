#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsUtil.h"

using namespace std;

class clsAddNewClientScreen : protected clsScreen
{
private:
	static void _ReadClientInfo(clsBankClient& Client)
	{
		Client.PinCode = clsInputValidate::ReadString("\n\n\tEnter a pin code: ");
		Client.FirstName = clsInputValidate::ReadString("\tEnter first name: ");
		Client.LastName = clsInputValidate::ReadString("\tEnter last name: ");
		Client.Email = clsInputValidate::ReadString("\tEnter email: ");
		Client.PhoneNumber = clsInputValidate::ReadString("\tEnter phone number: ");
		Client.Balance = clsInputValidate::ReadNumber<float>("\tEnter balance: ");
	}

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
	static void ShowAddNewClientScreen()
	{
		if (!CheckAccessRights(clsBankUser::enPermissions::pAddNewClient))
		{
			return;
		}
		string Title = clsUtil::Tabs(7) + "Add New Client";
		_DrawScreenHeader(Title);

		string AccNumber = clsInputValidate::ReadString("\tEnter account number: ");

		while (clsBankClient::IsClientExist(AccNumber))
		{
			AccNumber = clsInputValidate::ReadString("\tAccount already exists, enter different account number: ");
		}

		clsBankClient NewClient = clsBankClient::NewClientObject(AccNumber);
		_ReadClientInfo(NewClient);
		clsBankClient::enSaveResult SavingResult = NewClient.Save();
		switch (SavingResult)
		{
		case clsBankClient::svAddedSuccessfully:
			cout << "\n\tNew client added successfully!";
			_Print(NewClient);
			break;
		case clsBankClient::svFailed:
			cout << "\n\tAdding new client has been failed!";
			break;
		default:
			cout << "\n\tAdding new client has been failed!";
			break;
		}
	}
};

