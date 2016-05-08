#pragma once
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

	string name() const
	{
		return _name;
	}

	void rename(const string& name)
	{
		this->_name = name;
	}

	void AddSub(Subdivision* pSub)
	{
		subs.push_back(pSub);
	}

	Subdivision* GetUpSub() const
	{
		return pSub;
	}

	void ChangeUpSub(Subdivision* pSub)
	{
		this->pSub = pSub;
	}

	vector<Subdivision*> ListSubs() const
	{
		return subs;
	}

	vector<Employee*> ListEmps() const
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

	void DelSub(Subdivision* pSub)
	{
		for (unsigned i = 0; i < subs.size(); i++)
			if (subs.at(i) == pSub) subs.erase(subs.begin() + i);
	}

	~Subdivision() {};
};