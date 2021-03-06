/*

C++ Standard Library : STL


STL은

자료구조와 알고리즘을 다루고있다



크게 STL은 3가지

	Constainer
		- 자료구조를 위한 템플릿 클래스
		- 컬렉션이라고 부르기도 함
		- 각 컨테이너는 장단점을 가지고있기때문에 
		  자료구조의 특성을 알고있어야한다


	Iterator
		- 컨테이너에 들어있는 원소를 순회하기위해
		
		- 자료구조의 요소를 순회하기 위한 일반화된 방법 (템플릿)
		
		- 일반화가 핵심
		
		- 포인터개념과 동일하다 역참조를 하면 원소를 가지고 올수있다
		  잘생각해보면 당연한거다 컨테이너의 요소를 접근하기위해
		  복사보다는 포인터로 가지고 오는것이 좀더 효율적이니깐
		
		- 포인터 연산 가능 : ++ -- == !=
		
		- begin(), end()
	
	
	Algorithm
		- 정렬 , 검색 , 복사 , 탐색 , 합계 , 최소값..... 등등

	Etc
		- 메모리 관리(동적할당), 멀티스레드, 예외처리... 등등


###########################################################################

string 라이브러리

#include<iostream>

int main()
{
	char ch1 = 'a'; // 아스키 리터럴
	wchar_t ch2 = L'가'; // 유니코드 리터럴 혹은 와이드 캐릭터 리터럴
						 //'' 앞에 대문자L이 있어야한다

	char str1[] = "hello";    // 아스키 스트링 리터럴
	wchar_t str2[] = L"가나다라"; // 와이드 스트링 리터럴

	std::string s1{ "abcd" };
	std::string s2{ "1234" };

	s1 = s2;		// 가능 
	s2 = std::string("hello") + std::string("world"); // 가능  r-value로 서로 연산
	s1 += s2;		// 가능
	s2[0] = 'H';	// 가능

	
	s1.c_str(); // c스타일의 문자열(char) 
	즉 스트링에 들어있는걸 캐릭터 포인터 함수로 받아올수있게
	char* 이거로 변환
	////////////////////////////////////

	컨테이너 개념

	st.size();
	s1.insert();
	s1.append();
	s1.earase();
	s1.find();
	// 사실상 컨테이너도 이름의 형태가 비슷하다
	// 왜냐하면 string도 컨테이너의 한종류니깐
	////////////////////////////////////////////

	iterator 개념

	st.begin();
	s1.end();
}

std::string이 컨테이너의 한종류


예제>>
########################################################################

void Print(const std::string& str)
{
	std::cout << str.size() << " : " << std::endl;
}

int main()
{
	std::string empty; //비어잇는 스르링컨테이너
	Print(empty);

	std::string sized(10, '\0'); // '\0' 10개의 null문자로 만들어주는
	Print(sized);

	std::string s1("test");
	std::cout << s1[0] << s1[1] << s1[2] << std::endl;

	std::string s2(s1); //복사생성
	Print(s2);

	std::string s3 = s1 + s2;
	Print(s3);

	empty = s3;
	Print(empty);


}
########################################################################

#include <string>
int main()
{
	int number = 123;
	std::string s1;

	s1 = std::to_string(number); // 123을 "123"으로변환해주는 기능

	number = std::stoi(s1); // 문자열을 인트형으로 변환  "123" -> 123으로
	자주 사용한다
}


string은 컨테이너중에 하나

############################################################################################
또다른 컨테이너

#벡터

std::vector

	- 원소의 타입을 지정해서 특수화 하는 템플릿 // 특스화 각각의 객체마다 구별할수있는 특성
	- 원소의 갯수와 해당원소들의 시퀀스(포인터)를 가지고 있다
		- 배열첨자 사용가능
	- #include <vector>

	대충 그림으로 표현하자면
	
	
	vector
	#############################
		size
	-----------------------------
	집합[배열]을 카르키고있는 포인터
	#############################
	
	// vector : 연속된 n개의 값을 벡터라 한다  즉 < 집합 >

#####################################################################




#include <vector>
int main()
{
	std::vector<int> v{ 2,3,1,6,5 };
	// 동적배열이라고 보면된다
	std::vector<std::string> v2{ " asd", "fg", "qwe" };
	// 원하는 타입으로 특수화 해서 사용하면된다

	std::vector v3(5); // 집합의 크기를 지정하는 생성자

	std::vector v3(5, 1); // 집합의 크기가 5이고 각각의 요소를 1로초기화
	// 생성자의 문법과 유니폼 초기화는 각각 의미하는 바가 다르다


	// [	) 이상 미만
	// [	] 이상 이하
	// (	) 초과 미만




	//간략한 표현식!
	// 범위 기반 반복문 [0 : size)
	for (int e : v)// 여기서 e는 v1의 요소를 복사 대입하는 과정을 거친다
	{
		std::cout << e << std::endl;
	}
	int myArray[]{ 1,2,3,4,5 };
	for (int e : myArray)
	{
		std::cout << e << std::endl;
	}
	
	
	
	v.push_back(4); // 4를 밀어넣는 기능 어디에? 맨뒤에

}


##############################################################

#범위 기반 반복문

for (원소 : 집합)
{
}


벡터는 size와 배열을 가르키는 포인터를 멤버로 가지고 있다
즉 크기가 가변이다


##################################################################
연습문제
	// 숫자들을 입력받고 총합계와 평균을 구해봅시다.
	// 예 > 1 2 3 7 4 9 10 
	// 숫자를 공백으로 구분하여 입력하세요
	// 입력 종료는 숫자가 아닌 문자를 입력하면 됩니다.

##################################################################
	
#include <vector>
int main()
{
	int value{};
	int sum{};
	std::vector<int> v{};


	//while문으로 구현
	while (std::cin >> value)
	{
		v.push_back(value);
	}

	

	// for으로 구현
	for (int value; std::cin >> value;)
	{
		v.push_back(value);
	}
	
	for (int e : v)
	{
		sum += e;
	}

	std::cout << sum << std::endl;
	std::cout << static_cast<float>(sum) / v.size() << std::endl;
}


##################################################################


# Iterator
컨테이너의 원소를 순회

원소를 순회하려면 컨테이너의 첫번째 원소가 무슨타입인지 알아야한다

예제>>
##################################################################

#include <vector>
int main()
{
	std::vector<int> v{ 1,2,3 };

	std::vector<int>::iterator itr;
	//int로 특수화된 벡터 안에 타입이 들어있다
	//컨테이너 안에 이터레이터가 정의 되어있다
	//그래서 범위 연산자를 사용
	// 특수화된 벡터 안에 이터레이터라는 타입이 들어있다 라고 생각하면됨

	itr = v.begin();
	// 컨테이너 첫번째 원소에 접근
	// 포인터라
	// 이터레이터란 원소를 순회하기 위한 포인터!!

	//while 버전
	while (itr != v.end())
	{
		std::cout << *itr << std::endl; // 이터레이터는 포인터라 역참조를 해야한다
		itr++; // 포인터라 배열을 이런식으로 접근 가능하다
	}

	//for문 버전
	for (std::vector<int>::iterator itr = v.begin(), itr != v.end(); itr++)
	{
		std::cout << *itr << std::endl;
	}

}


*/

