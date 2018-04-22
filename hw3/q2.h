void drop_front(int k) throw(ArgumentException, UnderflowException){
  if(k < 0){
    throw ArgumentException();
  }
  else{
    for(int i = 0; i < k; i++){
      if(_head == NULL){
        throw UnderflowException();
      }
      else{
        SinglyLinkedNode<ELEMENT>* new_head = _head->next();
        _head->next();
        delete _head;
        _head = new_head;
      }
    }
  }
}
