#include <iostream>
using namespace std;

class Aa {
public:
    int a;
};
class Ab {
public:
    int num = 8;
    void change(int*b) {
        *b = 10;
    }
};


int main(int argc, char const *argv[])
{
    Ab a;
    int value = a.num;
    cout << "Value before change: " << value << endl;
    a.change(&value);
    return 0;
}
