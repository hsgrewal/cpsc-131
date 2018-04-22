class GiftCard{
  public:
    GiftCard(int balance){
      _balance = balance;
      _active = true;
    }
    int getBalance(){return _balance}
    bool getActive(){return _active}
    void freeze() throw(CardInactiveException){
      if (!_active){
        throw CardInactiveException;
      }
      else{
        _active = false;
      }
    }
    void deposit(int amountDeposit)
    throw(CardInactiveException, InvalidAmountExpection){
      if (!_active){
        throw CardInactiveException;
      }
      else if (amountDeposit<0){
        throw InvalidAmountExpection;
      }
      else{
        _balance += newDeposit;
      }
    }
    void spend(int amountSpent)
    throw(CardInactiveException, InvalidAmountExpection, OverdrawException){
      if (!_active){
        throw CardInactiveException;
      }
      else if (amountSpent < 0){
        throw InvalidAmountExpection;
      }
      else if (amountSpent > _balance){
        throw OverdrawExpection;
      }
      else{
        _balance -= amountSpent;
      }
    }

  private:
    int _balance;
    bool _active;
}

class CardInactive{
  public:
    cout << "ERROR: GiftCard is inactive.\n";
}

class InvalidAmount{
  public:
    cout << "ERROR: Invalid amount entered. " <<
    "Amount must be greater than or equal to 0.\n";
}

class OverdrawCard{
  public:
    cout << "ERROR: Amount entered will overdraw card. " <<
    "Enter different amount.\n";
}
