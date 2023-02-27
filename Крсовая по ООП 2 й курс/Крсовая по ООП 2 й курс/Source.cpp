#include "Header.h"

const int MAX_SIZE = 50;
int a = 0;

//������� ��� �������� �� ����
void check_for_string(char* str)
{
	char string[MAX_SIZE];
	int counter = 0;
	int flag;
	while (true)
	{
		flag = 0;
		gets_s(string);

		for (int i = 0; i < strlen(string); i++)
		{
			if (string[i] < 97 || string[i]>122)
			{
				cin.clear();
				flag = 1;
				cout << "������������ ����. ����������, ���������� ��� ���.\n��������� ������ ��������� ����� ������� ��������\n���������� �����: "; break;
			}
		}
		//if (flag == 0) { strcpy(str, string); break; }
	}
}

int check_gender(string g) 
{
	if (g == "m" || g == "w") { return 1; }
	else return 0;
}

int check_menu(int counter) {
	int n;
	while (true) {
		cin >> n;
		if (cin.fail() || cin.peek() != '\n' || n < 1 || n > counter) {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "������������ ������. ����������, ���������� ��� ���.\n��� �����: ";
		}
		else
			return n;
	}
}

int check_int() 
{
	int s;
	while (true) {
		cin >> s;
		if (s<=0) {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "������������ ������. ����������, ���������� ��� ���.\n��� �����: ";
		}
		else
			return s;
	}
}

int check_day(int t)
{
	if (t >= 1 && t <= 30)
	{
		return 1;
	}
	return 0;
}

int check_month(int y)
{
	if (y >= 1 && y <= 12)
	{
		return 1;
	}
	return 0;
}

int check_year(int g)
{
	if (g >= 1900 && g <= 2025)
	{
		return 1;
	}
	return 0;
}



template <typename S>

class Admin//������������
{
public:
	Admin()
	{
		login_admin = "Admin";
		password_admin = "FRIDAY!#TH";
	}

	Admin(S log, S pass)
	{
		this->login_admin = log;
		this->password_admin = pass;
	}

	static void Out()
	{
		cout << "�����: " << login_admin << "\t������: " << password_admin << endl;
	}

	~Admin() {}

	bool Proverca(S& log, S& pass)
	{
		if (login_admin == log && password_admin == pass)
		{
			return TRUE;
		}
		else {
			return FALSE;
		}

	}

private:
	S login_admin;
	S password_admin;

};

int index;

class User//������������
{
public:
	User()
	{
		login_user = "User1";
		password_user = "1111";
	}

	User(string log, string pass)
	{
		this->login_user = log;
		this->password_user = pass;
	}

	void Out()
	{
		cout << "�����: " << login_user << "\t������: " << password_user << endl;
	}
	~User() {}

	bool Proverca(string log, string pass)
	{
		if (login_user == log && password_user == pass)
		{
			//cout << "���� �������� !" << endl;
			return TRUE;
		}
		else {
			//cout << "������ ������������ !" << endl;

			return FALSE;
		}

	}

	bool checkLogin(string log)
	{
		if (login_user == log) { return TRUE; }
	}

	string GetLogin()
	{
		return login_user;
	}
	string GetPassword()
	{
		return password_user;
	}
	bool operator()(User& a, User& b)
	{
		return a.GetLogin() < b.GetLogin();
	}
private:
	string login_user;
	string password_user;

};
vector<User> DB;

int auntification()
{
	string log, pass;
	char c;
	Admin<string> ad;
	int flag = 0;
	cout << "������� �����: ";
	cin >> log;
	cout << "������� ������: ";
	while ((c = _getch()) != '\r')
	{
		pass.push_back(c);
		_putch('*');
	}

	index = 0;
	if (ad.Proverca(log, pass) == TRUE) {
		cout << endl << "���� �������� !" << endl << "�����" << endl;
		flag = 1;
		index = 1;
	}
	else {
		for (int i = 0; i < DB.size(); i++) {
			if (DB[i].Proverca(log, pass) == TRUE)
			{
				cout << endl << "���� �������� !" << endl;
				flag = 1;
				index = 2;
				break;
			}
		}
		if (flag == 0)
		{
			cout << endl << "������ ����� !" << endl;
			return 0;
		}
	}
}
void add_users()
{
	int profiles;
	ofstream user_add_data;
	cout << "������� ���������� ������� �������������: ";
	cin >> profiles;
	static string login, pass;

	for (int i = 0; i < profiles; i++)
	{
		system("cls");
		cout << "������� ����� � ������ ��� " << i + 1 << " ������� ������" << endl;
		cout << "������� �����: ";
		cin >> login;
		cout << "������� ������: ";
		cin >> pass;
		DB.push_back(User(login, pass));
	}

	user_add_data.open("user.bin", ios::binary | ios::out);
	user_add_data.clear();
	for (int i = 0; i < DB.size(); i++)
	{
		user_add_data.write((char*)&DB[i], sizeof(User));
	}
	user_add_data.close();
}
void del_users()
{
	string log;
	cout << "������� ����� ������������ ��� ��������: ";
	cin >> log;
	int flag = 0;
	for (int i = 0; i < DB.size(); i++) {
		if (DB[i].checkLogin(log) == TRUE)
		{
			DB.erase(DB.begin() + i);
			flag = 1;
			ofstream user_add_data;

			user_add_data.open("user.bin", ios::binary | ios::out);
			user_add_data.clear();
			for (int i = 0; i < DB.size(); i++)
			{
				user_add_data.write((char*)&DB[i], sizeof(User));
			}
			user_add_data.close();
			break;
		}
	}
	if (flag == 0) { cout << "������ � ����� ������ �� ����������" << endl; }
	else cout << "�������� ������ � ������� " << log << " ���������" << endl;
}
void out_users()
{
	for (int i = 0; i < DB.size(); i++)
	{
		DB[i].Out();
	}
}

