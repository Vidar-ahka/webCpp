#include"bytearray.h"

bytearray::bytearray()
{
    this->byte      = nullptr;
    this->capacity_ = 0;
    this->size_     = 0;
    this->setcapacity = false;

}
bytearray::bytearray(bytearray & byte)
{
    this->write(byte);
}
bytearray::~bytearray()
{
    if(byte !=nullptr)
    {
        delete [] byte;
    } 
}
    

void  bytearray::appned(bytearray & byte)
{
    appned(byte.data(),byte.size_);
}
void  bytearray::appned(char * byte, size_t  size)
{
    if(size == 0 && !check_negative_meaning(size))
    {
        return;
    }
   
    size_t new_size = size_+size;

    if(new_size>capacity_)
    {
        this->capacity_  = new_size+new_size/2;    
        update_byte(this->capacity_);
    }
    else if(setcapacity)
    {
        update_byte(this->capacity_);
        setcapacity  = false;
    }

    std::copy(byte , byte+size , this->byte+size_);

    this->size_ = new_size;  

}
void  bytearray::write(char *  byte , size_t size)
{   
    if(size == 0 && !check_negative_meaning(size))
    {
        return;
    }
    else if(size>capacity_)
    {
        this->capacity_ = size+size/2;
        new_byte(this->capacity_);
    }
    else if(setcapacity)
    {
        new_byte(this->capacity_);
        setcapacity = false;
    }
    std::copy(byte,byte+size,this->byte);
    this->size_ = size;
}

void  bytearray::reserver(size_t size)
{
    if(!check_negative_meaning(size))
    {
        size = 0;
    }
    if(size<size_)
    {
        this->byte[size] =  this->byte[size_];
        this->size_ = size;    
        this->setcapacity = true;
    }
    else if(byte == nullptr)
    {
        byte = new char[size];
        this->size_ = size/4;
    }
    else 
    {
        this->setcapacity = true;
    }
    this->capacity_ = size;
}



void  bytearray::write(bytearray &byte)
{
    if(byte.empty())
    {
        return ;
    }
    this->write(byte.byte, byte.size_);
}

void  bytearray::resize(size_t size)
{
    
    if(!check_negative_meaning(size))
    {
        size = 0;
    }    
    if(byte == nullptr)
    {
        byte =  new char[size+size/2];
    }
    if(size>size_)
    {
        if(size>capacity_)update_byte(size + size/2);
        while(size_<size)
        {
            byte[size_++] = '0';
        }
    }
    else 
    {
        this->byte[size] = this->byte[size_];
        this->size_  = size;
    }

}

void bytearray::update_byte(size_t new_capcity)
{
    char * arr = new char[new_capcity];
    std::copy(byte,byte +(new_capcity>size_ ? size_: new_capcity),arr);
    if(byte != nullptr )delete [] byte;
    byte = arr;
}
void bytearray::new_byte(size_t  new_capacity)
{
    if(this->byte != nullptr) delete [] this->byte;
    this->byte = new char[new_capacity];
}
void bytearray::operator=(bytearray & byte)
{
    this->write(byte);
}

bool  bytearray::empty()
{
    return byte == nullptr || size_== 0;
}

bool bytearray::check_negative_meaning(size_t & size_)
{
    return size_!=static_cast<size_t>(-1);
}

char * bytearray::data()
{
    
    return byte;
}
size_t bytearray::size()
{
    return size_;
}
size_t bytearray::capacity()
{
    return capacity_;
}
