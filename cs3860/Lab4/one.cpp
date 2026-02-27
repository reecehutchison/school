#include <iostream>

using namespace std; 

int main() {
  string inputString;
  int chunkSize; 
  
  cout << "enter a string: "; 
  cin >> inputString;
  cout << "enter n for chunking: ";
  cin >> chunkSize; 

  int i = 0; 
  int n = inputString.length(); 
  vector<string> result;

  while (i < n) {
    string curr = "";
    int k = 0; 

    while (i < n && k < chunkSize) {
      curr += inputString[i]; 
      k++; 
      i++; 
    }

    result.push_back(curr); 
  }

  for (auto str : result) {
    cout << str << " ";
  }
  cout << endl; 
  
  return 0; 
}