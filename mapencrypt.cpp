//
// Created by Keith on 24-12-27.
//

#include "MapEncrypt.h"


void MapEncrypt::encrypt()  {
    std::string output = _data;
    for(size_t i = 0; i < _data.size(); ++i) {

        if(isalpha(_data[i])) {
            char base = islower(_data[i]) ? _data[i] : toupper(_data[i]);
            output[i] = (_data[i]-base+getShift())%26+base;
        }
        else if(isdigit(_data[i])) {
            output[i] = (_data[i]-'0'-getShift())%10+'0';
        }
    }
    setData(output);
}
void MapEncrypt::decrypt() {
    setShift(24-getShift());
    encrypt();
}
std::string MapEncrypt::show() {
    return _data;
}

