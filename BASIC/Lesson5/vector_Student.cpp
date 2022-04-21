#include <iostream>
#include <vector>

class Student
{

public:
	int mNumber;
	std::string mName;
	int mScore;

	void Print() const
	{
		std::cout << "(" << mNumber << ")" <<
			mName << " : " << mScore << std::endl;

	}
};

using Students = std::vector<Student>;

void AddStudent(Students& v)
{
	int num{};
	std::string name;
	int score{};

	std::cout << "��ȣ �̸� ���� : ";

	
	Student newStudnet{num,name,score};
	
	if (std::cin >> newStudnet.mNumber >> newStudnet.mName >> newStudnet.mScore)
	{

		// ����
		auto itr = std::find_if(v.begin(), v.end(), [&](auto& e) {
			return e.mNumber == newStudnet.mNumber;
			});
		if (itr != v.end())
		{
			std::cout << "�ߺ��� ��ȣ�Դϴ�" << std::endl;
			return;
		}
		//Ư���� �˻��� ������ �´� ���Ҹ� ã���ִ±��

//########################################################################################

	/*	for (const auto& e : v)
		{
			if (e.mNumber == newStudnet.mNumber)
			{
				std::cout << "�ߺ��� ��ȣ�Դϴ�" << std::endl;
				return;
			}
		}
		�� ǥ���� ���� ������ ǥ��
		*/
		v.push_back(newStudnet);
	}
	else
	{
		std::cout << "�߸��� �Է��Դϴ�." << std::endl;
	}
}

void RemoveStudent(Students& v)
{
	std::cout << "������ ��ȣ : ";
	int number;
	if (std::cin >> number)
	{

		//����
		auto itr = std::remove_if(v.begin(), v.end(), [&](auto& e) {
			return e.mNumver == number;
			});

		

		// remove ����� ���ٸ� ���� �߿��Ѱ���
		// erase ����� �ݵ�� ���� ����Ѵ�
		// �����̳��� remove�� ���Ҹ� ����°��� �ƴϴ�
		// �׳� ���� �ڷ� ����������
		// ������ ���ʿ��� �ݺ��� �����ʱ�����
		// �ϳ��� �Ź� ��ȸ�� �ؾ��ϴ� ���ʿ����۾��� �ʿ��ؼ�
		// �ٷιٷ� ã�¿��Ҹ� �ڷα׳� ����������
		// �׷��� �ڷ� ���� ���Ҹ� ������� erase����� �ݵ�� ������Ѵ�
		if (itr == v.end())
		{
			std::cout << "�ش��ȣ�� �л��� ���������ʽ��ϴ�." << std::endl;
		}
		// if (itr == nullptr) ���� ǥ���ϸ� ������ ����
		// ���ͷ����ʹ� nullptr�� ��������ʴ´�
		// ������ end�� ��ġ�� ������������ ��ġ�� �ƴ�
		// ������������ �ٷεڿ� ��ġ���ִ� �迭�� \0 �� ���� ��ġ
		// ã�� ���Ұ� ���ٸ� v.end�� ��ġ���ִ�
		// if (itr == v.end())�׷��� �̷� ǥ���� ����

		v.erase(itr); // �ſ��߿�!!

//########################################################################################
		/*for (auto itr = v.begin(); itr != v.end(); itr++)
		{
			if (itr->mNumber == number)
			{
				v.erase(itr);
				return;
			}
		}
		�� ǥ���� ���� ������ ǥ��
		std::cout << "�ش��ȣ�� �л��� ���������ʽ��ϴ�." << std::endl;
		*/
	}
	else
	{
		std::cout << "�߸��� �Է�" << std::endl;
	}
}

void PrintStudents(const Students& v)
{
	for (const auto& e : v)
	{
		e.Print();
	}
}

void PrintScoreInfo(const Students& v)
{
	int total{};
	for (const auto& e : v)
	{
		total += e.mScore;
	}
	std::cout << " Total : " 
		<< total << ". Average : " 
		<< static_cast<float>(total) / v.size() << std::endl;
}

void PrintOverAverage(const Students& v)
{
	int average{};
	for (const auto& e : v)
	{
		average += e.mScore;
	}
	average /= v.size();

	for (const auto& e : v)
	{
		if (e.mScore >= average)
		{
			e.Print();
		}
	}
}
int main()
{
	std::vector<Student> students{
		{1, "kim", 80},
		{2, "Lee" , 20},
		{3, "pak", 50},
		{4, "choi", 30}
	};

	int command{};
	while (command != 6)
	{

		std::cout << "1 �л��߰�" << std::endl;
		std::cout << "2 �л� ����" << std::endl;
		std::cout << "3 ��ü ���" << std::endl;
		std::cout << "4 ��չ� ����" << std::endl;
		std::cout << "5 ����̻� �л� ���" << std::endl;
		std::cout << "6 ����" << std::endl;

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
			std::cout << " ��Ե� ��ɾ� " << std::endl;
			break;
		}
	}
}