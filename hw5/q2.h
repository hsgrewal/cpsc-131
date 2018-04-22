int main() {                // using fixedstack template on GitHub
  const int COUNT = 5;
  int x;
  FixedStack<int> fixed(COUNT);   // Creates empty stack.
  do{                       // do loop for populating
    cout << "Enter a value for x: ";  // stack with values from user
    cin >> x;
    if (x > 0){
      fixed.push(x);
    }
    else if (x < 0){
      cout << " " << fixed.peek();
      fixed.pop();
    }
  }while (x != 0);

  while (!fixed.is_empty()){
    cout << " " << fixed.peek();
    fixed.pop();
  }

  cout << endl << endl;
  return 0;
}
