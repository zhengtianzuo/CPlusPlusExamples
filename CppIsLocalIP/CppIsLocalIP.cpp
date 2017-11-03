/*!
 *@file CppIsLocalIP.cpp
 *@brief 程序主文件
 *@version 1.0
 *@section LICENSE Copyright (C) 2003-2103 CamelSoft Corporation
 *@author zhengtianzuo
*/
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

/*----------------------------------------- 
局域网IP地址范围 
A类：10.0.0.0-10.255.255.255 
B类：172.16.0.0-172.31.255.255  
C类：192.168.0.0-192.168.255.255 
-------------------------------------------*/ 
bool IsLocalIP(const string& ipstring)
{
	istringstream st(ipstring);
	int ip[2];
	for (int i = 0; i < 2; i++)
	{
		string temp;
		getline(st, temp, '.');
		istringstream a(temp);
		a >> ip[i];
	}
	if ((ip[0] == 10) || (ip[0] == 172 && ip[1] >= 16 && ip[1] <= 31) || (ip[0] == 192 && ip[1] == 168))
		return true;
	else return false;
}

int main(int argc, char* argv[])
{
	cout << IsLocalIP("10.0.0.1") << "\n";
	cout << IsLocalIP("192.168.0.1") << "\n";
	cout << IsLocalIP("171.217.52.62") << "\n";
    return 0;
}
