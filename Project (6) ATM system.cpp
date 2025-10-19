
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


enum enATMmenuOptions
{
	enQuickWithDraw = 1,
	enNormalWithDraw,
	enDeposite,
	enCheckBalance,
	enChangePassword,
	enLogOut
};


enum enQuickWithdrawMenuOptions
{
	Twenty = 1,
	Fifty,
	OneHundred,
	TwoHundred,
	FourHundred,
	SixHundred,
	EightHundred,
	OneThounsd,
	Exit


};


vector <stClient> vClients;


stClient CurrentClient;

int CurrentClientPosition; 

string FileNamePathForClients = "ClientsDataBaseFile.txt";



#pragma region secondary Functions

void ShowLogOutScreen();

void ShowChangePasswordScreen();


void ShowQuickWithDrawMenuScreen();


void clearScreen()
{
	system("cls");
}


void ShowATM_MenuScreen();


void PressAnyKeyToGetBackToATMMenu()
{
	cout << ("\n\nPress any key to go back to Main Menu...\t");
	system("pause > 0");

	ShowATM_MenuScreen();
}


void PressAnyKeyToGetBackToChangePasswordScreen()
{
	cout << ("\n\nPress any key to Try again...\t");
	system("pause > 0");

	ShowChangePasswordScreen();
}


void PressAnyKeyToGetBackToQuickWithdrawMenu()
{
	cout << ("\n\nPress any key to go back to the quick withdraw Menu...\t");
	system("pause > 0");

	ShowQuickWithDrawMenuScreen();
}


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


string ConvertClientToRecord(stClient NewClient, string Seprator = "#//#")
{
	string Record = "";

	Record += NewClient.AccountNumber;
	Record += Seprator;

	Record += NewClient.PinCode;
	Record += Seprator;

	Record += NewClient.FullName;
	Record += Seprator;

	Record += NewClient.PhoneNumber;
	Record += Seprator;


	Record += to_string(NewClient.Balance);

	return Record;
}


void UpdateClientVectorWithDataAndPushToFile()
{
	vector<string> vData;

	for (int i = 0; i < ::vClients.size(); i++)
	{
		vData.push_back(ConvertClientToRecord(vClients[i]));
	}

	RemoveAllFileDataAndRe_AddThem(FileNamePathForClients, vData);
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
			::CurrentClientPosition = pos;
			ShowATM_MenuScreen();
			return;
		}
		
		ReadAccNumberAndPinCodeFromUser(AccNumber, PinCode);
	}

}


void ShowLoginScreen()
{
	clearScreen();

	PrintScreenHeader("Login Screen");

	Login();
}


#pragma endregion



#pragma region Logout Function

void ShowLogOutScreen()
{
	ShowLoginScreen();
}


#pragma endregion



#pragma region Check Balance Function


double GetClientBalance()
{
	return ::CurrentClient.Balance;
}


void PrintCurrentBalance()
{
	double CurrentBalance = GetClientBalance();
	cout << "Your balance is $" << CurrentBalance << "\n\n";

}


void ShowCheckBalanceScreen()
{
	clearScreen();

	PrintScreenHeader("Current Balance");

	PrintCurrentBalance();

	PressAnyKeyToGetBackToATMMenu();
}


#pragma endregion



#pragma region Quick Withdraw function


bool IsBalanceSufficient(double Balance, double Amount)
{
	return (Balance >= Amount);
}



bool SubtractAmountFromBalance(double Amount)
{
	if (IsBalanceSufficient(::CurrentClient.Balance, Amount))
	{
		::CurrentClient.Balance -= Amount;
		return true;
	}
	else
		return false;
}



void PrintSubstractionResult(double Amount)
{

	if (ReadAnswerYesOrNO("\nAre you sure you want to perform this transaction?"))
	{
		if (SubtractAmountFromBalance(Amount))
		{
			cout << "\nDone successfully. New balance is " << GetClientBalance() << "\n\n";
			::vClients[::CurrentClientPosition] = CurrentClient;

			UpdateClientVectorWithDataAndPushToFile();
		}

		else
		{
			cout << "\nThe amount exceeds  your balance, make another choice.\n";
		}
	}

	PressAnyKeyToGetBackToATMMenu();

}
 


void ApplyQuickWithDrawOptions(enQuickWithdrawMenuOptions Option)
{
	switch (Option)
	{
	case enQuickWithdrawMenuOptions::Exit:
		ShowATM_MenuScreen();
		break;
	case enQuickWithdrawMenuOptions::Twenty:
		PrintSubstractionResult(20);
		break;
	case enQuickWithdrawMenuOptions::Fifty:
		PrintSubstractionResult(50);
		break;
	case enQuickWithdrawMenuOptions::OneHundred:
		PrintSubstractionResult(100);
		break;
	case enQuickWithdrawMenuOptions::TwoHundred:
		PrintSubstractionResult(200);
		break;
	case enQuickWithdrawMenuOptions::FourHundred:
		PrintSubstractionResult(400);
		break;
	case enQuickWithdrawMenuOptions::SixHundred:
		PrintSubstractionResult(600);
		break;
	case enQuickWithdrawMenuOptions::EightHundred:
		PrintSubstractionResult(800);
		break;
	case enQuickWithdrawMenuOptions::OneThounsd:
		PrintSubstractionResult(1000);
		break;
	}

}



