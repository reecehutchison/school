from abc import ABC, abstractmethod
from typing import Type


# products and foods!

class Product(ABC):
    """Product is an interface for products to follow. 
    
        Interface will be inherited by all food products. 
    """

    @abstractmethod    
    def __init__() -> None:
        pass
        
    @abstractmethod
    def getPrice(self) -> int:
        pass
    
    @abstractmethod
    def getDescription(self) -> str:
        pass
  
    
class Burger(Product):
    """An interface for burger types.
    
        Burger types will inherit this class!
    """
    
    def __init__(self,
                 price: int,
                 calories: int,
                 description: str, 
                 ) -> None:
        self.price = price
        self.calories = calories
        self.description = description
        
    def getPrice(self) -> int:
        return self.price
    
    def getCalories(self) -> int:         
        return self.calories
    
    def getDescription(self) -> str:
        return self.description
    

class Pizza(Product):
    """An interface for pizza types.
    
        Pizza types will inherit this class!
    """
    
    def __init__(self,
                 price: int,
                 calories: int,
                 description: str, 
                 ) -> None:
        self.price = price
        self.calories = calories
        self.description = description
        
    def getPrice(self) -> int:
        return self.price
    
    def getCalories(self) -> int:         
        return self.calories
    
    def getDescription(self) -> str:
        return self.description
    
    
class Noodles(Product):
    """An interface for noodles types.
    
        Noodles types will inherit this class!
    """
    
    def __init__(self,
                 price: int,
                 calories: int,
                 description: str, 
                 ) -> None:
        self.price = price
        self.calories = calories
        self.description = description
        
    def getPrice(self) -> int:
        return self.price
    
    def getCalories(self) -> int:         
        return self.calories
    
    def getDescription(self) -> str:
        return self.description
    

class VegBurger(Burger):
    """A veg burger.
    
        Tasty!
    """
    
    def __init__(self, 
                 price: int = 0,
                 calories: int = 0, 
                 description: str = "veg burger",  
                 ) -> None: 
        self.price = price
        self.calories = calories
        self.description = description
    
        
class VegPizza(Pizza):
    """A veg pizza.
    
        Excellent!
    """
    
    def __init__(self, 
                 price: int = 0,
                 calories: int = 0, 
                 description: str = "veg pizza",  
                 ) -> None: 
        self.price = price
        self.calories = calories
        self.description = description
      

class VegNoodles(Noodles):
    """A veg noodles.
    
        Mmmmm!
    """
    
    def __init__(self, 
                 price: int = 0,
                 calories: int = 0, 
                 description: str = "veg noodles",  
                 ) -> None: 
        self.price = price
        self.calories = calories
        self.description = description
      
      
class NonVegBurger(Burger):
    """A non veg burger.
    
        Delicious!
    """
    
    def __init__(self, 
                 price: int = 0,
                 calories: int = 0, 
                 description: str = "non veg burger",  
                 ) -> None: 
        self.price = price
        self.calories = calories
        self.description = description
    
        
class NonVegPizza(Pizza):
    """A non veg pizza.
    
        Yummy!
    """
    
    def __init__(self, 
                 price: int = 0,
                 calories: int = 0, 
                 description: str = "non veg pizza",  
                 ) -> None: 
        self.price = price
        self.calories = calories
        self.description = description
      

class NonVegNoodles(Noodles):
    """A non veg noodles.
    
        Terrific!
    """
    
    def __init__(self, 
                 price: int = 0,
                 calories: int = 0, 
                 description: str = "non veg noodles",  
                 ) -> None: 
        self.price = price
        self.calories = calories
        self.description = description
      
      
class NonVegCutlet(Product):
    """A non veg cutlet.
    
        Scrumptious.
    """
    
    def __init__(self,
                 price: int = 0,
                 calories: int = 0,
                 description: str = "non veg cutlet", 
                 ) -> None:
        self.price = price
        self.calories = calories
        self.description = description
        
    def getPrice(self) -> int:
        return self.price
    
    def getCalories(self) -> int:         
        return self.calories
    
    def getDescription(self) -> str:
        return self.description
    
    
# factories 

class ProductFactory(ABC):
    """ The abstract factory.
    
        Interface that the factories will implement. 
    """
    
    @abstractmethod
    def createBurger(self,
                     price, 
                     calories, 
                     description
                     ) -> Burger:
        pass
    
    @abstractmethod
    def createPizza(self,
                    price, 
                    calories, 
                    description
                    ) -> Pizza:
        pass
    
    @abstractmethod
    def createNoodles(self,
                    price, 
                    calories, 
                    description
                    ) -> Noodles:
        pass
    

