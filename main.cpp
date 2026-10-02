#include "include/utils.h"
// #include "include/tests.h"
// #include "src/tests.cpp"
#include "src/utils.cpp"
#include <iostream>
#include <cstring>

int my_strlen(const char *str)
{
    /**
     * 统计字符串的长度，太简单了。
     */

    // IMPLEMENT YOUR CODE HERE
    int len = 0;
    while (str[len] != '\0')
    {
        len++;
    }
    return len;
}

// 练习2，实现库函数strcat

/**
 * 将字符串str_2拼接到str_1之后，我们保证str_1指向的内存空间足够用于添加str_2。
 * 注意结束符'\0'的处理。
 */

// IMPLEMENT YOUR CODE HERE
char *my_strcat(char *dest, const char *src)
{
    // 第一步：找到 dest 的结尾（'\0' 的位置）
    int i = 0;
    while (dest[i] != '\0')
    {
        i++;
    }

    // 第二步：把 src 逐个字符拷过去
    int j = 0;
    while (src[j] != '\0')
    {
        dest[i] = src[j];
        i++;
        j++;
    }

    // 第三步：手动补上结束符
    dest[i] = '\0';

    return dest;
}

// 练习3，实现库函数strstr
char *my_strstr(const char *s, const char *p)
{
    /**
     * 在字符串s中搜索字符串p，如果存在就返回第一次找到的地址，不存在就返回空指针(0)。
     * 例如：
     * s = "123456", p = "34"，应该返回指向字符'3'的指针。
     */

    // IMPLEMENT YOUR CODE HERE

    int i = 0;
    while (s[i] != '\0')
    {
        // 每次从 haystack[i] 开始，尝试和 needle 逐个字符匹配
        int j = 0;
        while (s[i + j] != '\0' && p[j] != '\0')
        {
            if (s[i + j] != p[j])
            {
                break; // 有一个字符不匹配，放弃这次尝试
            }
            j++;
        }
        // 如果 needle[j] 走到了 '\0'，说明 needle 的每一个字符都匹配成功了
        if (p[j] == '\0')
        {
            return (char *)(s + i);
        }
        i++; // 否则 haystack 起始位置往后挪一位，重新试
    }

    return 0; // 整个 haystack 都试完了也没找到
}
// 练习4，将彩色图片(rgb)转化为灰度图片
void rgb2gray(float *in, float *out, int h, int w)
{
    /**
     * 编写这个函数，将一张彩色图片转化为灰度图片。以下是各个参数的含义：
     * (1) float *in:  指向彩色图片对应的内存区域（或者说数组）首地址的指针。
     * (2) float *out: 指向灰度图片对应的内存区域（或者说数组）首地址的指针。
     * (3) int h:      height，即图片的高度。
     * (4) int w:      width，即图片的宽度。
     *
     * 提示：
     * (1) in数组只管读取就行了，别修改它的值。out数组只修改不读取。
     * (2) 利用公式 V = 0.1140 * B  + 0.5870 * G + 0.2989 * R 计算彩色图片每个
     *     像素对应的灰度值，写到灰度图片相同的位置中就行。
     * (3) 使用for循环来遍历每个位置。利用图片在内存中的存储顺序，计算出每个位置像素
     *     的地址。
     *
     * 考点：
     * (1) for循环的使用。
     * (2) 内存的访问。
     */

    // IMPLEMENT YOUR CODE HERE
    // ...

    // 遍历每一行每一列的像素
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            // 彩色图片在内存中按 R G B R G B ... 存储
            // 像素 (i, j) 的 R 分量在索引 (i * w + j) * 3 处
            int cai = (i * w + j) * 3;
            float R = in[cai];
            float G = in[cai + 1];
            float B = in[cai + 2];
            // 利用公式 V = 0.1140 * B + 0.5870 * G + 0.2989 * R 计算灰度值
            float V = 0.1140 * B + 0.5870 * G + 0.2989 * R;
            // 写入灰度图片，灰度图每个像素只占一个位置
            out[i * w + j] = V;
        }
    }
}

