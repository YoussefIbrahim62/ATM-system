#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cctype>
#include <iomanip>

using namespace std;


namespace AllLibs
{

	int validateInputIsNumber()
	{
		int Number;
		cin >> Number;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "\n\nInvalid input, please try again:  ";

			cin >> Number;
		}

		return Number;
	}


	int ReadNumberInRange(string message, int From, int To)
	{
		int Number = -99999999;

		cout << "\n" << message << " ";
		Number = validateInputIsNumber();

		while (Number < From || Number > To)
		{
			cout << "\n\nInvalid input, please entr a number between (" << From << " & " << To << "):  ";
			Number = validateInputIsNumber();
		}

		return Number;
	}


	float validateInputIsNumberfloat(string Message)
	{
		float Number;

		cout << Message << " ";
		cin >> Number;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "\n\nInvalid input, please try again:  ";

			cin >> Number;
		}

		return Number;
	}


	string ReadString(string Message)
	{
		string input;


		cout << Message << " ";
		getline(cin >> ws, input);

		return input;
	}


	void RemoveAllFileDataAndRe_AddThem(string fileName, vector<string> vData)
	{
		fstream File;

		File.open(fileName, ios::out);

		if (File.is_open())
		{
			for (int i = 0; i < vData.size(); i++)
			{
				if (vData[i] != "")
					File << vData[i] << "\n";

			}

			File.close();
		}

	}


	void AddDataToFile(string fileName, vector<string> vData)
	{
		fstream File;

		File.open(fileName, ios::out | ios::app);

		if (File.is_open())
		{
			for (int i = 0; i < vData.size(); i++)
			{
				if (vData[i] != "")
					File << vData[i] << "\n";

			}

			File.close();
		}

	}


	void LoadDataFromFile(string fileName, vector<string>& vData)
	{
		fstream File;
		string line;

		File.open(fileName, ios::in);

		if (File.is_open())
		{

			while (getline(File, line))
			{
				if (line != "")
					vData.push_back(line);
			}

			File.close();
		}

	}


	void AddSingleRecordToFile(string fileName, string Record)
	{
		fstream File;

		File.open(fileName, ios::out | ios::app);

		if (File.is_open())
		{
			if (Record != "")
				File << Record << "\n";

			File.close();
		}

	}


	vector<string> SplitString(string input, string delim = " ")
	{
		vector<string> vWords;

		short pos = 0;

		string sWord = "";

		while ((pos = input.find(delim)) != std::string::npos)
		{
			sWord = input.substr(0, pos);

			if (sWord != "")
				vWords.push_back(sWord);

			input = input.erase(0, pos + delim.length());
		}

		if (input != "")
			vWords.push_back(input);

		return vWords;
	}


	bool ReadAnswerYesOrNO(string message)
	{
		char answer;

		cout << message << "  ";
		cin >> answer;

		while (cin.fail() || (tolower(answer) != 'y' && tolower(answer) != 'n'))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << "\nInvalid input, try again: ";
			cin >> answer;
		}

		if (tolower(answer) == 'y')
			return true;
		else
			return false;
	}


	bool AskUserToGetBackToMainMenu()
	{
		return ReadAnswerYesOrNO("\nDo you want to get back to main menu [Y] [N] ? ");
	}


	bool IsNumberPositive(int number)
	{
		return (number > 0);
	}

}