#pragma once
#include <iostream>
#include "clsUtil.h"
#include "clsBankUser.h"
#include "Global.h"
#include "clsDate.h"

using namespace std;

class clsScreen
{
protected:
	static bool CheckAccessRights(clsBankUser::enPermissions Permission)
	{
		if (!CurrentUser.CheckAccess(Permission))
		{
			string Title = clsUtil::Tabs(7) + "Access Denied!", Subtitle = clsUtil::Tabs(6) + "      Contact your admin";
			_DrawScreenHeader(Title, Subtitle);
			return false;
		}
		return true;
	}

	static void _DrawScreenHeader(string ScreenName, string Subtitle = "")
	{
		cout << "\n" << clsUtil::Tabs(5) << "____________________________________________\n";
		cout << "\n" << ScreenName;
		if(Subtitle != "")
			cout << "\n" << Subtitle;
		cout << "\n" << clsUtil::Tabs(5) << "____________________________________________\n";
		cout << "\n" << clsUtil::Tabs(5) << "User: " << CurrentUser.Username;
		cout << "\n" << clsUtil::Tabs(5) << "Date: " << clsDate::DateToString(clsDate()) << "\n\n";
	}
};

