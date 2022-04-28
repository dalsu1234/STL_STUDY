#include "Monster.h"
#include <iostream>
#include <fstream>
#include <string>

std::ifstream& Monster::ReadBinary(std::ifstream& ifs)
{
	int len;

	// 읽어올 문자열의 길이
	ifs.read(reinterpret_cast<char*>( & len), sizeof(int));
	
	mName.resize(len); // 읽어올 문자열의 크기
	//읽어올 문자열
	ifs.read(&mName[0], len);

	//&mName[0]은 mName의 문자열의 첫글자의 주소값

	// 각각 정수형 데이터
	ifs.read(reinterpret_cast<char*>(&mLevel), sizeof(int));
	ifs.read(reinterpret_cast<char*>(&mHP), sizeof(int));
	ifs.read(reinterpret_cast<char*>(&mMP), sizeof(int));
	


	return ifs;
}

std::ofstream& Monster::WriteBinary(std::ofstream& ofs)
{
	// 길이 문자열 정수 정수 정수
	int len{static_cast<int>(mName.size())};
	

	//저장될 문자열의 길이 (읽어오는 문자열의 길이, 타입)
	ofs.write(reinterpret_cast<char*>(&len), sizeof(int));
	
	// 문자열 저장
	ofs.write(mName.c_str(), len);

	// 가각 레벨, HP , MP 의 저장
	// (복사할값의 위치 주소, 저장될 공간의 사이즈)
	ofs.write(reinterpret_cast<char*>(&mLevel), sizeof(int));
	ofs.write(reinterpret_cast<char*>(&mHP), sizeof(int));
	ofs.write(reinterpret_cast<char*>(&mMP), sizeof(int));

	return ofs;
	// &len 은 len의 주소가 int형 주소인데
	// wirte()의 매개변수 첫번째는 char형으로 받는 형식
	// 그래서 형변환을 해줘야한다
	// 그래서 &len 을 아래처럼 형변환 해줘야한다
	// reinterpret_cast<char*>(&len)
	// reinterpret_cast는 전혀 다른 타입간의 형변환을 해줌
	// reinterpret_cast는 주로 포인터와 일반형 또는 
	// 포인터와 포인터끼리의 형변환에 사용된다
	// static_cast는 함수를 호출하고 변환된 결과를 임시변수로 
	// 반환 한다 즉 static_cast<>() 함수라고 생각하면됨
	// reinterpret_cast는 함수를 호출 하지 않는다
	// 컴파일이 알아서 해줌

	//즉 static_cast는 일반자료형끼리의 형변환
	//reinterpret_cast는 그외에 형변환(예> 포인터와 포인터)

	// reinterpret_cast<char*>(&len)은 int형의 포인터를 char형포인터로 변환
	// static_cast<int>(mName.size()) 은 size타입을 int로 변환


	//write(매개변수1,매개변수2) 함수는
	// 매개변수2는 저장할때  메모리의 몇칸 즉 어느 길이만큼 저장하겠냐라는뜻
	// int형의 크기니깐 4바이트씩 나눠서 저장
	// 매개변수1은 저장할 문자열 스트링 (char 타입) 왜 char타입이냐 char타입은 1바이트니깐
	// 메모리에서 읽어올때 1바이트씩 읽어 와야해서
	// 매개변수1은 저장할 변수의 메모리 주소를 필요로 한다

	// mName.c_str()에서 c_str기능은 mName이 std::string 타입인데
	// char 배열의 형태로 변환 즉 char포인터
}


/*


메모리에 저장되는 구조가

인트형 4바이트마다 저장하는방식으로
스트링에 길이를 먼저 인트형으로 저장하고
나머지 스탯들은 인트형으로 저장


*/