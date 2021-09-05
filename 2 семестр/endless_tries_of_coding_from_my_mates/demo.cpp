#include <iostream>

int main() {
//
    sravnenie(a1,s1,a2,s2, result, &r_size);
    sravnenie(a2,s2,a1,s1, result, &r_size);
    vivid(result);
    return 0;
}


void sravnenie(man* arr1, int cout1, man* arr2, int count2, man* result, int* size){
    int condition_2223;
    for (int i = 0; i < count1; i++) {
        condition_2223 = 1;
        for (int j = 0; j < count2; j++) {
            // if (arr1[i] == arr2[j]) {
            if(arr1[i].surname == arr2[j].surname && arr1.field2 == arr2.field2){
                condition_2223 = 0;
                break;
            }
        }

        if (condition_2223 == 1) {
            // cout<<
            result[size] = arr[i];
            (*size)++;
        }
    }
}