void change_users()
{
	string log;
	cout << "������� ����� ������������ ��� ���������: ";
	cin >> log;
	int flag = 0;
	for (int i = 0; i < DB.size(); i++) {
		if (DB[i].checkLogin(log) == TRUE)
		{
			string login, pass;
			flag = 1;
			ofstream user_add_data;
			cout << "������� �����: ";
			cin >> login;
			cout << "������� ������: ";
			cin >> pass;

			DB[i] = (User(login, pass));

			user_add_data.open("user.bin", ios::binary | ios::out);
			user_add_data.clear();
			for (int i = 0; i < DB.size(); i++)
			{
				user_add_data.write((char*)&DB[i], sizeof(User));
			}
			user_add_data.close();
			break;
		}
	}
	if (flag == 0) { cout << "������ � ����� ������ �� ����������" << endl; }
	else cout << "��������� ������ ���������" << endl;
}


void sort_users()
{
	system("cls");
	sort(DB.begin(), DB.end(), User());
	ofstream user_add_data;
	user_add_data.open("user.bin", ios::binary | ios::out);
	user_add_data.clear();
	for (int i = 0; i < DB.size(); i++)
	{
		user_add_data.write((char*)&DB[i], sizeof(User));
	}
	user_add_data.close();
	cout << "������ ������������" << endl;
}

int work_with_users() {
	system("cls");
	while (true)
	{
		int iItem;
		cout << "��������:\n";
		cout << "1 - ���������� �������������\n";
		cout << "2 - �������� �������������\n";
		cout << "3 - ����� �������������\n";
		cout << "4 - ��������������� �������������\n";
		cout << "5 - ���������� �������������\n";
		cout << "6 - �����\n";
		cout << "��� �����: ";

		cin >> iItem;
		switch (iItem)
		{
		case 1:
			system("cls");
			add_users();
			break;
		case 2:
			system("cls");
			del_users();
			break;
		case 3:
			system("cls");
			out_users();
			break;
		case 4:
			system("cls");
			change_users();
			break;
		case 5:
			system("cls");
			sort_users();
			break;
		default:
			system("cls");
			cout << "�����!";
			return 0;
			break;
		}
	}
}


//�����, ���������� ������� ���������� � ��������
class Human
{

public:
	Human()
	{
		fio = "Nikolai Famin";
		gender = "men";
	}
	Human(string fio, string gender)
	{
		this->fio = fio;
		this->gender = gender;

	}

	string get_fio() 
	{
		return fio;
	}

	bool operator()(Human& a, Human& b)
	{
		return a.get_fio() < b.get_fio();
	}
	
protected:
	string fio;
	string gender;
};

//�����, ���������� ������� ���������� � ���������
class Logist :public Human
{
public:
	Logist(string doljnost, string company, string fio, string gender) : Human(fio, gender)
	{
		this->doljnost = doljnost;
		this->company = company;
	}
	Logist()
	{
		doljnost = "Manager-Logist";
		company = "Amazon";
	}
	~Logist() {}

	string get_doljnost() 
	{
		return doljnost;
	}

	bool operator()(Logist& a, Logist& b)
	{
		return a.get_doljnost() < b.get_doljnost();
	}

	
protected:
	string doljnost;
	string company;
};

//�����, ���������� ���������� � ������������� �����
class Cargo : public Logist//����
{
public:

	Cargo()
	{
		name = "Mishlen";
		type = "Shini";
		day = 12;
		mounth = 2;
		year = 2021;
		id = 000;
	}

