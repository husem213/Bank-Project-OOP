#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankUser.h"
#include "clsUtil.h"
#include "clsDate.h"
#include "clsBankClient.h"

using namespace std;

class clsTansferLogListScreen : protected clsScreen
{
	static void _TableHeader()
	{
		cout << clsUtil::Tabs(2) << "____________________________________________________________________________________________________________________\n\n";
		cout << clsUtil::Tabs(2) << "| " << left << setw(25) << "Date & Time";
		cout << "| " << left << setw(12) << "Sender acc";
		cout << "| " << left << setw(13) << "Receiver acc";
		cout << "| " << left << setw(12) << "Amount";
		cout << "| " << left << setw(15) << "Sender balance";
		cout << "| " << left << setw(17) << "Receiver balance";
		cout << "| " << left << setw(10) << "User\n";
		cout << clsUtil::Tabs(2) << "____________________________________________________________________________________________________________________\n\n";
	}

	static void _PrintOneTransferLog(clsBankClient::stTransferLog Transfer)
	{
		cout << clsUtil::Tabs(2) << "| " << left << setw(25) << Transfer.DateTime;
		cout << "| " << left << setw(12) << Transfer.Sender;
		cout << "| " << left << setw(13) << Transfer.Receiver;
		cout << "| " << left << setw(12) << Transfer.Amount;
		cout << "| " << left << setw(15) << Transfer.SenderBalance;
		cout << "| " << left << setw(17) << Transfer.ReceiverBalance;
		cout << "| " << left << setw(10) << Transfer.User;
	}

	static void _PrintTransferLogs(vector <clsBankClient::stTransferLog>& vTransfers)
	{
		_TableHeader();
		for (clsBankClient::stTransferLog& Transfer : vTransfers)
		{
			_PrintOneTransferLog(Transfer);
			cout << endl;
		}
		cout << clsUtil::Tabs(2) << "____________________________________________________________________________________________________________________\n\n";
	}

public:
	static void ShowTransferLogListScreen()
	{
		string Title = clsUtil::Tabs(6) + "      Transfer Log List";

		vector <clsBankClient::stTransferLog> vTransfers = clsBankClient::GetTransferLogList();
		string Subtitle = clsUtil::Tabs(7) + "(" + to_string(static_cast<int>(vTransfers.size())) + ") Records";

		_DrawScreenHeader(Title, Subtitle);
		_PrintTransferLogs(vTransfers);
	}
};

