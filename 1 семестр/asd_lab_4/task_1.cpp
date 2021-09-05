#include <iostream>
#include <cstdlib>
#include <ctime>
#define N 4

using namespace std;
struct Ball {
	string color;
	bool isStripped;
	int number;
};

struct Stack {
	Ball pocket[N];
	int top;
};

Ball generate_ball();

bool empty(Stack* stack);
void push(Stack* stack, Ball *ball);
void pop(Stack* stack);
int size(Stack* stack);
Ball top(Stack* stack);
void look_at_ball(Ball *ball);
void print(Stack* stack);

int main() {
	srand(time(NULL));
	//create pocket for balls
	Stack pocket;
	pocket.top = -1;
	Ball ball_in_hand;

	cout << "\n<<<<Забиваємо в лузу три різні кулі>>>>" << endl;
	for (int i = 0; i < 3; i++) {
		ball_in_hand = generate_ball();
		push(&pocket, &ball_in_hand);
	}
	print(&pocket);

	cout << "\n<<<<Забираємо верхню кулю>>>>" << endl;
	pop(&pocket);
	print(&pocket);

	cout << "\n<<<<Забиваємо ще 3 кулі>>>>" << endl;
	for (int i = 0; i < 3; i++) {
		ball_in_hand = generate_ball();
		push(&pocket, &ball_in_hand);
	}
	print(&pocket);

	cout << "\n<<<<Обираємо з верхніх куль, кулю з найбільшим номером>>>>" << endl;
	//takes one ball
	ball_in_hand = top(&pocket);
	pop(&pocket);
	//takes another ball and immediately compares them
	ball_in_hand = (ball_in_hand.number > top(&pocket).number) ? ball_in_hand : top(&pocket);
	pop(&pocket);
	push(&pocket, &ball_in_hand);
	print(&pocket);

	cout << "\n<<<<Забираємо 5 куль>>>>" << endl;
	for (int i = 0; i < 5; i++)
		pop(&pocket);

	print(&pocket);

	cout << endl;
	return 0;
}

//choses random values of Ball structures fields
Ball generate_ball(){
	string colors[5] = {"Червона", "Чорна", "Зелена", "Біла", "Чорна"};
	string color = colors[rand()%5];
	int number = rand()%15 + 1;
	bool isStripped= rand()%2;
	Ball ballchik = {color, isStripped, number};
	return ballchik;
}

void push(Stack* stack, Ball *ball) {
	//checks for a new item off the stack
	if (stack->top+1 >= N) {
		cout << "push denied: stack overflow" << endl;
		return;
	}
	//add new element to stack
	stack->top++;
	stack->pocket[stack->top] = *ball;
}

void pop(Stack* stack){
	//checks if stack is not empty
	if (empty(stack)) {
		cout << "pop denied: stack underflow" << endl;
		return;
	}
	//we can't delete an item, but we can do everything as if it doesn't exist
	stack->top--;
}

bool empty(Stack* stack){
	//if top equal to 0, stack is empty. Otherwise it is not empty
	return stack->top == -1;
}


int size(Stack* stack){
	//size of array is actually our top
	return stack->top+1;
}

Ball top(Stack* stack){
	return stack->pocket[stack->top];
}

void print(Stack* stack){
	cout << "На даний момент в лузі знаходяться:" << endl;
	// keep in memory size of input stack
	int old_size = size(stack);
	Ball top_ball;
	// by LIFO: prints top element and temporarily forgets about it and repeats
	for (int i = 0; i < old_size; i++) {
		top_ball = top(stack);
		look_at_ball(&top_ball);
		pop(stack);
	}
	// suddenly remembers about all temporarily forgotten elements
	stack->top = old_size-1;
}

void look_at_ball(Ball *ball){

	cout << ball->color << " та ";
	cout << (ball->isStripped ? "смугаста" : "суцільна");
	cout << " куля номер " << ball->number << endl;

}
