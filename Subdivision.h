#pragma once
#include <string>
#include <vector>
#include <iostream>
using namespace std;
class Employee;


class Subdivision
{
	string _name;
	Subdivision* pSub;
	vector<Employee*> emps;
	vector<Subdivision*> subs;
public:
	Subdivision(const string& name, const Subdivision* pSub)
	{
		this->_name = name;
		this->pSub = const_cast<Subdivision*>(pSub);
	}

	string name()
	{
		return _name;
	}

	void AddSub(Subdivision* pSub)
	{
		subs.push_back(pSub);
	}

	vector<Subdivision*> ListSubs() 
	{
		return subs;
	}

	vector<Employee*> ListEmps()
	{
		return emps;
	}

	void print() const { cout << _name << endl; };

	void AddEmp(Employee* pEmp)
	{
		emps.push_back(pEmp);
	}

	void DelEmp(Employee* pEmp)
	{
		for (unsigned i = 0; i < emps.size(); i++)
			if (emps.at(i) == pEmp) emps.erase(emps.begin() + i);
	}

	~Subdivision() {};
};