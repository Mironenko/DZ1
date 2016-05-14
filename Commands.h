#pragma once
using namespace std;
class Subdivision;
class Employee;


Subdivision* FindSub(Subdivision *pComp, const string& name)  // Найти подразделение по названию (вернуть указатель на него)
{
	Subdivision* pSub = pComp;
	if (pSub->name() == name) return pSub;
	if (pSub->ListSubs().size() != 0) // лишняя проверка
	{
		vector<Subdivision*> cs = pSub->ListSubs();
		for (unsigned i = 0; i < cs.size(); i++)
			if (FindSub(cs.at(i), name)) return FindSub(cs.at(i), name); // два поиска?
	}
	return NULL;
}


Employee* FindEmp(Subdivision *pComp, const string& name)  // Найти сотрудника по имени (вернуть указатель на него)
{
	Subdivision* pSub = pComp;
	if (pSub->ListEmps().size() != 0) // !
	{
		vector<Employee*> emps = pSub->ListEmps();
		for (unsigned i = 0; i < emps.size(); i++) // use iterators!
			if (emps.at(i)->name() == name) return emps.at(i);
	}
	if (pSub->ListSubs().size() != 0)
	{
		vector<Subdivision*> cs = pSub->ListSubs();
		for (unsigned i = 0; i < cs.size(); i++)
		{
			if (FindEmp(cs.at(i), name)) return FindEmp(cs.at(i), name); // !
		}
	}
	return NULL;
}


void CreateEmp(Subdivision *pComp, const string& _sub, const string& name)  // Нанять сотрудника
{
	try
	{
		if (FindEmp(pComp, name)) throw 1; // типы, а не значения
		Subdivision* pSub = FindSub(pComp, _sub);
		if (pSub == NULL) throw 2;
		Employee* pEmp = new Employee(name, pSub);
		pSub->AddEmp(pEmp);
		string move = "Was hired to ";
		move += pSub->name();
		pEmp->AddHist(move);
	}
	catch (int i)
	{
		if (i == 1) cout << "Error " << i << ": this employee already exist!" << endl;
		if (i == 2) cout << "Error " << i << ": subdivision does not exist!" << endl;
	}
}


void ChangeSubordination(Subdivision* pComp, const string& adm, const string& emp)  // Добавить/изменить связь начальник-подчиненный
{
	try
	{
		Employee* pEmp = FindEmp(pComp, emp);
		if (pEmp == NULL) throw 1;
		Employee* pAdm = FindEmp(pComp, adm);
		if (pAdm == NULL) throw 2;
		Employee* pExAdm = pEmp->GetAdm();
		if (pAdm == pExAdm) throw 3;
		if (pExAdm) pExAdm->DelEmp(pEmp);
		pEmp->AddAdm(pAdm);
		pAdm->AddEmp(pEmp);
	}
	catch (int i)
	{
		if (i == 1) cout << "Error " << i << ": this employee does not exist!" << endl;
		if (i == 2) cout << "Error " << i << ": this admin does not exist!" << endl;
		if (i == 3) cout << "Error " << i << ": this employee already has this chief" << endl;
	}
}


void DelSubordination(Subdivision* pComp, const string& name1, const string& name2)  // Удалить связь начальник-подчиненный (по именам)
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


void DelSubordination(Subdivision* pComp, Employee* pEmp1, Employee* pEmp2)  // Удалить связь начальник-подчиненный (по указателям)
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


void TransEmp(Subdivision* pComp, const string& emp, const string& sub)  // Перевести сотрудника в другое подразделение (по имени и названию)
{
	try
	{
		Employee* pEmp = FindEmp(pComp, emp);
		if (pEmp == NULL) throw 1;
		Subdivision* pSub = FindSub(pComp, sub);
		if (pSub == NULL) throw 2;
		Subdivision* pExSub = pEmp->GetSub();
		if (pSub == pExSub) throw 3;
		// а что с начальниками и подчиненными?
		// go call TransEmp
		pExSub->DelEmp(pEmp);
		pSub->AddEmp(pEmp);
		pEmp->ChangeSub(pSub);
		string move = "Was transferred to ";
		move += pSub->name();
		pEmp->AddHist(move);
	}
	catch (int i)
	{
		if (i == 1) cout << "Error " << i << ": this employee does not exist!" << endl;
		if (i == 2) cout << "Error " << i << ": this subdivision does not exist!" << endl;
		if (i == 3) cout << "Error " << i << ": this employee is already in this subdivision!" << endl;
	}
}


