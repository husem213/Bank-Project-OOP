#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsUtil.h"

using namespace std;

class clsUpdateClient : protected clsScreen
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

	static void _ReadClientInfo(clsBankClient& Client)
	{
		Client.PinCode = clsInputValidate::ReadString("\n\n\tEnter a pin code: ");
		Client.FirstName = clsInputValidate::ReadString("\tEnter first name: ");
		Client.LastName = clsInputValidate::ReadString("\tEnter last name: ");
		Client.Email = clsInputValidate::ReadString("\tEnter email: ");
		Client.PhoneNumber = clsInputValidate::ReadString("\tEnter phone number: ");
		Client.Balance = clsInputValidate::ReadNumber<float>("\tEnter balance: ");
	}
public:
	static void ShowUpdateClientScreen()
	{
		if (!CheckAccessRights(clsBankUser::enPermissions::pUpdateClient))
		{
			return;
		}
		string Title = clsUtil::Tabs(6) + "Update Client";
		_DrawScreenHeader(Title);

		string AccNumber = clsInputValidate::ReadString("\tEnter account number: ");

		while (!clsBankClient::IsClientExist(AccNumber))
		{
			AccNumber = clsInputValidate::ReadString("\tAccount was not found, enter another account number: ");
		}
		clsBankClient Client = clsBankClient::Find(AccNumber);
		
		_Print(Client);
		_ReadClientInfo(Client);

		clsBankClient::enSaveResult SavingResult;
		SavingResult = Client.Save();
		if (SavingResult == clsBankClient::svUpdatedSuccessfully)
		{
			cout << "\n\tClient updated successfully!";
			_Print(Client);
		}
		else
		{
			cout << "\n\tError! Client was not saved, because it is empty.";
		}
	}
};

