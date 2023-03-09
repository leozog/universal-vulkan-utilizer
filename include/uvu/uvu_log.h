#pragma once
#include <string>
#include <iostream>


template <class T>
void uvu_log(T &x, char end = '\n')
{
    std::cout<<std::to_string(x)<<end;
}
template <>
void uvu_log(std::string &x, char end)
{
    std::cout<<x<<end;
}
template <>
void uvu_log(char (&x)[], char end)
{
    std::string str(x);
    std::cout<<str<<end;
}