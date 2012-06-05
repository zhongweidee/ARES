#include <iostream>
using namespace std;
class A {
  public:
      A(){
      cout<<" call A function"<<endl;
         };
};
class B:public A {
  public:
      B(){
      cout<<" call B function"<<endl;
         };
};

int main(void){
    B b;
}
