#ifndef ALLELE_H
#define ALLELE_H

#include "bits/stdc++.h"
#include "VectorMath.h"

template<typename T>
class Allele{
    private:
        std::string name;
        T value;
        T minimum;
        T maximum;
    public:
        Allele(std::string name, T minimum, T maximum, T value){
            this->name = name;
            this->value = value;
            this->minimum = minimum;
            this->maximum = maximum;
        }

        void mutate(){
            this->value += Generator::instance().getNormal();
            clamp<T>(this->minimum, this->maximum, &this->value);
        }

        T getValue(){
            return this->value;
        }

        std::string getName(){
            return this->name;
        }

        T getMin(){
            return this->minimum;
        }

        T getMax(){
            return this->maximum;
        }

};

#endif // ALLELE_H
