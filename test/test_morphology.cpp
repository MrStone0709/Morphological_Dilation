#include "BinaryImage.h"
#include "StructuringElement.h"
#include "Morphology.h"

#include <cassert>
#include <iostream>
#include <vector>


/*
 * 辅助函数：
 * 判断 BinaryImage 是否与预期二维 vector 完全相同
 */
void assertImageEqual(
    const BinaryImage& image,
    const std::vector<std::vector<int>>& expected)
{
    // 检查行数
    assert(image.rows() == static_cast<int>(expected.size()));

    // 检查列数
    if (!expected.empty())
    {
        assert(image.cols() ==
               static_cast<int>(expected[0].size()));
    }

    // 检查每一个像素
    for (int row = 0; row < image.rows(); row++)
    {
        for (int col = 0; col < image.cols(); col++)
        {
            assert(image.get(row, col) ==
                   expected[row][col]);
        }
    }
}


/*
 * 辅助函数：
 * 判断 StructuringElement 是否与预期二维 vector 完全相同
 */
void assertElementEqual(
    const StructuringElement& element,
    const std::vector<std::vector<int>>& expected)
{
    assert(element.rows() ==
           static_cast<int>(expected.size()));

    if (!expected.empty())
    {
        assert(element.cols() ==
               static_cast<int>(expected[0].size()));
    }

    for (int row = 0; row < element.rows(); row++)
    {
        for (int col = 0; col < element.cols(); col++)
        {
            assert(element.get(row, col) ==
                   expected[row][col]);
        }
    }
}


