#include <iostream>
#include <string>
#include <vector>
#include "Subdivision.h"
#include "Employee.h"
#include "Commands.h"
using namespace std;


void main()
{
	Subdivision* pComp = new Subdivision("Company", NULL);
	string name = "Sub1";
	CreateSub(pComp, "Company", name);
	name = "Sub4";
	CreateSub(pComp, "Sub1", name);
	name = "Sub2";
	CreateSub(pComp, "Company", name);
	name = "Sub6";
	CreateSub(pComp, "Sub2", name);
	name = "Sub5";
	CreateSub(pComp, "Sub1", name);
	name = "Sub3";
	CreateSub(pComp, "Company", name);
	name = "Emp1";
	CreateEmp(pComp, "Company", name);
	name = "Emp2";
	CreateEmp(pComp, "Sub3", name);
	name = "Emp3";
	CreateEmp(pComp, "Sub6", name);
	AddSubordination(pComp, "Emp1", "Emp2");
	AddSubordination(pComp, "Emp2", "Emp3");
	DeleteEmp(pComp, "Emp2");
	DeleteEmp(pComp, "Emp4");
	system("pause");
}


