#include "../field/field.h"
#include "../MagicWord/MagicWord.h"
#include "../UI/UI.h"
#include <gtest/gtest.h>

TEST(Testfield, cube){
    int prov = 1;
    UI q(50, 0);
    ifstream in("Test_files/1-1i.txt");
    if (in.is_open() == 0)
	{
		cout << "Входной файл не найден. Возможно, неправильно указан путь." << endl;
	}
    q.parcer(in);
    q.next_tick(q.born_rule1, q.born_rule2, q.survival_rule1, q.survival_rule2);
    ofstream f("Test_files/1-1o.txt");
    q.dump(f, "Test_files/1-1o.txt", q.name);
    in.close();
    f.close();
    ifstream in1("Test_files/1-1o.txt");
    ifstream in2("Test_files/1-1c.txt");
    string s1, s2;
    while ((getline(in1, s1))&&(getline(in2, s2)))
    {
        if (s1 != s2)
        {
            prov = 0;
            break;
        }
    }
    ASSERT_TRUE(prov == 1);
}

TEST(Testfield, blinker){
    int prov = 1;
    UI q(50, 0);
    ifstream in("Test_files/2-1i.txt");
    if (in.is_open() == 0)
	{
		cout << "Входной файл не найден. Возможно, неправильно указан путь." << endl;
	}
    q.parcer(in);
    q.next_tick(q.born_rule1, q.born_rule2, q.survival_rule1, q.survival_rule2);
    ofstream f("Test_files/2-1o.txt");
    q.dump(f, "Test_files/2-1o.txt", q.name);
    in.close();
    f.close();
    ifstream in1("Test_files/2-1o.txt");
    ifstream in2("Test_files/2-1c.txt");
    string s1, s2;
    while ((getline(in1, s1))&&(getline(in2, s2)))
    {
        if (s1 != s2)
        {
            prov = 0;
            break;
        }
    }
    ASSERT_TRUE(prov == 1);
}

TEST(Testfield, beacon){
    int prov = 1;
    UI q(50, 0);
    ifstream in("Test_files/3-1i.txt");
    if (in.is_open() == 0)
	{
		cout << "Входной файл не найден. Возможно, неправильно указан путь." << endl;
	}
    q.parcer(in);
    q.next_tick(q.born_rule1, q.born_rule2, q.survival_rule1, q.survival_rule2);
    ofstream f("Test_files/3-1o.txt");
    q.dump(f, "Test_files/3-1o.txt", q.name);
    in.close();
    f.close();
    ifstream in1("Test_files/3-1o.txt");
    ifstream in2("Test_files/3-1c.txt");
    string s1, s2;
    while ((getline(in1, s1))&&(getline(in2, s2)))
    {
        if (s1 != s2)
        {
            prov = 0;
            break;
        }
    }
    ASSERT_TRUE(prov == 1);
}

TEST(Testfield, glider){
    int prov = 1;
    UI q(50, 0);
    ifstream in("Test_files/4-1i.txt");
    if (in.is_open() == 0)
	{
		cout << "Входной файл не найден. Возможно, неправильно указан путь." << endl;
	}
    q.parcer(in);
    q.next_tick(q.born_rule1, q.born_rule2, q.survival_rule1, q.survival_rule2);
    ofstream f("Test_files/4-1o.txt");
    q.dump(f, "Test_files/4-1o.txt", q.name);
    q.next_tick(q.born_rule1, q.born_rule2, q.survival_rule1, q.survival_rule2);
    f.close();
    f.open("Test_files/4-2o.txt");
    q.dump(f, "Test_files/4-2o.txt", q.name);
    q.next_tick(q.born_rule1, q.born_rule2, q.survival_rule1, q.survival_rule2);
    f.close();
    f.open("Test_files/4-3o.txt");
    q.dump(f, "Test_files/4-3o.txt", q.name);
    q.next_tick(q.born_rule1, q.born_rule2, q.survival_rule1, q.survival_rule2);
    f.close();
    f.open("Test_files/4-4o.txt");
    q.dump(f, "Test_files/4-4o.txt", q.name);
    in.close();
    f.close();
    string s1, s2;
    ifstream in1("Test_files/4-1o.txt");
    ifstream in2("Test_files/4-1c.txt");
    while ((getline(in1, s1))&&(getline(in2, s2)))
    {
        if (s1 != s2)
        {
            prov = 0;
            break;
        }
    }
    in1.close();
    in2.close();
    in1.open("Test_files/4-2o.txt");
    in2.open("Test_files/4-2c.txt");
    while ((getline(in1, s1))&&(getline(in2, s2)))
    {
        if (s1 != s2)
        {
            prov = 0;
            break;
        }
    }
    in1.close();
    in2.close();
    in1.open("Test_files/4-3o.txt");
    in2.open("Test_files/4-3c.txt");
    while ((getline(in1, s1))&&(getline(in2, s2)))
    {
        if (s1 != s2)
        {
            prov = 0;
            break;
        }
    }
    in1.close();
    in2.close();
    in1.open("Test_files/4-4o.txt");
    in2.open("Test_files/4-4c.txt");
    while ((getline(in1, s1))&&(getline(in2, s2)))
    {
        if (s1 != s2)
        {
            prov = 0;
            break;
        }
    }
    in1.close();
    in2.close();
    ASSERT_TRUE(prov == 1);
}

 int main(int argc, char** argv){
    setlocale(LC_CTYPE, "rus");
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
 }