#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "clsPerson.h"
#include "clsString.h"
#include <fstream>
#include <iomanip>
#include "Global.h"

using namespace std;

class clsBankClient : public clsPerson
{
	enum enMode {EmptyMode = 0, UpdateMode = 1, AddNewMode = 2};

	enMode _Mode;
	string _AccNumber, _PinCode;
	double _Balance;
	bool _MarkedForDeletion = false;

	static clsBankClient _ConvertLineToClientObject(string Line)
	{
		vector <string> vData = clsString::Split(Line, "/##/");

		return clsBankClient(UpdateMode, vData[0], vData[1], vData[2], vData[3], vData[4], vData[5], stof(vData[6]));
	}

	static clsBankClient _GetEmptyClientObject()
	{
		clsBankClient Client(EmptyMode, "", "", "", "", "", "", 0);
		return Client;
	}

	static vector <clsBankClient> _LoadClientsFromFile()
	{
		vector <clsBankClient> vClients;
		fstream ClientsData;

		ClientsData.open("Clients.txt", ios::in);

		if (ClientsData.is_open())
		{
			string Line;
			while (getline(ClientsData, Line))
			{
				if (Line.empty())
					continue;
				vClients.push_back(_ConvertLineToClientObject(Line));
			}
			ClientsData.close();
		}
		return vClients;
	}

	struct stTransferLog;

	static stTransferLog _ConvertLineToTransferLog(string Line)
	{
		vector <string> vData = clsString::Split(Line, "/##/");
		stTransferLog Transfer;

		Transfer.DateTime = vData[0];
		Transfer.Sender = vData[1];
		Transfer.Receiver = vData[2];
		Transfer.Amount = stod(vData[3]);
		Transfer.SenderBalance = stod(vData[4]);
		Transfer.ReceiverBalance = stod(vData[5]);
		Transfer.User = vData[6];

		return Transfer;
	}

	static vector <stTransferLog> _LoadTransferLogsFromFile()
	{
		vector <stTransferLog> vTransfers;
		fstream TransferLog;

		TransferLog.open("TransferLog.txt", ios::in);

		if (TransferLog.is_open())
		{
			string Line;
			while (getline(TransferLog, Line))
			{
				if (Line.empty())
					continue;
				vTransfers.push_back(_ConvertLineToTransferLog(Line));
			}
			TransferLog.close();
		}
		return vTransfers;
	}

	string _ConvertClientObjectToLine(clsBankClient& ClientData, string Deliminator = "/##/")
	{
		string Line = "";
		Line += ClientData.AccNumber + Deliminator;
		Line += ClientData.PinCode + Deliminator;
		Line += ClientData.FirstName + Deliminator;
		Line += ClientData.LastName + Deliminator;
		Line += ClientData.Email + Deliminator;
		Line += ClientData.PhoneNumber + Deliminator;
		Line += to_string(ClientData.Balance);
		return Line;
	}

	void _SaveClientsToFile(vector <clsBankClient>& vClients)
	{
		string DataLine = "";
		vector <string> vClientsLines;
		for (clsBankClient& Client : vClients)
		{
			if (Client.MarkedForDeletion == false)
			{
				DataLine = _ConvertClientObjectToLine(Client);
				vClientsLines.push_back(DataLine);
			}
		}

		fstream ClientsDataFile;

		ClientsDataFile.open("Clients.txt", ios::out);

		if (ClientsDataFile.is_open())
		{
			for (string& ClientLine : vClientsLines)
			{
				ClientsDataFile << ClientLine << endl;
			}
			ClientsDataFile.close();
		}
	}

	void _Update()
	{
		vector <clsBankClient> vClients = _LoadClientsFromFile();
		for (clsBankClient& C : vClients)
		{
			if (C.AccNumber == AccNumber)
			{
				C = *this;
				break;
			}
		}
		_SaveClientsToFile(vClients);
	}

	void _AddClientLineToFile(string ClientLine)
	{
		fstream File;
		File.open("Clients.txt", ios::out | ios::app);

		if (File.is_open())
		{
			File << ClientLine << endl;
			File.close();
		}
	}

	void _AddNewClient()
	{
		_AddClientLineToFile(_ConvertClientObjectToLine(*this));
	}

	struct stTransferLog;

	string _SetTransferLogToSave(clsBankClient ClientReceiver, double Amount)
	{
		string Line = "", Delimitor = "/##/";
		
		Line += clsDate::GetDateTimeString() + Delimitor;
		Line += AccNumber + Delimitor;
		Line += ClientReceiver.AccNumber + Delimitor;
		Line += to_string(Amount) + Delimitor;
		Line += to_string(Balance) + Delimitor;
		Line += to_string(ClientReceiver.Balance) + Delimitor;
		Line += CurrentUser.Username;

		return Line;
	}