// 练习5，实现图像处理算法 resize：缩小或放大图像
void resize(float *in, float *out, int h, int w, int c, float scale)
{
    /**
     * 图像处理知识：
     *  1.单线性插值法
     *      假设有两个已知 点1(x1, y1) 和 点2(x2, y2)，
     *      点1 的值为v1，点2 的值为v2，
     *      待插值点 (x, y)处于 点1 和 点2 中间，值为 v，
     *      如下图所示(*表示点，/表示三个点在一条直线上)：
     *
     *                                * (x2, y2), v2
     *                               /
     *                              /
     *                             * (x, y), v
     *                            /
     *                           * (x1, y1), v1
     *
     *      则满足下面的条件：
     *                    x2 - x          x - x1
     *          v = v1 * ———————— + v2 * ————————
     *                   x2 - x1         x2 - x1
     *      也就是说，v的值是 点1 和 点2 的值的加权平均值，权重与到两点的距离相关
     *      (公式中的 x也可以是 y，因为是在一条直线上)。
     *
     *  2.双线性插值法
     *     2.1 由于图片是二维的，每个像素点有两个方向可以用来插值，所以可以使用双线性插值法。
     *     假设有四个已知 P1(x1, y2), P2(x2, y2), P3(x1, y1), P4(x2, y1)，
     *      如下图（看起来是在一条直线上就是在一条直线上）
     *
     *          P1(x1, y2)                      P2(x2, y2)
     *              *                               *
     *
     *                              * P(x, y)
     *
     *              *                               *
     *          P3(x1, y1)                      P4(x2, y1)
     *
     *      2.2 核心思想：
     *          双线性差值相当于三次差值，如下图所示：
     *
     *              P1(x1, y2)      Q1(x, y2)       P2(x2, y2)
     *                  *               *               *
     *
     *                                  * P(x, y)
     *
     *                  *               *               *
     *              P3(x1, y1)      Q2(x, y1)       P4(x2, y1)
     *
     *          先用单线性插值法计算出 Q1 和 Q2 的值，再用单线性插值法计算出 P 的值，即
     *                     x2 - x          x - x1
     *          Q1 = P1 * ———————— + P2 * ————————
     *                     x2 - x1         x2 - x1
     *
     *                     x2 - x          x - x1
     *          Q2 = P3 * ———————— + P4 * ————————
     *                     x2 - x1         x2 - x1
     *
     *                    y2 - y          y - y1
     *          P = Q1 * ———————— + Q2 * ————————
     *                    y2 - y1         y2 - y1
     *
     *      2.3 化简：
     *          记 Dx = x2 - x1, Dy = y2 - y1, dx = x - x1, dy = y - y1，
     *
     *                     (Dx - dx)(Dy - dy)         dx(Dy - dy)
     *          Q = P1 * ———————————————————— + P2 * ————————————— +
     *                          Dx * Dy                 Dx * Dy
     *
     *                    (Dx - dx)dy           dxdy
     *              P3 * ————————————— + P4 * —————————
     *                      Dx * Dy            Dx * Dy
     *
     *  3. 双线性插值用于 resize 图片
     *      记 原图为 src，目标图为 dst，
     *         比例 dst宽高 = src宽高 * scale，
     *      设一个点 resize 后的坐标为 (x, y)，resize 前的坐标为 (x', y')，
     *      则有 x' = x / scale, y' = y / scale，
     *
     *      现在，对于每个目标图片中的像素点 (x, y)：
     *          1. 找到对应的源图片中的像素点 (x', y')
     *          2. 找到其在原图中的四个邻居点 (这四个邻居是相邻的四个点，组成一个正方形)
     *          3. 用双线性插值法计算出 该像素点 的值
     *
     *      不难发现，在这种情况下：Dx = Dy = 1（原图中相邻的四个像素横竖距离是1）
     *      所以，上面的公式可以化简为：
     *          Q = P1 * (1 - dx)(1 - dy) + P2 * dx(1 - dy)
     *            + P3 * (1 - dx)dy + P4 * dxdy
     * HINT:
     *     1. 对于每个 dst 中的像素点 (x, y)，先计算出其在 src 中的坐标 float(x0, y0)，
     *     2. 然后计算出其在 src 中的四个邻居点:
     *        x1 = static_cast<int>(x0), y1 = static_cast<int>(y0)
     *        上面这样可以直接将 float 通过下取整的方式转换为 int，
     *        剩下三个邻居就好找了
     *     3. 注意上面的方法中，四个邻居点的坐标可能会超出 src 的范围，
     *        所以需要对其进行边界检查
     */

    int new_h = h * scale, new_w = w * scale;
    // IMPLEMENT YOUR CODE HERE

    // 遍历目标图像的每个像素 (x, y)
    for (int y = 0; y < new_h; y++)
    {
        for (int x = 0; x < new_w; x++)
        {
            // 1. 计算对应源图像的坐标
            float x0 = (float)x / scale;
            float y0 = (float)y / scale;

            // 2. 计算四个邻居点的坐标
            int x1 = (int)x0; // floor(x0)
            int y1 = (int)y0; // floor(y0)
            int x2 = x1 + 1;
            int y2 = y1 + 1;

            // 小数部分作为插值权重
            float dx = x0 - x1;
            float dy = y0 - y1;

            // 3. 边界检查：防止邻居坐标超出源图像范围
            if (x1 < 0)
                x1 = 0;
            if (x2 >= w)
                x2 = w - 1;
            if (y1 < 0)
                y1 = 0;
            if (y2 >= h)
                y2 = h - 1;

            // 4. 对每个通道分别进行双线性插值
            for (int ch = 0; ch < c; ch++)
            {
                // 获取四个邻居像素的值
                // P1 = (x1, y2) 左上角, P2 = (x2, y2) 右上角
                // P3 = (x1, y1) 左下角, P4 = (x2, y1) 右下角
                float P1 = in[(y2 * w + x1) * c + ch];
                float P2 = in[(y2 * w + x2) * c + ch];
                float P3 = in[(y1 * w + x1) * c + ch];
                float P4 = in[(y1 * w + x2) * c + ch];

                // 双线性插值公式
                float Q = P1 * (1 - dx) * (1 - dy) + P2 * dx * (1 - dy) + P3 * (1 - dx) * dy + P4 * dx * dy;

                // 写入目标图像
                out[(y * new_w + x) * c + ch] = Q;
            }
        }
    }
}

