#include <iostream>
#include <fstream>
using namespace std;

class Student
{
private:
	char* name;
	int age;
	int* arrMarks;
	int countMarks;
	float avgMark;

	bool IsValidAge(int age) const
	{
		return age >= 0 && age <= 100;
	}

	void SetAveregeMark()
	{
		int suma = 0;
		for (int i = 0; i < countMarks; i++) 
		{
			suma += arrMarks[i];
		}
			avgMark = suma / countMarks;
	}

public:
	
	Student() // конструктор за замовчуванням
	{
		name = nullptr;
		SetName("No name");
		age = 0;
		countMarks = 0;
		avgMark = 0;
	}
	// параметризовані конструктори
	Student(const char* _name, int _age)
	{
		cout << "Constructor 2 (parametrized) !!!\n";

		name = nullptr;
		SetName(_name);

		if (IsValidAge(_age))
			age = _age;
		else
			age = 0;

		avgMark = 0;

		countMarks = 0;

	}

	Student(const char* _name, int _age, float _avgMark) : Student(_name, _age)
	{
		cout << "Constructor 3 (parametrized) !!!\n";
		avgMark = _avgMark;
	}
		
	~Student()
	{
		DeleteMemoryName();
		DeleteMemoryMarks();
	}

	void DeleteMemoryName()
	{
		if (name != nullptr) delete[] name;
			
	}

	void DeleteMemoryMarks()
	{
		if (arrMarks != nullptr) delete[] arrMarks;
	}

	// getters - методи для отримання значень
	const char* GetName() const
	{
		return name;
	}
	int GetAge() const
	{
		return age;
	}

	float GetAverege() const
	{
		return avgMark;
	}
	// setter - методи для встановлення значень
	void SetName(const char* _name)
	{
		if (name != nullptr)
			delete[] name;

		int size = strlen(_name) + 1;
		name = new char[size];
		strcpy_s(name, size, _name);
	}

	void AddMarks()
	{

		int size = countMarks + 1;
		int* tmp = new int[size];
		for (int i = 0; i < size; i++) {
			tmp[i] = arrMarks[i];
		}
		int MyMark;
		cout << "Enter mark: ";
		cin >> MyMark;
		tmp[size] = MyMark;
		delete[]arrMarks;

		for (int i = 0; i < size; i++) {
			arrMarks[i] = tmp[i];
		}
		size++;
		countMarks++;
		delete[]tmp;

		SetAveregeMark();
	}


	void SetAge(int _age)
	{
		if (IsValidAge(_age))
			age = _age;
	}

	

	void Print() const
	{
		cout << "--------- STUDENT ----------\n";
		if (name != nullptr)
			cout << "NAME: " << name << endl;
		cout << "Age: " << age << endl;
		cout << "Average mark: " << avgMark << endl;
		cout << "------------------------------\n";
	}

	void Save() const
	{
		ofstream fout;
		fout.open("Students.txt");
		bool isOpen = fout.is_open();
		if (!isOpen) {
			cout << "Error" << endl;
		}

		fout.write((char*)&a, sizeof(Student));
		fout.close();
	}

	void Load() const
	{
		ifstream fin;
		fin.open("Students.txt");
		if (!fin.is_open()) {
			cout << "Error" << endl;
		}

		Student tmp;
		while (fin.read((char*)&tmp, sizeof(Student)))
		{
			tmp.Print();
		}
		fin.close();
	}
};

int main()
{
	if (true)
	{
		Student st1;					// виклик конструтора
		st1.Print();
	}

	Student st2("Petro", 30);		// виклик конструтора

	Student st3("Bill", 33, 9);	// виклик конструтора

	const char* str = st2.GetName();

	cout << "st2: " << st2.GetName() << endl;
	cout << "st3: " << st3.GetName() << endl;

	st2.SetName("Tom");
	st3.SetAge(-10);

	cout << "st2 name: " << st2.GetName() << endl;
	cout << "st3 age: " << st3.GetAge() << endl;

	return 0;
}