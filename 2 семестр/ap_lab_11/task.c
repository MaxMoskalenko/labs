#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int n = 10;
//some random words from well-known "Lorem ipsum" text
char words[30][20] = {"lorem", "ipsum", "dolor", "sit", "amet", "consectetur", "adipiscing", "elit", "sed", "do", "eiusmod", "tempor", "incididunt", "ut", "labore", "et", "dolore", "magna", "aliqua", "nisl", "tincidunt", "eget", "nullam", "non", "quis", "hendrerit", "dolor", "magna", "eget", "est"};

void fill_array(char **arr);
void print_array(char **arr);
void delete_odd(char **arr);
void reverse_words(char **arr);
int len(char *string);
void copy(char *dst, char *src);

int main()
{
	srand(time(NULL));
	//allocating memory for 2d array of chars
	char **S = (char **)malloc(n * sizeof(char *));
	//fill our array with some stuff
	fill_array(S);
	printf("Before permutations:\n");
	print_array(S);
	//performing main task: delete strings with odd length and reverse all others
	delete_odd(S);
	reverse_words(S);

	printf("---------\n");
	print_array(S);

	//free previously allocating memory
	for (int i = 0; i < n; i++)
	{
		free(S[i]);
	}
	free(S);

	return 0;
}

void fill_array(char **arr)
{
	for (int i = 0; i < n; i++)
	{
		//allocating memory for each string in array (20 symbols)
		arr[i] = (char *)malloc(20 * sizeof(char));
		//making copy of existing string and not pointing on it
		copy(arr[i], words[rand() % 30]);
	}
}

void print_array(char **arr)
{
	for (int i = 0; i < n; i++)
		if (len(arr[i]) > 0)
			printf("%s\n", arr[i]);
}

void delete_odd(char **arr)
{
	//if length of string divides on 2 with reminders - this length is odd
	for (int i = 0; i < n; i++)
		if (len(arr[i]) % 2 == 1)
			copy(arr[i], "");
}

void reverse_words(char **arr)
{
	for (int i = 0; i < n; i++)
	{
		int length = len(arr[i]);
		//if it`s no string - nothing to reverse
		if (length == 0)
			continue;

		char new_string[length];
		//reverse by each symbol
		for (int j = 0; j < length; j++)
			new_string[j] = arr[i][length - j - 1];

		//end reversed string in usuall (for strings in C) way
		new_string[length] = '\0';
		//making copy of existing string and not pointing on it
		copy(arr[i], new_string);
	}
}

int len(char *string)
{
	int size = 0;
	//increasing our length until we found '\0' - end of string
	while (string[size] != '\0')
		size++;
	return size;
}

void copy(char *dst, char *src)
{
	//creating independent copy of string
	int i = 0;
	for (i = 0; i < len(src); i++)
		dst[i] = src[i];
	dst[i] = '\0';
}
