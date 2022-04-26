/*

���ü� ���α׷���

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

Thread1 �� Thread2 �� ������ ���鼭 �����



---------------------------------------------------------------------

�񵿱�ȭ ���α׷���

�񵿱�ȭ ���α׷����� #include<future>�� �߰��ؾ��Ѵ�

����>
#####################################################################
#include<iostream>
#include<future>

int main()
{
	std::future<void> async1 = std::async(PrintInt);
	std::future<void> async2 = std::async(PrintAscii);  // �Լ�ȣ���� �񵿱�ȭ

	std::cout << "== ��� �۾��� �������ϴ�. ==" << std::endl;

}

Thread�� ��������??

����ȭ ���α׷�����
async1�� ������ ������ async2�� ȣ��Ǵ� ���������� ����Ǿ��ٸ�

�񵿱�ȭ���α׷�����

async1�� ȣ���ϰ� ������ �������ʾƵ� async2�� ȣ���Ѵ�
�׸��� ����۾��� �������ϴ� ��� ���ڸ� ȣ���Ѵ�
�׷��� �Լ�ȣ���� async1�� async2�� �� ���������
����۾��� �������ϴ� ��� ���ڰ� ���� ���´�

������� ��ٸ����ʰ� �Լ� ȣ�����

�����庸�� �� ���� ����Ѵ�
�������� ������ (�����, �Ӱ豸�����)�� �Ͼ���ʴ´�
���� �������̴�


int main()
{
	std::future<void> async1 = std::async(PrintInt);
	std::future<void> async2 = std::async(PrintAscii);

	std::cout << "== ��� �۾��� �������ϴ�. ==" << std::endl;

	async1.get(); // future�� �̷ﳽ ��ȯ���� �ٷ� �������� ��
		// �� �Ŀ��� �ٷ� ������� ���´�

	std::cout << " �Ϸ� " << std::endl;

}



-----------------------------------------------------------------------------

���� �����

#stream



		ios - base						- ���
		     |
			ios
	.........|...........
	|					|
istream				ostream				- �Ļ�






#�ֱ����ġ(RAM)
	- �ֹ߼�
	- ��������

#���������ġ(HDD)
	- ���ֹ߼�
	- ��������



#���� �����

c++ style File System
	��Ʈ�� ��ü
	- ����
		good()
		eof()
		fail() - �������
		bad()  - �ɰ��� ���� (������ �ջ�)



##################################################################

istream : �Է� - ������ �о���°�
	- ifstream



ostream : ��� - ���Ϸ� �����ϴ°�
	- ofstream




	// 1. ���� ��Ʈ�� ��ü ���� (�뵵�� �´�)
	//	1.1 ��带 ���� (�б�/����/�ؽ�Ʈ/���̳ʸ����)
	//	1.2 ������(�����̸�)
	//	1.3 �� ������Ʈ ���� -> ���� ����

	// 2. ���� �۾�
	//	2.1 ��Ʈ�� ������
	//	2.2 ��� �Լ�

	// 3. ���� �ݱ�


	����>>
######################################################################


#include <iostream>
#include <fstream>

bool LoadFile(const std::string& filename)
{

	// 1. ���� ��Ʈ�� ��ü ���� (�뵵�� �´�)
	std::ifstream ifs(filename); //i:�Է� f:����

	if (!ifs)
	{
		std::cout << filename << "�� ã���������ϴ�." << std::endl;
		return false;
	}

	// 2. ���� �۾�
	char ch;
	while (ifs >> ch)
	{
		std::cout << ch;
	}

		//.get() ���� ǥ��
	char ch;
	while (ifs) // ifs�� ���������� ��ȯ
	{
		ifs.get(ch);
		std::cout << ch;
	}

	//get() ���� ǥ���ϸ� �ٹٲ� �� ������ش� �ִ� �״�� �� �������
	// ���� ���� �ٹٲ� �ȵ�


	// 3. ���� �ݱ�
	ifs.close();

	return true;
}


int main()
{

	LoadFile("Data/SimpleData.txt"); // Data/SimpleData.txt �о�� �ؽ�Ʈ ���� ���
	// exe���� �����Ҷ��� ������ �Ҷ��� ��ΰ� ���� �ٸ���
	// exe�� �����Ҷ��� exe�� ��ġ���������� ���
	// �������� ������Ʈ���� ��ġ���������� ���
}

������ �ü��

"Data\SimpleData.txt"
�Ǵ�
"Data\\SimpleData.txt"
�Ǵ�
R"("Data/SimpleData.txt")";


������ �ü��

"Data/SimpleData.txt"


�������� �ص� �� �����Ѵ�
"Data/SimpleData.txt" �̷� ǥ�Ⱑ ���� ����..



if (!ifs)��  // ifs == nullptr �̳� ifs == false�� �ǹ��ϴ°� �ƴϴ�
ifs�� �����͵� �������� �ƴϴ�

! ������ �����ε�

�⺻�����δ� ���������� ���̵��ƿ´�

����ȯ



ifs.get() // �Է� ��Ʈ������ �ϳ� �̻��� ���ڸ� �д�

������ ���� �����ϸ� eof (end of file)�� ��ȯ�Ѵ�

eof�� char* �迭 ���� �������� \0�� �����°Ͱ� ���� �ǹ̴�

������ �������� eof�� ����ִ�



// 2. ���� �۾�
	char ch;
	while (ifs >> ch)
	{
		if(ifs.bad())
		{
			std::cout << "������ �ջ�Ǿ����ϴ�." << std::endl;
			ifs.colse(); // ����
			return false; //��ȯ
		}
		if(ifs.fail())
		{
			std::cout << "�ǵ�ġ ���� �۾��Դϴ�." << std::endl;
			ifs.close();
			return;
		}
		std::cout << ch;
	}

	�̷������� ��������� �ڵ带 �ۼ��Ҽ�������

	exception ����ó���� ó���Ҽ��ִ�
	���� ����ϰ� �ڵ带 �ۼ��Ҽ��ִ�

*/

