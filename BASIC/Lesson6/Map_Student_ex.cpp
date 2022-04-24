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
	std::cout << " 번호 이름 점수 : ";
	Student newStudent;
	int number;
	
	if (std::cin >> number >> newStudent.mName >> newStudent.mScore)
	{
		// v.insert({number,newStudent}); 
		// pair는 유니폼초기화 간단히 초기화 할수있다
		// .insert의 반환값이 iterator와 bool값이 돌아온다
		// 반환값이 두개 pair는 반환값이 두개다
		// std::pair<std::map<int, Student>::iterator,bool>
		// 여기서 auto는 
		// auto result = std::pair<std::map<int, Student>::iterator,bool>
		
		auto result = v.insert({number, newStudent});
		
		if (result.second == false)// map의 두번째값이 bool값이니깐 이런식
		{
			std::cout << "중복된 학생 번호입니다." << std::endl;
		}
	}
	else
	{
		std::cout << " 잘못된 입력입니다. " << std::endl;
	}
}

void RemoveStudent(Students& v)
{
	std::cout << "지울 학생 번호 : ";
	int number;
	if (std::cin >> number)
	{
		//eraser-remove idiom
		//연관 컨테이너에서는 지울때 메모리 구조가 변경되지않는다
		// 그래서 eraser-remove idiom이 필요없다 그냥 지우면된다
		//v.erase(number) 는 반환값이 0과 1이다
		// 삭제가 된다면 1 안된다면0 
		// 그래서 반환값이 0이면 
		if (v.erase(number))
		{
			std::cout << "없는 번호입니다." << std::endl;
		}
	
	}
	else
	{
		std::cout << "잘못된 입력입니다." << std::endl;
	}
}

void PrintStudents(const Students& v)
{
	for (const auto& e : v)
	{
		std::cout << "(" << e.first << ") ";
		e.second.Print();
	}
	// 여기서 e의 타입은?
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
	// map은 pair를 써야함
	// key 와 value
	// value를 클래스 멤버들을 넣어줘야하는데
	// 유니폼초기화로 하면 편하다
	int command{};

	while (command != 6)
	{
		std::cout << "1. 학생 추가" << std::endl;
		std::cout << "2. 학생 제거" << std::endl;
		std::cout << "3. 전체 학생 출력" << std::endl;
		std::cout << "4. 클래스 평균 및 총점" << std::endl;
		std::cout << "5. 클래스 평균 이상 학생 목록" << std::endl;
		std::cout << "6. 종료" << std::endl;

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