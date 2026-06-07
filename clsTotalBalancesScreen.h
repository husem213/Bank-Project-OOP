#pragma once
#include <iostream>
#include "clsScreen.h"
#include "Global.h"
#include "clsBankClient.h"
#include "clsUtil.h"

using namespace std;

class clsTotalBalancesScreen : protected clsScreen
{
	static void _ClientsTableHeader()
	{
		cout << clsUtil::Tabs(2) << "_____________________________________________________________________________\n\n";
		cout << clsUtil::Tabs(2) << "| " << left << setw(20) << "Account Number";
		cout << "| " << left << setw(20) << "Full Name";
		cout << "| " << left << setw(10) << "Balance\n";
		cout << clsUtil::Tabs(2) << "_____________________________________________________________________________\n\n";
	}

	static void _PrintClientLine(clsBankClient Client)
	{
		cout << clsUtil::Tabs(2);
		cout << "| " << left << setw(20) << Client.AccNumber;
		cout << "| " << left << setw(20) << Client.FullName();
		cout << "| " << left << setw(10) << Client.Balance;
		cout << endl;
	}

public:
	static void ShowTotalBalances()
	{
		vector <clsBankClient> vClients = clsBankClient::GetClientsList();
		unsigned int ClientsNumber = static_cast<unsigned int>(vClients.size());

		string Title = clsUtil::Tabs(7) + "Total Balances", Subtitle = clsUtil::Tabs(6) + "       (" + to_string(ClientsNumber) + ") clients(s)\n";
		_DrawScreenHeader(Title, Subtitle);
		_ClientsTableHeader();

		double TotalBalances = 0;

		for (clsBankClient& Client : vClients)
		{
			TotalBalances += Client.Balance;
		}

		if (static_cast<unsigned int>(vClients.size()) == 0)
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
		cout << clsUtil::Tabs(2) << "_____________________________________________________________________________\n\n";
		cout << "\n" << clsUtil::Tabs(3) << "Total balances = " << TotalBalances << endl;
		cout << "\t\t" << clsString::NumberToString(static_cast<unsigned int>(TotalBalances));
	}
};

