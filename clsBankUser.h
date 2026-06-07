#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "clsPerson.h"
#include "clsString.h"
#include <fstream>
#include <iomanip>
#include "clsDate.h"
#include "clsUtil.h"

using namespace std;

class clsBankUser : public clsPerson
{
private:
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };

	enMode _Mode;
	string _Username, _Password;
	int _Permissions;
	bool _MarkedForDeletion = false;

	static clsBankUser _GetEmptyUserObject()
	{
		clsBankUser User(EmptyMode, "", "", "", "", "", "", 0);
		return User;
	}

	static clsBankUser _ConvertLineToUserObject(string Line)
	{
		vector <string> vData = clsString::Split(Line, "/##/");

		return clsBankUser(UpdateMode, vData[0], _DecryptPassword(vData[1]), vData[2], vData[3], vData[4], vData[5], stoi(vData[6]));
	}

	static string _DecryptPassword(string EncryptedPsswords)
	{
		return clsUtil::DecryptText(EncryptedPsswords, 4);
	}

	static vector <clsBankUser> _LoadUsersFromFile()
	{
		vector <clsBankUser> vUsers;
		fstream UsersData;

		UsersData.open("Users.txt", ios::in);

		if (UsersData.is_open())
		{
			string Line;
			while (getline(UsersData, Line))
			{
				if (Line.empty())
					continue;
				clsBankUser User = _ConvertLineToUserObject(Line);
				vUsers.push_back(User);
			}
			UsersData.close();
		}
		return vUsers;
	}

	string _ConvertUserObjectToLine(clsBankUser& UserData, string Deliminator = "/##/")
	{
		string Line = "";
		Line += UserData.Username + Deliminator;
		Line += _EncryptPassword(UserData.Password) + Deliminator;
		Line += UserData.FirstName + Deliminator;
		Line += UserData.LastName + Deliminator;
		Line += UserData.Email + Deliminator;
		Line += UserData.PhoneNumber + Deliminator;
		Line += to_string(UserData.Permissions);
		return Line;
	}

	static string _EncryptPassword(string Password)
	{
		return clsUtil::EncryptText(Password, 4);
	}

	void _SaveUsersToFile(vector <clsBankUser>& vUsers)
	{
		string DataLine = "";
		vector <string> vUsersLines;
		for (clsBankUser& User : vUsers)
		{
			if (User.MarkedForDeletion == false)
			{
				DataLine = _ConvertUserObjectToLine(User);
				vUsersLines.push_back(DataLine);
			}
		}

		fstream UsersDataFile;

		UsersDataFile.open("Users.txt", ios::out);

		if (UsersDataFile.is_open())
		{
			for (string& UserLine : vUsersLines)
			{
				UsersDataFile << UserLine << endl;
			}
			UsersDataFile.close();
		}
	}

	void _Update()
	{
		vector <clsBankUser> vUsers = _LoadUsersFromFile();
		for (clsBankUser& C : vUsers)
		{
			if (C.Username == Username)
			{
				C = *this;
				break;
			}
		}
		_SaveUsersToFile(vUsers);
	}
	
	void _AddUserLineToFile(string UserLine)
	{
		fstream File;
		File.open("Users.txt", ios::out | ios::app);

		if (File.is_open())
		{
			File << endl << UserLine;
			File.close();
		}
	}

	void _AddNewUser()
	{
		_AddUserLineToFile(_ConvertUserObjectToLine(*this));
	}

	string _PrepareLoginRegister(string Deliminator = "/##/")
	{
		string Line = "";
		Line += clsDate::GetDateTimeString() + Deliminator;
		Line += Username + Deliminator;
		Line += _EncryptPassword(Password) + Deliminator;
		Line += to_string(Permissions);
		return Line;
	}

	struct stLoginRegister;

	static stLoginRegister _ConvertLineToLoginRegister(string Line)
	{
		stLoginRegister User;
		vector <string> vData = clsString::Split(Line, "/##/");

		User.DateAndTimeString = vData[0];
		User.Username = vData[1];
		User.Password = _DecryptPassword(vData[2]);
		User.Permissions = stoi(vData[3]);

		return User;
	}

