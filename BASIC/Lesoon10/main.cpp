// ���̳ʸ� Ÿ������ �����

#include <iostream>
#include <vector>
#include "Monster.h"

std::ifstream& operator >> (std::ifstream& ifs, Monster& monster)
{
	return monster.ReadBinary(ifs);
	// Monster Ŭ���� �ȿ� �Լ��� �̷��� �ҷ�����
	// friend ������� ���������ʰ� �̷������� ǥ���� �����ϴ�
}

std::ofstream& operator << (std::ofstream& ofs, Monster& monster)
{
	return monster.WriteBinary(ofs);
}

// ��Ʈ�� �����ڴ� ������Ͽ��� �����ϸ� �ߺ� �������� �߻�



struct Header
{
	int version{1};
	int monsterCount{};
};

bool SaveToFile(const std::string& filename, std::vector<Monster>& monsters)
{
	std::ofstream ofs;
	ofs.exceptions(std::ofstream::badbit | std::ofstream::failbit);
	try
	{
		ofs.open(filename, std::ofstream::binary);
		
		Header h{ 1, monsters.size() };
		ofs.write(reinterpret_cast<char*>(&h), sizeof(Header));
		// ����ü�� POD�̱⶧���� ����Ÿ �״�� ���͵� ������ ����
		// Header��� �ѵ���� ������ char�� 1����Ʈ�� �о���� �Ǵ� ������ �ٲٴ� ����

		for (auto& e:monsters)
		{
			ofs << e;
		}
	
	}
	catch (std::ofstream::failure e)
	{
		std::cout << "���� ���� ���� �߻� : " << e.what() << std::endl;
		ofs.close();
		return false;
	}
	return true;
}

bool LoadToFile(const std::string& filename, std::vector<Monster>& monsters)
{
	std::ifstream ifs;
	ifs.exceptions(std::ifstream::badbit | std::ifstream::failbit);
	try
	{
		ifs.open(filename, std::ifstream::binary);
	
		Header h;
		ifs.read(reinterpret_cast<char*>(&h), sizeof(Header));
		for (int i =0; i < h.monsterCount; ++i)
		{
			Monster m;
			ifs >> m;
			monsters.push_back(m);
		}
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "�б� ���� ���ܰ� �߻� : " << e.what() << std::endl;
		ifs.close();
		return false;
	}
	return true;

	return true;
}
int main()
{
	std::vector<Monster> monsters{
		{"Jelly",1,1,1},
		{"Wolf",5,5,5,},
		{"Demon",10,10,10,}
	};

	//�ؽ�Ʈ ���� ���̳ʸ� ����� ������ ������� ��������?
	// ���� �޸𸮵����͸� �״�� �����ϴ� ����� ���̳ʸ� ���




	SaveToFile("Data/SimpleData.dat", monsters);

	monsters.clear();

	LoadToFile("Data/SimpleData.dat", monsters);

}