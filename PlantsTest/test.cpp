#include "pch.h"
#include "../Plants/Garden.h"
#include "../Plants/Garden.cpp"

TEST(TestCaseName, TestName_1) {
  EXPECT_EQ(1, 1);
  cout << "expect true" << endl;
}
//
//TEST(TestCaseName, TestName_2) {
//	EXPECT_EQ(1, 2);
//	cout << "expect false" << endl;
//}

struct MyClassCombo : public testing::Test {
	Tree *tree;
	Shrub *shrub;
	Flower *flower;
	ifstream file_i;
	void SetUp() 
	{ 
		tree = new Tree; 
		shrub = new Shrub;
		flower = new Flower;
	}
	void Erase() { delete tree; delete shrub; delete flower;}

};

struct MyClassShrub : public testing::Test {
	Shrub *shrub;
	ifstream file_i;
	void SetUp()
	{
		shrub = new Shrub;
	}
	void Erase() { delete shrub; }

};

struct MyClassFlower : public testing::Test {
	Flower *flower;
	ifstream file_i;
	void SetUp()
	{
		flower = new Flower;
	}
	void Erase() { delete flower; }

};

TEST_F(MyClassCombo, EmptyFileTest)
{
	file_i.open("Test1_empty.txt");
	tree = InTree(file_i);
	ASSERT_EQ(-1, tree->age);
	shrub = InShrub(file_i);
	ASSERT_EQ(0, shrub->month);
	flower = InFlower(file_i);
	ASSERT_EQ(0, flower->type);
	file_i.close();
}

TEST_F(MyClassCombo, WrongFileFormatTest)
{
	file_i.open("Test2_Wrong_Format.txt");
	tree = InTree(file_i);
	ASSERT_EQ(-2, tree->age);
	shrub = InShrub(file_i);
	ASSERT_EQ(0, shrub->month);
	flower = InFlower(file_i);
	ASSERT_EQ(0, flower->type);
	file_i.close();
}
/*int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}*/