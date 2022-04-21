/*



자주 사용하는 3가지

vector
	
	- 뒤에서 추가 / 삭제
	- 데이터가 적은 경우 (Random Access & Contiguous)

list

	- 중간에서 추가 / 삭제
	- 데이터가 적은 경우

map
	
	- 데이터가 많은경우

	- <ket, value>


set

	- key
	- 정렬이 되어 있어서 검색이 빠름



	고려해볼 우선순위

1. vector 가 가장 빠르다

2. set, map

3. list

-----------------------------------------------------------------------------

erase-remove idiom

	- Seqence Container
	- container.erase(remove());

	모든컨테이너는 erase remove를 해줘야한다


*/