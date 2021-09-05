#include <iostream>
#include <algorithm>

using namespace std;

char **split(int &n, char *input);
void copy(char *dst, char *src);
int len(char *string);
void print_string(int *mask, char **strings, int n);

int main()
{
	char *input = new char[100];
	cout << "Введіть слова через нижнє підкреслювання:" << endl;
	cin >> input;
	int n;
	//array of words splited by underscore
	char **words = split(n, input);
	//mask of permutations
	int *mask = new int[n];
	for (int i = 0; i < n; i++)
		mask[i] = i;

	//permutate and cout all possible combinations of words via some STL function
	cout << "Всі можливі перестановки даних слів:" << endl;

	do
	{
		print_string(mask, words, n);
	} while (next_permutation(mask, mask + n));

	// free alllocating memory
	delete[] input;
	for (int i = 0; i < n; i++)
		delete[] words[i];

	delete[] words;
	delete[] mask;
	return 0;
}

char **split(int &n, char *input)
{
	int length = len(input);
	n = 0;
	// counts number of words in input string
	for (int i = 0; i < length; i++)
		if (input[i] == '_')
			n++;
	//allocate memory for all words
	char **words = new char *[++n];
	int words_number = 0;
	//prev_index is the index of the last underscore
	int prev_index = -1;
	//go across all symbols in string
	for (int i = 0; i <= length; i++)
	{
		//if we find underscore or the end of string, then we add new word
		if (input[i] != '_' && input[i] != '\0')
			continue;
		//allocates memory for each word
		words[words_number] = new char[i - prev_index];
		//add all symbols starting from the last underscore index
		for (int j = 0; j + 1 < i - prev_index; j++)
			words[words_number][j] = input[prev_index + j + 1];

		// ends our word
		words[words_number][i - prev_index] = '\0';
		//relocate our prev_index on new underscore
		prev_index = i;
		//increases number of words
		words_number++;
	}
	return words;
}

int len(char *string)
{
	int size = 0;
	//increasing our length until we found '\0' - end of string
	while (string[size] != '\0')
		size++;
	return size;
}

void print_string(int *mask, char **strings, int n)
{
	for (int i = 0; i < n; i++)
	{
		if (i != 0)
			cout << "_";

		cout << strings[mask[i]];
	}
	cout << endl;
}