	void _SaveTransferLog(clsBankClient ClientReceiver, double Amount)
	{
		fstream TransferLogs;

		TransferLogs.open("TransferLog.txt", ios::out | ios::app);

		if (TransferLogs.is_open())
		{
			string Line = _SetTransferLogToSave(ClientReceiver, Amount);
			TransferLogs << Line << endl;
			TransferLogs.close();
		}
	}

public:
	clsBankClient(enMode Mode, string AccountNumber, string PinCode, string FirstName, string LastName,
		 string Email, string Phone, float Balance)
		: clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_AccNumber = AccountNumber;
		_PinCode = PinCode;
		_Balance = Balance;
	}

	struct stTransferLog {
		string DateTime, Sender, Receiver, User;
		double Amount, SenderBalance, ReceiverBalance;
	};

	string FullName()
	{
		return FirstName + " " + LastName;
	}

	string GetAccountNumber()
	{
		return _AccNumber;
	}

	void SetMode(enMode Mode)
	{
		_Mode = Mode;
	}

	enMode GetMode()
	{
		return _Mode;
	}
	__declspec(property(get = GetMode, put = SetMode)) enMode Mode;

	void MarkForDeletion(bool Mark)
	{
		_MarkedForDeletion = Mark;
	}

	bool GetMarkForDeletion()
	{
		return _MarkedForDeletion;
	}
	__declspec(property(get = GetMarkForDeletion, put = MarkForDeletion)) bool MarkedForDeletion;

	void SetAccNumber(string AccNumber)
	{
		_AccNumber = AccNumber;
	}

	string GetAccNumber()
	{
		return _AccNumber;
	}
	__declspec(property(get = GetAccNumber, put = SetAccNumber)) string AccNumber;

	void SetPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}

	string GetPinCode()
	{
		return _PinCode;
	}
	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

	void SetBalance(double Balance)
	{
		_Balance = Balance;
	}

	double GetBalance()
	{
		return _Balance;
	}
	__declspec(property(get = GetBalance, put = SetBalance)) double Balance;

	bool IsEmpty()
	{
		return (Mode == EmptyMode);
	}

	static clsBankClient Find(string AccountNumber)
	{
		vector <clsBankClient> vClients;
		fstream ClientsData;

		ClientsData.open("Clients.txt", ios::in);

		if (ClientsData.is_open())
		{
			string Line;
			while (getline(ClientsData, Line))
			{
				if (Line.empty())
					continue;
				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.AccNumber == AccountNumber)
				{
					ClientsData.close();
					return Client;
				}
			}
		}
		return _GetEmptyClientObject();
	}

	static clsBankClient Find(string AccountNumber, string PinCode)
	{
		vector <clsBankClient> vClients;
		fstream ClientsData;

		ClientsData.open("Clients.txt", ios::in);

		if (ClientsData.is_open())
		{
			string Line;
			while (getline(ClientsData, Line))
			{
				if (Line.empty())
					continue;
				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.AccNumber == AccountNumber && Client.PinCode == PinCode)
				{
					ClientsData.close();
					return Client;
				}
			}
		}
		return _GetEmptyClientObject();
	}

	static bool IsClientExist(string AccountNumber)
	{
		clsBankClient Client = Find(AccountNumber);
		return !Client.IsEmpty();
	}
	
	enum enSaveResult { svUpdatedSuccessfully = 0, svFailed = 1, svAddedSuccessfully = 2 };

	enSaveResult Save()
	{
		switch (Mode)
		{
		case UpdateMode:
			if (IsEmpty())
			{
				return svFailed;
			}
			_Update();
			return svUpdatedSuccessfully;
		case EmptyMode:
			return svFailed;
		case AddNewMode:
			if (IsClientExist(AccNumber))
			{
				return svFailed;
			}
			_AddNewClient();
			Mode = UpdateMode;
			return svAddedSuccessfully;
		default:
			return svFailed;
		}
	}

	static clsBankClient NewClientObject(string AccountNumber)
	{
		return clsBankClient(AddNewMode, AccountNumber, "", "", "", "", "", 0);
	}

	bool Delete()
	{
		vector <clsBankClient> vClients = _LoadClientsFromFile();
		for (clsBankClient& C : vClients)
		{
			if (C.AccNumber == AccNumber)
			{
				C.MarkedForDeletion = true;
				*this = _GetEmptyClientObject();
				break;
			}
		}
		if (IsEmpty())
		{
			_SaveClientsToFile(vClients);
			return true;
		}
		else
		{
			return false;
		}
	}

	static vector <clsBankClient> GetClientsList()
	{
		return _LoadClientsFromFile();
	}

	static double GetTotalBalances()
	{
		vector <clsBankClient> vClients = _LoadClientsFromFile();
		double Total = 0;
		for (clsBankClient& Client : vClients)
		{
			Total += Client.Balance;
		}
		return Total;
	}

	void Deposit(double Amount)
	{
		Balance += Amount;
		Save();
	}

	bool Withdraw(double Amount)
	{
		if (Amount > Balance)
			return false;
		else
		{
			Balance -= Amount;
			Save();
			return true;
		}
	}

	bool Transfer(double Amount, clsBankClient& ClientReceiver)
	{
		if (Amount > Balance)
		{
			return false;
		}

		Withdraw(Amount);
		ClientReceiver.Deposit(Amount);
		_SaveTransferLog(ClientReceiver, Amount);
		return true;
	}

	static vector <stTransferLog> GetTransferLogList()
	{
		return _LoadTransferLogsFromFile();
	}
};

