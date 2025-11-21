from abc import ABC, abstractmethod


class Customer:
    """Represents a customer object.
    """
    
    def __init__(self,
                 firstName: str,
                 middleName: str,
                 lastName: str,
                 primaryEmail: str,
                 secondaryEmail: str,
                 primaryMobileNumber: str,
                 secondaryMobileNumber: str
    ) -> None:
        self.firstName = firstName
        self.middleName = middleName
        self.lastName = lastName
        self.primaryEmail = primaryEmail
        self.secondaryEmail = secondaryEmail
        self.primaryMobileNumber = primaryMobileNumber
        self.secondaryMobileNumber = secondaryMobileNumber
        
    def __str__(self):
        result = "Customer details:\n"
        for key, value in self.__dict__.items():
            if not value:
                continue
            
            result += f"{key}: {value}\n"
        
        return result

class CustomerBuilder(ABC):
    """ This customer builder will act as an interface for the 
        web app and mobile app for their customer builders.
    """
    
    @abstractmethod
    def firstName(self, val: str):
        pass
    
    @abstractmethod
    def lastName(self, val: str):
        pass
    
    # not required in both apps
    def middleName(self, val: str):
        pass
    
    @abstractmethod
    def primaryEmail(self, val: str):
        pass
    
    # not required in both apps
    def secondaryEmail(self, val: str):
        pass
    
    @abstractmethod
    def primaryMobileNumber(self, val: str):
        pass
    
    # not required in both apps
    def secondaryMobileNumber(self, val: str):
        pass
    
    @abstractmethod
    def build(self) -> Customer:
        pass
    
    
class WebCustomerBuilder(CustomerBuilder):
    """Builder class used for the web app. 
    """
    
    def __init__(self):
        self._firstName = None
        self._middleName = None
        self._lastName = None
        self._primaryEmail = None
        self._secondaryEmail = None
        self._primaryMobileNumber = None
        self._secondaryMobileNumber = None
        
    def firstName(self, val: str):
        self._firstName = val
        return self
        
    def middleName(self, val: str):
        self._middleName = val
        return self
    
    def lastName(self, val: str):
        self._lastName = val
        return self
        
    def primaryEmail(self, val: str):
        self._primaryEmail = val
        return self
        
    def secondaryEmail(self, val: str):
        self._secondaryEmail = val
        return self
        
    def primaryMobileNumber(self, val: str):
        self._primaryMobileNumber = val
        return self
        
    def secondaryMobileNumber(self, val: str):
        self._secondaryMobileNumber = val
        return self
        
    def build(self) -> Customer:
        return Customer(
            self._firstName,
            self._middleName,
            self._lastName,
            self._primaryEmail,
            self._secondaryEmail,
            self._primaryMobileNumber,
            self._secondaryMobileNumber
        )
        
        
class MobileCustomerBuilder(CustomerBuilder):
    """Builder class used for the mobile app. 
    """
    
    def __init__(self):
        self._firstName = None
        self._lastName = None
        self._primaryEmail = None
        self._primaryMobileNumber = None
        
    def firstName(self, val: str) -> None:
        self._firstName = val
        return self
    
    def lastName(self, val: str) -> None:
        self._lastName = val
        return self
        
    def primaryEmail(self, val: str) -> None:
        self._primaryEmail = val
        return self
        
    def primaryMobileNumber(self, val: str) -> None:
        self._primaryMobileNumber = val
        return self
        
    def build(self) -> Customer:
        return Customer(
            self._firstName,
            None,
            self._lastName,
            self._primaryEmail,
            None,
            self._primaryMobileNumber,
            None
        )
        

# test the builders!

print("\n- web builder -")
webBuilder = WebCustomerBuilder()
webCustomer = (webBuilder
               .firstName("Reece")
               .middleName("Adan")
               .lastName("Hutchison")
               .primaryEmail("abc@gmail.com")
               .secondaryEmail("cba.@gmail.com")
               .primaryMobileNumber("123456789")
               .secondaryMobileNumber("987654321")
               .build())
print(f"{webCustomer}")

print("- mobile builder -")
webBuilder = WebCustomerBuilder()
webCustomer = (webBuilder
               .firstName("Reece")
               .lastName("Hutchison")
               .primaryEmail("abc@gmail.com")
               .primaryMobileNumber("123456789")
               .build())
print(f"{webCustomer}")