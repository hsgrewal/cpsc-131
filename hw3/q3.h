void swizzle() throw(UnderflowException){
  if(_head == NULL || _head->next() == NULL){
    throw UnderflowException();
  }
  else{
    _head->next() = _head->next()->next();
    _head.set_next(_head->next());
    _head->next()->next()->set_prev() = _head->prev();
    _head->next()->set_prev() = _head;
  }
}