void PrintQuickWithDrawMenuScreen()
{
	clearScreen();

	cout << "========================================================";
	cout << "\n\t\t  Quick Withdraw \n";
	cout << "========================================================\n";

	cout << "\t\t[1] 20  \t [2] 50 \n";
	cout << "\t\t[3] 100 \t [4] 200 \n";
	cout << "\t\t[5] 400 \t [6] 600 \n";
	cout << "\t\t[7] 800 \t [8] 1000 \n";
	cout << "\t\t[9] Exit \n";

	cout << "========================================================\n";

	PrintCurrentBalance();

	ApplyQuickWithDrawOptions((enQuickWithdrawMenuOptions)ReadNumberInRange("Choose an option [1 to 9]? ", 1, 9));
}



void ShowQuickWithDrawMenuScreen()
{
	PrintQuickWithDrawMenuScreen();
}


#pragma endregion



#pragma region Normal Withdraw function


bool IsAmountDivisilbeBy5(int EnteredAmount)
{
	return (EnteredAmount % 5 == 0);
}


int ReadTheWithdrawAmountFromUser()
{
	int Amount = 3;

	while (!IsAmountDivisilbeBy5(Amount))
	{
		cout << "Enter an amount multiple of 5's? ";
		cin >> Amount;
	}
	
	return Amount;
}


void ShowNormalWithdrawScreen()
{
	clearScreen();
	PrintScreenHeader("Normal Withdraw Screen");

	int amount = ReadTheWithdrawAmountFromUser();

	PrintSubstractionResult(amount);

}


#pragma endregion



#pragma region Deposite function


int ReadTheDepositeAmountFromUser()
{
	int Amount = -1;

	while (!IsNumberPositive(Amount))
	{
		cout << "Enter a positive amount: ";
		cin >> Amount;
	}

	return Amount;
}


void showDepositeScreen()
{
	clearScreen();
	PrintScreenHeader("Deposite Screen");

	int amount = ReadTheDepositeAmountFromUser();

	PrintSubstractionResult(-amount);

}



#pragma endregion



#pragma region Change password function

bool DoPINsMatch(string PINCode1, string PINCode2)
{
	return(PINCode1 == PINCode2);
}


void ChangePIN()
{
	string NewPIN = "", ConfirmPIN = " ";

	cout << "\n\nPlease enter the new PIN: ";
	cin >> NewPIN;

	cout << "\nPlease re-enter the new PIN: ";
	cin >> ConfirmPIN;

	while (!DoPINsMatch(NewPIN, ConfirmPIN)) 
	{
		cout << "\nPIN codes don't match!!";

		cout << "\n\nPlease enter the new PIN: ";
		cin >> NewPIN;

		cout << "\nPlease re-enter the new PIN: ";
		cin >> ConfirmPIN;
	}

	::CurrentClient.PinCode = NewPIN;

	vClients[::CurrentClientPosition] = CurrentClient;

	UpdateClientVectorWithDataAndPushToFile();

}


void ReadPINcodes()
{
	string OldPin;

	cout << "\nPlease enter the old PIN: ";
	cin >> OldPin;

	if (DoPINsMatch(OldPin,::CurrentClient.PinCode))
	{
		ChangePIN();
		cout << "\nPIN code has been updated successfully\n";
		PressAnyKeyToGetBackToATMMenu();

	}
	else
	{
		cout << "\n\n!!! Wrong PIN, Please try again\n";
		PressAnyKeyToGetBackToChangePasswordScreen();
	}

}


void ShowChangePasswordScreen()
{
	clearScreen();
	PrintScreenHeader("Change Password Screen");
	ReadPINcodes();

}


#pragma endregion




#pragma region ATM Main Menu

void ApplyUserOption(enATMmenuOptions Option)
{
	switch (Option)
	{
	case enATMmenuOptions::enLogOut:
		ShowLogOutScreen();
		break;
	case enATMmenuOptions::enCheckBalance:
		ShowCheckBalanceScreen();
		break;
	case enATMmenuOptions::enQuickWithDraw:
		ShowQuickWithDrawMenuScreen();
		break;
	case enATMmenuOptions::enNormalWithDraw:
		ShowNormalWithdrawScreen();
		break;
	case enATMmenuOptions::enDeposite:
		showDepositeScreen();
		break;
	case enATMmenuOptions::enChangePassword:
		ShowChangePasswordScreen();
		break;

	}

}


void ShowATM_MenuScreen()
{
	clearScreen();

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

	ApplyUserOption((enATMmenuOptions)ReadNumberInRange("What do you want to do? Choose an option [1 to 6]? ", 1, 6));
}


#pragma endregion




int main()
{
	ShowLoginScreen();
}