public:
	clsBankUser(enMode Mode, string Username, string Password, string FirstName,
		string LastName, string Email, string Phone, int Permissions)
		: clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_Username = Username;
		_Password = Password;
		_Permissions = Permissions;
	}

	enum enPermissions {pAll = -1, pClientsList = 1, pAddNewClient = 2, pDeleteClient = 4, pUpdateClient = 8,
		pFindClient = 16, pTransactions = 32, pManageUsers = 64, pLoginRegister = 128, pCurrencyExchange = 256};

	struct stLoginRegister
	{
		string DateAndTimeString, Username, Password;
		int Permissions = 0;
	};

	string FullName()
	{
		return FirstName + " " + LastName;
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

	void SetUsername(string Username)
	{
		_Username = Username;
	}

	string GetUsername()
	{
		return _Username;
	}
	__declspec(property(get = GetUsername, put = SetUsername)) string Username;

	void SetPassword(string Password)
	{
		_Password = Password;
	}

	string GetPassword()
	{
		return _Password;
	}
	__declspec(property(get = GetPassword, put = SetPassword)) string Password;

	void SetPermissions(int Permissions)
	{
		_Permissions = Permissions;
	}

	int GetPermissions()
	{
		return _Permissions;
	}
	__declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;

	bool IsEmpty()
	{
		return (Mode == EmptyMode);
	}

	static clsBankUser Find(string Username)
	{
		vector <clsBankUser> vUsers;
		fstream UsersData;

		UsersData.open("Users.txt", ios::in);

		if (UsersData.is_open())
		{
			string Line;
			while (getline(UsersData, Line))
			{
				if (Line.empty())
					continue;
				clsBankUser User = _ConvertLineToUserObject(Line);
				if (User.Username == Username)
				{
					UsersData.close();
					return User;
				}
			}
		}
		return _GetEmptyUserObject();
	}

	static clsBankUser Find(string Username, string Password)
	{
		vector <clsBankUser> vUsers;
		fstream UsersData;

		UsersData.open("Users.txt", ios::in);

		if (UsersData.is_open())
		{
			string Line;
			while (getline(UsersData, Line))
			{
				if (Line.empty())
					continue;
				clsBankUser User = _ConvertLineToUserObject(Line);
				if (User.Username == Username && User.Password == Password)
				{
					UsersData.close();
					return User;
				}
			}
		}
		return _GetEmptyUserObject();
	}

	static bool IsUserExist(string Username)
	{
		clsBankUser User = Find(Username);
		return !User.IsEmpty();
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
			if (IsUserExist(Username))
			{
				return svFailed;
			}
			_AddNewUser();
			Mode = UpdateMode;
			return svAddedSuccessfully;
		default:
			return svFailed;
		}
	}

	static clsBankUser NewUserObject(string Username)
	{
		return clsBankUser(AddNewMode, Username, "", "", "", "", "", 0);
	}

	bool Delete()
	{
		vector <clsBankUser> vUsers = _LoadUsersFromFile();
		for (clsBankUser& C : vUsers)
		{
			if (C.Username == Username)
			{
				C.MarkedForDeletion = true;
				*this = _GetEmptyUserObject();
				break;
			}
		}
		if (IsEmpty())
		{
			_SaveUsersToFile(vUsers);
			return true;
		}
		else
		{
			return false;
		}
	}

	static vector <clsBankUser> GetUsersList()
	{
		return _LoadUsersFromFile();
	}

	bool CheckAccess(enPermissions Permission)
	{
		if (this->Permissions == enPermissions::pAll)
			return true;

		if ((this->Permissions & Permission) == Permission)
			return true;

		return false;
	}

	void RegisterLogin()
	{
		string DataLine = "";

		DataLine = _PrepareLoginRegister();

		fstream LogedInUsers;

		LogedInUsers.open("LoginRegister.txt", ios::out | ios::app);

		if (LogedInUsers.is_open())
		{
			LogedInUsers << DataLine << endl;
			LogedInUsers.close();
		}
	}

	static vector <stLoginRegister> GetLoginRegisterList()
	{
		vector <clsBankUser::stLoginRegister> vUsers;
		fstream UsersData;

		UsersData.open("LoginRegister.txt", ios::in);

		if (UsersData.is_open())
		{
			string Line;
			while (getline(UsersData, Line))
			{
				if (Line.empty())
					continue;
				vUsers.push_back(_ConvertLineToLoginRegister(Line));
			}
			UsersData.close();
		}
		return vUsers;
	}
};

