#include<iostream>
#include<string>
#include<array>

using namespace std;

// 时间复杂度为O(n平方)
string *deleteItem(string A[], int n, string item){  
    for(int i=0;i<n;i++){
        cout << "begin num n is " << n << endl;
        if(A[i]==item){
            for(int j=i+1;j<n;j++){
                A[j-1] = A[j];
            }
            n = n-1;
        }
        cout << "number n is " << n << endl;
    }
    return A;
}

//优化删除元素，时间复杂度为O(n)
string *deleteItem01(string A[], int n, string item){  
    int m =0;
    for(int i=0;i<n; i++){
        if(A[i]==item){
            m++;
        }else{
            A[i-m]=A[i];
        }
    }
    return A;
}

int main() { 
    string A[6] = {"a","e","c","d","e","f"};
    string item = "e";
    string *sd = deleteItem01(A, 6, item); 
    for(int i=0;i<4;i++){
        cout << sd[i] << endl;
    }
    return 0;
}