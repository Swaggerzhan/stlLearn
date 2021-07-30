#include "simple_allocator.h"
#include <vector>

using std::vector;


int main() {
    int a[5] = {1, 2, 3, 4, 5};
    vector<int, MyAllocator::allocator<int> > test(a, a+5);
    for (int tmp : test){
        std::cout << tmp << " ";
    }
    std::cout << std::endl;
}
