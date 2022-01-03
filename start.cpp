// laba4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

using namespace std;

struct FIO
{
	string name;
	string surname;
	string patronymic;
	FIO(string name, string surname, string patronymic)
	{
		this->name = name;
		this->surname = surname;
		this->patronymic = patronymic;
	}
	FIO()
	{
		name = surname = patronymic = "";
	}
	FIO(string data)
	{
		string temp = "";
		for (size_t i = 0; i < data.size(); i++)
		{
			if (data[i] == '_')
			{
				if (surname.empty())
				{
					surname = temp;
					temp = "";
				}
				else if (name.empty())
				{
					name = temp;
					temp = "";
				}
			}
			else
			{
				temp += data[i];
			}
		}
		patronymic = temp;
	}
	bool operator==(const FIO& other)
	{
		return (this->name == other.name && this->surname == other.surname && this->patronymic == other.patronymic);
	}
	bool operator>(const FIO& other)
	{
		if (this->surname == other.surname && this->name == other.name)
			return (this->patronymic > other.patronymic);
		else if (this->surname == other.surname)
			return (this->name > other.name);
		else return (this->surname > other.surname);
	}
	bool operator<(const FIO& other)
	{
		return (!(*this > other || *this == other));
	}
};


struct Date
{
	int day = 0;
	int month = 0;
	int year = 0;
	Date()
	{
		day = 0; month = 0; year = 0;
	}
	Date(string data)
	{
		string temp = "";
		for (size_t i = 0; i < data.size(); i++)
		{
			if (data[i] == '/')
			{
				if (day == 0)
				{
					day = stoi(temp);
					temp = "";
				}
				else if (month == 0)
				{
					month = stoi(temp);
					temp = "";
				}
			}
			else
			{
				temp += data[i];
			}
		}
		year = stoi(temp);
	}
	bool operator==(const Date& other)
	{
		return (this->day == other.day && this->month == other.month && this->year == other.year);
	}
	bool operator>(const Date& other)
	{
		if (this->year == other.year && this->month == other.month)
			return (this->day > other.day);
		else if (this->year == other.year)
			return (this->month > other.month);
		else return (this->year > other.year);
	}
	bool operator<(const Date& other)
	{
		return (!(*this > other || *this == other));
	}
};

struct Student
{
	FIO fio;
	string major;
	string group_number;
	Date date_of_birthday;
	string phone_number;
	Student()
	{
		fio = FIO();
		major = group_number = phone_number = "";
		date_of_birthday = Date();
	}
	Student(string data)
	{
		string temp = "";
		for (size_t i = 0; i < data.size(); i++)
		{
			if (data[i] == ' ')
			{
				if (fio == FIO())
				{
					fio = FIO(temp);
					temp = "";
				}
				else if (major == "")
				{
					major = temp;
					temp = "";
				}
				else if (group_number == "")
				{
					group_number = temp;
					temp = "";
				}
				else if (date_of_birthday == Date())
				{
					date_of_birthday = Date(temp);
					temp = "";
				}
			}
			else
				temp += data[i];

		}
		phone_number = temp;
	}
	bool operator>(const Student& other)
	{
		if (this->fio > other.fio)
			return true;
		else if (this->fio == other.fio)
			if (this->date_of_birthday > other.date_of_birthday)
				return true;
		return false;
	}
	bool operator<(const Student& other)
	{
		if (this->fio < other.fio)
			return true;
		else if (this->fio == other.fio)
			if (this->date_of_birthday < other.date_of_birthday)
				return true;
		return false;
	}
	bool operator==(const Student& other)
	{
		return (!(*this > other && *this < other));
	}
	bool operator!=(const Student& other)
	{
		return (!(*this == other));
	}

};

ostream& operator<< (std::ostream& out, const FIO& fio)
{
	out << fio.surname << " " << fio.name << " " << fio.patronymic;
	return out;
}

ostream& operator<< (std::ostream& out, const Date& date)
{
	out << date.day << "." << date.month << "." << date.year;
	return out;
}

ostream& operator<< (std::ostream& out, const Student& student)
{
	out << student.fio << '\t' << student.date_of_birthday << '\t' << student.group_number << '\t' << student.major << '\t' << student.phone_number << endl;
	return out;
}





