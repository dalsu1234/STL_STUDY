/*

#상태 플래그

	- goodbit
	- eofbit
	- failbit
	- badbit


#예외처리

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

	// 파일 스트림 객체 생성
	std::ifstream ifs;

	//exception  예외처리
	ifs.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		// 파일 읽기
		ifs.open(filename);

		// 파일작업
		char ch;
		while (ifs >> ch) // false가 발생 즉 에러가 발생
		{ 				  // 그러면 예외처리에서 에러가 발생했다고 알려준다
			std::cout << ch;
		}
		// 파일 닫기
		ifs.close();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "파일 작업 도중 에러가 발생했습니다." << std::endl;
		std::cout << e.code() << std::endl;
		std::cout << e.what() << std::endl; // e.what() 에러의 설명

		ifs.close();
		return false;
	}

	return true;
}


====================================================================================
while (ifs >> ch) // false가 발생 즉 에러가 발생
				  // 그러면 예외처리에서 에러가 발생했다고 알려준다





===============================================================================

#include <iostream>
#include <fstream>

bool LoadFile(const std::string& filename)
{

	// 파일 스트림 객체 생성
	std::ifstream ifs;

	//exception  예외처리
	ifs.exceptions(std::ifstream::badbit);


	// 파일 읽기
	ifs.open(filename);

	// 파일작업
	char ch;
	while (ifs.get(ch))
	{
		std::cout << ch;
	}
	// 파일 닫기
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
		std::cout << "파일 작업 도중 에러가 발생했습니다." << std::endl;
		std::cout << e.what() << std::endl; // e.what() 에러의 설명

		return false;
	}
}

// std::exception 은 모든 예외처리의 상위개념(failure 같은 기능)
// std::exception 을 사용하면 code()를 사용하지못함


===============================================================================





파일 입출력 예제>>
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
	//m.SetName(buffer); // friend 이기 때문에 위처럼 바로 멤버에 접근 가능

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
	//1 . 스트림 객체 생성
	std::ifstream ifs;

	ifs.exceptions(std::ifstream::badbit);

	try {

	//2 . 파일 열기
		ifs.open(filename);

	//3 . 파일 작업

		std::string buffer;

		// 헤더 읽고 버리기
		std::getline(ifs, buffer);

		while (!ifs.eof())
		{
			Monster m;

			ifs >> m;
			//연산자 오버로딩으로 코딩을 줄일수있다
			// 밑에 표현을 위에 한줄로 줄였다
			//std::getline(ifs, buffer, ',');
			//m.SetName(buffer);
			//
			//std::getline(ifs, buffer, ',');
			//m.SetLevel(std::stoi(buffer));
			//
			//std::getline(ifs, buffer, ',');
			//m.SetHP(std::stoi(buffer));
			//
			//std::getline(ifs, buffer);  // 끝줄이니깐 ',' 구분하는 문장이 필요없다
			//m.SetMP(std::stoi(buffer));

			v.push_back(m);
		}

	//4 . 파일 닫기
		ifs.close();
		return true;
	}

	catch (std::ifstream::failure e)
	{
		std::cout << "파일이 잘못 되었습니다." << e.what() << std::endl;

		ifs.close();
		return false;
	}
	return true;
}

bool SaveToFile(const std::string& filename, std::vector<Monster>& v)
{
	//스트림 객체 생성
	std::ofstream ofs;
	ofs.exceptions(std::ostream::badbit);

	try {

	//열기
		ofs.open(filename);

	//작업
		// 헤더
		ofs << "=== Monster Data ===" << std::endl;

		for (auto& e : v)
		{
			ofs << e;
		}

	//닫기
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

	SaveToFile("Data/NewData.txt", monsters);  // 파일 저장
}

------------------------------------------------------------------------------------------

// getline(); // #include <sstream>을 선언해야 사용가능
// 한줄 읽기 기능
//
//std::getline(ifs, buffer); // 한줄읽기
// 줄바꿈이 될때까지 읽어 오는기능

//std::getline(ifs, buffer, ',');
// 한줄을 읽는데 ','여기까지 구분해서 읽는다
// 구분하는 식별 ','



//m.SetLevel(std::stoi(buffer));
// stoi  스트링을 인트형으로 변환 하는 기능이다



------------------------------------------------------------------------------------------


바이너리 모드
	1. 문자열 
		문자열의 길이 & 문자열

	2. 데이터 갯수

*/