	Cargo(string fio, string gender, string doljnost, string company, string name, string type, int day, int mounth, int year,int id) :Logist(doljnost, company, fio, gender)
	{

		this->name = name;
		this->type = type;
		this->day = day;
		this->mounth = mounth;
		this->year = year;
		this->id = id;
	}

	void out()
	{
		cout << "|   " << setw(30) << left << fio << "|  " << setw(7) << left << gender << "|   " << setw(9) << doljnost << "|   " << setw(9) << company << "|   " << setw(9) << name << "|    " << setw(10) << type << "| " << setw(2) << day<<'.'<<setw(2) <<mounth<<'.'<<setw(5) <<year << "| "<< setw(3) <<id<<"|" << endl;
		cout << "|___________________________________________________________________________________________________________________|\n";

	}
	void outdate()
	{
		int d = day;
		int m = mounth;
		int y = year;
		d = d + 14 + rand() % 7;
		if(d>30)
		{
			m++;
			if (m > 12) { year++; }
		}
		cout << "|   " << setw(10) << name << "|    " << setw(10) << type << "| " << setw(2) << d << '.' << setw(2) << m << '.' << setw(4) << y << "| " << setw(3) << id << "|" << endl;
		cout << "|---------------------------------------------|\n";

	}
	bool checkName_cargo(string nam)
	{
		if (name == nam) { return TRUE; }
	}

	string GetName_cargo()
	{
		return name;
	}

	bool operator()(Cargo& a, Cargo& b)
	{
		return a.GetName_cargo() < b.GetName_cargo();
	}

	void id_down(int index) 
	{
		if (id < index) 
		{
			cout << " ___________________________________________________________________________________________________________________\n";
			cout << setw(34) << left << "|          FIO " << setw(10) << left << "| Gender" << setw(13) << "| Doljost" << setw(13) << "| Company" << setw(13) << "| Corgo name" << setw(15) << "| Cargo type" << setw(10) << "| Order date" << setw(5) << "| ID " << "|" << endl;
			cout << "|------------------------------------------------------------------------------------------------------------------|\n";
			out();
		}
	}

	void id_up(int index)
	{
		if (id > index)
		{
			cout << " ___________________________________________________________________________________________________________________\n";
			cout << setw(34) << left << "|          FIO " << setw(10) << left << "| Gender" << setw(13) << "| Doljost" << setw(13) << "| Company" << setw(13) << "| Corgo name" << setw(15) << "| Cargo type" << setw(10) << "| Order date" << setw(5) << "| ID " << "|" << endl;
			cout << "|------------------------------------------------------------------------------------------------------------------|\n";
			out();
		}
	}

	void date(int d, int m, int y) 
	{
		if (year<y) 
		{
			cout << " ___________________________________________________________________________________________________________________\n";
			cout << setw(34) << left << "|          FIO " << setw(10) << left << "| Gender" << setw(13) << "| Doljost" << setw(13) << "| Company" << setw(13) << "| Corgo name" << setw(15) << "| Cargo type" << setw(10) << "| Order date" << setw(5) << "| ID " << "|" << endl;
			cout << "|------------------------------------------------------------------------------------------------------------------|\n";
			out();
		}
		else if (year==y) 
			{
			if (mounth < m) { 
				cout << " ___________________________________________________________________________________________________________________\n";
				cout << setw(34) << left << "|          FIO " << setw(10) << left << "| Gender" << setw(13) << "| Doljost" << setw(13) << "| Company" << setw(13) << "| Corgo name" << setw(15) << "| Cargo type" << setw(10) << "| Order date" << setw(5) << "| ID " << "|" << endl;
				cout << "|------------------------------------------------------------------------------------------------------------------|\n";
				out(); }
			else if (mounth == m) 
				{
				if (day <= d) {
					cout << " ___________________________________________________________________________________________________________________\n";
					cout << setw(34) << left << "|          FIO " << setw(10) << left << "| Gender" << setw(13) << "| Doljost" << setw(13) << "| Company" << setw(13) << "| Corgo name" << setw(15) << "| Cargo type" << setw(10) << "| Order date" << setw(5) << "| ID " << "|" << endl;
					cout << "|------------------------------------------------------------------------------------------------------------------|\n";
					out(); }
				}
			}
	}

	void dol(string d)
	{
		if (doljnost == d)
		{
			cout << " ___________________________________________________________________________________________________________________\n";
			cout << setw(34) << left << "|          FIO " << setw(10) << left << "| Gender" << setw(13) << "| Doljost" << setw(13) << "| Company" << setw(13) << "| Corgo name" << setw(15) << "| Cargo type" << setw(10) << "| Order date" << setw(5) << "| ID " << "|" << endl;
			cout << "|------------------------------------------------------------------------------------------------------------------|\n";

			out();
		}
	}

protected:
	string name;
	string type;
	int day,mounth,year,id;
};