// 练习6，实现图像处理算法：直方图均衡化
void hist_eq(float *in, int h, int w)
{
    /**
     * 将输入图片进行直方图均衡化处理。参数含义：
     * (1) float *in: 输入的灰度图片。
     * (2) int h:     height，即图片的高度。
     * (3) int w:      width，即图片的宽度。
     *
     * 参考资料：
     * https://blog.csdn.net/qq_15971883/article/details/88699218
     * 其它的博客也行。
     *
     * 提示：
     * (1) 输入图片是灰度图，每个像素值是[0, 255]内的小数
     * (2) 灰度级个数为256，也就是{0, 1, 2, 3, ..., 255}
     * (3) 使用数组来实现灰度级 => 灰度级的映射
     */

    // IMPLEMENT YOUR CODE HERE
    if (in == nullptr || h <= 0 || w <= 0)
        return; // 安全检查

    int total_pixels = h * w;
    int hist[256] = {0};

    // 1. 统计直方图 (将小数四舍五入映射到0-255的整数)
    for (int i = 0; i < total_pixels; i++)
    {
        int val = (int)(in[i] + 0.5f);
        if (val < 0)
            val = 0;
        if (val > 255)
            val = 255;
        hist[val]++;
    }

    // 2. 计算累积分布函数 (CDF)
    float cdf[256] = {0.0f};
    cdf[0] = (float)hist[0] / total_pixels;
    for (int i = 1; i < 256; i++)
    {
        cdf[i] = cdf[i - 1] + (float)hist[i] / total_pixels;
    }

    // 寻找非零的最小 CDF 值（标准均衡化公式所需，防止图像整体偏亮）
    float cdf_min = 0.0f;
    for (int i = 0; i < 256; i++)
    {
        if (hist[i] > 0)
        {
            cdf_min = cdf[i];
            break;
        }
    }

    // 3. 建立灰度级映射表
    unsigned char map[256];
    for (int i = 0; i < 256; i++)
    {
        if (cdf[i] <= cdf_min)
        {
            map[i] = 0;
        }
        else
        {
            // 标准均衡化公式，将结果映射回 0-255
            float new_val = (cdf[i] - cdf_min) / (1.0f - cdf_min) * 255.0f;
            map[i] = (unsigned char)(new_val + 0.5f);
        }
    }

    // 4. 应用映射表，原地修改输入图像
    for (int i = 0; i < total_pixels; i++)
    {
        int val = (int)(in[i] + 0.5f);
        if (val < 0)
            val = 0;
        if (val > 255)
            val = 255;
        in[i] = (float)map[val];
    }
}

void test_rgb2gray()
{
    std::cout << "开始测试函数 << rgb2gray >> ..." << std::endl;
    const char *path = "./images/rgb2gray/input.jpg";
    float *img;
    int h, w, c;

    imread(path, &img, &h, &w, &c);
    std::cout << "读取图片images/rgb2gray/input.jpg，高度为" << h << "，高度为" << w
              << "，通道数为" << c
              << std::endl;

    float *gray = fmalloc(h * w);
    rgb2gray(img, gray, h, w);

    const char *out_path = "./images/rgb2gray/output.jpg";
    imwrite(out_path, gray, h, w, 1);
    std::cout << "使用你的代码产生的灰度图片已经保存为images/rgb2gray/output.jpg"
              << std::endl
              << "可以与images/rgb2gray/answer.jpg进行比较，看结果是否正确"
              << std::endl;

    free(gray), free(img);
    std::cout << std::endl
              << std::endl;
}

