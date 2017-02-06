#ifndef PROXY_H
#define PROXY_H

#include <stdlib.h>
#include <iostream>

class Proxy{
    public:
        Proxy(double* array);
        double operator[](int index) const;
        double& operator[](int index);
    private:
        double* array;
};

#endif //PROXY_H
