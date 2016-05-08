#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Subdivision.h"
#include "Employee.h"
#include "Commands.h"
using namespace std;


void main()
{
	Subdivision* pComp = new Subdivision("Company", NULL);
	for (; ; )
	{
		string command;
		cin >> command;
		if (command == "exit")
		{
			try
			{
				cout << "Do you want to save current company? (Y or N): ";
				char ans;
				cin >> ans;
				if (ans == 'Y')
				{
					cout << "Enter file name: ";
					string name;
					cin >> name;
					Save(pComp, name);
					cout << "Saved to " << name << endl;
				}
				else if (ans != 'N') throw 1;
				ClearSub(pComp, pComp);
				break;
			}
			catch (int i)
			{
				if (i == 1) cout << "Invalid answer!";
			}
		}
		else
			Handler(pComp, command);
	}
	system("pause");
}


