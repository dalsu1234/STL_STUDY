#include <iostream>
#include <map>

class Student
{

public:
	std::string mName;
	int mScore;
	void Print() const
	{
		std::cout << mName << " : " << mScore << std::endl;
	}

};

using Students = std::map<int , Student>;

void AddStudent(Students& v)
{
	std::cout << " ��ȣ �̸� ���� : ";
	Student newStudent;
	int number;
	
	if (std::cin >> number >> newStudent.mName >> newStudent.mScore)
	{
		// v.insert({number,newStudent}); 
		// pair�� �������ʱ�ȭ ������ �ʱ�ȭ �Ҽ��ִ�
		// .insert�� ��ȯ���� iterator�� bool���� ���ƿ´�
		// ��ȯ���� �ΰ� pair�� ��ȯ���� �ΰ���
		// std::pair<std::map<int, Student>::iterator,bool>
		// ���⼭ auto�� 
		// auto result = std::pair<std::map<int, Student>::iterator,bool>
		
		auto result = v.insert({number, newStudent});
		
		if (result.second == false)// map�� �ι�°���� bool���̴ϱ� �̷���
		{
			std::cout << "�ߺ��� �л� ��ȣ�Դϴ�." << std::endl;
		}
	}
	else
	{
		std::cout << " �߸��� �Է��Դϴ�. " << std::endl;
	}
}

void RemoveStudent(Students& v)
{
	std::cout << "���� �л� ��ȣ : ";
	int number;
	if (std::cin >> number)
	{
		//eraser-remove idiom
		//���� �����̳ʿ����� ���ﶧ �޸� ������ ��������ʴ´�
		// �׷��� eraser-remove idiom�� �ʿ���� �׳� �����ȴ�
		//v.erase(number) �� ��ȯ���� 0�� 1�̴�
		// ������ �ȴٸ� 1 �ȵȴٸ�0 
		// �׷��� ��ȯ���� 0�̸� 
		if (v.erase(number))
		{
			std::cout << "���� ��ȣ�Դϴ�." << std::endl;
		}
	
	}
	else
	{
		std::cout << "�߸��� �Է��Դϴ�." << std::endl;
	}
}

void PrintStudents(const Students& v)
{
	for (const auto& e : v)
	{
		std::cout << "(" << e.first << ") ";
		e.second.Print();
	}
	// ���⼭ e�� Ÿ����?
	// pair<{number, Student}>
}

void PrintScoreInfo(const Students& v)
{
	float total{};
	for (const auto& e : v)
	{
		total += e.second.mScore;
	}
	std::cout << "Total : " << total
		<< ", Average" << total / v.size() << std::endl;
}

void PrintOverAverage(const Students& v)
{
	float average{};
	for (const auto& e: v)
	{
		average += e.second.mScore;
	}
	average /= v.size();
	for (const auto& e : v)
	{
		if (e.second.mScore >= average)
		{
			std::cout << "(" << e.first << ")";
			e.second.Print();
		}
	}
}

int main()
{
	Students students{
		{1, {"Kim", 80}},
		{2, {"Lee", 20}},
		{3, {"Pak", 50}},
		{4, {"Choi", 30}}
	};
	// map�� pair�� �����
	// key �� value
	// value�� Ŭ���� ������� �־�����ϴµ�
	// �������ʱ�ȭ�� �ϸ� ���ϴ�
	int command{};

	while (command != 6)
	{
		std::cout << "1. �л� �߰�" << std::endl;
		std::cout << "2. �л� ����" << std::endl;
		std::cout << "3. ��ü �л� ���" << std::endl;
		std::cout << "4. Ŭ���� ��� �� ����" << std::endl;
		std::cout << "5. Ŭ���� ��� �̻� �л� ���" << std::endl;
		std::cout << "6. ����" << std::endl;

		std::cout << "> ";
		std::cin >> command;
		
		switch (command)
		{
		case 1:
			AddStudent(students);
			break;
		case 2:
			RemoveStudent(students);
			break;
		case 3:
			PrintStudents(students);
			break;
		case 4:
			PrintScoreInfo(students);
			break;
		case 5:
			PrintOverAverage(students);
			break;
		case 6:

			break;
		default:
			break;
		}
	}
}