struct Set
{
    Student data;
    Set* next;


};
void init(Set*& h)
{
    h = nullptr;

}
void add(Set*& h, Student value)
{
    if (h == nullptr)
    {
        h = new Set();
        h->data = value;
        h->next = nullptr;
    }
    else
    {
        bool SAME_NUMBERS_FLAG = false;
        Set* cur = h;
        Set* cur1 = new Set();
        cur1->data = value;
        cur1->next = nullptr;
        //cur = h;
        if (h->data != value)
        {
            while (cur->next != nullptr)
            {
                if ((cur->next->data == value) || (h->data == value))
                {
                    SAME_NUMBERS_FLAG = true;
                }
                cur = cur->next;
            }
            if (!SAME_NUMBERS_FLAG)
            {
                cur->next = cur1;
            }
        }
    }
}

void add(Set*& h, Set* addSet)
{
    if (h == addSet)
    {

    }
    else if (addSet != nullptr)
    {
        Set* cur = addSet;
        while (cur != nullptr)
        {
            add(h, cur->data);
            cur = cur->next;
        }
    }
}

int length(Set* h)
{
    int temp = 0;
    Set* cur = h;
    while (cur != nullptr)
    {
        cur = cur->next;
        temp++;
    }
    return temp;
}

void pop(Set*& h, Student value)
{
    if (h != nullptr)
    {
        if (h->data == value)
        {
            Set* cur = h;
            h = h->next;
            delete cur;
        }
        else
        {
            Set* cur1 = h;
            Set* cur2 = h->next;
            while (cur2 != nullptr)
            {
                if (cur2->data != value)
                {
                    cur1 = cur1->next;
                    cur2 = cur2->next;
                }
                else
                {
                    cur1->next = cur2->next;
                    delete cur2;
                    break;
                }
            }
        }
    }
}

bool found(Set* h, Student value)
{
    Set* cur = h;
    while (cur != nullptr)
    {
        if (cur->data == value)
        {
            return true;
        }
        cur = cur->next;
    }
    return false;
}

void clear(Set*& h)
{
    //Set* cur = h;
    while (h != nullptr)
    {
        pop(h, h->data);
    }
}

void crossSets(Set*& h, Set* crossSet)
{
    if ((h == nullptr) || (crossSet == nullptr))
    {
        clear(h);
    }
    else if (h == crossSet)
    {

    }
    else
    {
        Set* curCrossSet = crossSet;
        Set* curh = h;
        while (curh != nullptr)
        {
            if (!found(crossSet, curh->data))//удалять нельзя, так как элемент ищется в crossSet, а удаляется из h
            {
                Set* temp = curh;
                curh = curh->next;
                pop(h, temp->data);

            }
            else
            {
                curh = curh->next;
            }
        }
    }
}

void difference(Set*& h, Set* subtrahend)
{
    if (subtrahend != nullptr)
    {
        if (h == subtrahend) { clear(h); }
        else
        {
            Set* curSubtrahend = subtrahend;
            Set* curh = h;
            while (curh != nullptr)
            {
                if (found(subtrahend, curh->data))//аналогично, удалять нельзя
                {
                    Set* temp = curh;
                    curh = curh->next;
                    pop(h, temp->data);

                }
                else
                {
                    curh = curh->next;
                }
            }
        }
    }
}

void print(Set* h)
{
    if (h != nullptr)
    {
        Set* cur = h;
        while (cur != nullptr)
        {
            cout << cur->data << ' ';
            cur = cur->next;
        }
    }
    cout << endl;
    cout << "Set's power = " << length(h) << endl;
    cout << endl;
}


int main()
{
	setlocale(LC_ALL, "ru");
	fstream fin;
	string path = "input.txt";
	fin.open(path, ios::in);
	if (!fin.is_open())
	{
		cout << "Ошибка: не удалось открыть файл" << endl;
		return -1;
	}
	string temp;
	getline(fin, temp);
	int record_count = stoi(temp);
	Set* students;
	init(students);
	for (size_t i = 0; i < (record_count); i++)
	{
		getline(fin, temp);
		if (temp == "") continue;
		add(students, Student(temp));
	}
	fin.close();
	print(students);
	return 0;
}

