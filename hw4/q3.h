void decimate() throw(UnderflowException){
  if(_head != NULL){
    SNode <ELT> *new_head = _head->next();
    delete _head;
    _head = new_head;
    decimate();
  }
}
