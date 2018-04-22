class GiftCard{
  public:
    GiftCard(int balance){
      _balance = balance;
      _active = true;
    }
    int getBalance(){return _balance}
    bool getActive(){return _active}
    void freeze(){
      assert (_active);
      _active = false;
    }
    void deposit(int amountDeposit){
      assert (_active);
      assert (amountDeposit > 0);
      _balance += newDeposit;
    }
    void spend(int amountSpent){
      assert (_active);
      assert (amountSpent > 0);
      assert (amountSpent < _balance);
      _balance -= amountSpent;
    }

  private:
    int _balance;
    bool _active;
}