vector<Cargo> order;

class Sklad
{
public:
	Sklad()
	{
		sch = 0;
		location = "Pr. Mira 5";
	}

	Sklad(int sch, string& location)
	{
		this->sch = sch;
		this->location = location;
	}

	Sklad(const Sklad & ref_Skl) 
	{
		sch = ref_Skl.sch;
		location = ref_Skl.location;
	}

	

	void update(int sch)//���������� �������� 
	{
		this->sch = sch;
	}
protected:

	friend void set_Sch(Sklad&, int sch);
	int sch;//�������
	string location;
};


void set_Sch(Sklad& a, int sch) 
{
	a.sch = sch;
}

class Rab :public Sklad, public Human
{
public:
	Rab()
	{
		staj = 10;
	}
	Rab(string fio, string gender, int staj, string location, int sch) :Sklad(sch, location), Human(fio, gender)
	{
		this->staj = staj;
	}
	void Out()
	{
		cout << " __________________________________________________________________________________________\n";
		cout << setw(34) << left << "|          ��� ���������� ������ " << setw(10) << left << "| ���" << setw(13) << "| ����" << setw(13) << "| ����� ������" << setw(13) << "| ���������� ������" << setw(13) << "|" << endl;
		cout << "|-----------------------------------------------------------------------------------------|\n";
		cout << "|   " << setw(30) << left << fio << "|  " << setw(7) << left << gender << "|   " << setw(9) << staj << "|   " << setw(10) << location << "|   " << setw(15) <<sch<< "|" << endl;
		cout << "|_________________________________________________________________________________________|\n";
	}
	void update(int sch)//���������� �������� 
	{
		this->sch = sch;
	}
protected:
	int staj;

} sklad;

//������� �������� ������
void create(int n)
{
	int sch = 0;
	string fio, gender, doljnost, company, name, type, location;
	int day,mounth,year,staj,id;
	system("cls");

	if (sch < n)
	{
		ofstream order_add_data;
		order_add_data.open("order.bin", ios::binary | ios::out);
		for (int i = 0; i < n; i++)
		{
			system("cls");
			cout << "����������, �������  ������ ������������� �� ����� �������!\n";
			cout << "������� ���: ";
			getline(cin, fio);
			getline(cin, fio);
			while (TRUE) {
				cout << "������� ���: ";
				getline(cin, gender);
				if (check_gender(gender) == 1) { break; }
				else {
					system("cls");
					cout << "������� ����� ���, ���������� ��� ��� ! �������� ������� \"w\",\"m\"" << endl;
				}
			}
			cout << "������� ����� ������ (��������): ";
			getline(cin, company);
			system("cls");
			cout << "����������, ������ ������ � ������ !\n";

			cout << "������� �������� ������: ";
			getline(cin, name);

			cin.seekg(cin.eof());
			cout << "\n������� ��� ������: ";
			getline(cin, type);
			while (TRUE) {

				cout << "\n������� ���� ����������� ������: ";
				cin >> setw(2) >> day;
				if (check_day(day) == 1) {
					cin.ignore();
					cin >> setw(2) >> mounth;
					if (check_month(mounth) == 1) {
						cin.ignore();
						cin >> setw(2) >> year;
						if (check_year(year) == 1) { break; }
						else system("cls"); cout << "������� ������� ����, ���������� ��� ��� !" << endl;
					}
					else system("cls"); cout << "������� ������� ����, ���������� ��� ��� !" << endl;
				}
				else system("cls"); cout << "������� ������� ����, ���������� ��� ��� !" << endl;
			}
			int id = rand() % 999;

			shared_ptr<Cargo> c(new Cargo(fio, gender, doljnost, company, name, type, day, mounth, year,id));
			order.push_back(Cargo(fio, gender, doljnost, company, name, type, day, mounth, year, id));
			order_add_data.write((char*)&order[i], sizeof(Cargo));
			sch++;
			
		}
		order_add_data.close();
		system("cls");
		cout << " ����������, �������  ������ ������������� �� �����!\n";
		ofstream sklad_create_data;
		sklad_create_data.open("sklad.bin", ios::binary | ios::out);
		sklad_create_data.clear();
		cout << "������� ���: ";
		getline(cin, fio);
		getline(cin, fio);
		while (TRUE) {
			cout << "������� ���: ";
			getline(cin, gender);
			if (check_gender(gender) == 1) { break; }
			else {
				system("cls");
				cout << "������� ����� ���, ���������� ��� ��� ! �������� ������� \"w\",\"m\"" << endl;
			}
		}
		cout << "������� ���� ������: ";
		staj=check_int();
		cout << "������� ������ ������: ";
		getline(cin, location);
		getline(cin, location);
		shared_ptr<Rab> s(new Rab(fio, gender, staj, location, order.size()));
		sklad = *s;
		sklad_create_data.write((char*)&sklad, sizeof(Rab));
		sklad_create_data.close();
	}
	else cout << "\n������� ������������ ���-�� �������\n";
	system("cls");
}

