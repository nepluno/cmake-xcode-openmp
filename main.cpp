#include <iostream>
#include <omp.h>

int main(int argc, const char * argv[]) {
#pragma omp parallel
#pragma omp critical
    std::cout << "Greetings from thread "<<omp_get_thread_num()<<std::endl;
    return 0;
}

