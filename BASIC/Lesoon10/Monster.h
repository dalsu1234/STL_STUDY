#pragma once
#include <fstream>
#include <string>

class Monster
{
private:
	std::string mName;
	int mLevel;
	int mHP;
	int mMP;

public:

	//Monster() : mName{}, mLevel{}, mHP{}, mMP{}{};
	// 기본생성자를 아래처럼 표현할수 있다
	
	Monster() : Monster("",0,0,0) {};
	// 대리생성자

	Monster(std::string name, int level, int hp, int mp) :
		mName{ name }, mLevel{ level }, mHP{ hp }, mMP{ mp }{};

	std::ifstream& ReadBinary(std::ifstream& ifs);
	std::ofstream& WriteBinary(std::ofstream& ofs);
};

