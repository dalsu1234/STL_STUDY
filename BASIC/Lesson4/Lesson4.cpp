/*

---------------------------------------------------------------------
std::array
---------------------------------------------------------------------
	- Sequence Container : 순차 컨테이너
	- Contiquos : 연속된 메모리 공간
	- Fixed Size : 고정 크기
	- 배열 대신 사용
	표현식>
	예
	std::array<int, 4> intArray{0,1,2,3};
	<int, 4> 타입의 크기와, 배열의 크기
---------------------------------------------------------------------
std::vector
---------------------------------------------------------------------
	- Sequential 순차적 컨테이너
	- Contiguous    / Allocator
연속적인 메모리공간 / 상황에따라 동적으로 할당할수있다
	- Dynamic Size
		동적 사이즈
	- 동적배열 - 뒤에 원소가 추가되거나 삭제되는 경우
	 원소의 추가 / 삭제가 뒤에서 일어날때
---------------------------------------------------------------------
std::forward_list
---------------------------------------------------------------------
	- Sequential 원소는 정해진 순서대로 저장된다 // 순차적
	- single linked list // 이 이유때문에 배열첨자가 사용이 불가능하다
	- 연속된 메모리를 차지하진않는다
	- 동적


---------------------------------------------------------------------
std::list
---------------------------------------------------------------------
	- Sequential
	- Double Linked List
	- Dynamic

	예제>>
==========================================================================
int main()
{
	std::list<int> container{ 1,2,3 };

	std::list<int> container2{ 4,6,5 };

	container.merge(container2);
	// 원소가 정렬되어 있지않으면 오류가 나온다 객체 둘다 모두 정렬이 되어있어야한다
	container.sort();
	container2.sort();
	// 정렬후에 merge를 사용해야함
	// merge의 조건은 두객체가 모두 정렬이 되어있어야한다
	// 카피가 일어나진않음


	for (const auto& e : container)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;

}

---------------------------------------------------------------------
std::deque
---------------------------------------------------------------------
	- Sequential
	- Double Ended Queue // 양방향으로 추가/삭제가 가능하다
	- Dynamic
	
	벡터와 다른점 
	메모리에서 연속된 공간을 사용하지않고
	쪼개져서 공간을 사용할수도 있다


==============================================================================
#####################################################################


# Container Adaptor(보조 컨테이너)
	
	- std::stack

	- std::queue

	- std::prioity_queue


#####################################################################
==============================================================================


예제>>std::stack
==============================================================================
#include <stack>

	int main()
	{
		std::stack<int> container;

		container.push(1);
		container.push(2);
		container.push(3);
		container.pop();

---------------------------------------------------------------------
		stack 은 범위기반반복문이 안된다

		for (const auto& e : container)
		{
			std::cout << e << " ";
		}
		std::cout << std::endl;
---------------------------------------------------------------------
		 stack 은 첨자배열반복문도 안된다

		for (int i = 0; i < container.size(); ++i)
		{
			std::cout << container[i] << " ";
		}
	
---------------------------------------------------------------------
		stakc은 이터레이터 반복도 불가능하다

		std::stack<int>::iterator itr = container.begin();
	
---------------------------------------------------------------------
		stack은 이 3가지 반복문 모두 불가능하다
		 그럼 스택은 출력을 어떻게 해야할까

---------------------------------------------------------------------
	while (!container.empty())
	{
		std::cout << container.top() << " ";
		container.pop();
	}
	std::cout << std::endl;

	이렇게도 가능하지만 출력을 한후에도 원소가 모두 비어있게됨

	어쩔수없이 복사를 한후에 출력을 해야한다


---------------------------------------------------------------------
	std::stack<int> tempContainer(container);

	while (!tempContainer.empty())
	{
		std::cout << tempContainer.top() << " ";
		tempContainer.pop();
	}
	std::cout << std::endl;


	stack은 반드시 복사를 한후에 출력이 가능



	}
---------------------------------------------------------------------

예제>>std::queue

==============================================================================
int main()
{
	std::queue<int> container;

	container.push(1);
	container.push(2);
	container.push(3);
	container.pop();

	// queue는 .top 가 없다
	// .front로 사용
	std::cout << container.front() << std::endl;

	container.pop();

	출력은 스택과 동일하다

}

==============================================================================
예제>>std::priority_queue
==============================================================================
int main()
{

	std::priority_queue<int> q;

	q.push(1);
	q.push(2);
	q.push(3);
	q.push(2);
	q.push(1);

	std::cout << q.top() << std::endl;

	// queue의 형태인데 왜 front가 아니라 top일까
	// priority_queue 는 순차적으로 나오는게 아니라
	// 우선순위가 가장높은순위가 빠져나오는 형태이기때문에

	// 우선순위는 값이 큰녀석들부터 나오게된다
	// 하지만 반복된 동일한 수가 있으면 반복되는 순간부터 무시하고
	// 출력된다
	q.pop();
}

==============================================================================
##############################################################################

Associative Container (연관 컨테이너)
	
	- std::set
		트리구조

	- std::map

	- std::multiset

	- std::multimap

##############################################################################
==============================================================================

	std::set
		Binary Search Tree (BST) 구조
		검색에 특화되어있음

	std::map
		다른언어에서는 Dictionary
		각원소에 태그같이 정보를 붙여놓은 구조
		<키, 값> 키와 밸류 두개가 묶여져있는 구조가 필요함

		std::map을 사용하기 위해선 std::pair 를 반드시 알아야함

		std::pair 변수 두개를 묶어줌
		std::pair<T1, T2>;

==============================================================================

std::set 예제>>
==============================================================================
#include <set>

int main()
{
	std::set<int> container{ 8,3,1,6 };
	
	// 오름차순으로 출력

	for (const auto& e : container)
	{
		std::cout << e << std::endl;
	}
	// 단점이 존재하는데 동일한 수가 존재한다면 
	// 반복된수는 컨테이너 담지도 않는다 
	// 그래서 출력도 안된다
}






==============================================================================

std::map 예제>>
==============================================================================


#include <map>

using MyPair = std::pair<std::string, std::string>;

int main()
{
	std::map<std::string, std::string> container;


	std::pair<std::string, std::string> element;
	element.first = "array";
	element.second = "simple static Array";

	// first는 첫벗째인 키에 들어가는값
	// second는 두번째인 값에 들어가는값으로 생각하면될듯


	container.insert(std::pair<std::string, std::string>("vector", "Dynamic Array"));
	// 이렇게 붙여서 쓸수도 있다
	// 하지만코드가 너무 길어지고 가독성도 떨이진다
	// 이럴때 using을 사용하자


	// using alias
	container.insert(MyPair("stack", "Lifo"));


	//유니폼 초기화식
	container.insert({"queue", "FiFO"});

	// 유니폼초기화식을 가장 많이 사용한다

	for (const auto& e : container)
	{
		// std::cout << e << std::endl;
		// 이런식으로 사용할수가없다
		// auto e의 타입은?
		// 컨테이너 원소의 타입은 클래스이기때문에
		// 클래스를 통째로 출력하진 못한다

		std::cout << e.first << " : " << e.second << std::endl;
		//이런식으로 사용해야한다 first와 second
	}


	// 키로 접근하는 방법
	std::cout << container.at("array") << std::endl;

	std::cout << container["array"] << std::endl;

}

// map의 특징은 정렬이 알파벳순으로 정렬한다

*/
