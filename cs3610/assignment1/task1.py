from abc import ABC, abstractmethod
from typing import Type


class Animal(ABC):
    """Animal acts as an interface that animals should inherit from.

        Inheriting classes will need to implement the SAY_SOMETHING()
        method.
    """
    
    @abstractmethod
    def SAY_SOMETHING(self) -> str:
        pass
    
    
class Lion(Animal):
    """Lion is a derived animal class that will roar. 
    
        Lion over-rides the inherited method SAY_SOMETHING() to roar. 
    """
    
    def __init__(self):
        pass
    
    def SAY_SOMETHING(self) -> str:
        return "ROAR!"
    

class Elephant(Animal):
    """Elephant is a derived animal class that will trumpet.

        Elephant over-rides the inherited method SAY_SOMETHING() to trumpet.
    """
    
    def __init__(self):
        pass
    
    def SAY_SOMETHING(self) -> str:
        return "TRUMPET!"
  
    
class Penguin(Animal):
    """Penguin is a derived animal class that will squawk.

        Penguin over-rides the inherited method SAY_SOMETHING() to squawk.
    """
    
    def __init__(self):
        pass
    
    def SAY_SOMETHING(self) -> str:
        return "SQUAWK!"
    
    
class WhiteBear(Animal):
    """White bear is a derived animal class that will grrrrr.

        White bear over-rides the inherited method SAY_SOMETHING() to grrrrr.
    """
    
    def __init__(self):
        pass
    
    def SAY_SOMETHING(self) -> str:
        return "GRRRRR!"
   
    
class GrizzlyBear(Animal):
    """Grizzly bear is a derived animal class that will growl.

        Grizzly bear over-rides the inherited method SAY_SOMETHING() to growl.
    """
    
    def __init__(self):
        pass
    
    def SAY_SOMETHING(self) -> str:
        return "GROWL!"


class Moose(Animal):
    """Moose is a derived animal class that will bellow.

        Moose over-rides the inherited method SAY_SOMETHING() to bellow.
    """
    
    def __init__(self):
        pass
    
    def SAY_SOMETHING(self) -> str:
        return "BELLOW!"


class AnimalFactory:
    """Animal Factory will be used to create and return animals. 
    
        Animal types are immutable after creating the factory.
    """
    
    def __init__(self, animals: list[type]) -> None:
        self.animals = animals
            
    def getAnimals(self) -> list:
        return self.animals
    
    def create(self, animalType: type) -> Animal:
        if animalType not in self.animals:
            raise ValueError(f"{animalType} not able to be made!")
        else:
            return animalType()


class Zoo: 
    """Zoo is an abstract class that zoo will implement.
    
        Derived classes are real zoos!
    """
    
    def __init__(self, ourItinerary: str):
        self.animals = list()
        self.ourItinerary = ourItinerary
        
    @abstractmethod
    def createAnimals(self) -> None:
        pass
    
    def askEachAnimalToSaySomething(self) -> None:
        for animal in self.animals:
            print(animal.SAY_SOMETHING())
            
    def startVisit(self):
        print(self.ourItinerary)
        self.askEachAnimalToSaySomething()


class TorontoZoo(Zoo):
    """Toronto zoo is the Toronto Zoo!
    
        It has lions, elephants, penguins and white bears.
    """
    
    def __init__(self, ourItinerary: str):
        super().__init__(ourItinerary)
        
    def createAnimals(self) -> None:
        animals = [Lion, Elephant, Penguin, WhiteBear]
        torontoAnimalFactory = AnimalFactory(animals)
        
        for animal in torontoAnimalFactory.getAnimals():
            self.animals.append(torontoAnimalFactory.create(animal))
        

class CalgaryZoo(Zoo):
    """Calgary zoo is the Calgary Zoo!
    
        It has grizzly bears, moose, and penguins.
    """
    
    def __init__(self, ourItinerary: str):
        super().__init__(ourItinerary)
        
    def createAnimals(self) -> None:
        animals = [GrizzlyBear, Moose, Penguin]
        calgaryAnimalFactory = AnimalFactory(animals)
        
        for animal in calgaryAnimalFactory.getAnimals():
            self.animals.append(calgaryAnimalFactory.create(animal))
        

# test the classes!
torontoItinerary = "Welcome to the Toronto Zoo! Our Itinerary: 1) African Savanna. 2) Tundra Trek"
calgaryItinerary = "Welcome to the Calgary Zoo! Our Itinerary: 1) Penguin Plunge. 2) Wild Canada"

torontoZoo = TorontoZoo(torontoItinerary)
calgaryZoo = CalgaryZoo(calgaryItinerary)

print("\n ~--~ Toronto Zoo ~--~")
torontoZoo.createAnimals()
torontoZoo.startVisit()
print(" ~-------------------~\n")

print(" ~--~ Calgary Zoo ~--~")
calgaryZoo.createAnimals()
calgaryZoo.startVisit()
print(" ~-------------------~\n")
