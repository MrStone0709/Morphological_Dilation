#ifndef MORPHOLOGY_H
#define MORPHOLOGY_H

#include "BinaryImage.h"
#include "StructuringElement.h"

class Morphology {
public:
  static BinaryImage dilation(const BinaryImage &image,
                              const StructuringElement &element);

  static BinaryImage erosion(const BinaryImage &image,
                             const StructuringElement &element);
};

#endif