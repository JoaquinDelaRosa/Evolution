#ifndef PRINTER_H_INCLUDED
#define PRINTER_H_INCLUDED

#include<bits/stdc++.h>

inline void printHorizontal(int width){
    for(int i = 0; i <= width; i++) std::cout<<"-";
        std::cout<<"\n";
}

template<typename T>
inline void printTableCell(T entry, int width = 10){
    std::cout<<std::left<<std::setw(width)<<entry<<std::setfill(' ')<<" | ";
}

#endif // PRINTER_H_INCLUDED
