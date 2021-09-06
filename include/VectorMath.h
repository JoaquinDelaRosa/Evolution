#ifndef VECTORMATH_H_INCLUDED
#define VECTORMATH_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "bits/stdc++.h"

#define PI 3.14

inline sf::Vector2f normalize(sf::Vector2f v){
    float length = sqrt(v.x * v.x + v.y * v.y);
    if(length != 0)
        return (1.0f / length) * v;
    return v;
}

inline double getDistance(sf::Vector2f o, sf::Vector2f p){
    double dx = p.x - o.x;
    double dy = p.y - o.y;

    return sqrt(dx * dx + dy * dy);
}

inline float dot(sf::Vector2f v1, sf::Vector2f v2){
    return v1.x * v2.x + v1.y * v2.y;
}

inline float length(sf::Vector2f v){
    return getDistance(v, sf::Vector2f(0, 0));
}

inline float getAngle(sf::Vector2f v){
    return atan2(v.y, v.x);
}

inline float getAngle(sf::Vector2f v, sf::Vector2f w){
    return dot(v, w) / (length(v) * length(w));
}

inline void rotateVector(sf::Vector2f* v, float angle){
    float x = v->x;
    float y = v->y;
    float c = cos(angle);
    float s = sin(angle);

    v->x = x * c + y * s;
    v->y = -x * s + y * c;
}

inline sf::Vector2f getVectorRadial(float angle, float radius, sf::Vector2f center){
    return sf::Vector2f(center.x + radius * cos(angle), center.y + radius * sin(angle));
}



template<typename T>
inline void clamp(T smallest, T largest, T* val){
    if(*val <= smallest)
        *val = smallest;
    if(*val >= largest)
        *val= largest;
}


class Generator{
    private:
        std::mt19937 generator;
        std::uniform_real_distribution<float> UWidth;
        std::uniform_real_distribution<float> UHeight;
        std::uniform_real_distribution<float> UProbability;
        std::normal_distribution<float> NProbability;

        std::mt19937 getGenerator(){
            std::random_device rd;

            std::mt19937::result_type seed = rd() ^ (
                    (std::mt19937::result_type)
                    std::chrono::duration_cast<std::chrono::seconds>(
                        std::chrono::system_clock::now().time_since_epoch()
                        ).count() +
                    (std::mt19937::result_type)
                    std::chrono::duration_cast<std::chrono::microseconds>(
                        std::chrono::high_resolution_clock::now().time_since_epoch()
                        ).count() );


            std::mt19937 generator(seed);
            return generator;
        }

        Generator(){
            generator = getGenerator();
            UProbability = std::uniform_real_distribution<float>(0.0f, 1.0f);
            NProbability = std::normal_distribution<float>(0.0f, 1.0f);
        }

    public:
        Generator(Generator const&) = delete;
        void operator=(Generator const&) = delete;

        static Generator& instance(){
            static Generator instance;
            return instance;
        }

        sf::Vector2f getRandomVector(float minx = -500, float maxx = 500, float miny = -500, float maxy = 500){
            std::uniform_real_distribution<float> UWidth(minx, maxx);
            std::uniform_real_distribution<float> UHeight(miny, maxy);
            return sf::Vector2f(UWidth(generator), UHeight(generator));
        }

        sf::Vector2f getRandomVector(float radius, sf::Vector2f center){
            float r = getRandomNumber(0, radius);
            float theta = getRandomNumber(0, 2 * PI);
            return sf::Vector2f(center.x + r * cos(theta), center.y + r * sin(theta));
        }

        float getRandomNumber(float minx, float maxx){
            std::uniform_real_distribution<float> P(minx, maxx);
            return (float) P(generator);
        }

        float getUniform(){
            return (float) UProbability(generator);
        }

        float getNormal(float stdev = 1.0f){
            this->NProbability = std::normal_distribution<float>(0.0f, stdev);
            return (float) NProbability(generator);
        }

};



#endif // VECTORMATH_H_INCLUDED
