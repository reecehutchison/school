from abc import ABC, abstractmethod

class PaymentProcessor(ABC):
    """
    Interface for the types of payments.
    """
    
    @abstractmethod
    def makePayment(self) -> None:
        pass


class BankTransfer(PaymentProcessor):
    """
    Bank transfer payment!
    """
    
    def makePayment(self) -> None:
        print("Bank transfer!")


class Cheque(PaymentProcessor):
    """
    Cheque payment!
    """
    
    def makePayment(self) -> None:
        print("Cheque!")


class DigitalWallet(PaymentProcessor):
    """
    Digital wallet payment!
    """
    
    def makePayment(self) -> None:
        print("Digital wallet!")


class PaymentMethodFactory():
    """
    Will create the different types of payment methods.
    """
    
    paymentMethodTypes = {
        "bt": BankTransfer,
        "c": Cheque,
        "dw": DigitalWallet
    }
    
    def createPaymentMethod(self, type: str) -> PaymentProcessor:
        return (self.paymentMethodTypes[type])()


class Employee(ABC):
    """
    Interface that types of employees will implement
    """
    
    def __init__(self, name: str, paymentProcessor: PaymentProcessor):
        self.name = name
        self.paymentProcessor = paymentProcessor
    
    @abstractmethod
    def process_payment(self) -> None:
        pass


class SalariedEmployee(Employee):
    def process_payment(self) -> None:
        self.paymentProcessor.makePayment()


class HourlyEmployee(Employee):
    def process_payment(self) -> None:
        self.paymentProcessor.makePayment()


class Contractor(Employee):
    def process_payment(self) -> None:
        self.paymentProcessor.makePayment()


class App:
    def __init__(self):
        self.AvailPaymentMethods = PaymentMethodFactory()


# test it out!
if __name__ == "__main__":
    app = App()
    
    bankTransfer = app.AvailPaymentMethods.createPaymentMethod("bt")
    cheque = app.AvailPaymentMethods.createPaymentMethod("c")
    digitalWallet = app.AvailPaymentMethods.createPaymentMethod("dw")
    
    alice = SalariedEmployee("Alice", bankTransfer)
    bob = HourlyEmployee("Bob", cheque)
    charlie = Contractor("Charlie", digitalWallet)
    
    alice.process_payment()
    bob.process_payment()
    charlie.process_payment()