#ifndef GRID_H
#define GRID_H

#include "bits/stdc++.h"

template<typename T>
class Grid
{
    private:
        std::vector<std::vector<std::vector<T>>> grid;
        int width;
        int height;

    public:
        Grid(int width, int height){
            this->width = width;
            this->height = height;

            for(int i = 0; i < height; i++){
                std::vector<std::vector<T>> row(width);
                grid.push_back(row);
            }
        }

        T get(int x, int y){
            if(grid[y][x].size() > 0)
                return grid[y][x][0];
            return NULL;
        }

        void set(int x, int y, T val){
            grid[y][x].push_back(val);
        }
};

#endif // GRID_H
