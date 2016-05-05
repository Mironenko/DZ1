#pragma once
#include <string>
#include <vector>
#include <iostream>
using namespace std;
class Subdivision;


class Employee
{
	string _name;
	Employee* pEmp;
	Subdivision* pSub;
	vector<Employee*> emps;
public:
	Employee(const string& name, const Subdivision* pSub)
	{
		this->_name = name;
		this->pSub = const_cast<Subdivision*>(pSub);
	}

	string name()
	{
		return _name;
	}

	void AddEmp(Employee* pEmp)
	{
		emps.push_back(pEmp);
	}

	void DelEmp(Employee* pEmp)
	{
		for (unsigned i = 0; i < emps.size(); i++)
			if (emps.at(i) == pEmp) emps.erase(emps.begin() + i);
	}

	void AddAdm(Employee* pEmp)
	{
		this->pEmp = pEmp;
	}

	Employee* GetAdm()
	{
		return pEmp;
	}

	void DelAdm()
	{
		pEmp = NULL;
	}

	vector<Employee*> ListEmps()
	{
		return emps;
	}

	void ClearEmps()
	{
		emps.clear();
	}

	Subdivision* GetSub()
	{
		return pSub;
	}

	void print() const { cout << _name << endl; }

	~Employee() {};
};