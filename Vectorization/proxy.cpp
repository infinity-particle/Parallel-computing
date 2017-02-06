#include "proxy.h"

Proxy::Proxy(double* array) : array(array){

}

double Proxy::operator [](int index) const{
    return *(array + index);
}

double& Proxy::operator [](int index){
    return *(array + index);
}
