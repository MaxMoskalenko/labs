#include <iostream>
#include <ctime>

using namespace std;


struct Meme {
	string memplate;
	string text;
	int likes;
};

void print_meme(Meme* meme);

struct Node {
	Meme data;
	Node* next;
};

struct LinkedList {
	Node* head; // points on the first element
	Node* tail; // points on the last element
	int list_size;

    //simple constructor
	LinkedList(){
		head = NULL;
		tail = NULL;
        list_size = 0;
	}
	void push_back(Meme* meme){
        //create new Node and putting data
		Node * new_node = new Node;
		new_node->data = *meme;

        //if list is empty,then we perform push front
		if (head == NULL)
			head = new_node;
		else
        //node, what is pointed by tail, start pointing on new node
			tail->next = new_node;

        // tail points on new node
		tail = new_node;
        // new node points on NULL
		new_node->next = NULL;
		list_size++;

	}
	void push_front(Meme* meme){
        //create new Node and putting data
		Node * new_node = new Node;
		new_node->data = *meme;

        //if list is empty,then we perform push back
		if (head == NULL)
			tail = new_node;
        // new node points on node, what is pointed by head
		new_node->next = head;
        //head points on new node
		head = new_node;
		list_size++;
	}
	Meme pop_back(){
        // if list is empty, then returns empty structure
		if (head == NULL)
			return {};
		Meme old_meme;
		list_size--;
        //if list contains only one element:
		if (head->next == NULL) {
            //remember structure
			old_meme = head->data;
            //free memory
			delete head;
            //default empty list
			head = NULL;
			tail = NULL;
			return old_meme;
		}
		Node* tmp_p = head;
        // finds pre-last node
		while (tmp_p->next->next != NULL)
			tmp_p = tmp_p->next;
        //tail points on pre-last node
		tail = tmp_p;
        //remembers meme
		old_meme = tmp_p->next->data;
        //pre last node points on NULL
		tmp_p->next = NULL;
        //free memory
		delete tmp_p->next;
		return old_meme;
	}
	Meme pop_front(){
        // if list is empty, then return empty structure
		if (head == NULL)
			return {};
        //if list contains only one element, then we need also change a tail
		if (head->next == NULL)
			tail = NULL;
        //remembers structure
		Meme old_meme = head->data;
        //remembers first position to delete it
		Node* tmp_p = head;
        //head points on second node (after-first?)
		head = head->next;
        //free memory
		delete tmp_p;
		list_size--;
		return old_meme;
	}
    Meme get(int n){
        //if n is bigger then number of elements in list, then returns an empty structure
        if (list_size < n)
            return {};
        // going through all elements to the needed one
        Node* tmp_p = head;
        for (int i = 0; i < n; i++)
            tmp_p = tmp_p->next;

        return tmp_p->data;

    }

	int size(){
		return list_size;
	}

	void print(){
		Node* tmp_p = head;
		while (tmp_p != NULL) {
			print_meme(&(tmp_p->data));
			tmp_p = tmp_p->next;
		}
	}
    //simple destructor to free remain (allocating) memory
	~LinkedList(){
		Node* tmp_p = head;
		Node* next_p;
		while (tmp_p != NULL) {
			next_p = tmp_p->next;
			delete tmp_p;
			tmp_p = next_p;
		}
	}
};

Meme generate_meme();

string memplates[4] = {"Doge on steroids", "Drake reaction", "Pepe in depression", "Rich Winnie the Pooh"};
string meme_text[5] ={"the turnstiles", "the new serial on Netflix", "Jacque Fresco", "the Cyberpunk 2077", "a recursion"};

int main() {
	srand(time(NULL));
	LinkedList list;
	Meme some_meme;
    clock_t global_start = clock();

    clock_t local_start = clock();
    //push back 50000 elements
    for (int i = 0; i < 50000; i++) {
        some_meme = generate_meme();
        list.push_back(&some_meme);
    }
    clock_t local_end = clock();
    float seconds = (float(local_end - local_start)) / CLOCKS_PER_SEC;
    cout << "push back (50000) time: " << seconds << endl;

    local_start = clock();
    //push front 10000 elements
    for (int i = 0; i < 10000; i++) {
        some_meme = generate_meme();
        list.push_front(&some_meme);
    }
    local_end = clock();
    seconds = (float(local_end - local_start)) / CLOCKS_PER_SEC;
    cout << "push front (10000) time: " << seconds << endl;

    local_start = clock();
    //get 20000 elements
    for (int i = 0; i < 20000; i++) {
        some_meme = list.get(rand()%60001);
    }
    local_end = clock();
    seconds = (float(local_end - local_start)) / CLOCKS_PER_SEC;
    cout << "get (20000) time: " << seconds << endl;

    local_start = clock();
    //pop front 5000 elements
    for (int i = 0; i < 5000; i++) {
        list.pop_front();
    }
    local_end = clock();
    seconds = (float(local_end - local_start)) / CLOCKS_PER_SEC;
    cout << "pop front (5000) time: " << seconds << endl;

    local_start = clock();
    //pop back 5000 elements
    for (int i = 0; i < 5000; i++) {
        list.pop_back();
    }
    local_end = clock();
    seconds = (float(local_end - local_start)) / CLOCKS_PER_SEC;
    cout << "pop back (5000) time: " << seconds << endl;

    clock_t global_end = clock();
    seconds = (float(global_end - global_start)) / CLOCKS_PER_SEC;
    cout << "linked list time: " << seconds << endl;

	return 0;
}

Meme generate_meme(){
	return {memplates[rand()%4], meme_text[rand()%5], rand()%10001};
}

void print_meme(Meme* meme) {
	if (meme->text == "") {
		cout << "This is very abstract meme without any words" << endl;
		return;
	}
	cout << "Meme with " << meme->memplate;
	cout << " about " << meme->text;
	cout << " gain " << meme->likes;
	cout << " likes" << endl;
}