void out()
{	system("cls");
	cout << " ____________________________________________________________________________________________________________________\n";
	cout << setw(34) << left << "|          ��� " << setw(10) << left << "| ���" << setw(13) << "| ���������" << setw(13) << "| ��������" << setw(13) << "| ��� ������" << setw(15) << "| ��� ������"  << setw(10) << "| ���� ������" << setw(5) << "| ID " << "|" << endl;
	cout << "|-------------------------------------------------------------------------------------------------------------------|\n";
	for (int j = 0; j < order.size(); j++)
	{
		order[j].out();
	}
	sklad.Out();
}

void add()
{
	string fio, gender, doljnost, company, name, type;
	int n,day,mounth,year;
	cout << "������� ���������� ������� ��� ����������: ";
	n = check_menu(10);
	if ((order.size() + n) <= 10)
	{
		ofstream order_add_data;
		order_add_data.open("order.bin", ios::binary | ios::out);
		for (int i = 0; i < n; i++)
		{
			cout << "����������, �������  ������ ������������� �� ����� �������!\n";
			cout << "������� ���: ";
			getline(cin, fio);
			getline(cin, fio);
			while (TRUE) {
				cout << "������� ���: ";
				getline(cin, gender);
				if (check_gender(gender) == 1) { break; }
				else { 
				system("cls"); 
				cout << "������� ����� ���, ���������� ��� ��� ! �������� ������� \"w\",\"m\"" << endl;
				}
			}
			cout << "������� ����� ������ (��������): ";
			getline(cin, company);
			system("cls");
			cout << "����������, ������ ������ � ������ !\n";

			cout << "������� �������� ������: ";
			getline(cin, name);

			cin.seekg(cin.eof());
			cout << "\n������� ��� ������: ";
			getline(cin,type);
			while (TRUE) {
				
				cout << "\n������� ���� ����������� ������: ";
				cin >> setw(2) >> day;
				if (check_day(day) == 1) {
					cin.ignore();
					cin >> setw(2) >> mounth;
					if (check_month(mounth) == 1) {
						cin.ignore();
						cin >> setw(2) >> year;
						if (check_year(year) == 1) { break; }
						else system("cls"); cout << "������� ������� ����, ���������� ��� ��� !" << endl;
					}
					else system("cls"); cout << "������� ������� ����, ���������� ��� ��� !" << endl;
				}
				else system("cls"); cout << "������� ������� ����, ���������� ��� ��� !" << endl;
			}
			int id = rand() % 999;
			shared_ptr<Cargo> c(new Cargo(fio, gender, doljnost, company, name, type, day, mounth, year,id));
			order.push_back(Cargo(fio, gender, doljnost, company, name, type, day, mounth, year, id));
			order_add_data.write((char*)&order[i], sizeof(Cargo));
		}
		order_add_data.close();
		sklad.update(order.size());
		system("cls");
		cout << "���������� ��������� �������\n";
	}
	else cout << "���������� �������� ������� �������\n";
}

void del()
{
	string name;
	cout << "������� ��� ������ ��� ��������: ";
	cin >> name;
	int flag = 0;
	for (int i = 0; i < order.size(); i++) {
		if (order[i].checkName_cargo(name) == TRUE)
		{
			order.erase(order.begin() + i);
			flag = 1;
			ofstream order_del_data;
			order_del_data.open("order.bin", ios::binary | ios::out);
			order_del_data.clear();
			for (int i = 0; i < order.size(); i++)
			{
				order_del_data.write((char*)&order[i], sizeof(Cargo));
			}
			order_del_data.close();
			sklad.update(order.size());
			break;
		}
	}
	if (flag == 0) { cout << "������ � ����� ������ �� ����������" << endl; }
	else cout << "�������� ������ c ������ ������ " << name << " ���������" << endl;
}

