class VendingMachine:
    def __init__(self, name, cost):
        self.snack = name
        self.price = cost
        self.amount = 0
        self.balance = 0

    def vend(self):
        if self.amount == 0:
            return 'Machine is out of stock.'
        elif self.balance < self.price:
            return 'You must deposit ${0} more.'.format(self.price - self.balance)
        elif self.balance == self.price:
            self.amount -= 1
            self.balance = 0
            return 'Here is your {0}.'.format(self.snack)
        else:
            temp = self.balance
            self.balance = 0
            self.amount -= 1
            return 'Here is your {0} and ${1} change.'.format(self.snack, temp - self.price)

    def deposit(self, money):
        assert money > 0
        if self.amount == 0:
            return 'Machine is out of stock. Here is your ${0}.'.format(money)
        else:
            self.balance += money
            return 'Current balance: ${0}'.format(self.balance)

    def restock(self, add):
        assert add > 0
        self.amount += add
        return 'Current {0} stock: {1}'.format(self.snack, self.amount)