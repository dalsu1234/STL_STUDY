#include "Monster.h"
#include <iostream>
#include <fstream>
#include <string>

std::ifstream& Monster::ReadBinary(std::ifstream& ifs)
{
	int len;

	// �о�� ���ڿ��� ����
	ifs.read(reinterpret_cast<char*>( & len), sizeof(int));
	
	mName.resize(len); // �о�� ���ڿ��� ũ��
	//�о�� ���ڿ�
	ifs.read(&mName[0], len);

	//&mName[0]�� mName�� ���ڿ��� ù������ �ּҰ�

	// ���� ������ ������
	ifs.read(reinterpret_cast<char*>(&mLevel), sizeof(int));
	ifs.read(reinterpret_cast<char*>(&mHP), sizeof(int));
	ifs.read(reinterpret_cast<char*>(&mMP), sizeof(int));
	


	return ifs;
}

std::ofstream& Monster::WriteBinary(std::ofstream& ofs)
{
	// ���� ���ڿ� ���� ���� ����
	int len{static_cast<int>(mName.size())};
	

	//����� ���ڿ��� ���� (�о���� ���ڿ��� ����, Ÿ��)
	ofs.write(reinterpret_cast<char*>(&len), sizeof(int));
	
	// ���ڿ� ����
	ofs.write(mName.c_str(), len);

	// ���� ����, HP , MP �� ����
	// (�����Ұ��� ��ġ �ּ�, ����� ������ ������)
	ofs.write(reinterpret_cast<char*>(&mLevel), sizeof(int));
	ofs.write(reinterpret_cast<char*>(&mHP), sizeof(int));
	ofs.write(reinterpret_cast<char*>(&mMP), sizeof(int));

	return ofs;
	// &len �� len�� �ּҰ� int�� �ּ��ε�
	// wirte()�� �Ű����� ù��°�� char������ �޴� ����
	// �׷��� ����ȯ�� ������Ѵ�
	// �׷��� &len �� �Ʒ�ó�� ����ȯ ������Ѵ�
	// reinterpret_cast<char*>(&len)
	// reinterpret_cast�� ���� �ٸ� Ÿ�԰��� ����ȯ�� ����
	// reinterpret_cast�� �ַ� �����Ϳ� �Ϲ��� �Ǵ� 
	// �����Ϳ� �����ͳ����� ����ȯ�� ���ȴ�
	// static_cast�� �Լ��� ȣ���ϰ� ��ȯ�� ����� �ӽú����� 
	// ��ȯ �Ѵ� �� static_cast<>() �Լ���� �����ϸ��
	// reinterpret_cast�� �Լ��� ȣ�� ���� �ʴ´�
	// �������� �˾Ƽ� ����

	//�� static_cast�� �Ϲ��ڷ��������� ����ȯ
	//reinterpret_cast�� �׿ܿ� ����ȯ(��> �����Ϳ� ������)

	// reinterpret_cast<char*>(&len)�� int���� �����͸� char�������ͷ� ��ȯ
	// static_cast<int>(mName.size()) �� sizeŸ���� int�� ��ȯ


	//write(�Ű�����1,�Ű�����2) �Լ���
	// �Ű�����2�� �����Ҷ�  �޸��� ��ĭ �� ��� ���̸�ŭ �����ϰڳĶ�¶�
	// int���� ũ��ϱ� 4����Ʈ�� ������ ����
	// �Ű�����1�� ������ ���ڿ� ��Ʈ�� (char Ÿ��) �� charŸ���̳� charŸ���� 1����Ʈ�ϱ�
	// �޸𸮿��� �о�ö� 1����Ʈ�� �о� �;��ؼ�
	// �Ű�����1�� ������ ������ �޸� �ּҸ� �ʿ�� �Ѵ�

	// mName.c_str()���� c_str����� mName�� std::string Ÿ���ε�
	// char �迭�� ���·� ��ȯ �� char������
}


/*


�޸𸮿� ����Ǵ� ������

��Ʈ�� 4����Ʈ���� �����ϴ¹������
��Ʈ���� ���̸� ���� ��Ʈ������ �����ϰ�
������ ���ȵ��� ��Ʈ������ ����


*/