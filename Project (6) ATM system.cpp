
#include "MySecondaryFunctionslib.h"

using namespace AllLibs;


struct stClient
{
	string AccountNumber;
	string FullName;
	string PhoneNumber;
	string PinCode;
	double Balance;
};


vector <stClient> vClients;

stClient CurrentClient;


string FileNamePathForClients = "ClientsDataBaseFile.txt";



#pragma region secondary Functions

void PrintScreenHeader(string HeaderName)
{
	cout << "-----------------------------------------------\n";
	cout << "\t\t  " << HeaderName << "\n";
	cout << "-----------------------------------------------\n";
}


stClient ConvertRecordToClient(string Record)
{
	stClient Client;
	vector <string> vWords = SplitString(Record, "#//#");

	Client.AccountNumber = vWords[0];
	Client.PinCode = vWords[1];
	Client.FullName = vWords[2];
	Client.PhoneNumber = vWords[3];
	Client.Balance = stod(vWords[4]);

	return Client;
}


void AddClientsDataFromFileToClientsVector()
{

	vector <string> vRecords;
	stClient Client;

	LoadDataFromFile(FileNamePathForClients, vRecords);

	::vClients.clear();

	for (int i = 0; i < vRecords.size(); i++)
	{
		Client = ConvertRecordToClient(vRecords[i]);
		::vClients.push_back(Client);
	}

}


bool IsClientExisted(string accountNumber, int& pos)
{
	AddClientsDataFromFileToClientsVector();

	for (int i = 0; i < vClients.size(); i++)
	{
		if (vClients[i].AccountNumber == accountNumber)
		{
			pos = i;
			return true;
		}

	}

	pos = -1;
	return false;
}


#pragma endregion




#pragma region ATM Main Menu

//void ApplyUserOption(enMainMenuOptions Option)
//{
//	switch (Option)
//	{
//	case enMainMenuOptions::enShowClientList:
//		if (::currentUser.Permissions & 1)
//			ShowClientsList();
//		else
//			AccessDeniedMessageScreen();
//		break;
//	case enMainMenuOptions::enAddNewClient:
//		if (::currentUser.Permissions & 2)
//			AddNewClient();
//		else
//			AccessDeniedMessageScreen();
//		break;
//	case enMainMenuOptions::enDeleteClient:
//		if (::currentUser.Permissions & 4)
//			DeleteClientScreen();
//		else
//			AccessDeniedMessageScreen();
//		break;
//	case enMainMenuOptions::enUpdateClientInfo:
//		if (::currentUser.Permissions & 8)
//			UpdateClientScreen();
//		else
//			AccessDeniedMessageScreen();
//		break;
//	case enMainMenuOptions::enFindClient:
//		if (::currentUser.Permissions & 16)
//			ShowFindClientByAccountNumberScreen();
//		else
//			AccessDeniedMessageScreen();
//		break;
//	case enMainMenuOptions::enTransactions:
//		if (::currentUser.Permissions & 32)
//			ShowTransactionMenu();
//		else
//			AccessDeniedMessageScreen();
//		break;
//	case enMainMenuOptions::enManageUsers:
//		if (::currentUser.Permissions & 64)
//			ShowManageUsersScreen();
//		else
//			AccessDeniedMessageScreen();
//		break;
//	case enMainMenuOptions::enLogout:
//		ShowLogOutScreen();
//		break;
//	}
//
//
//
//}


void ShowATM_MenuScreen()
{
	system("cls");
	cout << "========================================================";
	cout << "\n\t\t  ATM Menu Screen \n";
	cout << "========================================================\n";

	cout << "\t\t[1] Quick withdraw  \n";
	cout << "\t\t[2] Normal withdraw \n";
	cout << "\t\t[3] Deposite \n";
	cout << "\t\t[4] Check balance \n";
	cout << "\t\t[5] Change password \n";
	cout << "\t\t[6] Log out \n";

	cout << "========================================================\n";

	//ApplyUserOption((enMainMenuOptions)ReadUserOptionFromMenuList("What do you want to do? Choose an option [1 to 8]? ", 1, 8));
}


#pragma endregion




#pragma region Login function


bool DoesAccountNumberAndPINCodeMatch(string InputAccNumber, string InputPINCode, stClient Client)
{
	return (InputAccNumber == Client.AccountNumber && InputPINCode == Client.PinCode);
}


void ReadAccNumberAndPinCodeFromUser(string &AccNumber, string &PinCode)
{
	AccNumber = ReadString("Enter Account Number?");
	PinCode = ReadString("Enter Pin Code?");
}


void Login()
{
	string AccNumber, PinCode;
	int pos;


	ReadAccNumberAndPinCodeFromUser(AccNumber, PinCode);


	while (true)
	{
		if (!IsClientExisted(AccNumber, pos))
			cout << "This account number doesn't exist in our system!!\n\n";
	
		else if (!DoesAccountNumberAndPINCodeMatch(AccNumber, PinCode, vClients[pos]))
			cout << "Incorrect username OR password\n\n";
		else
		{
			CurrentClient = vClients[pos];
			ShowATM_MenuScreen();
			return;
		}
		
		ReadAccNumberAndPinCodeFromUser(AccNumber, PinCode);
	}

}


void ShowLoginScreen()
{
	system("cls");
	PrintScreenHeader("Login Screen");
	Login();
}


#pragma endregion






int main()
{
	ShowLoginScreen();
}

