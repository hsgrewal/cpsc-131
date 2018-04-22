void remove_back() throw(UnderflowException){
  if (is_empty()){
    throw UnderflowException();
  }
  else{
    SNode <ELT> *left, *right;
    right = _head;
    while (right != NULL){
      SNode <ELT> *righter = right->next();
      left = right;
      right = righter;
    }
    delete left;
    left = right;
  }
}
