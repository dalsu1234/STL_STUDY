/*

템플릿 자동적으로 추론

template<typename T>
void Function(T t)
{
}

Function<int>(1);
위에 식을

Function(1);
자동적으로 추론해서 이렇게생략할수있다


이것과 비슷한 auto라는게 있다

######################################################

int x = 1;
은

auto x = 1; 과 같다


그럼 타입이 길어지면 auto를 사용해서 코드길이를 줄일수있음


#######################################################

#include <vector>
int main()
{
	std::vector<int> v{1,2,3,4,5};


	for (int e : v)
	{
		std::cout << e << std::endl;
	}

	std::vector<int>::iterator itr;

	itr = v.begin();

	while (itr != v.end())
	{
		std::cout << *itr << std::endl;
		itr++;
	}

	for (auto itr=v.begin(); itr != v.end(); itr++)
		// 이렇게 auto를 쓸수있는건 자동으로
		//어떤 타입으로 변환하는지 위에 컴파일이 추론할수있게
		//선언이 되어 있어야지만 auto를 쓸수있다
	{
		std::cout << *itr << std::endl;
	}

	// 컴파일러가 추측할수있어야한다
	auto itr2;
	// 이렇게는 사용할수없다는 말이다
}


#######################################################

범위 기반 연산자는 값이기 때문에
값을 넣기위해 참조를 사용한다

######################################################
	
	
	for (int& e : v) // 참조를 해야지만 v의 값이 변경이된다
	{				 // e와 v는 서로 다른객체니깐
		e = 1;
		std::cout << e << std::endl;
	}
	이런식으로 사용한다

	
	
	
	
범위 기반연산자의 주의점
	-원소를 값 타입 혹은 참조 타입 사용
	
#############################################################

#include <vector>
int main()
{
	std::vector<int> v{1,2,3,4,5};


# 범위 기반 연산자
	for (int& e : v) // 참조를 해야지만 v의 값이 변경이된다
	{				 // e와 v는 서로 다른객체니깐
		e = 1;
		std::cout << e << std::endl;
	}


	std::vector<int>::iterator itr = v.begin();
# 이터레이터
	for (;itr < v.end(); itr++)
	{
		*itr = 1; // 이터레이터는 포인터니깐 바로 역참조 가능하다
		std::cout << *itr << std::endl;
	}


# index for loop
	// 3가지 방법중 유일하게 인덱스에 바로 접근할수있는방법
	for (int i = 0; i < v.size(); ++i)
	{
		v[i] = i;
	}


	for (const int& e : v) // 빠르게 참조로 그리고 그값을 안전하게 지키기 위해 cosnt로
	{
		std::cout << e << std::endl;
	}

}

#############################################################################

#범위 기반연산자의 단점!!

	- 배열의 인덱스를 알수가 없다

	int index{};
	for (int& e : v) 
	{			
		if(index == 3)
		{
			e = 1;
		}
		std::cout << e << std::endl;
		index++;
	}

	이런식으로 밖에 할수없다

#############################################################################

3가지 방법 정리하자면

1 범위 기반 연산자는 
	= 대부분의 경우 쉽게 쓸수있어서 사용하기좋고

2 배열 첨자 반복문은
	= 인덱스가 필요한경우

3 이터레이터는
	= STL과 관련된 모든작업에 사용하면 된다

#############################################################################

STL의 알고리즘

#퀵소트

qsort(void *__base, size_t __nel, size_t __width,
int(* _Nonnull __comar)(const void * , const void *));

이런형태인데
하나하나 뜯어보자면

void *__base 는 void 배열을 받는  

즉 어떠한 타입이든간에 정렬할 배열을
인자로 받겠다라는 뜻



size_t __nel 

음수가 아닌 양수가 들어감

원소의 갯수

size_t __width

음수가 아닌 양수가 들어감

원소의 갯수


왜 원소의 갯수를 받는 인자가 2개나 필요할까

이유는 
첫번째 매개변수가 보이드 타입의 포인터인데
역참조를 할수가없다
왜냐면 타입을 모르잔냐
void니깐
타입을 알아야 그타입의 크기만큼 순회를 할수있을텐데
그게 불가능

그래서 
size_t __width
는 타입의 크기를 뜻하는거다
타입의 크기!!



int(* _Nonnull __compar)(const void * , const void *)

이건 함수 포인터다
함수포인터는 함수 매개변수로 쓰기위해 

Nonnull은 아무값도 없는지 확인하는것
(* _Nonnull __compar) 즉 비교함수임


예제>>
#############################################################################

#include <iostream>
#include <vector>
#include <algorithm>

int Compare(const void* left, const void* right)
{

	int arg1 = *static_cast<const int*>(left);
	// left는 void 포인터라 명시적으로 형변환 해줘야한다
	// const void* 니깐 그러면 형변환도 동일하게
	// const int* 로 써주면 된다
	// 표기법 잘 봐둬
	int arg2 = *static_cast<const int*>(right);


	if (arg1 == arg2)
	{
		return -1;
	}
	else if (arg1 < arg2) // 오름차순과 내림차순에따라 바꿔주면된다
	{
		return 1;
	}
	return 0;
	// 위식을
	// 한줄로 표현가능
	return arg1 - arg2; // 이렇게도 비교가 가능하다
}

int main()
{
	std::vector<int> v{1,2,3,4,5};

	std::qsort(&v[0], v.size(), sizeof(int), Compare); // 퀵소트 표현식

	std::sort(v.begin(), v.end()); // 그냥 소트


	for (const auto& e : v)
	{
		std::cout << e << std::endl;
	}
}

##################################################################################

일반 소트는 알고리즘에
퀵소트는 std라이브러리에


퀵소트는 일반배열형태도 사용할수있고
	- C style

일반소트는 이터레이터형식에만 사용할수있다 벡터
	- C++ style

형태에 맞게 사용하면된다


###########################################################################
함수를 만드는것은
여러번 재활용할수있을때 만들어서 사용하는거지만 
한번만 사용해야한다면??
일회성이라면

여기서 
###########################################################################
#람다식


예제

int Compare(const void* left, const void* right)
를 람다식으로 바꾼다면?

(const void* left, const void* right)->int{

}





std::qsort(&v[0], v.size(), sizeof(int), Compare);

를 람다식으로

std::qsort(&v[0], v.size(), sizeof(int), 
	[](const void* leff, const void* right)->int
{
	int arg1 = *static_cast<const int*>(left);
	int arg2 = *static_cast<const int*>(right);
	
	return arg1 - arg2;
});



다른 예제
######################################################################

std::for_each(v.begin(), v.end(), [](const int& vlaue)
		{
			std::cout << value << std::endl;
		});


for_each는 범위를 정하고 그 범위 안에서
순회하면서 함수를 실행하는 알고리즘
#####################################################################

한번쓰고 버리는 함수는 이렇게
람다식으로 사용한다





*/
