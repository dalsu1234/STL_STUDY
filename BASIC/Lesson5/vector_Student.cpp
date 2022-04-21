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

	std::cout << "번호 이름 점수 : ";

	
	Student newStudnet{num,name,score};
	
	if (std::cin >> newStudnet.mNumber >> newStudnet.mName >> newStudnet.mScore)
	{

		// 개선
		auto itr = std::find_if(v.begin(), v.end(), [&](auto& e) {
			return e.mNumber == newStudnet.mNumber;
			});
		if (itr != v.end())
		{
			std::cout << "중복된 번호입니다" << std::endl;
			return;
		}
		//특정한 검색의 조건을 맞는 원소를 찾아주는기능

//########################################################################################

	/*	for (const auto& e : v)
		{
			if (e.mNumber == newStudnet.mNumber)
			{
				std::cout << "중복된 번호입니다" << std::endl;
				return;
			}
		}
		위 표현이 좀더 간결한 표현
		*/
		v.push_back(newStudnet);
	}
	else
	{
		std::cout << "잘못된 입력입니다." << std::endl;
	}
}

void RemoveStudent(Students& v)
{
	std::cout << "삭제된 번호 : ";
	int number;
	if (std::cin >> number)
	{

		//개선
		auto itr = std::remove_if(v.begin(), v.end(), [&](auto& e) {
			return e.mNumver == number;
			});

		

		// remove 기능을 쓴다면 가장 중요한것은
		// erase 기능을 반드시 같이 써야한다
		// 컨테이너의 remove는 원소를 지우는것이 아니다
		// 그냥 가장 뒤로 보내버린다
		// 이유는 불필요한 반복을 하지않기위해
		// 하나씩 매번 순회를 해야하는 불필요한작업이 필요해서
		// 바로바로 찾는원소를 뒤로그냥 보내버린다
		// 그래서 뒤로 보낸 원소를 지우려면 erase기능을 반드시 써줘야한다
		if (itr == v.end())
		{
			std::cout << "해당번호의 학생이 존재하지않습니다." << std::endl;
		}
		// if (itr == nullptr) 으로 표현하면 컴파일 에러
		// 이터레이터는 nullptr을 허용하지않는다
		// 이유는 end의 위치는 마지막원소의 위치가 아닌
		// 마지막원소의 바로뒤에 위치해있다 배열의 \0 과 같은 위치
		// 찾는 원소가 없다면 v.end에 위치에있다
		// if (itr == v.end())그래서 이런 표현을 쓴다

		v.erase(itr); // 매우중요!!

//########################################################################################
		/*for (auto itr = v.begin(); itr != v.end(); itr++)
		{
			if (itr->mNumber == number)
			{
				v.erase(itr);
				return;
			}
		}
		위 표현이 좀더 개선된 표현
		std::cout << "해당번호의 학생이 존재하지않습니다." << std::endl;
		*/
	}
	else
	{
		std::cout << "잘못된 입력" << std::endl;
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

		std::cout << "1 학생추가" << std::endl;
		std::cout << "2 학생 제거" << std::endl;
		std::cout << "3 전체 출력" << std::endl;
		std::cout << "4 평균및 총점" << std::endl;
		std::cout << "5 평균이상 학생 목록" << std::endl;
		std::cout << "6 종료" << std::endl;

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
			std::cout << " 잠롯된 명령어 " << std::endl;
			break;
		}
	}
}