#include <iostream>
using namespace std; 
  
string * reverse(string A[] , int n){
    for(int i=0;i< n/2;i++){ 
        string temp = A[i];
        A[i] = A[n-i-1];
        A[n-i-1] = temp;
    }
    return A;
}

int main(int argc, const char** argv) {
    string A[5] = {"a1","a2","a3","a4","a5"};
    string *end = reverse(A, 5); 
    for(int i=0;i<5;i++){
        cout << end[i] << endl;
    }
    return 0;
}