/*

#���� �÷���

	- goodbit
	- eofbit
	- failbit
	- badbit


#����ó��

try
{
}
catch()
{
}


==========================================================================

#include <iostream>
#include <fstream>

bool LoadFile(const std::string& filename)
{

	// ���� ��Ʈ�� ��ü ����
	std::ifstream ifs;

	//exception  ����ó��
	ifs.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		// ���� �б�
		ifs.open(filename);

		// �����۾�
		char ch;
		while (ifs >> ch) // false�� �߻� �� ������ �߻�
		{ 				  // �׷��� ����ó������ ������ �߻��ߴٰ� �˷��ش�
			std::cout << ch;
		}
		// ���� �ݱ�
		ifs.close();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "���� �۾� ���� ������ �߻��߽��ϴ�." << std::endl;
		std::cout << e.code() << std::endl;
		std::cout << e.what() << std::endl; // e.what() ������ ����

		ifs.close();
		return false;
	}

	return true;
}


====================================================================================
while (ifs >> ch) // false�� �߻� �� ������ �߻�
				  // �׷��� ����ó������ ������ �߻��ߴٰ� �˷��ش�





===============================================================================

#include <iostream>
#include <fstream>

bool LoadFile(const std::string& filename)
{

	// ���� ��Ʈ�� ��ü ����
	std::ifstream ifs;

	//exception  ����ó��
	ifs.exceptions(std::ifstream::badbit);


	// ���� �б�
	ifs.open(filename);

	// �����۾�
	char ch;
	while (ifs.get(ch))
	{
		std::cout << ch;
	}
	// ���� �ݱ�
	ifs.close();


	return true;
}


int main()
{
	try
	{
		LoadFile("Data/SimpleData.txt");
	}
	catch (std::exception e)
	{
		std::cout << "���� �۾� ���� ������ �߻��߽��ϴ�." << std::endl;
		std::cout << e.what() << std::endl; // e.what() ������ ����

		return false;
	}
}

// std::exception �� ��� ����ó���� ��������(failure ���� ���)
// std::exception �� ����ϸ� code()�� �����������


===============================================================================





���� ����� ����>>
===============================================================================



#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>


class Monster
{
private:
	std::string mName;
	int mLevel;
	int mHP;
	int mMP;

public:

	Monster() :mName{ "" }, mLevel{}, mHP{}, mMP{} {};
	Monster(std::string name, int level, int hp, int mp) :
		mName{ name }, mLevel{ level }, mHP{ hp }, mMP{mp}
	{

	}

	void SetName(std::string name) { mName = name; }
	void SetLevel(int level) { mLevel = level; }
	void SetHP(int hp) { mHP = hp; }
	void SetMP(int mp) { mMP = mp; }

	friend std::ostream& operator << (std::ostream& os, Monster& monster);
	friend std::istream& operator >> (std::istream& ifs, Monster& monster);

};

std::ostream& operator << (std::ostream& os, Monster& monster)
{
	os << monster.mName << ", "
		<< monster.mLevel << ", "
		<< monster.mHP << ", "
		<< monster.mMP << std::endl;
	return os;
}

std::istream& operator >> (std::istream& ifs, Monster& m)
{
	std::string buffer;

	try {
	std::getline(ifs, buffer, ',');
	m.mName = buffer;
	//m.SetName(buffer); // friend �̱� ������ ��ó�� �ٷ� ����� ���� ����

	std::getline(ifs, buffer, ',');
	m.SetLevel(std::stoi(buffer));

	std::getline(ifs, buffer, ',');
	m.SetHP(std::stoi(buffer));

	std::getline(ifs, buffer);
	m.SetMP(std::stoi(buffer));


	}
	catch (std::exception e)
	{
		std::cout << "error : " << e.what() << std::endl;
	}
	return ifs;
}

bool CreateFromFile(const std::string& filename, std::vector<Monster>& v)
{
	//1 . ��Ʈ�� ��ü ����
	std::ifstream ifs;

	ifs.exceptions(std::ifstream::badbit);

	try {

	//2 . ���� ����
		ifs.open(filename);

	//3 . ���� �۾�

		std::string buffer;

		// ��� �а� ������
		std::getline(ifs, buffer);

		while (!ifs.eof())
		{
			Monster m;

			ifs >> m;
			//������ �����ε����� �ڵ��� ���ϼ��ִ�
			// �ؿ� ǥ���� ���� ���ٷ� �ٿ���
			//std::getline(ifs, buffer, ',');
			//m.SetName(buffer);
			//
			//std::getline(ifs, buffer, ',');
			//m.SetLevel(std::stoi(buffer));
			//
			//std::getline(ifs, buffer, ',');
			//m.SetHP(std::stoi(buffer));
			//
			//std::getline(ifs, buffer);  // �����̴ϱ� ',' �����ϴ� ������ �ʿ����
			//m.SetMP(std::stoi(buffer));

			v.push_back(m);
		}

	//4 . ���� �ݱ�
		ifs.close();
		return true;
	}

	catch (std::ifstream::failure e)
	{
		std::cout << "������ �߸� �Ǿ����ϴ�." << e.what() << std::endl;

		ifs.close();
		return false;
	}
	return true;
}

bool SaveToFile(const std::string& filename, std::vector<Monster>& v)
{
	//��Ʈ�� ��ü ����
	std::ofstream ofs;
	ofs.exceptions(std::ostream::badbit);

	try {

	//����
		ofs.open(filename);

	//�۾�
		// ���
		ofs << "=== Monster Data ===" << std::endl;

		for (auto& e : v)
		{
			ofs << e;
		}

	//�ݱ�
		ofs.close();

	}

	catch (std::ostream::failure e)
	{
		std::cout << "error : " << e.what() << std::endl;
		ofs.close();
		return false;
	}
	return true;
}
int main()
{
	std::vector<Monster> monsters;
	CreateFromFile("Data/SimpleData.txt",monsters);

	for (auto& e : monsters)
	{
		std::cout << e;
	}

	SaveToFile("Data/NewData.txt", monsters);  // ���� ����
}

------------------------------------------------------------------------------------------

// getline(); // #include <sstream>�� �����ؾ� ��밡��
// ���� �б� ���
//
//std::getline(ifs, buffer); // �����б�
// �ٹٲ��� �ɶ����� �о� ���±��

//std::getline(ifs, buffer, ',');
// ������ �дµ� ','������� �����ؼ� �д´�
// �����ϴ� �ĺ� ','



//m.SetLevel(std::stoi(buffer));
// stoi  ��Ʈ���� ��Ʈ������ ��ȯ �ϴ� ����̴�



------------------------------------------------------------------------------------------


���̳ʸ� ���
	1. ���ڿ� 
		���ڿ��� ���� & ���ڿ�

	2. ������ ����

*/

