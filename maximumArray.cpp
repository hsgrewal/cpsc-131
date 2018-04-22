#include<iostream>
using namespace std;

int maximum(int array[], int n){
  _ASSERT (n >= 1);
  if (n == 1){
    return array[0];
  }
  else{
    if (maximum(array, n - 1) > array[n - 1]){
      return maximum(array, n - 1);
    }
    else{
      return array[n - 1];
    }
  }
}

int main(){
  int arr[5] = { 2, 6, 8, 24, 1 };
  cout << maximum(arr, 5) << endl << endl;
  return 0;
}
