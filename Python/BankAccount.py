'''Ryan Paulsen
May 30, 2012'''

class BankAccount():
    'bank account class'
    def __init__(self, balance=0):
        'initialize balance, default is 0'
        self.balance = balance

    def withdraw(self, amount=0):
        'subtract from the balance'
        self.balance -= amount

    def deposit(self, amount=0):
        'add to the balance'
        self.balance += amount

    def balance(self):
        'print the balance'
        print(self.balance)


def test():
    a = BankAccount(500)
    assert a.balance == 500
    a.withdraw(300)
    assert a.balance == 200
    a.deposit(20)
    assert a.balance == 220
