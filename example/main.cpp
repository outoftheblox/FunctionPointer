using namespace std;

#include <iostream>
#include "../src/FunctionPointer.h"

void isr(){
    cout << "ISR" << endl;
}

int main(){
    auto fn = FunctionPointer<void()>([&]
    {
        isr();
    });
    fn();
}