class VegProductFactory(ProductFactory): 
    """Making tons of veggies and stuffffff. 
    
        Yum and yummier. 
    """
    
    def __init__(self) -> None:
        pass
    
    def createBurger(self,
                     price = 0, 
                     calories = 0,
                     description = "veg burger"
                     ) -> VegBurger:
        return VegBurger(price, calories, description)
    
    def createPizza(self,
                    price = 0, 
                    calories = 0,
                    description = "veg pizza"
                    ) -> VegBurger:
        return VegPizza(price, calories, description)
    
    def createNoodles(self,
                     price = 0, 
                     calories = 0,
                     description = "veg noodles"
                     ) -> VegNoodles:
        return VegNoodles(price, calories, description)
    
    
class NonVegProductFactory(ProductFactory): 
    """Making tons of meats yum! 
    
        Tasty and tastier. 
    """
    
    def __init__(self) -> None:
        pass
    
    def createBurger(self,
                     price = 0, 
                     calories = 0,
                     description = "non veg burger"
                     ) -> NonVegBurger:
        return NonVegBurger(price, calories, description)
    
    def createPizza(self,
                    price = 0, 
                    calories = 0,
                    description = "non veg pizza"
                    ) -> NonVegBurger:
        return NonVegPizza(price, calories, description)
    
    def createNoodles(self,
                     price = 0, 
                     calories = 0,
                     description = "non veg noodles"
                     ) -> NonVegNoodles:
        return NonVegNoodles(price, calories, description)
    
    def createCutlet(self,
                     price = 0, 
                     calories = 0,
                     description = "non veg cutlet"
                     ) -> NonVegCutlet:
        return NonVegCutlet(price, calories, description)
    
    
### client app

class FoodApp: 
    """Food app where you can make orders, and get descriptions. 
    
        Very tasty. 
    """
    availableVegProducts = [
        VegBurger,
        VegPizza,
        VegNoodles
    ]
    
    availableNonVegProducts = [
        NonVegBurger,
        NonVegPizza,
        NonVegNoodles,
        NonVegCutlet
    ]
    
    def __init__(self):
        self.vegFactory = VegProductFactory()
        self.nonVegFactory = NonVegProductFactory()
        
    def makeOrder(self, productsOrdered: list[type]) -> list[Product]:
        def createVegProduct(productType: type):
            if productType == VegBurger:
                return self.vegFactory.createBurger()
            elif productType == VegPizza:
                return self.vegFactory.createPizza()
            elif productType == VegNoodles:
                return self.vegFactory.createNoodles()
            else:
                raise ValueError("Error!")
            
        def createNonVegProduct(productType: type):
            if productType == NonVegBurger:
                return self.nonVegFactory.createBurger()
            elif productType == NonVegPizza:
                return self.nonVegFactory.createPizza()
            elif productType == NonVegNoodles:
                return self.nonVegFactory.createNoodles()
            elif productType == NonVegCutlet:
                return self.nonVegFactory.createCutlet()
            else:
                raise ValueError("Error!")
        
        order = []
        for product in productsOrdered:
            if (product not in self.availableVegProducts 
                and product not in self.availableNonVegProducts):
                raise ValueError("Product not available!")
            elif product in self.availableNonVegProducts:
                order.append(createNonVegProduct(product))
            else:
                order.append(createVegProduct(product))
                

        return order
    
    def getOrderDescription(self, order: list[Product]) -> str: 
        orderDescription = "Products: \n"
        if len(order) < 1:
            orderDescription += "No products in order"
            return orderDescription
        
        for product in order: 
            orderDescription += f"{product.getDescription()}\n"
            
        return orderDescription
    
    
### test run of client

app = FoodApp()

# empty order 
print("\n - Empty order -")
print(app.getOrderDescription([]))
print("\n")

# veg order 
print("- Veg order -")
vegOrder = app.makeOrder([VegBurger, VegNoodles])
print(app.getOrderDescription(vegOrder))
print("")

# non veg order 
print("- Non veg order -")
nonVegOrder = app.makeOrder([NonVegPizza, NonVegCutlet])
print(app.getOrderDescription(nonVegOrder))
print("")

# mixed order 
print("- Mixed order -")
mixedOrder = app.makeOrder([VegPizza, NonVegNoodles])
print(app.getOrderDescription(mixedOrder))
print("")