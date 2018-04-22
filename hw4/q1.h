int maximum(int array[], int n){
  arrert(n >= 1);
  if (n == 1){
    return array[0];
  }
  else{
    if (maximum(array, n-1) > array[n-1]){
      return maximum(array,n-1);
    }
    else{
      return array[n-1];
    }
  }
}
