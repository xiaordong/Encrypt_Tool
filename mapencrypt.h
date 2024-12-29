//
// Created by Keith on 24-12-27.
//

#ifndef ENCRYPT_H
#define ENCRYPT_H
#include <string>


class MapEncrypt {
public:
    MapEncrypt(std::string data,int shift):_data(data),_shift(shift){}
    void encrypt();
    std::string getData() const{return _data;}
    void setShift(int shift){_shift=shift;}
    void decrypt();
    std::string  show();
    const std::string& getData(){return _data;}
    int getShift() const {return _shift;}
    void setData(const std::string& data){_data = data;}

    std::string _data;
    int _shift;
};



#endif //ENCRYPT_H
