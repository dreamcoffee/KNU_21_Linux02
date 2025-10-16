#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
										
		int num1 = atof(argv[1]);
		int num2 = atof(argv[3]);
		char op = argv[2][0];
		
	int add(int num1, int num2){
		return num1 + num2;
	}


	int minus(int num1, int num2){
		return num1 - num2;
	}

	int mult(int num1, int num2){
		return num1 * num2;
	}

	int div(int num1, int num2){
		return num1 / num2;
	}	
		
	if(argc != 4) {
		printf("불가능 한 입력입니다.");
		return 1;
	}

	int result;

	switch (op){
		case '+':
			result = add(num1,num2);
			break;
		case '-':
			result = minus(num1,num2);
			break;
		case 'x':
			result = mult(num1,num2);
			break;
		case '/':
			result = div(num1, num2);
			break;
		default:
			printf("에러 발생");
			return 1;
	}
	printf("%d\n", result);

	return 0;
}