void TransEmp(Subdivision* pComp, Employee* pEmp, Subdivision* pSub)  // Перевести сотрудника в другое подразделение (по указателям)
{
	Subdivision* pExSub = pEmp->GetSub();
	pExSub->DelEmp(pEmp);
	pSub->AddEmp(pEmp);
	pEmp->ChangeSub(pSub);
	string move = "Was transferred to ";
	move += pSub->name();
	pEmp->AddHist(move);
}


void ShowSubordination(Subdivision* pComp, const string& name)  // Показать структуру подчиненности для сотрудника
{
	try
	{
		Employee* pEmp = FindEmp(pComp, name);
		if (pEmp == NULL) throw 1;
		Employee* pAdm = pEmp->GetAdm();
		if (pAdm) cout << "Chief: " << pAdm->name() << endl;
		else cout << "No chief" << endl;
		vector<Employee*> emps = pEmp->ListEmps();
		if (emps.size())
		{
			cout << "Subordinates: ";
			for (unsigned i = 0; i < (emps.size() - 1); i++)
				cout << emps.at(i)->name() << ", ";
			cout << emps.back()->name() << endl;
		}
		else cout << "No subordinates" << endl;
	}
	catch (int i)
	{
		if (i == 1) cout << "Error " << i << ": this employee does not exist!" << endl;
	}
}


void ShowHist(Subdivision* pComp, const string& name)  // Показать историю перемещений сотрудника
{
	try
	{
		Employee* pEmp = FindEmp(pComp, name);
		if (pEmp == NULL) throw 1;
		pEmp->ListHist();
	}
	catch (int i)
	{
		if (i == 1) cout << "Error " << i << ": this employee does not exist!" << endl;
	}
}


