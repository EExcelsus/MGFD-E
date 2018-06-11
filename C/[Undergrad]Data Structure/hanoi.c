#include <stdio.h>

//하노이 자동이동!
int hanoiMove(int n, char start, char middle, char end) {
	//0에 대해서는 아무것도 안함!
	if (n == 0)
		return 0;

	int tempCount = 0;

	//A에서 B로 n-1더미 자동이동!
	tempCount += hanoiMove(n - 1, start, end, middle);

	//A에서 C로 n디스크 이동!
	printf("%d번 원판을 %c에서 %c로 이동\n", n, start, end);
	tempCount++;

	//B에 치워둔 n-1더미 C로 자동이동!
	tempCount += hanoiMove(n - 1, middle, start, end);

	return tempCount;
}

int main() {
	int numberOfPlates = 0;

	//입력부
	printf("원판의 개수를 입력하시오: ");
	scanf("%d", &numberOfPlates);

	//출력부
	printf("총 이동 횟수: %d\n", hanoiMove(numberOfPlates, 'A', 'B', 'C'));

	return 0;
}