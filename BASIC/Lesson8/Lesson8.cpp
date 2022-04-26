/*

동시성 프로그래밍

#include <iostream>
#include <thread>
#include <mutex>

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



#######################################################################

		App(process)
	#########################
	main
	{

	}
	#########################
			    |
	............|............
   |					     |
##############      #################
Thread1				 Thread2
worker1.join();		 worker2.join();
##############		#################

Thread1 과 Thread2 이 번갈아 가면서 실행됨



---------------------------------------------------------------------

비동기화 프로그래밍

비동기화 프로그래밍은 #include<future>를 추가해야한다

예제>
#####################################################################
#include<iostream>
#include<future>

int main()
{
	std::future<void> async1 = std::async(PrintInt);
	std::future<void> async2 = std::async(PrintAscii);  // 함수호출을 비동기화

	std::cout << "== 모든 작업이 끝났습니다. ==" << std::endl;

}

Thread와 차이점은??

동기화 프로그래밍은
async1의 연산이 끝나고 async2이 호출되는 순차적으로 진행되었다면

비동기화프로그래밍은

async1를 호출하고 연산이 끝나지않아도 async2를 호출한다
그리고 모든작업이 끝났습니다 라는 글자를 호출한다
그래서 함수호출한 async1과 async2는 의 결과값보다
모든작업이 끝났습니다 라는 글자가 먼저 나온다

결과값을 기다리지않고 함수 호출부터

쓰레드보다 더 많이 사용한다
쓰레드의 문제점 (데드락, 임계구역등등)이 일어나지않는다
좀더 안정적이다


int main()
{
	std::future<void> async1 = std::async(PrintInt);
	std::future<void> async2 = std::async(PrintAscii);

	std::cout << "== 모든 작업이 끝났습니다. ==" << std::endl;

	async1.get(); // future로 미뤄낸 반환값을 바로 가져오는 식
		// 이 식에서 바로 결과값이 나온다

	std::cout << " 완료 " << std::endl;

}



-----------------------------------------------------------------------------

파일 입출력

#stream



		ios - base						- 기반
		     |
			ios
	.........|...........
	|					|
istream				ostream				- 파생






#주기억장치(RAM)
	- 휘발성
	- 임의접근

#보조기억장치(HDD)
	- 비휘발성
	- 순차접근



#파일 입출력

c++ style File System
	스트림 객체
	- 상태
		good()
		eof()
		fail() - 연산실패
		bad()  - 심각한 오류 (물리적 손상)



##################################################################

istream : 입력 - 파일을 읽어오는것
	- ifstream



ostream : 출력 - 파일로 저장하는것
	- ofstream




	// 1. 파일 스트림 객체 생성 (용도에 맞는)
	//	1.1 모드를 지정 (읽기/쓰기/텍스트/바이너리모드)
	//	1.2 생성자(파일이름)
	//	1.3 빈 오브젝트 생성 -> 파일 열기

	// 2. 파일 작업
	//	2.1 스트림 연산자
	//	2.2 멤버 함수

	// 3. 파일 닫기


	예제>>
######################################################################


#include <iostream>
#include <fstream>

bool LoadFile(const std::string& filename)
{

	// 1. 파일 스트림 객체 생성 (용도에 맞는)
	std::ifstream ifs(filename); //i:입력 f:파일

	if (!ifs)
	{
		std::cout << filename << "을 찾을수없습니다." << std::endl;
		return false;
	}

	// 2. 파일 작업
	char ch;
	while (ifs >> ch)
	{
		std::cout << ch;
	}

		//.get() 으로 표현
	char ch;
	while (ifs) // ifs는 참거짓으로 반환
	{
		ifs.get(ch);
		std::cout << ch;
	}

	//get() 으로 표현하면 줄바뀜도 다 출력해준다 있는 그대로 다 출력해줌
	// 위에 식은 줄바뀜 안됨


	// 3. 파일 닫기
	ifs.close();

	return true;
}


int main()
{

	LoadFile("Data/SimpleData.txt"); // Data/SimpleData.txt 읽어올 텍스트 파일 경로
	// exe에서 실행할때와 컴파일 할때의 경로가 서로 다르다
	// exe로 실행할때는 exe의 위치에서부터의 경로
	// 컴파일은 프로젝트파일 위치에서부터의 경로
}

윈도우 운영체제

"Data\SimpleData.txt"
또는
"Data\\SimpleData.txt"
또는
R"("Data/SimpleData.txt")";


리눅스 운영체제

"Data/SimpleData.txt"


무엇으로 해도 다 지원한다
"Data/SimpleData.txt" 이런 표기가 보기 편한..



if (!ifs)는  // ifs == nullptr 이나 ifs == false를 의미하는게 아니다
ifs는 포인터도 참거짓도 아니다

! 연산자 오버로딩

기본적으로는 참거짓으로 값이돌아온다

형변환



ifs.get() // 입력 스트림에서 하나 이상의 문자를 읽는

파일의 끝에 도달하면 eof (end of file)를 반환한다

eof는 char* 배열 에서 마지막은 \0로 끝나는것과 같은 의미다

파일의 마지막은 eof가 들어있다



// 2. 파일 작업
	char ch;
	while (ifs >> ch)
	{
		if(ifs.bad())
		{
			std::cout << "파일이 손상되었습니다." << std::endl;
			ifs.colse(); // 종료
			return false; //반환
		}
		if(ifs.fail())
		{
			std::cout << "의도치 않은 작업입니다." << std::endl;
			ifs.close();
			return;
		}
		std::cout << ch;
	}

	이런식으로 방어적으로 코드를 작성할수있지만

	exception 예외처리로 처리할수있다
	좀더 깔끔하게 코드를 작성할수있다

*/

