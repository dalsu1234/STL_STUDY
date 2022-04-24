/*


--------------Modern C++----------------

- nullptr

- auto

- 유니폼 초기화

- range based loop

- Lambda Expression
	익명 함수

- Delegaing Constructor

- Member 초기화


-----------------------------------------------------------------------------------


람다식

요소

[] () ->
{}

[] : 캡처절 / 외부의 변수를 캡처해서 람다식안에 쓸수있게해줌
	[] : 외부 변수 사용불가
	[&] : 외부 변수를 참조형으로 사용
	[=] : 외부 변수를 값형으로 사용

() : 매개변수 목록

-> : 반환 타입
	추론을 통해서 생략이 가능

{} : 람다식 정의

-----------------------------------------------------------------------------------


#람다식 예제

// 둘다 캡처는 없음
// 매개변수 int  두개를 받고 반환타입이 없는 람다식

[](int,int){};


using Lambda = void (*) (int , int) // 밑 예제의 람다의 타입

int main()
{
	Lambda lambda = [](int x, int y) -> void {
	std::cout << x << " " << y;
	};
	// 반환타입 생략가능 -> void
	lamda(1,2);
}

하지만 auto로 간단히 가능

int main()
{
	auto lambda = [](int x, int y) -> void {
	std::cout << x << " " << y;
	};
}

// 매개변수 int , float을 받고 bool을 반환하는 람다식

[](int, float){return true}


// 캡처절의 범위는 스코프내에서만



-----------------------------------------------------------------------------------


- R-value Reference (&&) 
우측값 참조

예제

template<typename T>
void Swap(T& a, T& b)
{
	T tmp = a;
	a = b;
	b = tmp; // 복사
}

int main
{
	int x{10}, y{20};
	Swap<int>(x,y);

	std::cout << x << " : " << y << std::endl;
}

참조를 한다해도 복사가 이루어진다

우측값 참조는 오브젝트의 값을 복사해서 옮기는것이 아니라

이름없는 R Value에 변수명만 붙이는것
복사없이 이름만 변경
>>
void Swap(T&& a, T&& b)
혹은


std::move()

template<typename T>
void Swap(T& a, T& b)
{
	T tmp = std::move(a);// a라는 오브젝트에 tmp의 이름만 붙이는것
	a = std::move(b); // b라는 오브젝트에 a의 이름을 붙이는것
	b = std::move(tmp); // 마찬가지
}
복사없이 변경이 가능하다

-----------------------------------------------------------------------------------

- constexpr
	const + expression
	상수식

예제


int main()
{
	int n = 1;

	//runtime
	const int x = n;
	
	// x의 값이 들어가는 시점은 런타임
	// 계산을 해야하니깐 런타임


	// 컴파일때 상수를 결정하게 해주는
	constexpr int y = n + 1; // 에러
	constexpr int y = n; // 에러
	constexpr int y = x; // 에러
	// 컴파일시간에 명확하게 알수있는것만 가능

	constexpr int y = 1; // 가능



	std::cout << x << std::endl;

}



예제2


enum Flags
{
	poison = 1,
	bleed = 2,
	paralyze =4
};

constexpr int operator | (Flags f1, Flags f2)
{
	return Flgs(int(f1) | int (f2));
}

int main()
{
	Flags status;

	switch(status)
	{
	case poison :
	break;
	
	case poison | bleed;  // 이것과 같은경우는 런타임에 결정되기때문에
	break;				  // 스위치 케이스같은 경우에는  컴파일에 결정되야 사용이 가능하다
						  // 이럴때 constexpr로 사용가능
	case bleed;
	break;
	}
	std::cout << status1 << " " << status2 << std::endl;

}


-----------------------------------------------------------------------------------


- 복사 생성자 - 이동 생성자
	MyClass(MyClass&& c)

- 복사 대입 연산자 - 이동 대입 연산자
	MyClass& operator=(MyClass&& c)
	
	MyClass c1 = MyClass(); 

	이름 없는 MyClass객체를 생성하고 바로 이름을 붙여주는 형태
	복사가 이루어 지지않는다

-----------------------------------------------------------------------------------

- enum class

그냥 enum보다 enum class를 쓰는것이 좋다


enum끼리 멤버변수명이 겹치면 컴파일 오류가 나지만

enum class는 멤버변수들이 겹쳐도 문제없다

-----------------------------------------------------------------------------------

- Raw String Literal

"'\'"
일반적으로
std::string str = "\"\'\\\'\"";
이렇게 표현해야하지만
std::string str = R"("'\'")";

이렇게 쉽게 표현이 가능해진다

R"(이안에 넣는 문자는 모두 출력이 가능해진다)"


-----------------------------------------------------------------------------------






*/