void change()
{
	string name;
	cout << "������� ��� ������ ��� ���������: ";
	cin >> name;
	int flag = 0;
	int day, mounth, year;
	for (int i = 0; i < order.size(); i++) {
		if (order[i].checkName_cargo(name) == TRUE)
		{
			flag = 1;
			string fio, gender, doljnost, company, name, type, date, location;
			int staj;
			system("cls");
			cout << "����������, �������  ������ ������������� �� ����� �������!\n";
			cout << "������� ���: ";
			getline(cin, fio);
			getline(cin, fio);
			cout << "������� ���: ";
			getline(cin, gender);
			cout << "������� ���������: ";
			getline(cin, doljnost);
			cout << "������� ����� ������ (��������): ";
			getline(cin, company);
			system("cls");
			cout << "����������, ������ ������ � ������ !\n";

			cout << "������� �������� ������: ";
			getline(cin, name);

			cin.seekg(cin.eof());
			cout << "\n������� ��� ������: ";
			getline(cin, type);

			cout << "\n������� ���� ����������� ������: ";
			cin >> setw(2) >> day;
			cin.ignore();
			cin >> setw(2) >> mounth;
			cin.ignore();
			cin >> setw(2) >> year;
			
			int id = rand() % 999;
			order[i]=Cargo(fio, gender, doljnost, company, name, type, day, mounth, year, id);

			ofstream order_change_data;
			order_change_data.open("order.bin", ios::binary | ios::out);
			order_change_data.clear();
			for (int i = 0; i < order.size(); i++)
			{
				order_change_data.write((char*)&order[i], sizeof(Cargo));
			}
			order_change_data.close();
			break;
		}
	}
	if (flag == 0) { cout << "������ � ����� ������ �� ����������" << endl; }
	else cout << "��������� ������ ���������" << endl;
}

void change_sklad() 
{
	string fio, gender, location;
	int staj;
	ofstream sklad_create_data;
	sklad_create_data.open("sklad.bin", ios::binary | ios::out);
	sklad_create_data.clear();
	cout << "������� ���: ";
	getline(cin, fio);
	cout << "������� ���: ";
	getline(cin, gender);
	cout << "������� ���� ������: ";
	cin >> staj;
	cout << "������� ������ ������: ";
	getline(cin, location);
	sklad = Rab(fio, gender, staj, location, order.size());
	sklad_create_data.write((char*)&sklad, sizeof(Rab));
	sklad_create_data.close();
}

//����������� �����
class Menu
{
public:
	virtual int menu_out() = 0;
};

class menu_�hange :public Menu
{
public:
	int menu_out() override 
	{
		int ch;
		cout << "�������� ��� �� ������ �������������: \n";
		cout << "1) ����� � ������������� �� ����\n";
		cout << "2) �����\n";
		cout << "3) �����\n";
		cout << "��� �����: ";
		ch = check_menu(4);
		switch (ch)
		{
		case 1: system("cls");
			change();
			break;
		case 2: system("cls");
			change_sklad();
			break;
		default:
			system("cls");
			return 0;
		}
	}
};

void sort_by_fio() 
{
	system("cls");
	sort(order.begin(), order.end(), Human());
	ofstream order_change_data;
	order_change_data.open("order.bin", ios::binary | ios::out);
	order_change_data.clear();
	for (int i = 0; i < order.size(); i++)
	{
		order_change_data.write((char*)&order[i], sizeof(Cargo));
	}
	order_change_data.close();
	cout << "����������� �� ����� �������������" << endl;
}

void sort_by_name_of_cargo()
{
	system("cls");
	sort(order.begin(), order.end(), Cargo());
	ofstream order_change_data;
	order_change_data.open("order.bin", ios::binary | ios::out);
	order_change_data.clear();
	for (int i = 0; i < order.size(); i++)
	{
		order_change_data.write((char*)&order[i], sizeof(Cargo));
	}
	order_change_data.close();
	cout << "����������� �� ����� ������ �������������" << endl;
}

void sort_by_doljnost() 
{
	system("cls");
	sort(order.begin(), order.end(), Logist());
	ofstream order_change_data;
	order_change_data.open("order.bin", ios::binary | ios::out);
	order_change_data.clear();
	for (int i = 0; i < order.size(); i++)
	{
		order_change_data.write((char*)&order[i], sizeof(Cargo));
	}
	order_change_data.close();
	cout << "����������� �� ��������� �������������" << endl;
}

void clear()
{
	ofstream order_change_data;
	order_change_data.open("order.bin", ios::binary | ios::out);
	order_change_data.clear();
	order.clear();
	ofstream sklad_change_data;
	sklad_change_data.open("sklad.bin", ios::binary | ios::out);
	sklad_change_data.clear();
	order.clear();
	cout << "������ ���� ������� ������� !" << endl;
}

//����������
class menu_sort :public Menu
{
public:
	int menu_out() override {
		int ch;
		cout << "�������� �������� ��� ����������: \n";
		cout << "1) �� ����� ������\n";
		cout << "2) �� ���\n";
		cout << "3) �� ���������\n";
		cout << "4) �����\n";
		cout << "��� �����: ";
		ch = check_menu(4);
		switch (ch)
		{
		case 1: sort_by_name_of_cargo();
			break;
		case 2: sort_by_fio();
			break;
		case 3: sort_by_doljnost();
			break;
		default:
			system("cls");
			return 0;
		}
	}
};


