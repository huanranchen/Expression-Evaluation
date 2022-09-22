#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include <math.h>
#include <queue>
#include <string.h>

#define MAX 100
using namespace std;

char in_stack_precedence[128];
char incoming_precedence[128];
bool calculate_flag = true;

void init_precedence() {
	/*
	* now bugs:
	* 1.没有加乘方运算
	*/
	in_stack_precedence['+'] = 40;
	in_stack_precedence['-'] = 40;
	in_stack_precedence['*'] = 60;
	in_stack_precedence['/'] = 60;
	in_stack_precedence['%'] = 60;
	in_stack_precedence['('] = 20;
	in_stack_precedence[')'] = 0;
	in_stack_precedence['^'] = 70;

	incoming_precedence['+'] = 30;
	incoming_precedence['-'] = 30;
	incoming_precedence['*'] = 50;
	incoming_precedence['/'] = 50;
	incoming_precedence['%'] = 50;
	incoming_precedence['('] = 100;
	incoming_precedence[')'] = 20;
	incoming_precedence['^'] = 80;

}

int calculate(int a, int b, char operant) {//异常返回-1
	/*
	* now bugs:
	* 1.没有加乘方运算
	*/
	if (operant == '+') {
		return a + b;
	}
	if (operant == '-') {
		return b - a;
	}
	if (operant == '*') {
		return a * b;
	}
	if (operant == '/') {
		if (a == 0) {
			printf("Divide 0.\n");
			calculate_flag = false;
			return 0;
		}
		return b / a;
	}
	if (operant == '^') {
		if (a < 0) {
			printf("error.\n");
			calculate_flag = false;
		}
		return (int)pow((double)b, (double)a);
	}
	if (operant == '%') {
		return b % a;
	}
	return -1;
}


int next(char* a) {//如果是数字 return -1,符号return 1,没了return 0
	if (strlen(a) <= 0)
		return 0;
	char now = *a;
	if (now >= '0' && now <= '9')
		return -1;
	if (strlen(a) >= 2 && (*a) != '(') {//处理负数 因为除了(其他符号不会出现在开头
		char next_one = *(a + 1);
		char last_one = *(a - 1);
		if (now == '-' && next_one >= '0' && next_one <= '9' )
			if(!(last_one >= '0' && last_one <= '9'))
				return -1;
	}
	return 1;
}

bool pre_check(char* a) {
	/*
	情况：
	1. (*
	2. *)
	3. 10--3
	*/
	int lens = strlen(a);
	for (int i = 0; i < lens-1; i++) {
		if (a[i] == '(' && next(&a[i + 1]) == 1 && a[i + 1] != '(') {
			// (*这种情况
			return false;
		}
		if (a[i+1] == ')' && next(&a[i]) == 1 && a[i] != ')') {
			// *)这种情况
			return false;
		}
	}


	return true;
}

void solve() {
	/*
	now bugs:
	1.没有对括号进行非法判断。因为我不确定后面判断是否会覆盖这种情况，如果覆盖我就轻松了。。
	2.没有解决10--8这种负数问题
	3.除以0
	*/
	char* data = new char[MAX];
	scanf("%s", data);
	if (!pre_check(data)) {
		printf("error.\n");
		return;
	}
	stack<int> operants;
	stack<char> operators;
	//next这个命名有点误导我，记住是当前的，不是下一个的！！！！！！
	while (next(data) != 0) {
		if (next(data) == -1) {
			//数字
			char* temp = new char[MAX];
			int i = 0;
			while (next(data) == -1){ //一直读到不是数字
				temp[i] = *data;
				i += 1;
				data++;
			}
			operants.push(atoi(temp));
		}
		if (next(data) == 1) { // 符号
			if (operators.empty() || in_stack_precedence[operators.top()] < incoming_precedence[*data]) {
				operators.push(*data);
				data++;
			}
			else { //in_stack_precedence[operators.top()] > incoming_precedence[*data]
				while (!operators.empty() && 
					in_stack_precedence[operators.top()] >= incoming_precedence[*data]) {
					if (in_stack_precedence[operators.top()] == incoming_precedence[*data] &&
						*data == ')') {
						//只有"( )"会进入
						break;
					}

					char now_operator = operators.top();
					operators.pop();

					if (operants.empty()) {
						printf("error.\n");
						return;
					}
					int a = operants.top();
					operants.pop();
					if (operants.empty()) {
						printf("error.\n");
						return;
					}
					int b = operants.top();
					operants.pop();

					int result = calculate(a, b, now_operator);
					if (!calculate_flag){
						return;
					}
					operants.push(result);
				}
				if (*data == ')') {
					if (operators.empty() || 
						in_stack_precedence[operators.top()] < incoming_precedence[*data]) {
						printf("error.\n");
						return;
					}
					operators.pop();
				}
				
				if(*data != ')')
					operators.push(*data);
				data++;
			}
		}
	}
	if (next(data) == 0) {
		//下一个没了
		while (!operators.empty()) { //清空两个栈，以operator为准
			char now_operator = operators.top();
			operators.pop();

			if (operants.empty()) {
				printf("error.\n");
				return;
			}
			int a = operants.top();
			operants.pop();
			if (operants.empty()) {
				printf("error.\n");
				return;
			}
			int b = operants.top();
			operants.pop();

			int result = calculate(a, b, now_operator); 
			if (!calculate_flag) {
				return;
			}
			operants.push(result);

		}
		if (operants.size() != 1) { //如果operator都清空了，operant有2个以上，那就error
			printf("error.\n");
			return;
		}
		else {
			printf("%d\n", operants.top());
			operants.empty();
			
		}

	}
}

int main() {
	int n;
	scanf("%d", &n);
	init_precedence();
	while (n--) {
		calculate_flag = true;
		solve();
	}
	return 0;
}
