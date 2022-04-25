/*

- Variadic Template


����
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
	int arr[]{ args... }; // �迭�� ��뵵 ����
}

int main()
{
	Functuion(1,2,3);
}

// ���ѻ����� Ÿ���� ���ƾ߸� ������
�޶� �����Ѱ� ���߿� ����


////////////////////////////////////////////////////////////////////////////
//////////////////////����Լ��� ǥ��///////////////////////////////////////

void Function() // ��� ����
{
	std::cout << "end" << std::endl;
}

template<typename T, typename... Types>
void Function(T arg,Types... args)
{
	std::cout << arg << " ";

	//���
	Function(args...);
}


int main()
{
	Function(1,2,3);
	Function(1, 2.0, "asd");
}


////////////////////////////////////////////////////////////////////////////

�Ű������� ������ �ް� �������� Ȱ�밡��

����
////////////////////////////////////////////////////////////////////////////

Warrior* Make();
Archer* Make(int arg1);
Wizard* Make(int arg1, int arg2);
Thief* Make(double arg1);

�̷��� ������ �������� �Ű������� ���� �ٸ��ٸ�


template<typename T, typename...Types>
T* Make(Types... args)
{
	return new T(args...);
}

�̷��� ǥ���� �����ϴ�

�̷� ǥ���� Factory Pattern �̶�� �Ѵ�




##############################################################################
##############################################################################

Smart Pointer
	- delete�� �˾Ƽ� ����

���

	- release()
		delete

	- reset()
		delete
		p = nullptre;

		���������� ������ ����

	- get()
		�����͸� ��ȯ
		


����Ʈ �������� ���� 3����

1> std::unique_ptr
	- ��ü�� �������� ����
		1 : 1
	- ���簡 �ȵȴ�(���������, ������� �Ѵ� �ȵ�)
	- �� �̵��� ���� (r-value) ����������


2> std::shared_ptr
	- ��ü�� �������� ����
		1 : N

3> std::weak_ptr
	- shared�� �⺻������ ����
	- �� �������� ������������
	- use_count�� ���� ��Ű������
	- ��� Ƚ���� �þ���ʴ´� �ϳ��� �������� �����ִ�

����
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
	�Ǵ�
	std::unique_ptr<MyClass> sp{ std::make_unique<MyClass>() };

	// delete�� ������ �������ʿ����
}

-------------------------------------------------------------------------------
//���� ��
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

	spSong.get(); // Song �����Ͱ� ���ƿ´�
	// get()�� �ʿ��� ����
	// c ��Ÿ���� �����Ͱ� �Ű������� �ʿ��Ҷ�?
	a(spSong.get());
	// �̷��� ���
}


///////////////////////////////////////////////////////////////////
shared_ptr/////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

class Image
{
	// �׸�����
};


class Bug
{
	Image* pImage; // �̷����̸� ������ �̹����� ��� ���� �����ϴ°��� �ƴ϶�
	// �Ź� ��ü�� ���鶧���� �̹����� �ε��ؾ��ϴ°�
	// �̷��� shared_ptr�� ���
	// ������ �̹����� ���� ��ü�� �����Ѵ�
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

	// ������ �������� ����ũ ��ü
	// �̹����� ������ �̹����� ������ü�� ����
}


##############################################################################
##############################################################################

���ü�
���ÿ� �۾�
	- ��Ƽ ���μ���

	- ��Ƽ ������
	���ÿ� �۾��ϱ⶧����
	deadlock�� ������ ����
	{
		- std::thread
		
		- std::mutex
	}


///////////////////////////////////////////////////////////////////
��Ƽ ������/////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

#include <iostream>
#include <thread>
#include <mutex> // ������� ������ �ذ����ټ��ִ� ��� //��ȣ���� 
// ������ �Ϻ��ϰ� ������ �ذ��������ʴ´�

std::mutex gMutex;

//Worker A
void PrintInt()
{
	for (int i = 0; i < 500; ++i)
	{
		gMutex.lock(); // �������´�� ���� �ɾ��ִ�
		std::cout << "worker1 : " << i << std::endl;
		gMutex.unlock(); // ���� Ǯ���ִ�
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

������ ������� ������ �Ϻ��ϰ� �ذ��������ʴ´�
������ ���� ���� ���ÿ� �ö���Եȴٸ�
������ ������� �������� �����
gMutex.lock();
�ϳ��� �ö���� �ϳ��� ���� �ɾ������ ���

�׷��� gMutex.try_lock()�� �ذᰡ���ϴ�
��� for�����δ� ������ �Ұ���
while�� �ؾ��Ѵ�

/////////////////////////////////////////////////////////

#include <iostream>
#include <thread>
#include <mutex> // ������� ������ �ذ����ټ��ִ� ���

std::mutex gMutex;

//Worker A
void PrintInt()
{
	int i{};
	while (i < 500)
	{
		if (gMutex.try_lock())// ������ �ذ� ���
		{
		gMutex.lock();
		std::cout << "worker1 : " << i << std::endl;
		i++;
		gMutex.unlock();
		}
		else
		{
			//���
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
				//���
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