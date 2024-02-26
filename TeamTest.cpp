//
// Created by Lior on 24/02/2024.
//
#include "gtest/gtest.h"
#include "../wet1util.h"
#include "../Pair.h"
#include "../Team.h"

#define SUCCESS StatusType::SUCCESS
#define FAILURE StatusType::FAILURE
#define SUITE TeamTest

class EmptyTeamFixture : public ::testing::Test
{
protected:
	int id = 20;
	
	Sport sport = Sport::SWIMMING;
	
//	AVL_Tree<int, Contestant*> contestantTrees[SUB_GROUPS] = {AVL_Tree<int, Contestant*>(),
//															  AVL_Tree<int, Contestant*>(),
//															  AVL_Tree<int, Contestant*>()};
//
//	AVL_Tree<Pair<int, int>, Contestant*> contestantsByStrength[SUB_GROUPS] = {AVL_Tree<Pair<int, int>, Contestant*>(),
//																			   AVL_Tree<Pair<int, int>, Contestant*>(),
//																			   AVL_Tree<Pair<int, int>, Contestant*>()};
	
	std::vector<Pair<int, int>> vec = {{0,  5},
									   {4,  70},
									   {1,  70},
									   {7,  70},
									   {6,  70},
									   {10, 50},
									   {8,  70},
									   {30, 13},
									   {2,  70},
									   {5,  70},
									   {11, 30}};
	
	Team team = Team(id, sport, nullptr);
};

class TeamFixture : public ::testing::Test
{
protected:
	int id;
	
	Sport sport;
	
	AVL_Tree<int, Contestant*> contestantTrees[SUB_GROUPS] = {AVL_Tree<int, Contestant*>(),
															  AVL_Tree<int, Contestant*>(),
															  AVL_Tree<int, Contestant*>()};;
	
	AVL_Tree<Pair<int, int>, Contestant*> contestantsByStrength[SUB_GROUPS] = {AVL_Tree<Pair<int, int>, Contestant*>(),
																			   AVL_Tree<Pair<int, int>, Contestant*>(),
																			   AVL_Tree<Pair<int, int>, Contestant*>()};;
	
	std::vector<Pair<int, int>> vec = {{0,  5},
									   {4,  70},
									   {1,  70},
									   {7,  70},
									   {6,  70},
									   {10, 50},
									   {8,  70},
									   {30, 13},
									   {2,  70},
									   {5,  70},
									   {11, 30}};
	
	Team team = Team(id, sport, nullptr);
	
	void SetUp() override
	{
		for (auto pair : vec)
		{
			team.add_contestant(new Contestant(pair.get_first(), nullptr, sport, pair.get_second()));
		}
	}
};

TEST_F(EmptyTeamFixture, Constructor)
{
	auto team = Team(id, sport, nullptr);
	EXPECT_EQ(team.get_id(), id);
	EXPECT_EQ(team.get_sport(), sport);
	EXPECT_EQ(team.get_country(), nullptr);
	EXPECT_EQ(team.get_size(), 0);
	EXPECT_TRUE(team.is_empty());
}

TEST_F(EmptyTeamFixture, AddContestant)
{
	for (const auto& pair : vec)
	{
		auto allContestantsBefore = team.all_contestants_to_vec();
		EXPECT_EQ(team.add_contestant(new Contestant(pair.get_first(), nullptr, sport, pair.get_second())), SUCCESS);
//		EXPECT_EQ(team.contestantTrees[0].find(1).status(), SUCCESS);
		int groupSize = team.get_size() / 3;
		for (const auto& group : team.contestantTrees)
		{
			
			dsdi
			ASSERT_TRUE(group.is_valid());
			ASSERT_LE(group.get_size(), groupSize + 1);
			ASSERT_GE(group.get_size(), groupSize);
		}
		for (int i = 0; i < SUB_GROUPS - 1; ++i)
		{
			auto res1 = team.contestantTrees[i].get_max();
			auto res2 = team.contestantTrees[i + 1].get_min();
			if (res1.status() == SUCCESS && res2.status() == SUCCESS)
			{
				EXPECT_LT(res1.ans()->id, res2.ans()->id);
			}
		}
		allContestantsBefore.push_back(Contestant(pair.get_first(), nullptr, Sport::BOULDERING, pair.get_second()));
		for (auto contestant : allContestantsBefore)
		{
			int counter = 0;
			for (const auto& group : team.contestantTrees)
			{
				if (group.find(contestant.id).status() == SUCCESS)
				{
					++counter;
				}
			}
			EXPECT_EQ(counter, 1);
		}
	}
}

