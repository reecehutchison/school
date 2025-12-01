from abc import ABC, abstractmethod


class CompanyComponent(ABC):
    """
        Will act as an interface to represent the different objects in 
        the company.
    """
    
    @abstractmethod
    def getSalary(self) -> int:
        pass
    
    @abstractmethod
    def doOperation(self) -> None:
        pass
    

class Employee(CompanyComponent):
    """
        Represents the employees at the company. Will be part of departments.
    """
    
    def __init__(self, name: str, salary: int):
        self.name = name
        self.salary = salary
        
    def getSalary(self):
        return self.salary
    
    def doOperation(self, op: str) -> None:
        print(f"{self.name} is doing {op}")
        
    
class Department(CompanyComponent): 
    """
        The department will serve as a group of employees.
    """
    
    def __init__(self, name: str):
        self.name = name
        self.employees: list[CompanyComponent] = []
        
    def getSalary(self) -> int:
        totalSalary = 0
        for employee in self.employees:
            totalSalary += employee.getSalary()
            
        return totalSalary
    
    def doOperation(self, op: str) -> None:
        print(f"{self.name} is doing {op}")
        
    def addEmployee(self, emp: Employee):
        self.employees.append(emp)


# test it all out
if __name__ == "__main__":
    dep1 = Department("Department1")
    dep2 = Department("Department2")
    
    emp1 = Employee("Bob", 60000)
    emp2 = Employee("Alice", 70000)
    emp3 = Employee("Greg", 80000)
    
    dep1.addEmployee(emp1)
    dep1.addEmployee(emp2)
    dep2.addEmployee(emp3)
    
    print("\nStuff about the company:\n")
    
    print(f"Department 1's employees make: {dep1.getSalary()}")
    print(f"Greg is making: {emp3.getSalary()}")
    
    emp1.doOperation("Research and Development")
    dep2.doOperation("Marketing")
    
    print()