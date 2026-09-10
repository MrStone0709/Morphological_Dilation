#include "BinaryImage.h"

int main()
{
    BinaryImage image(5, 5);

    image.set(2, 2, 1);

    image.set(1, 2, 1);
    image.set(3, 2, 1);

    image.set(2, 1, 1);
    image.set(2, 3, 1);

    image.print();

    return 0;
}