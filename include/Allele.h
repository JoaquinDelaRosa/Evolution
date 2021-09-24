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
        float stdev;

    public:
        Allele(std::string name, T minimum, T maximum, T value, float stdev = 0.2f){
            this->name = name;
            this->value = value;
            this->minimum = minimum;
            this->maximum = maximum;
            this->stdev = stdev;
        }

        void mutate(){
            this->value += Generator::instance().getNormal(stdev);
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

        T getWeight(){
            return (value - minimum) / (maximum - minimum);
        }

};

#endif // ALLELE_H