void filtration_id_down();
void filtration_id_up();
void filtration_date();
void filtratoin_doljnost();
//���������� ������� �� ���������
class menu_filtration :public Menu
{
public:
	int menu_out() override {
		int ch;
		cout << "�������� �������� ��� ���������� ������: \n";
		cout << "1) �� id ������\n";
		cout << "2) �� ���������\n";
		cout << "3) �� ����\n";
		cout << "4) �����\n";
		cout << "��� �����: ";
		ch = check_menu(4);
		switch (ch)
		{
		case 1:
			int choise;
			cout << "�������� �������� ��� ���������� ������: \n";
			cout << "1) �� id ������ ���� ��������\n";
			cout << "2) �� id ������ ���� ��������\n";
			cout << "3) �����\n";
			cout << "��� �����: ";
			choise = check_menu(3);
			switch (choise) 
			{
			case 1:
				system("cls");
				filtration_id_down();
				break;
			case 2:
				system("cls");
				filtration_id_up();
				break;
			default:
				system("cls");
				break;
			}
			break;
		case 2: 
			system("cls");
			filtratoin_doljnost();
			break;
		case 3: filtration_date();
			break;
		default:
			system("cls");
			return 0;
		}
	}
};

class m_out 
{
public:
	int menu_out(Menu *menu)
	{
		menu->menu_out();
		return 0;
	}
};

void filtration_id_down()
{
	system("cls");
	int id;
	int flag=0;
	cout << "������� ID: ";
	cin >> id;
	for (int i = 0; i < order.size(); i++) 
	{
		order[i].id_down(id);
		flag = 1;
	}
	if (flag = 0) cout << "������� ���� ����� ID �� ����������" << endl;
}

void filtration_id_up()
{
	system("cls");
	int id;
	int flag = 0;
	cout << "������� ID: ";
	cin >> id;
	for (int i = 0; i < order.size(); i++)
	{
		order[i].id_up(id);
		flag = 1;
	}
	if (flag = 0) cout << "������� ���e ����� ID �� ����������" << endl;
}

void filtration_date() 
{
	int day, mounth, year;
	cout << "\n������� ����: ";
	cin >> setw(2) >> day;
	cin.ignore();
	cin >> setw(2) >> mounth;
	cin.ignore();
	cin >> setw(2) >> year;
	cout << "\n\n" << day << '\t' << mounth << '\t' << year;

	for (int i = 0; i < order.size(); i++) 
	{
		order[i].date(day,mounth,year);
	}
	
}

void filtratoin_doljnost() 
{
	string doljnost;
	cout << "������� ���������: ";
	cin >> doljnost;

	for (int i = 0; i < order.size(); i++) 
	{
		order[i].dol(doljnost);
	}
}


//���� �������������� � ������������
int menu_adm()
{
	cout << "����� ���������� � ��������� �ר�� � ����������� ������ �� ����� ������������� ��������\n\n";
	cout << "��������� �������� ���������:\n\n";
	int choise;
	cout << "1) ���� ������\n";
	cout << "2) ����� ������\n";
	cout << "3) ���������� ������\n";
	cout << "4) �������������� ������\n";
	cout << "5) �������� ������\n";
	cout << "6) ���������� ������ �� ���������\n";
	cout << "7) ����� ������ �� ���������\n";
	cout << "8) ������ � ��������������\n";
	cout << "9) �������� ������\n";
	cout << "10) ����� �� ���������\n";
	cout << "��� �����: ";
	choise = check_menu(15);
	system("cls");
	return choise;
}
int menu_user()
{
	int choise;
	cout << "1) �������� ������\n";
	cout << "2) ���������� ������ �� ���������\n";
	cout << "3) ���������� ������\n";
	cout << "4) ���������� ������ �� ���������\n";
	cout << "5) �������� �������\n";
	cout << "6) ������ ���� ��������\n";
	cout << "7) ����� �� ���������\n";
	cout << "��� �����: ";

	choise = check_menu(6);
	return choise;
}


//���� �������
void set_color()
{
	CONSOLE_SCREEN_BUFFER_INFOEX info;
	info.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfoEx(hConsole, &info);
	info.ColorTable[1] = RGB(229, 33, 101); //���� ������ 
	info.ColorTable[0] = RGB(5, 7, 22); //���� ���� 
	SetConsoleScreenBufferInfoEx(hConsole, &info);
	SetConsoleTextAttribute(hConsole, 1);
}

