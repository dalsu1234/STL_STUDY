// 바이너리 타입으로 입출력

#include <iostream>
#include <vector>
#include "Monster.h"

std::ifstream& operator >> (std::ifstream& ifs, Monster& monster)
{
	return monster.ReadBinary(ifs);
	// Monster 클래스 안에 함수를 이렇게 불러내서
	// friend 기능으로 구현하지않고 이런식으로 표현이 가능하다
}

std::ofstream& operator << (std::ofstream& ofs, Monster& monster)
{
	return monster.WriteBinary(ofs);
}

// 스트림 연산자는 헤더파일에서 선언하면 중복 오류문제 발생



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
		// 구조체는 POD이기때문에 데이타 그대로 들고와도 문제가 없다
		// Header라는 한덩어리의 구조를 char의 1바이트씩 읽어오게 되는 구조로 바꾸는 과정

		for (auto& e:monsters)
		{
			ofs << e;
		}
	
	}
	catch (std::ofstream::failure e)
	{
		std::cout << "저장 도중 예외 발생 : " << e.what() << std::endl;
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
		std::cout << "읽기 도중 예외가 발생 : " << e.what() << std::endl;
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

	//텍스트 모드와 바이너리 모드의 데이터 입출력의 차이점은?
	// 실제 메모리데이터를 그대로 저장하는 방식이 바이너리 모드




	SaveToFile("Data/SimpleData.dat", monsters);

	monsters.clear();

	LoadToFile("Data/SimpleData.dat", monsters);

}