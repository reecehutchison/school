import csv
import json
import xml.etree.ElementTree as ET
from io import StringIO
from abc import ABC, abstractmethod

class TaxCollector:
    """
        Tax collector mocks csv. 
    """
    
    def getTaxInfo(self) -> str: 
        return """
Field,Value
TaxRate,0.25
Income,120000.34
Deductions,10000.25
        """.strip()
        
        
class AccountingModule:
    """
        Accounting module mocks xml. 
    """
    
    def getAccountingInfo(self) -> str:
        return """
<account>
    <id>123</id>
    <balance currency="USD">3900.12</balance>
    <status>1</status>
</account>
        """.strip()
        
        
class CreditAuthorizationService:
    """
        Credit authorization service mocks the json.
    """
    
    def getCreditAuth(self) -> str:
        return """
{
    "user_id": "321",
    "credit": 655,
    "risk": "Low",
    "max_loan_amount": 25000.00
}
        """.strip()
        

class DataAdaptor(ABC):
    """
        Interface for adaptors.
    """
    
    @abstractmethod
    def getJsonData(self) -> str:
        pass


class CsvAdaptor(DataAdaptor):
    """
        csv format to json format.
    """
    
    def getJsonData(self, csvData: str) -> str:
        reader = csv.DictReader(StringIO(csvData))
        rows = list(reader)
        
        result = {}
        for row in rows:
            field = row.get("Field", "")
            value = row.get("Value", "")
            
            try:
                result[field] = float(value)
            except ValueError:
                result[field] = value
        
        return json.dumps(result)


class XmlAdaptor(DataAdaptor):
    """
        xml format to json format.
    """
    
    def getJsonData(self, xmlData: str) -> str:
        root = ET.fromstring(xmlData)
        
        result = {}
        for child in root:
            key = child.tag
            value = child.text
            
            if len(child.attrib) > 0:
                result[key] = value
                for attrName, attrValue in child.attrib.items():
                    result[key + "_" + attrName] = attrValue
            else:
                try:
                    result[key] = float(value)
                except ValueError:
                    result[key] = value
        
        return json.dumps(result)

class JsonAdaptor(DataAdaptor):
    """
        json format to json format. 
    """
    
    def getJsonData(self, jsonData: str) -> str:
        return jsonData


class ForecastingFinanceModule:
    """
        Client that uses the json.
    """
    
    def generateReport(self, jsonDataList: list) -> None:
        print("Financial Report\n")
        
        for jsonData in jsonDataList:
            data = json.loads(jsonData)
            print(f"{json.dumps(data)}\n")
           
            
# using the adaptors 
if __name__ == "__main__":
    taxCollector = TaxCollector()
    accountingModule = AccountingModule()
    creditService = CreditAuthorizationService()
    
    csvAdaptor = CsvAdaptor()
    xmlAdaptor = XmlAdaptor()
    jsonAdaptor = JsonAdaptor()
    
    taxData = taxCollector.getTaxInfo()
    accountData = accountingModule.getAccountingInfo()
    creditData = creditService.getCreditAuth()
    
    jsonTaxData = csvAdaptor.getJsonData(taxData)
    jsonAccountData = xmlAdaptor.getJsonData(accountData)
    jsonCreditData = jsonAdaptor.getJsonData(creditData)
    
    forecastingModule = ForecastingFinanceModule()
    forecastingModule.generateReport([jsonTaxData, jsonAccountData, jsonCreditData])