#pragma once
#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsScreen.h"
#include <vector>
#include "clsUtil.h"
#include <string>

using namespace std;

class clsShowClientsList : protected clsScreen
{
private:
	static void _ClientsTableHeader(int ClientsNumber)
	{
		string Title = clsUtil::Tabs(7) + "Clients List" , Subtitle = clsUtil::Tabs(6) + "       (" + to_string(ClientsNumber) + ") clients(s)\n";
		clsScreen::_DrawScreenHeader(Title, Subtitle);
		cout << clsUtil::Tabs(2) << "_____________________________________________________________________________________________________________\n\n";
		cout << clsUtil::Tabs(2) << "| " << left << setw(20) << "Account Number";
		cout << "| " << left << setw(12) << "Pin Code";
		cout << "| " << left << setw(20) << "Full Name";
		cout << "| " << left << setw(20) << "Email";
		cout << "| " << left << setw(15) << "Phone Number";
		cout << "| " << left << setw(10) << "Balance\n";
		cout << clsUtil::Tabs(2) << "_____________________________________________________________________________________________________________\n\n";
	}

	static void _PrintClientLine(clsBankClient Client)
	{
		cout << clsUtil::Tabs(2);
		cout << "| " << left << setw(20) << Client.AccNumber;
		cout << "| " << left << setw(12) << Client.PinCode;
		cout << "| " << left << setw(20) << Client.FullName();
		cout << "| " << left << setw(20) << Client.Email;
		cout << "| " << left << setw(15) << Client.PhoneNumber;
		cout << "| " << left << setw(10) << Client.Balance;
		cout << endl;
	}

public:
	static void ShowClientsList()
	{
		if (!CheckAccessRights(clsBankUser::enPermissions::pClientsList))
		{
			return;
		}
		vector <clsBankClient> vClients = clsBankClient::GetClientsList();
		_ClientsTableHeader(static_cast<int>(vClients.size()));
		if (static_cast<int>(vClients.size()) == 0)
		{
			cout << "\nThere are no clients in the system!";
		}
		else
		{
			for (clsBankClient& Client : vClients)
			{
				_PrintClientLine(Client);
			}
		}
		cout << clsUtil::Tabs(2) << "_____________________________________________________________________________________________________________\n\n";
	}
};