int main()
{
    std::cout << "Running morphology tests..."
              << std::endl;


    /*
     * ==================================================
     * Test 1
     * BinaryImage 基本功能
     * ==================================================
     */

    std::vector<std::vector<int>> imageMatrix =
    {
        {0, 0, 0},
        {0, 1, 0},
        {0, 0, 0}
    };

    BinaryImage image(imageMatrix);

    assertImageEqual(
        image,
        imageMatrix
    );

    std::cout << "Test 1 passed: BinaryImage"
              << std::endl;


    /*
     * ==================================================
     * Test 2
     * StructuringElement 基本功能
     * ==================================================
     */

    std::vector<std::vector<int>> elementMatrix =
    {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };

    StructuringElement element(
        elementMatrix,
        1,
        1
    );

    assertElementEqual(
        element,
        elementMatrix
    );

    assert(element.getAnchorRow() == 1);
    assert(element.getAnchorCol() == 1);

    std::cout << "Test 2 passed: StructuringElement"
              << std::endl;


    /*
     * ==================================================
     * Test 3
     * 测试结构元素 180°旋转
     * ==================================================
     *
     * 原结构元素：
     *
     * 0 1 1
     * 0 1 0
     * 0 0 0
     *
     * 旋转后：
     *
     * 0 0 0
     * 0 1 0
     * 1 1 0
     */

    std::vector<std::vector<int>> asymmetricMatrix =
    {
        {0, 1, 1},
        {0, 1, 0},
        {0, 0, 0}
    };

    StructuringElement asymmetricElement(
        asymmetricMatrix,
        1,
        1
    );

    StructuringElement reflectedElement =
        asymmetricElement.reflected();

    std::vector<std::vector<int>> expectedReflected =
    {
        {0, 0, 0},
        {0, 1, 0},
        {1, 1, 0}
    };

    assertElementEqual(
        reflectedElement,
        expectedReflected
    );

    // 因为锚点位于矩阵中心，
    // 旋转后仍然位于中心
    assert(
        reflectedElement.getAnchorRow() == 1
    );

    assert(
        reflectedElement.getAnchorCol() == 1
    );

    std::cout << "Test 3 passed: Reflection"
              << std::endl;


    /*
     * ==================================================
     * Test 4
     * 测试数学定义下的膨胀
     * ==================================================
     *
     * 输入：
     *
     * 0 0 0 0 0
     * 0 0 1 0 0
     * 0 0 0 0 0
     * 0 0 0 0 0
     * 0 0 0 0 0
     *
     * 原结构元素：
     *
     * 0 1 1
     * 0 1 0
     * 0 0 0
     *
     * 反射后：
     *
     * 0 0 0
     * 0 1 0
     * 1 1 0
     *
     * 数学定义：
     *
     * A ⊕ B = {z | B_hat_z ∩ A != ∅}
     *
     * 预期结果：
     *
     * 0 0 1 1 0
     * 0 0 1 0 0
     * 0 0 0 0 0
     * 0 0 0 0 0
     * 0 0 0 0 0
     */

    std::vector<std::vector<int>> dilationInput =
    {
        {0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };

    BinaryImage dilationImage(dilationInput);

    BinaryImage dilated =
        Morphology::dilation(
            dilationImage,
            asymmetricElement
        );

    std::vector<std::vector<int>> expectedDilation =
    {
        {0, 0, 1, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };

    assertImageEqual(
        dilated,
        expectedDilation
    );

    std::cout << "Test 4 passed: Dilation"
              << std::endl;


    /*
     * ==================================================
     * Test 5
     * 测试腐蚀
     * ==================================================
     *
     * 输入：
     *
     * 1 1 1
     * 1 1 1
     * 1 1 1
     *
     * 结构元素：
     *
     * 1 1 1
     * 1 1 1
     * 1 1 1
     *
     * 只有中心位置能够完全容纳结构元素。
     *
     * 预期：
     *
     * 0 0 0
     * 0 1 0
     * 0 0 0
     */

    std::vector<std::vector<int>> erosionInput =
    {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };

    BinaryImage erosionImage(erosionInput);

    BinaryImage eroded =
        Morphology::erosion(
            erosionImage,
            element
        );

    std::vector<std::vector<int>> expectedErosion =
    {
        {0, 0, 0},
        {0, 1, 0},
        {0, 0, 0}
    };

    assertImageEqual(
        eroded,
        expectedErosion
    );

    std::cout << "Test 5 passed: Erosion"
              << std::endl;


    /*
     * ==================================================
     * Test 6
     * 测试结构元素替换
     * ==================================================
     *
     * 相同输入图像分别使用：
     *
     * 1. 十字形结构元素
     * 2. 3×3 全 1 结构元素
     *
     * 两种结构元素应该产生不同结果。
     */

    std::vector<std::vector<int>> replaceInput =
    {
        {0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };

    BinaryImage replaceImage(replaceInput);


    /*
     * 十字形结构元素
     *
     * 0 1 0
     * 1 1 1
     * 0 1 0
     */

    std::vector<std::vector<int>> crossMatrix =
    {
        {0, 1, 0},
        {1, 1, 1},
        {0, 1, 0}
    };

    StructuringElement crossElement(
        crossMatrix,
        1,
        1
    );


    /*
     * 使用十字形结构元素膨胀
     */

    BinaryImage crossResult =
        Morphology::dilation(
            replaceImage,
            crossElement
        );


    /*
     * 预期结果
     */

    std::vector<std::vector<int>> expectedCross =
    {
        {0, 0, 1, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };

    assertImageEqual(
        crossResult,
        expectedCross
    );


    /*
     * 使用 3×3 全 1 结构元素
     */

    BinaryImage squareResult =
        Morphology::dilation(
            replaceImage,
            element
        );


    /*
     * 预期结果
     */

    std::vector<std::vector<int>> expectedSquare =
    {
        {0, 1, 1, 1, 0},
        {0, 1, 1, 1, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };

    assertImageEqual(
        squareResult,
        expectedSquare
    );


    /*
     * 确认两种结构元素确实产生不同结果
     */

    assert(
        crossResult.get(0, 1) == 0
    );

    assert(
        squareResult.get(0, 1) == 1
    );

    std::cout << "Test 6 passed: "
              << "Replaceable Structuring Element"
              << std::endl;


    /*
     * 所有测试通过
     */

    std::cout << std::endl;
    std::cout << "All tests passed!"
              << std::endl;

    return 0;
}