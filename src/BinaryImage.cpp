#include "BinaryImage.h"
#include <iostream> 

BinaryImage::BinaryImage(int rows, int cols)
{
    data = std::vector<std::vector<int>>(
        rows,
        std::vector<int>(cols, 0)
    );
}

int BinaryImage::get(int row, int col) const
{
    return data[row][col];
}

void BinaryImage::set(int row, int col, int value)
{
    data[row][col] = value;
}

int BinaryImage::rows() const
{
    return data.size();
}

int BinaryImage::cols() const
{
    if (data.empty())
    {
        return 0;
    }

    return data[0].size();
}

void BinaryImage::print() const
{
    for (const auto& row : data)
    {
        for (int value : row)
        {
            std::cout << value << " ";
        }

        std::cout << std::endl;
    }
}