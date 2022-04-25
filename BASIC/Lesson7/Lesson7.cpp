/*

- Variadic Template


예제
------------------------------------------------------------------------

template<typename... Types>
void Functuion(Types... args)
{
	std::cout << sizeof...(Types) << std::endl;
	std::cout << sizeof...(args) << std::endl;
}

int main()
{
	Functuion(1,2,3);
	Functuion(1,2.0,"asd");
}

////////////////////////////////////////////////////////////////////////////

template<typename... Types>
void Functuion(Types... args) 
{
	int arr[]{ args... }; // 배열로 사용도 가능
}

int main()
{
	Functuion(1,2,3);
}

// 제한사항은 타입이 같아야만 가능함
달라도 가능한건 나중에 따로


////////////////////////////////////////////////////////////////////////////
//////////////////////재귀함수로 표현///////////////////////////////////////

void Function() // 재귀 종료
{
	std::cout << "end" << std::endl;
}

template<typename T, typename... Types>
void Function(T arg,Types... args)
{
	std::cout << arg << " ";

	//재귀
	Function(args...);
}


int main()
{
	Function(1,2,3);
	Function(1, 2.0, "asd");
}


////////////////////////////////////////////////////////////////////////////

매개변수를 가변을 받고 싶을때도 활용가능

예제
////////////////////////////////////////////////////////////////////////////

Warrior* Make();
Archer* Make(int arg1);
Wizard* Make(int arg1, int arg2);
Thief* Make(double arg1);

이렇게 직업이 여러개고 매개변수가 각각 다르다면


template<typename T, typename...Types>
T* Make(Types... args)
{
	return new T(args...);
}

이렇게 표현이 가능하다

이런 표현을 Factory Pattern 이라고 한다




##############################################################################
##############################################################################

Smart Pointer
	- delete를 알아서 해줌

기능

	- release()
		delete

	- reset()
		delete
		p = nullptre;

		직접적으로 포인터 해제

	- get()
		포인터를 반환
		


스마트 포인터의 종류 3가지

1> std::unique_ptr
	- 객체의 소유권을 가짐
		1 : 1
	- 복사가 안된다(복사생성자, 복사대입 둘다 안됨)
	- 단 이동은 가능 (r-value) 우측값참조


2> std::shared_ptr
	- 객체의 소유권을 공유
		1 : N

3> std::weak_ptr
	- shared와 기본적으로 같음
	- 단 소유권을 주장하지않음
	- use_count를 증가 시키지않음
	- 사용 횟수가 늘어나지않는다 하나로 여러개를 쓸수있다

예제
///////////////////////////////////////////////////////////////////
unique_ptr/////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
class MyClass
{

};

int main()
{
	MyClass* p = new MyClass;

	std::unique_ptr<MyClass> sp{ new MyClass };
	또는
	std::unique_ptr<MyClass> sp{ std::make_unique<MyClass>() };

	// delete로 포인터 지워줄필요없다
}

-------------------------------------------------------------------------------
//음악 앱
class Song
{
public:
	int mTrackNo;
	std::string mTitle;

	Song(int trackNo, std::string title) : mTrackNo{ trackNo }, mTitle{title}
	{
	}
};

int main()
{
	std::unique_ptr<Song> spSong{ std::make_unique<Song>(1, "BattleBGM")};

	std::cout << spSong->mTrackNo << " : " << spSong->mTitle << std::endl;

	spSong.get(); // Song 포인터가 돌아온다
	// get()이 필요한 이유
	// c 스타일의 포인터가 매개변수로 필요할때?
	a(spSong.get());
	// 이럴때 사용
}


///////////////////////////////////////////////////////////////////
shared_ptr/////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

class Image
{
	// 그림파일
};


class Bug
{
	Image* pImage; // 이런식이면 한장의 이미지를 계속 서로 공유하는것이 아니라
	// 매번 객체를 만들때마다 이미지를 로딩해야하는것
	// 이럴때 shared_ptr를 사용
	// 한장의 이미지를 여러 객체가 공유한다
	std::shared_ptr<Image> mspImage;
public:
	Bug(std::shared_ptr<Image> image) : mspImage{image}
	{
	}
};

int main()
{
	std::shared_ptr<Image> spImage{ std::make_shared<Image>() };

	auto spBug1 = std::make_unique<Bug>(spImage);
	auto spBug2 = std::make_unique<Bug>(spImage);
	auto spBug3 = std::make_unique<Bug>(spImage);

	// 각각의 벌레들은 유니크 객체
	// 이미지는 한장의 이미지로 여러객체가 공유
}


##############################################################################
##############################################################################

동시성
동시에 작업
	- 멀티 프로세스

	- 멀티 쓰레드
	동시에 작업하기때문에
	deadlock의 문제가 있음
	{
		- std::thread
		
		- std::mutex
	}


///////////////////////////////////////////////////////////////////
멀티 쓰레드/////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

#include <iostream>
#include <thread>
#include <mutex> // 데드락의 문제를 해결해줄수있는 기능 //상호배제 
// 하지만 완벽하게 문제를 해결해주진않는다

std::mutex gMutex;

//Worker A
void PrintInt()
{
	for (int i = 0; i < 500; ++i)
	{
		gMutex.lock(); // 교착상태대비 락을 걸어주는
		std::cout << "worker1 : " << i << std::endl;
		gMutex.unlock(); // 락을 풀어주는
	}
}

//Worker B

void PrintAscii()
{
	for (int repeat = 0; repeat < 5; ++repeat)
	{
		for (int i = 33; i < 126; ++i)
		{
			gMutex.lock();
			std::cout << "warker2 : " << (char)(i) << std::endl;
			gMutex.unlock();
		}
	}
}

int main()
{
	std::thread worker1(PrintInt);
	std::thread worker2(PrintAscii);

	worker1.join();
	worker2.join();

	std::cout << "---end---" << std::endl;
}


//////////////////////////////////////////////////////////

하지만 데드락의 문제를 완벽하게 해결해주진않는다
이유는 둘이 같이 동시에 올라오게된다면
여전히 데드락의 문제점이 생긴다
gMutex.lock();
하나가 올라오면 하나는 락을 걸어버리는 기능

그래서 gMutex.try_lock()로 해결가능하다
대신 for문으로는 구현이 불가능
while로 해야한다

/////////////////////////////////////////////////////////

#include <iostream>
#include <thread>
#include <mutex> // 데드락의 문제를 해결해줄수있는 기능

std::mutex gMutex;

//Worker A
void PrintInt()
{
	int i{};
	while (i < 500)
	{
		if (gMutex.try_lock())// 문제점 해결 방법
		{
		gMutex.lock();
		std::cout << "worker1 : " << i << std::endl;
		i++;
		gMutex.unlock();
		}
		else
		{
			//대기
		}
	}
}

//Worker B

void PrintAscii()
{
	for (int repeat = 0; repeat < 5; ++repeat)
	{
		int i = 33;
		while(i < 126)
		{
			if ( gMutex.try_lock())
			{
			gMutex.lock();
			std::cout << "warker2 : " << (char)(i) << std::endl;
			i++;
			gMutex.unlock();
			}
			else
			{
				//대기
			}
		}
	}
}

int main()
{
	std::thread worker1(PrintInt);
	std::thread worker2(PrintAscii);

	worker1.join();
	worker2.join();

	std::cout << "---end---" << std::endl;
}

##############################################################################
##############################################################################


*/