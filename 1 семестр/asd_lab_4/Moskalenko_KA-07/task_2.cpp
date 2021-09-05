#include <iostream>
#include <cstdlib>
#include <ctime>
#define N 9

using namespace std;
struct Message {
	string text;
	int user_id;
	int smiles_number;
};

struct Line {
	Message chat[N];
	int head; //index of first element
	int tail; //index of last element
	int capacity;
};

Message generate_message();
void move_right(Line* line);
bool empty(Line* line);

void push(Line* line, Message *msg);
void pop(Line* line);
int size(Line* line);
Message front(Line* line);
void print_message(Message *msg);
void print(Line* line);

int main(){
	srand(time(NULL));
	Line chat;
	chat.head = 0;
	chat.tail = 0;
	chat.capacity = 0;
	Message current_msg;

	cout << "\n<<<<Додаємо 7 різних повідомлень>>>>" << endl;
	for (int i = 0; i < 7; i++) {
		current_msg = generate_message();
		push(&chat, &current_msg);
	}
	print(&chat);

	cout << "\n<<<<Додаємо ще 4 повідомлення>>>>" << endl;
	for (int i = 0; i < 4; i++) {
		current_msg = generate_message();
		push(&chat, &current_msg);
	}
	print(&chat);

	cout << "\n<<<<Прибираємо 6 повідомлень>>>>" << endl;
	for (int i = 0; i < 6; i++)
		pop(&chat);

	print(&chat);

	cout << "\n<<<<Прибираємо смайлики у двох перших повідомлень>>>>" << endl;
	for (int i = 0; i < 2; i++) {
		current_msg = front(&chat);
		pop(&chat);
		current_msg.smiles_number = 0;
		push(&chat, &current_msg);
	}
	print(&chat);

	cout << "\n<<<<Прибираємо 6 повідомлень>>>>" << endl;
	for (int i = 0; i < 6; i++)
		pop(&chat);

	print(&chat);

	cout << endl;
	return 0;
}

//choses random values for Message structures fields
Message generate_message(){
	string messages[5] = {"Доброго ранку.", "Чи можна задати питання?", "Ви вже задали.", "Дякую за відповідь.", "Бажаю гарного дня."};
	string text = messages[rand()%5];
	int id = rand()%50000 + 1;
	int smiles_number = rand()%4;
	return {text, id, smiles_number};
}

void push(Line* line, Message *msg) {
	//checks if a new item "outside" the line
	if (line->capacity == N) {
		cout << "push denied: line overflow" << endl;
		return;
	}
	//add new element to line

	line->chat[line->tail] = *msg;
	// checks if the next element index will be out of array if yes, then the next index becomes qual to 0
	line->tail = line->tail == N-1 ? 0 : line->tail + 1;
	line->capacity++;

}

void pop(Line* line){
	//checks if line is not empty
	if (empty(line)) {
		cout << "pop denied: line underflow" << endl;
		return;
	}
	//we can't delete an item, but we can do everything as if it doesn't exist
	line->head = line->head == N-1 ? 0 : line->head + 1;
	line->capacity--;
}

bool empty(Line* line){
	//if top equal to -1, line is empty. Otherwise it is not empty
	return line->capacity == 0;
}
//
//
int size(Line* line){
	//size of array is actually our head + 1
	return line->capacity;
}
//
Message front(Line* line){
	return line->chat[line->head];
}

void print(Line* line){
	cout << "На даний момент чат має вигляд:" << endl;

	// keep in memory size of input line
	int old_tail = line->tail;
	int old_head = line->head;
	int old_capacity = line->capacity;
	Message top_msg;
	int a = 0;
	// by FIFO: prints front element and temporarily forgets about it and repeats
	while(line->capacity != 0){
		if( a == 10)
			break;
		a++;
		top_msg = front(line);
		print_message(&top_msg);
		pop(line);
	}
	// suddenly remembers about all temporarily forgotten elements
	line->tail = old_tail;
	line->head = old_head;
	line->capacity = old_capacity;
}

void print_message(Message *msg){
    //prints some Tarantino cues
	cout << "Користувач id=" << msg->user_id << ": ";
	cout << msg->text;
	for (int i = 0; i < msg->smiles_number; i++) {
		cout << "🗿";
	}
	cout << endl;

}
