#ifndef BYTEARRAY_H
#define BYTEARRAY_H
#include"algorithm"
#include"iostream"
class bytearray
{
public:
    bytearray();
    bytearray(bytearray & byte);
    ~bytearray();

    char * data();
    size_t size();
    size_t capacity();
    void  write(bytearray &byte);
    void  write(char *  byte , size_t size);

    void  appned(char * byte, size_t  size);
    void  appned(bytearray & byte);

    void  reserver(size_t size);
    void  resize(size_t size);
    bool  empty();
    
    void operator=(bytearray & byte);

private:

    bool check_negative_meaning(size_t & size_);
    void update_byte(size_t new_capacity);
    void new_byte(size_t new_capacity);

    char * byte;
    size_t size_;
    size_t capacity_;
    bool   setcapacity;
};

#endif

