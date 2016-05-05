#pragma once
class Subdivision;
class Employee;


Subdivision* FindSub(Subdivision *pComp, const string& name)
{
	Subdivision* pSub = pComp;
	if (pSub->name() == name) return pSub;
	if (pSub->ListSubs().size() != 0)
	{
		vector<Subdivision*> cs = pSub->ListSubs();
		for (unsigned i = 0; i < cs.size(); i++)
			if (FindSub(cs.at(i), name)) return FindSub(cs.at(i), name);
	}
	return NULL;
}


Employee* FindEmp(Subdivision *pComp, const string& name)
{
	Subdivision* pSub = pComp;
	if (pSub->ListEmps().size() != 0)
	{
		vector<Employee*> emps = pSub->ListEmps();
		for (unsigned i = 0; i < emps.size(); i++)
			if (emps.at(i)->name() == name) return emps.at(i);
	}
	if (pSub->ListSubs().size() != 0)
	{
		vector<Subdivision*> cs = pSub->ListSubs();
		for (unsigned i = 0; i < cs.size(); i++)
		{
			if (FindEmp(cs.at(i), name)) return FindEmp(cs.at(i), name);
		}
	}
	return NULL;
}


void CreateEmp(Subdivision *pComp, const string& _sub, const string& name)
{
	try
	{
		if (FindEmp(pComp, name)) throw 1;
		Subdivision* pSub = FindSub(pComp, _sub);
		if (pSub == NULL) throw 2;
		Employee* pEmp = new Employee(name, pSub);
		pSub->AddEmp(pEmp);
	}
	catch (int i)
	{
		if (i == 1) cout << "Error " << i << ": this employee already exist!" << endl;
		if (i == 2) cout << "Error " << i << ": subdivision in which you want to add does not exist!" << endl;
	}
}


void AddSubordination(Subdivision *pComp, const string& name1, const string& name2)
{
	try
	{
		Employee* pEmp1 = FindEmp(pComp, name1);
		if (pEmp1 == NULL) throw 1;
		Employee* pEmp2 = FindEmp(pComp, name2);
		if (pEmp2 == NULL) throw 2;
		pEmp1->AddEmp(pEmp2);
		pEmp2->AddAdm(pEmp1);
	}
	catch (int i)
	{
		if (i == 1) cout << "Error " << i << ": admin does not exist!" << endl;
		if (i == 2) cout << "Error " << i << ": employee does not exist!" << endl;
	}
}


void DelSubordination(Subdivision* pComp, const string& name1, const string& name2)
{
	try
	{
		Employee* pEmp1 = FindEmp(pComp, name1);
		if (pEmp1 == NULL) throw 1;
		Employee* pEmp2 = FindEmp(pComp, name2);
		if (pEmp2 == NULL) throw 2;
		if (pEmp2->GetAdm() != pEmp1) throw 3;
		pEmp1->DelEmp(pEmp2);
		pEmp2->DelAdm();
	}
	catch (int i)
	{
		if (i == 1) cout << "Error " << i << ": admin does not exist!" << endl;
		if (i == 2) cout << "Error " << i << ": employee does not exist!" << endl;
		if (i == 3) cout << "Error " << i << ": there is no relationship of subordination!" << endl;
	}
}


void DelSubordination(Subdivision* pComp, Employee* pEmp1, Employee* pEmp2)
{
	try
	{
		if (pEmp2->GetAdm() != pEmp1) throw 3;
		pEmp1->DelEmp(pEmp2);
		pEmp2->DelAdm();
	}
	catch (int i)
	{
		if (i == 3) cout << "Error " << i << ": there is no relationship of subordination!" << endl;
	}
}


void DeleteEmp(Subdivision* pComp, const string& name)
{
	try
	{
		Employee* pEmp = FindEmp(pComp, name);
		if (pEmp == NULL) throw 1;
		if (pEmp->GetAdm() != NULL) DelSubordination(pComp, pEmp->GetAdm(), pEmp);
		if (pEmp->ListEmps().size() != 0)
		{
			vector<Employee*> emps = pEmp->ListEmps();
			for (unsigned i = 0; i < emps.size(); i++)
			{
				DelSubordination(pComp, pEmp, emps.at(i));
			}
		}
		Subdivision* pSub = pEmp->GetSub();
		pSub->DelEmp(pEmp);
		delete pEmp;
	}
	catch (int i)
	{
		if (i == 1) cout << "Error " << i << ": this employee does not exist!" << endl;
	}
}


void CreateSub(Subdivision *pComp, const string& _sub, const string& name)
{
	try
	{
		if (FindSub(pComp, name)) throw 1;
		Subdivision* pSub1 = FindSub(pComp, _sub);
		if (pSub1 == NULL) throw 2;
		Subdivision* pSub2 = new Subdivision(name, pSub1);
		pSub1->AddSub(pSub2);
	}
	catch (int i)
	{
		if (i == 1) cout << "Error " << i << ": this subdivision already exist!" << endl;
		if (i == 2) cout << "Error " << i << ": subdivision in which you want to add does not exist!" << endl;
	}
}