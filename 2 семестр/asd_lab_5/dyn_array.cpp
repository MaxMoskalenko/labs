#include <iostream>
#include <ctime>

using namespace std;

struct Meme
{
	string memplate;
	string text;
	int likes;
};

Meme generate_meme();
void print_meme(Meme *meme);

struct DynamicArray
{
	Meme *array;
	int length; // length shows how many elements we have in array
	int cap;

	// cap show current max size of our array
	DynamicArray(int capacity)
	{										//constructor of array
		cap = capacity <= 0 ? 1 : capacity; // if start capacity lower or equal to zero make it equals to 1
		if (capacity <= 0)
		{
			cap = 1;
		}
		else
		{
			cap = capacity;
		}
		array = new Meme[cap];
		length = 0;
	}

	void push_back(Meme *meme)
	{
		//add value to array
		array[length] = *meme;

		length++;
		// if we need more space for future pushes, then extend our array
		if (length == cap)
			extend_array();
	}
	void push_front(Meme *meme)
	{
		// if we need more space for future pushes, then extend our array
		if (length == cap)
			extend_array();

		for (int i = length - 1; i >= 0; i--)
			array[i + 1] = array[i];

		//add value to array
		array[0] = *meme;
		//if front and back points on the same location we should move both of them

		length++;
	}
	Meme pop_back()
	{
		// if back equals to -1, then it starts to point on the end of array
		//pin structure to return
		if (length == 0)
			return {};

		Meme meme = array[length - 1];
		length--;
		//if it was last element, back and front returns to default
		return meme;
	}

	Meme pop_front()
	{
		if (length == 0)
			return {};
		//pin structure to return
		Meme meme = array[0];
		for (int i = 0; i < length; i++)
			array[i] = array[i + 1];
		length--;

		return meme;
	}

	void print()
	{
		for (int i = 0; i < length; i++)
			//prints all elements of array starting from front+1
			print_meme(&array[i]);
	}
	Meme get(int n)
	{
		//get n element starting from front+1
		Meme meme = array[n];
		return meme;
	}
	int size()
	{
		return length;
	}

	void extend_array()
	{
		//increase capacity in 2 times
		cap *= 2;
		//allocating memory for new array
		Meme *new_array = new Meme[cap];
		//copy elements from old array to the new one
		relocate_elements(new_array);
		// free memory, which was allocating for the old array
		delete[] array;
		//old array points on the new version of it
		array = new_array;
	}
	void relocate_elements(Meme *new_array)
	{
		//copy all elements from front+1 index to 0 index
		for (int i = 0; i < length; i++)
			//cap/2 because we need old memory size
			new_array[i] = array[i];
		//actualy back is length of array and front is -1
	}
};

string memplates[4] = {"Doge on steroids", "Drake reaction", "Pepe in depression", "Rich Winnie the Pooh"};
string meme_text[5] = {"the turnstiles", "the new serial on Netflix", "Jacque Fresco", "the Cyberpunk 2077", "a recursion"};

int main()
{
	srand(time(NULL));
	DynamicArray endless_memes(10);
	Meme some_meme;

	clock_t global_start = clock();

	clock_t local_start = clock();
	//push back 50000 elements
	for (int i = 0; i < 50000; i++)
	{
		some_meme = generate_meme();
		endless_memes.push_back(&some_meme);
	}
	clock_t local_end = clock();
	float seconds = (float(local_end - local_start)) / CLOCKS_PER_SEC;
	cout << "push back (50000) time: " << seconds << endl;

	local_start = clock();
	//push front 10000 elements
	for (int i = 0; i < 10000; i++)
	{
		some_meme = generate_meme();
		endless_memes.push_front(&some_meme);
	}
	local_end = clock();
	seconds = (float(local_end - local_start)) / CLOCKS_PER_SEC;
	cout << "push front (10000) time: " << seconds << endl;

	local_start = clock();
	//get 20000 elements
	for (int i = 0; i < 20000; i++)
	{
		some_meme = endless_memes.get(rand() % 60001);
	}
	local_end = clock();
	seconds = (float(local_end - local_start)) / CLOCKS_PER_SEC;
	cout << "get (20000) time: " << seconds << endl;

	local_start = clock();
	//pop front 5000 elements
	for (int i = 0; i < 5000; i++)
	{
		endless_memes.pop_front();
	}
	local_end = clock();
	seconds = (float(local_end - local_start)) / CLOCKS_PER_SEC;
	cout << "pop front (5000) time: " << seconds << endl;

	local_start = clock();
	//pop back 5000 elements
	for (int i = 0; i < 5000; i++)
	{
		endless_memes.pop_back();
	}
	local_end = clock();
	seconds = (float(local_end - local_start)) / CLOCKS_PER_SEC;
	cout << "pop back (5000) time: " << seconds << endl;

	clock_t global_end = clock();
	seconds = (float(global_end - global_start)) / CLOCKS_PER_SEC;
	cout << "dynamic array time: " << seconds << endl;
	// free memory, which was allocating for the dynamic array
	delete[] endless_memes.array;

	return 0;
}

Meme generate_meme()
{
	return {memplates[rand() % 4], meme_text[rand() % 5], rand() % 10001};
}

void print_meme(Meme *meme)
{
	cout << "Meme with " << meme->memplate;
	cout << " about " << meme->text;
	cout << " gain " << meme->likes;
	cout << " likes" << endl;
}
