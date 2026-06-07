#pragma once
#include <iostream>
#include "clsScreen.h"
#include "Global.h"
#include "clsBankUser.h"
#include "clsUtil.h"
#include "clsInputValidate.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTansferLogListScreen.h"

using namespace std;

class clsTransactionsScreen : protected clsScreen
{
	enum enTransactions { eDeposit = 1, eWithdraw = 2, eTotalBalances = 3, eTransfer = 4, eTransferLog = 5, eMainMenu = 6 };

	static void _BackToTransactionsScreen()
	{
		cout << "\nPress any key to go back to transactions menu...";
		system("pause>0");
		ShowTransactionScreen();
	}

	static void _DepositScreen()
	{
		system("cls");
		clsDepositScreen::ShowDepositScreen();
	}

	static void _WithdrawScreen()
	{
		system("cls");
		clsWithdrawScreen::ShowWithdrawScreen();
	}

	static void _TotalBalancesTable()
	{
		system("cls");
		clsTotalBalancesScreen::ShowTotalBalances();
	}

	static void _TransferScreen()
	{
		system("cls");
		clsTransferScreen::ShowTransferScreen();
	}

	static void _TransferLogListScreen()
	{
		system("cls");
		clsTansferLogListScreen::ShowTransferLogListScreen();
	}

	static void _Transactions(enTransactions Choice)
	{
		switch (Choice)
		{
		case eDeposit:
			_DepositScreen();
			_BackToTransactionsScreen();
			break;
		case eWithdraw:
			_WithdrawScreen();
			_BackToTransactionsScreen();
			break;
		case eTotalBalances:
			_TotalBalancesTable();
			_BackToTransactionsScreen();
			break;
		case eTransfer:
			_TransferScreen();
			_BackToTransactionsScreen();
			break;
		case eTransferLog:
			_TransferLogListScreen();
			_BackToTransactionsScreen();
			break;
		case eMainMenu:
			break;
		}
	}

	static short _ReadChoice(string Text)
	{
		short Choice = 0;
		cout << "\n" << Text;
		Choice = clsInputValidate::ReadNumberBetween<short>(1, 6, "Number out of range. Try again ");
		return Choice;
	}

public:
	static void ShowTransactionScreen()
	{
		if(!CheckAccessRights(clsBankUser::enPermissions::pTransactions))
			return;
		system("cls");
		string ScreenName = clsUtil::Tabs(7) + "Transactions";
		_DrawScreenHeader(ScreenName);
		cout << clsUtil::Tabs(5) << "============================================\n";
		cout << clsUtil::Tabs(6) << "[1] Deposit\n";
		cout << clsUtil::Tabs(6) << "[2] Withdraw\n";
		cout << clsUtil::Tabs(6) << "[3] Total Balances\n";
		cout << clsUtil::Tabs(6) << "[4] Transfer\n";
		cout << clsUtil::Tabs(6) << "[5] Transfer Log\n";
		cout << clsUtil::Tabs(6) << "[6] Main Menu\n";
		cout << clsUtil::Tabs(5) << "============================================\n";
		_Transactions((enTransactions)_ReadChoice(clsUtil::Tabs(2) + "Enter what you want to do [1 to 6]: "));
	}
};

