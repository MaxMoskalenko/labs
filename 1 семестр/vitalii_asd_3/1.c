#include <stdio.h>
#include <math.h>

int getWeigth(int digit) {

  int x = 1;
  int y = 10;
  float sum = 0;
  while (digit / x != 0) {
    sum += (digit % y) / x;
    x *= 10;
    y *= 10;
  }

  return sum;
}

void sort(int size, int arr[], int weigths[]) {
   int a;
  for (int k = 0; k < size - 1 ; k++) {
    for (int i = 0; i < size -1 - k; i++) {
      if (weigths[i] > weigths[i+1]) {
        a = arr[i+1];
        arr[i+1] = arr[i];
        arr[i] = a;

        a = weigths[i+1];
        weigths[i+1] = weigths[i];
        weigths[i] = a;
      } else if (weigths[i] == weigths[i+1]) {
        if (arr[i] > arr[i+1]) {
          a = arr[i+1];
          arr[i+1] = arr[i];
          arr[i] = a;
        }
      }
    }
  }
}

int main(void) {
  int arr[] = {123, 0, 1245, 100, 10000, 213, 324243};

  int size = sizeof(arr) / sizeof(int);

  int weigths[size];


  for (int i = 0; i < size; ++i) {
    weigths[i] = getWeigth(arr[i]);
  }

  printf("Unsorted arr:\n");
  for (int i = 0; i < size; ++i) {
    printf("%d ", arr[i]);
  }
  printf("\n");

  sort(size, arr, weigths);

  printf("Sorted arr:\n");
  for (int i = 0; i < size; ++i) {
    printf("%d ", arr[i]);
  }
  printf("\n");


  return 0;
}
