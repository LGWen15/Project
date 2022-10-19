#include <iostream>
using std::cout;
using std::exit;

#include "string.h" // include definition of class String

string::string()
    : bx(),
    mySize(0),
    myRes(15)
{
}

string::string(const char* const ptr, const size_type count)
    : bx(),
    mySize(0),
    myRes(15)
{
    if (count < 16) {
        bx.ptr = nullptr;
    }
    else {
        for (myRes; count > myRes; myRes += 16);

        bx.ptr = new value_type[myRes]();
    }
    for (int i = 0; i < count; i++) {
        myPtr()[i] = ptr[i];
    }
    mySize = count;
}

string::string(const size_type count, const char ch)
    : bx(),
    mySize(0),
    myRes(15)
{
    if (count < 16) {
        bx.ptr = nullptr;
    }
    else {
        for (myRes; count > myRes; myRes += 16);

        bx.ptr = new value_type[myRes]();
    }
    for (int i = 0; i < count; i++) {
        myPtr()[i] = ch;
    }
    mySize = count;
}

string::string(const string& right)
    : bx(),
    mySize(0),
    myRes(15)
{
    assign(right);
}

string::~string()
{
    if (myRes > 15)
        delete[] bx.ptr;
}

string::value_type* string::myPtr()
{
    if (myRes < 16)
        return bx.buf;
    else
        return bx.ptr;
}

const string::value_type* string::myPtr() const
{
    if (myRes < 16)
        return bx.buf;
    else
        return bx.ptr;
}

string& string::assign(const string& right)//right=str2
{
    if (myRes >= right.mySize) {//空格數大於等於str2的東西數直接丟
        for (int i = 0; i < right.mySize; i++) {
            myPtr()[i] = right.myPtr()[i];
        }
        mySize = right.mySize;
    }
    else {
        size_type newRes;
        if (right.mySize / 16 * 16 + 15 > myRes * 3 / 2) {
            newRes = right.mySize / 16 * 16 + 15;
        }
        else {
            newRes = myRes * 3 / 2;
        }
        myRes = newRes;
        
        bx.ptr=new value_type[myRes]();
        for (int i = 0; i < right.mySize; i++) {
            myPtr()[i] = right.myPtr()[i];
        }
        mySize = right.mySize;
    }
        return *this;
    
}

string::iterator string::insert(const_iterator where, const char ch)
{
    if (where >= myPtr() && where <= myPtr() + mySize)
    {
        size_type where_pos = where - myPtr();

        if (size() == capacity()) {
            size_type new_capacity;
            if ((size() + 1) / 16 * 16 + 15 > myRes * 3 / 2)
                new_capacity = capacity() + 16;
            else
                new_capacity = capacity() * 3 / 2;

            size_type new_size = size() + 1;
            pointer temp = new value_type[new_capacity]();

            for (int i = 0; i < where_pos; i++) {
                temp[i] = myPtr()[i];
            }
            temp[where_pos] = ch;
            for (int i = where_pos + 1; i < new_size; i++) {
                temp[i] = myPtr()[i - 1];
            }

            bx.ptr = temp;
            mySize = new_size;
            myRes = new_capacity;
        }
        else {
            size_type new_size = size() + 1;
            for (int i = size(); i > where_pos; i--) {
                myPtr()[i] = myPtr()[i - 1];
            }
            myPtr()[where_pos] = ch;

            mySize = new_size;
        }

        return myPtr();
    }
    else
        return iterator(nullptr);
}

string::iterator string::erase(const_iterator where)
{
    if (where >= myPtr() && where < myPtr() + mySize)
    {
        size_type where_erase = where - myPtr();
        for (size_type i = where_erase; i < myRes; i++) {
            myPtr()[i] = myPtr()[i + 1];
        }
        mySize--;
    }
    else
        return iterator(nullptr);
}

void string::clear()
{
    mySize = 0;
    myPtr()[0] = value_type();
}

string::iterator string::begin()
{
    return myPtr();
}

string::const_iterator string::begin() const
{
    return const_iterator(myPtr());
}

string::iterator string::end()
{
    return myPtr() + static_cast<difference_type>(mySize);
}

string::const_iterator string::end() const
{
    return const_iterator(myPtr() + static_cast<difference_type>(mySize));
}

string::reference string::element(const size_type off)
{
    if (off > mySize)
    {
        cout << "string subscript out of range\n";
        exit(1);
    }

    return myPtr()[off];
}

string::const_reference string::element(const size_type off) const
{
    if (off > mySize)
    {
        cout << "string subscript out of range\n";
        exit(1);
    }

    return myPtr()[off];
}

string::reference string::front()
{
    return myPtr()[0];
}

string::const_reference string::front() const
{
    return myPtr()[0];
}

string::reference string::back()
{
    return myPtr()[mySize - 1];
}

string::const_reference string::back() const
{
    return myPtr()[mySize - 1];
}

const char* string::c_str() const
{
    return myPtr();
}

string::size_type string::size() const
{
    return mySize;
}

string::size_type string::capacity() const
{
    return myRes;
}

bool string::empty() const
{
    return mySize == 0;
}