template <typename ELT>
class Maybe{
  public:
    Maybe(){
      _element = NULL;
    }
    bool is_empty(){
      if (_element == NULL){
        return true;
      }
      else{
        return false;
      }
    }
    void set(ELT element){
      _element = element;
    }
    ELT get(){
      return _element;
    }

  private:
    ELT _element;
}