void test_strlen()
{
    std::cout << "开始测试函数 << my_strlen >> ..." << std::endl;
    const char *strs[] = {
        "123456", "", "hello world!"};

    bool pass = true;
    for (int i = 0; i < 3; i++)
        if (strlen(strs[i]) != my_strlen(strs[i]))
        {
            std::cout << "未通过，错误的输入为" << strs[i] << std::endl;
            pass = false;
            break;
        }

    if (pass)
    {
        std::cout << "通过" << std::endl;
    }
    std::cout << std::endl
              << std::endl;
}

void test_strcat()
{
    std::cout << "开始测试函数 << my_strcat >> ..." << std::endl;

    const int n = 2000;
    // 来源：电影《绿皮书》
    char str1[n] =
        "Dear Dolores\n"
        "When I think of you, I'm reminded of the beautiful plains of Iowa. The distance \n"
        "between us is breaking my spirit. My time and experiences without you are meaningless\n"
        "to me. ";

    char str2[n] =
        "Falling in love with you was the easiest thing I have ever done. Nothing \n"
        "matters to me but you. And everyday I am alive, I'm aware of this. I loved you the day \n"
        "I met you, I love you today... And I will love you to rest of my life.";

    char str1_tmp[n], str2_tmp[n];
    strcpy(str1_tmp, str1), strcpy(str2_tmp, str2);

    strcat(str1, str2);
    my_strcat(str1_tmp, str2_tmp);

    if (!strcmp(str1, str1_tmp))
    {
        std::cout << "通过" << std::endl;
    }
    else
    {
        std::cout << "未通过" << std::endl;
    }
    std::cout << std::endl
              << std::endl;
}

void test_strstr()
{
    std::cout << "开始测试函数 << my_strstr >> ..." << std::endl;

    const char *s = "jaldjqionekqnwjsfjdviozdfaier234WDAJdlDAKDie3j";
    const char *p[] = {"wjsfjdvioz", "qqqqq", "j"};

    bool pass = true;
    for (int i = 0; i < 3; i++)
        if (strstr(s, p[i]) != my_strstr(s, p[i]))
        {
            std::cout << "未通过，错误的子串为" << p[i] << std::endl;
            pass = false;
            break;
        }

    if (pass)
    {
        std::cout << "通过" << std::endl;
    }
    std::cout << std::endl
              << std::endl;
}

void test_hist_eq()
{
    std::cout << "开始测试函数 << hist_eq >> ..." << std::endl;
    const char *path = "./images/hist_eq/input.jpg";
    float *img;
    int h, w, c;

    imread(path, &img, &h, &w, &c);
    std::cout << "读取图片images/hist_eq/input.jpg，高度为" << h << "，高度为" << w
              << "，通道数为" << c
              << std::endl;

    hist_eq(img, h, w);

    const char *out_path = "../images/hist_eq/output.jpg";
    imwrite(out_path, img, h, w, 1);
    std::cout << "使用你的代码产生的结果已经保存为images/hist_eq/output.jpg"
              << std::endl
              << "可以与images/hist_eq/answer.jpg进行比较，看结果是否正确"
              << std::endl;

    free(img);
    std::cout << std::endl
              << std::endl;
}

void test_resize()
{
    const char *path = "./images/resize/input.jpg";
    float *img;
    int h, w, c;

    imread(path, &img, &h, &w, &c);
    std::cout << "读取图片images/resize/input.jpg，高度为" << h << "，高度为" << w
              << std::endl;

    float scales[2] = {2.0 / 3, 2};
    for (int i = 0; i < 2; i++)
    {
        float scale = scales[i];
        int new_w = w * scale, new_h = h * scale;
        std::cout << "将图片 resize 为原来的" << scale << "倍，即" << new_h << ", " << new_w
                  << std::endl;
        float *resized = fmalloc(new_h * new_w * c);
        resize(img, resized, h, w, c, scale);

        char out_path[] = "./images/resize/output .jpg";
        out_path[23] = '0' + i;
        imwrite(out_path, resized, new_h, new_w, c);
        std::cout << "使用你的代码产生的图片已经保存为"
                  << out_path << std::endl;

        free(resized);
    }
    free(img);
}

int main()
{
    std::cout << "开始测试函数 << my_strlen >> ..." << std::endl;
    test_strlen();
    std::cout << "开始测试函数 << my_strcat >> ..." << std::endl;
    test_strcat();
    std::cout << "开始测试函数 << my_strstr >> ..." << std::endl;
    test_strstr();
    std::cout << "开始测试函数 << rgb2gray >> ..." << std::endl;
    test_rgb2gray();
    std::cout << "开始测试函数 << resize >> ..." << std::endl;
    test_resize();
    std::cout << "开始测试函数 << hist_eq >> ..." << std::endl;
    test_hist_eq();
    return 0;
}
