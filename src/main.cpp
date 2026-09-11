#include "BinaryImage.h"
#include "Morphology.h"
#include "StructuringElement.h"

#include <iostream>
#include <vector>

int main() {

  std::vector<std::vector<int>> imageData = {
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 1, 1, 1, 1, 1, 0, 0, 0},
      {0, 0, 1, 1, 1, 1, 1, 0, 0, 0},
      {0, 0, 1, 1, 1, 1, 1, 0, 0, 0},
      {0, 0, 1, 1, 1, 1, 1, 0, 0, 0},
      {0, 0, 1, 1, 1, 1, 1, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

  // 创建 10×10 图像
  BinaryImage image(imageData);

  std::cout << "Original image:" << std::endl;
  image.print();

  // 创建5*5矩形结构元素，锚点在中心
  std::vector<std::vector<int>> square = {{1, 1, 1, 1, 1},
                                          {1, 1, 1, 1, 1},
                                          {1, 1, 1, 1, 1},
                                          {1, 1, 1, 1, 1},
                                          {1, 1, 1, 1, 1}};

  StructuringElement square_element(square, 2, 2);

  std::cout << std::endl;
  std::cout << "Square structuring element:" << std::endl;

  square_element.print();

  // 膨胀
  BinaryImage dilated = Morphology::dilation(image, square_element);

  std::cout << std::endl;
  std::cout << "Dilated image:" << std::endl;

  dilated.print();

  // 腐蚀
  BinaryImage eroded = Morphology::erosion(image, square_element);

  std::cout << std::endl;
  std::cout << "Eroded image:" << std::endl;

  eroded.print();

  // 创建5*5圆形结构元素，锚点在中心
  std::vector<std::vector<int>> circle = {{0, 0, 1, 0, 0},
                                          {0, 1, 1, 1, 0},
                                          {1, 1, 1, 1, 1},
                                          {0, 1, 1, 1, 0},
                                          {0, 0, 1, 0, 0}};

  StructuringElement circle_element(circle, 2, 2);

  std::cout << std::endl;
  std::cout << "Circle structuring element:" << std::endl;

  circle_element.print();

  // 膨胀
  dilated = Morphology::dilation(image, circle_element);

  std::cout << std::endl;
  std::cout << "Dilated image:" << std::endl;

  dilated.print();

  // 腐蚀
  eroded = Morphology::erosion(image, circle_element);

  std::cout << std::endl;
  std::cout << "Eroded image:" << std::endl;

  eroded.print();
  
  return 0;
}