#include "pch.h"
#include "../Plants/Garden.h"
#include "../Plants/Garden.cpp"

struct MyClassCombo : public testing::Test {
	Tree *tree;
	Shrub *shrub;
	Flower *flower;
	ifstream file_i;
	void SetUp() { 
		tree = new Tree; 
		shrub = new Shrub;
		flower = new Flower;
	}
	void Erase() { delete tree; delete shrub; delete flower;}

};

TEST_F(MyClassCombo, EmptyFileTest)
{
	file_i.open("Test1_empty.txt");
	tree = InTree(file_i);
	ASSERT_EQ(-1, tree->age);
	file_i.close();
	file_i.open( "Test1_empty.txt" );
	shrub = InShrub(file_i);
	ASSERT_EQ(0, shrub->month);
	file_i.close();
	file_i.open( "Test1_empty.txt" );
	flower = InFlower(file_i);
	ASSERT_EQ(0, flower->type);
	file_i.close();
}

TEST_F(MyClassCombo, WrongFileFormatTest)
{
	file_i.open("Test2_Wrong_Format.txt");
	tree = InTree(file_i);
	ASSERT_EQ(-3, tree->age);
	file_i.close();
	file_i.open( "Test1_empty.txt" );
	shrub = InShrub(file_i);
	ASSERT_EQ(0, shrub->month);
	file_i.close();
	file_i.open( "Test1_empty.txt" );
	flower = InFlower(file_i);
	ASSERT_EQ(0, flower->type);
	file_i.close();
}

TEST_F(MyClassCombo, WrongFileFormatTest2)
{
	file_i.open("Test3_Wrong_Format.txt");
	tree = InTree(file_i);
	ASSERT_EQ(0, tree->age);
	file_i.close();
	file_i.open( "Test1_empty.txt" );
	shrub = InShrub(file_i);
	ASSERT_EQ(0, shrub->month);
	file_i.close();
	file_i.open( "Test1_empty.txt" );
	flower = InFlower(file_i);
	ASSERT_EQ(0, flower->type);
	file_i.close();
}

TEST_F(MyClassCombo, WrongFileFormatTest3)
{
	file_i.open("Test4_Wrong_Format.txt");
	tree = InTree(file_i);
	ASSERT_EQ(-3, tree->age);
	file_i.close();
	file_i.open( "Test1_empty.txt" );
	shrub = InShrub(file_i);
	ASSERT_EQ(0, shrub->month);
	file_i.close();
	file_i.open( "Test1_empty.txt" );
	flower = InFlower(file_i);
	ASSERT_EQ(0, flower->type);
	file_i.close();
}

TEST_F(MyClassCombo, WrongFileFormatTest4)
{
	file_i.open("Test5_Wrong_Format.txt");
	tree = InTree(file_i);
	ASSERT_EQ(-2, tree->age);
	file_i.close();
	file_i.open( "Test1_empty.txt" );
	shrub = InShrub(file_i);
	ASSERT_EQ(0, shrub->month);
	file_i.close();
	file_i.open( "Test1_empty.txt" );
	flower = InFlower(file_i);
	ASSERT_EQ(0, flower->type);
	file_i.close();
}

TEST_F(MyClassCombo, WrongPlantInTest)
{
	file_i.open("Test1_empty.txt");
	Plant *res = InPlant(file_i);
	EXPECT_FALSE(res);
	file_i.close();
}

TEST_F(MyClassCombo, WrongPlantInTest2)
{
	file_i.open("Test6_empty.txt");
	Plant *res = InPlant(file_i);
	EXPECT_FALSE(res);
	file_i.close();
}
/*int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}*/