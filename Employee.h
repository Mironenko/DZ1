#pragma once
using namespace std;
class Subdivision;


class Employee
{
	string _name;
	Employee* pEmp; // неочевидно, что это админ
	Subdivision* pSub;
	vector<Employee*> emps;
	vector<string> hist;
public:
	Employee(const string& name, const Subdivision* pSub)
	{
		this->_name = name;
		this->pSub = const_cast<Subdivision*>(pSub);
	}

	string name() const
	{
		return _name;
	}

	void AddHist(const string& move)
	{
		hist.push_back(move);
	}

	void ListHist() const
	{
		for (unsigned i = 0; i < hist.size(); i++)
			cout << hist.at(i) << endl;
	}

	void ChangeSub(Subdivision* pSub)
	{
		this->pSub = pSub;
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

	Employee* GetAdm() const
	{
		return pEmp;
	}

	void DelAdm()
	{
		pEmp = NULL;
	}

	vector<Employee*> ListEmps() const
	{
		return emps;
	}

	void ClearEmps()
	{
		emps.clear();
	}

	Subdivision* GetSub() const
	{
		return pSub;
	}

	void print() const { cout << _name << endl; }

	~Employee() {};
};