void DeleteEmp(Subdivision* pComp, const string& name)  // Уволить сотрудника (по имени)
{
	try
	{
		Employee* pEmp = FindEmp(pComp, name);
		if (pEmp == NULL) throw 1;
		// DeleteEmp(pComp, pEmp);
		if (pEmp->GetAdm()) DelSubordination(pComp, pEmp->GetAdm(), pEmp);
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


void DeleteEmp(Subdivision* pComp, Employee* pEmp)  // Уволить сотрудника (по указателю)
{
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


void CreateSub(Subdivision *pComp, const string& _sub, const string& name)  // Сформировать подразделение
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


void DeleteSub(Subdivision* pComp, Subdivision* pSub)  // Расформировать подразделение (по указателю)
{
	if (pSub->ListEmps().size() != 0)
	{
		vector<Employee*> emps = pSub->ListEmps();
		for (unsigned i = 0; i < emps.size(); i++)
			DeleteEmp(pComp, emps.at(i));
	}
	if (pSub->ListSubs().size() != 0)
	{
		vector<Subdivision*> subs = pSub->ListSubs();
		for (unsigned i = 0; i < subs.size(); i++)
			DeleteSub(pComp, subs.at(i));
	}
	Subdivision* pUpSub = pSub->GetUpSub();
	pUpSub->DelSub(pSub);
	delete pSub;
}


void DeleteSub(Subdivision* pComp, const string& name)  // Расформировать подразделение (по названию)
{
	try
	{
		Subdivision* pSub = FindSub(pComp, name);
		if (pSub == NULL) throw 1;
		if (pSub == pComp) throw 2;
		// !
		if (pSub->ListEmps().size() != 0)
		{
			vector<Employee*> emps = pSub->ListEmps();
			for (unsigned i = 0; i < emps.size(); i++)
				DeleteEmp(pComp, emps.at(i));
		}
		Subdivision* pUpSub = pSub->GetUpSub();
		pUpSub->DelSub(pSub);
		if (pSub->ListSubs().size() != 0)
		{
			vector<Subdivision*> subs = pSub->ListSubs();
			for (unsigned i = 0; i < subs.size(); i++)
				DeleteSub(pComp, subs.at(i));
		}
		delete pSub;
	}
	catch (int i)
	{
		if (i == 1) cout << "Error " << i << ": this subdivision does not exist!" << endl;
		if (i == 2) cout << "Error " << i << ": you can not disband your company!" << endl;
	}
}


void TransSub(Subdivision* pComp, const string& sub, const string& dest)  // Переместить подразделение в другое (по названиям)
{
	try
	{
		if (sub == dest) throw 1;
		Subdivision* pSub = FindSub(pComp, sub);
		if (pSub == NULL) throw 2;
		Subdivision* pDest = FindSub(pComp, dest);
		if (pDest == NULL) throw 3;
		if (pSub->GetUpSub() == pDest) throw 4;
		Subdivision* pExSub = pSub->GetUpSub();
		pExSub->DelSub(pSub);
		pDest->AddSub(pSub);
		pSub->ChangeUpSub(pDest);
	}
	catch (int i)
	{
		if (i == 1) cout << "Error " << i << ": you entered same subdivisions!" << endl;
		if (i == 2) cout << "Error " << i << ": this subdivision does not exist!" << endl;
		if (i == 3) cout << "Error " << i << ": this destination does not exist!" << endl;
		if (i == 4) cout << "Error " << i << ": this subdivision already in this destination!" << endl;
	}
}


void TransSub(Subdivision* pComp, Subdivision* pSub, Subdivision* pDest)  // Переместить подразделение в другое (по указателям)
{
	Subdivision* pExSub = pSub->GetUpSub();
	pExSub->DelSub(pSub);
	pDest->AddSub(pSub);
	pSub->ChangeUpSub(pDest);
}


void UniteSubs(Subdivision* pComp, const string& sub1, const string& sub2, const string& name)  // Объединить подразделения
{
	try
	{
		if (sub1 == sub2) throw 1;
		Subdivision* pSub1 = FindSub(pComp, sub1);
		if (pSub1 == NULL) throw 2;
		Subdivision* pSub2 = FindSub(pComp, sub2);
		if (pSub2 == NULL) throw 3;
		if (pSub1->GetUpSub() != pSub2->GetUpSub()) throw 4;
		if (pSub2->ListSubs().size())
		{
			vector<Subdivision*> subs = pSub2->ListSubs();
			for (unsigned i = 0; i < subs.size(); i++)
				TransSub(pComp, subs.at(i), pSub1);
		}
		if (pSub2->ListEmps().size())
		{
			vector<Employee*> emps = pSub2->ListEmps();
			for (unsigned i = 0; i < emps.size(); i++)
				TransEmp(pComp, emps.at(i), pSub1);
		}
		Subdivision* pHead = pSub1->GetUpSub();
		pHead->DelSub(pSub2);
		delete pSub2;
		pSub1->rename(name);
	}
	catch (int i)
	{
		if (i == 1) cout << "Error " << i << ": you entered same subdivisions!" << endl;
		if (i == 2) cout << "Error " << i << ": first subdivision does not exist!" << endl;
		if (i == 3) cout << "Error " << i << ": second subdivision does not exist!" << endl;
		if (i == 4) cout << "Error " << i << ": you can not unite subdivisions of deffenrent levels!" << endl;
	}
}


void ReformSub(Subdivision* pComp, const string& sub)  // Переформировать подразделение
{
	try
	{
		Subdivision* pSub = FindSub(pComp, sub);
		if (pSub == NULL) throw 1;
		cout << "Enter new name:" << endl;
		string name;
		cin >> name;
		bool chsubs = 0;
		bool chemps = 0;
		if (pSub->ListSubs().size())
		{
			cout << "Disband its subdivisions? (Y or N): ";
			char ans;
			cin >> ans;
			if (ans == 'Y') chsubs = 1;
			else if (ans != 'N') throw 2;
		}
		if (pSub->ListEmps().size())
		{
			cout << "Lay off its employees? (Y or N): ";
			char ans;
			cin >> ans;
			if (ans == 'Y') chemps = 1;
			else if (ans != 'N') throw 2;
		}
		if (chsubs)
		{
			vector<Subdivision*> subs = pSub->ListSubs();
			for (unsigned i = 0; i < subs.size(); i++)
				DeleteSub(pComp, subs.at(i));
		}
		if (chemps)
		{
			vector<Employee*> emps = pSub->ListEmps();
			for (unsigned i = 0; i < emps.size(); i++)
				DeleteEmp(pComp, emps.at(i));
		}
		pSub->rename(name);
	}
	catch (int i)
	{
		if (i == 1) cout << "Error " << i << ": this subdivision does not exist!" << endl;
		if (i == 2) cout << "Error " << i << ": invalid answer!" << endl;
	}
}


void ClearSub(Subdivision* pComp, Subdivision* pSub)  // Очистить подразделение
{
	vector<Subdivision*> subs = pSub->ListSubs();
	if (subs.size())
		for (unsigned i = 0; i < subs.size(); i++)
			DeleteSub(pComp, subs.at(i));
	vector<Employee*> emps = pSub->ListEmps();
	if (emps.size())
		for (unsigned i = 0; i < emps.size(); i++)
			DeleteEmp(pComp, emps.at(i));
}


void _Save(ofstream* out, Subdivision* pSub, vector<string>* subord)  // Сохранение в файл (рекурсия)
{
	vector<Employee*> emps = pSub->ListEmps();
	if (emps.size())
		for (unsigned i = 0; i < emps.size(); i++)
		{
			*out << "hire " << pSub->name() << " " << emps.at(i)->name() << endl;
			if (emps.at(i)->GetAdm())
			{
				string com;
				Employee* pAdm = emps.at(i)->GetAdm();
				com += "appointchief ";
				com += pAdm->name();
				com += " ";
				com += emps.at(i)->name();
				subord->push_back(com);
			}
		}
	vector<Subdivision*> subs = pSub->ListSubs();
	if (subs.size())
		for (unsigned i = 0; i < subs.size(); i++)
		{
			*out << "form " << pSub->name() << " " << subs.at(i)->name() << endl;
			_Save(out, subs.at(i), subord);
		}
}


void Save(Subdivision* pComp, const string& file)  // Сохранение в файл (начало)
{
	ofstream out(file);
	vector<string> subord;

	vector<Employee*> emps = pComp->ListEmps();
	if (emps.size())
		for (unsigned i = 0; i < emps.size(); i++)
		{
			out << "hire Company " << emps.at(i)->name() << endl;
			if (emps.at(i)->GetAdm())
			{
				string com;
				Employee* pAdm = emps.at(i)->GetAdm();
				com += "appointchief ";
				com += pAdm->name();
				com += " ";
				com += emps.at(i)->name();
				subord.push_back(com);
			}
		}
	vector<Subdivision*> subs = pComp->ListSubs();
	if (subs.size())
		for (unsigned i = 0; i < subs.size(); i++)
		{
			out << "form Company " << subs.at(i)->name() << endl;
			_Save(&out, subs.at(i), &subord);
		}
	for (unsigned i = 0; i < subord.size(); i++)
		out << subord.at(i) << endl;

	out << "stop";
	out.close();
}

// FileCommandsHandler?
void _Handler(ifstream* in, Subdivision* pComp, const string& command)  // Обработчик для команд из файла
{
	if (command == "hire")
	{
		string sub, name;
		*in >> sub >> name;
		CreateEmp(pComp, sub, name);
	}
	else if (command == "appointchief")
	{
		string chief, emp;
		*in >> chief >> emp;
		ChangeSubordination(pComp, chief, emp);
	}
	else if (command == "form")
	{
		string sub, name;
		*in >> sub >> name;
		CreateSub(pComp, sub, name);
	}
}


void Handler(Subdivision* pComp, const string& command)  // Обработчик комманд
{
	if (command == "hire")
	{
		string sub, name;
		cin >> sub >> name;
		CreateEmp(pComp, sub, name);
	}
	else if (command == "layof")
	{
		string name;
		cin >> name;
		DeleteEmp(pComp, name);
	}
	else if (command == "transferemployee")
	{
		string emp, dest;
		cin >> emp >> dest;
		TransEmp(pComp, emp, dest);
	}
	else if (command == "showmovements")
	{
		string emp;
		cin >> emp;
		ShowHist(pComp, emp);
	}
	else if (command == "appointchief")
	{
		string chief, emp;
		cin >> chief >> emp;
		ChangeSubordination(pComp, chief, emp);
	}
	else if (command == "changechief")
	{
		string chief, emp;
		cin >> chief >> emp;
		ChangeSubordination(pComp, chief, emp);
	}
	else if (command == "showsubordination")
	{
		string emp;
		cin >> emp;
		ShowSubordination(pComp, emp);
	}
	else if (command == "form")
	{
		string sub, name;
		cin >> sub >> name;
		CreateSub(pComp, sub, name);
	}
	else if (command == "disband")
	{
		string sub;
		cin >> sub;
		DeleteSub(pComp, sub);
	}
	else if (command == "transfersubdivision")
	{
		string sub, dest;
		cin >> sub >> dest;
		TransSub(pComp, sub, dest);
	}
	else if (command == "reform")
	{
		string sub;
		cin >> sub;
		ReformSub(pComp, sub);
	}
	else if (command == "unite")
	{
		string sub1, sub2, name;
		cin >> sub1 >> sub2;
		UniteSubs(pComp, sub1, sub2, name);
	}
	else if (command == "save")
	{
		string name;
		cin >> name;
		Save(pComp, name);
		cout << "Saved to " << name << endl;
	}
	else if (command == "load")
	{
		string name;
		cin >> name;
		ifstream in(name);
		if (!in.is_open())
			cout << "File does not exist!";
		else
			ClearSub(pComp, pComp);
			for (; ; )
			{
				string com;
				in >> com;
				if (com == "stop")
					break;
				else
					_Handler(&in, pComp, com);
			}
			in.close();
			cout << "Loaded from " << name << endl;
	}
	else cout << "Invalid command!" << endl;
}