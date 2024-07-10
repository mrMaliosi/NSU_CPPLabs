#include "../bitset/bitset.h"
#include <gtest/gtest.h>



////////////TestBitsetCreation////////////
TEST(TestBitset, simple_test1){
    BitArray first;
    ASSERT_EQ(first.size(), 0);
}

TEST(TestBitset, simple_test2){
    BitArray first(1, 1);
    ASSERT_EQ(first[31], 1);
}

////////////TestBitsetSwap////////////
TEST(TestBitset, simple_test3){
    BitArray first(1, 2);
    BitArray second(1, 1);
    first.swap(second);
    ASSERT_EQ(first[31], 1);
    ASSERT_EQ(second[30], 1);
}

////////////TestBitsetResize////////////
TEST(TestBitset, simple_test4){
    BitArray first(32, 1);
    first.resize(33, 0);
    BitArray second(33, 1);
    second.push_back(0);
    std::string s1 = first.to_string();
    std::string s2 = second.to_string();
    std::cout << first[0] << " " << second[0] << std::endl;
    std::cout << first.maxSize_ << " " << second.maxSize_ << std::endl;
    std::cout << first.size_ << " " << second.size_ << std::endl;
    std::cout << first.bytes_ << " " << second.bytes_ << std::endl;
    std::cout << first.to_string() << " " << second.to_string() << std::endl;
    if (first == second)
    {
        std::cout << 1 << std::endl;
    }
    std::cout << 0 << std::endl;

    ASSERT_TRUE(first == second);
}

TEST(TestBitset, simple_test5){
    BitArray first(33, 1);
    first.resize(1, 0);
    BitArray second(1, 0);
    ASSERT_TRUE(first == second);
}

////////////TestBitsetRavno////////////
TEST(TestBitset, simple_test6)
{
    BitArray first(33, 1);
    BitArray second = first;
    std::cout << first.to_string() << std::endl;
    std::cout << second.to_string() << std::endl;
    ASSERT_TRUE(first == second);
}

////////////TestBitsetClear////////////
TEST(TestBitset, simple_test7)
{
    BitArray first(33, 1);
    first.clear();

    ASSERT_TRUE(first.size() == 0);
}

////////////TestBitsetPush_back////////////
TEST(TestBitset, simple_test8)
{
    BitArray first(33, 1);
    first.push_back(1);
    // std::cout << first.size_ << std::endl;
    // std::cout << first.bits_[1] << std::endl;
    // std::cout << first.to_string() << std::endl;
    ASSERT_TRUE(first[32] == 1);
}

TEST(TestBitset, simple_test9)
{
    BitArray first(33, 1);
    first.push_back(0);
    ASSERT_TRUE(first[32] == 0);
}

////////////TestBitsetOperator////////////
TEST(TestBitset, simple_test10)
{
    BitArray first(32, 1);
    std::cout << first.to_string() << std::endl;
    first <<= 31;
    std::cout << first.to_string() << std::endl;
    ASSERT_TRUE(first[0] == 1);
}

TEST(TestBitset, simple_test11)
{
    BitArray first(32, 1);
    BitArray second(64, 2);
    ASSERT_TRUE(first != second);
}

TEST(TestBitset, simple_test12)
{
    BitArray first(32, 1);
    BitArray second(32, 1);
    BitArray nul(32, 0);
    second ^= first;
    std::cout << second.to_string() << std::endl;
    std::cout << nul.to_string() << std::endl;
    ASSERT_TRUE(second == nul);
}

TEST(TestBitset, simple_test13)
{
    BitArray first(32, 1);
    std::cout << first.to_string() << std::endl;
    first >>= 1;
    std::cout << first.to_string() << std::endl;
    ASSERT_TRUE(first[31] == 0);
}

TEST(TestBitset, simple_test14)
{
    BitArray first(32, 1);
    std::cout << first.to_string() << std::endl;
    first >>= 100;
    std::cout << first.to_string() << std::endl;
    ASSERT_TRUE(first[31] == 0);
}

TEST(TestBitset, simple_test15)
{
    BitArray first(32, 1);
    first = first >> 1;
    ASSERT_TRUE(first[31] == 0);
}

TEST(TestBitset, simple_test16)
{
    BitArray first(32, 1);
    first = first >> 100;
    ASSERT_TRUE(first[31] == 0);
}

TEST(TestBitset, simple_test17)
{
    BitArray first(32, 1);
    first = first << 33;
    ASSERT_TRUE(first[0] == 0);
}

////////////TestBitsetSet////////////
TEST(TestBitset, simple_test18)
{
    BitArray first(32, 1);
    first.set();
    for (int i = 0; i < 32; ++i)
    {
        ASSERT_EQ(first[i], 1);
    }
}

//

////////////TestBitsetReset////////////
TEST(TestBitset, simple_test19)
{
    BitArray first(1, 1);
    first.reset();
    for (int i = 0; i < 32; ++i)
    {
        ASSERT_EQ(first[i], 0);
    }
}

////////////TestBitsetAny////////////
TEST(TestBitset, simple_test20)
{
    BitArray first(1, 1);
    ASSERT_EQ(first.any(), 1);
}

////////////TestBitsetNone////////////
TEST(TestBitset, simple_test21)
{
    BitArray first(1, 0);
    ASSERT_EQ(first.none(), 1);
}

////////////TestBitsetCount////////////
TEST(TestBitset, simple_test22)
{
    BitArray first(32, 1);
    ASSERT_EQ(first.count(), 1);
}


 int main(int argc, char** argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
 }