#pragma once
#include <iostream>

using namespace std;

class InterfaceCommunication
{
public:
	virtual void SendEmail(string Title, string body) = 0;
	virtual void SendSMS(string Title, string body) = 0;
	virtual void SendFax(string Title, string body) = 0;
};