int main()
{
	set_color();
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int n;
	menu_�hange change;
	menu_sort sort;
	menu_filtration filtr;
	m_out menu;

	// �������� �������������
	/*int profiles;
	ofstream user_add_data;
	cout << "������� ���������� ������� �������������: ";
	cin >> profiles;
	static string login, pass;
	user_add_data.open("user.bin", ios::binary | ios::out);
	user_add_data.clear();
	for (int i = 0; i < profiles; i++)
	{
		system("cls");
		cout << "������� ����� � ������ ��� " << i + 1 << " ������� ������" << endl;
		cout << "������� �����: ";
		cin >> login;
		cout << "������� ������: ";
		cin >> pass;
		DB.push_back(User(login, pass));
		user_add_data.write((char*)&DB[i], sizeof(User));
	}
	user_add_data.close();

	DB.clear();*/

	//���������� ������ � ������������
	ifstream user_read_data;
	user_read_data.open("user.bin", ios::binary | ios::in);
	User ptr;
	while (user_read_data.read((char*)&ptr, sizeof(User)))
	{
		DB.push_back(ptr);
	}
	user_read_data.close();

	//���������� ������ � ������
	ifstream order_read_data;
	order_read_data.open("order.bin", ios::binary | ios::in);
	Cargo p;

	while (order_read_data.read((char*)&p, sizeof(Cargo)))
	{
		order.push_back(p);
	}
	order_read_data.close();

	//���������� ������ � ������
	ifstream sklad_read_data;
	sklad_read_data.open("sklad.bin", ios::binary | ios::in);
	Rab s;
	sklad_read_data.read((char*)&s, sizeof(Rab));
	sklad = s;


	while (TRUE)
	{	
		int id=0,flag = 3;
		while (flag !=0) {
			system("cls");
			cout << "� ��� �������� " << flag << " �������"<<endl;
			if (auntification() == FALSE)
			{
				cout << "������ �����. ���������� ����� !" << endl; flag--;
				system("PAUSE");
			}
			else { id = 1; system("cls"); break; }
		}
		if (flag == 0||id == 1) system("cls"); break;
	}
	while (1)
	{
		if (index == 1)
		{
			switch (menu_adm())
			{
			case 1:

				if (order.size() == 0)
				{
					system("cls");
					cout << "�������, ���������� ������� (�� ����� 10 �������): ";
					n = check_menu(10);
					create(n);
				}
				else
				{
					system("cls");
					cout << "\n 		��������� ��� �������� ������\n 		����������, �������������� �������� �3\n\n";
				}
				break;

			case 2:
				if (order.size() == 0) cout << "������ ���. �������������� ������ � 1 ��� 3! " << endl;
				else {
					system("cls");
					out();
				}
				break;

			case 3:
				if (order.size() != 0)
				{
					system("cls");
					add();
				}
				else
				{
					system("cls");
					cout << "\n����������, �������������� ������� �������� �1\n\n";
				}

				break;

			case 4:
				system("cls");
				menu.menu_out(&change);
				break;

			case 5:
				system("cls");
				del();
				break;

			case 6:
				if (order.size() == 0|| order.size()==1)
				{
					system("cls");
					cout << "������ �����������. �������������� ������ � 1"<<endl;
					break;
				}
				else 
				{
					system("cls");
					menu.menu_out(&sort);
					break;
				}

			case 7:
				if (order.size() != 0)
				{
					system("cls");
					menu.menu_out(&filtr);
				}
				else
				{
					system("cls");
					cout << "\n����������, �������������� ������� �������� �1\n\n";
				}
				break;

			case 8:
				system("cls");
				work_with_users();
				break;

			case 9:

				system("cls");
				if (order.size() != 0) clear();
				else cout << "� ����� ��� ������ �������������� ������� �1" << endl;
				break;

			case 10:
				return 0;

			default:puts("�������� ��������"); break;
			}
		}
		else if (index == 2) //������������
		{
			switch (menu_user())
			{
			case 1:

				system("cls");
				out();
				break;

			case 2:

				system("cls");
				sort_by_name_of_cargo();
				break;

			case 3:
				system("cls");
				add();
				break;

			case 4:
				system("cls");
				menu.menu_out(&filtr);
				break;

			case 5:
				system("cls");
				break;
			case 6:
				system("cls");
				cout << " ______________________________________________\n";
				cout << "|"<< setw(13)<<" ��� ������" << setw(15) << "| ��� ������" << setw(10) << "| ���� �����" << setw(5) << "| ID " << "|" << endl;
				cout << "|---------------------------------------------|\n";
				for (int i = 0; i < order.size(); i++) { order[i].outdate(); }
				break;
			case 7:
				return 0;
			default:puts("�������� ��������"); break;
			}
		}
	}
	if (index == 0) { 
		return 0; }
}