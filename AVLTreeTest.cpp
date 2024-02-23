//
// Created by Lior on 23/02/2024.
//

#include "gtest/gtest.h"
#include "../AVL_Tree.h"
TEST(AVLTreeTest, Constructor)
{
	AVL_Tree<int, int> tree = AVL_Tree<int, int>();
	EXPECT_EQ(tree.get_size(), 0);
	EXPECT_EQ(tree.get_max().status(), StatusType::FAILURE);
	EXPECT_EQ(tree.get_min().status(), StatusType::FAILURE);
	EXPECT_EQ(tree.find(0).status(), StatusType::FAILURE);
	EXPECT_EQ(tree.get_rank(0), 0);
	EXPECT_EQ(tree.select_rank(1).status(), StatusType::FAILURE);
	std::vector<Pair<int, int>> res = std::vector<Pair<int, int>>();
	EXPECT_EQ(tree.to_vec(), res);
	std::stringstream ss;
	tree.inorder(ss);
	EXPECT_EQ(ss.str(), "");
}

TEST(AVLTreeTest, Insert)
{

}
