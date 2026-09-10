#include "Morphology.h"

/*
 * 形态学膨胀
 *
 * 数学定义：
 *
 * A ⊕ B = { z | (B_hat)_z ∩ A != ∅ }
 *
 * B_hat 是 B 关于锚点旋转 180°后的结构元素。
 */
BinaryImage Morphology::dilation(const BinaryImage &image,
                                 const StructuringElement &element) {
  BinaryImage result(image.rows(), image.cols());

  // 获取结构元素的 180°反射
  StructuringElement reflectedElement = element.reflected();

  // 遍历输出图像
  for (int row = 0; row < image.rows(); row++) {
    for (int col = 0; col < image.cols(); col++) {
      bool found = false;

      // 遍历反射后的结构元素
      for (int erow = 0; erow < reflectedElement.rows(); erow++) {
        for (int ecol = 0; ecol < reflectedElement.cols(); ecol++) {
          // 结构元素为 0，不参与计算
          if (reflectedElement.get(erow, ecol) == 0) {
            continue;
          }

          // 计算结构元素对应的图像坐标
          int imageRow = row + erow - reflectedElement.getAnchorRow();

          int imageCol = col + ecol - reflectedElement.getAnchorCol();

          // 超出图像范围
          if (imageRow < 0 || imageRow >= image.rows() || imageCol < 0 ||
              imageCol >= image.cols()) {
            continue;
          }

          /*
           * 只要结构元素中有一个 1
           * 与输入图像中的 1 重合，
           * 当前输出位置就是 1。
           */
          if (image.get(imageRow, imageCol) == 1) {
            found = true;
            break;
          }
        }

        if (found) {
          break;
        }
      }

      if (found) {
        result.set(row, col, 1);
      }
    }
  }

  return result;
}

/*
 * 形态学腐蚀
 *
 * 数学定义：
 *
 * A ⊖ B = { z | B_z ⊆ A }
 */
BinaryImage Morphology::erosion(const BinaryImage &image,
                                const StructuringElement &element) {
  BinaryImage result(image.rows(), image.cols());

  // 遍历输出图像
  for (int row = 0; row < image.rows(); row++) {
    for (int col = 0; col < image.cols(); col++) {
      bool fits = true;

      // 遍历结构元素
      for (int erow = 0; erow < element.rows(); erow++) {
        for (int ecol = 0; ecol < element.cols(); ecol++) {
          // 结构元素为 0，不参与计算
          if (element.get(erow, ecol) == 0) {
            continue;
          }

          // 计算结构元素对应的图像坐标
          int imageRow = row + erow - element.getAnchorRow();

          int imageCol = col + ecol - element.getAnchorCol();

          /*
           * 超出图像范围：
           * 认为对应位置为背景。
           */
          if (imageRow < 0 || imageRow >= image.rows() || imageCol < 0 ||
              imageCol >= image.cols()) {
            fits = false;
            break;
          }

          /*
           * 只要有一个结构元素中的 1
           * 对应到输入图像中的 0，
           * 就无法完成腐蚀。
           */
          if (image.get(imageRow, imageCol) == 0) {
            fits = false;
            break;
          }
        }

        if (!fits) {
          break;
        }
      }

      /*
       * 结构元素完全落在前景区域内
       */
      if (fits) {
        result.set(row, col, 1);
      }
    }
  }

  return result;
}