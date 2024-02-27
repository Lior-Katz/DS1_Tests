//
// Created by Lior on 24/02/2024.
//
#include "gtest/gtest.h"
#include "../wet1util.h"
#include "../Pair.h"
#include "../Team.h"
#include "algorithm"

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
	
	std::vector<Pair<int, int>> contestantData = {{3,  5},
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
	
	std::vector<Pair<int, int>> vec2 = {{1,   2},
										{4,   5},
										{6,   3},
										{10,  10},
										{16,  11},
										{20,  15},
										{100, 7},
										{101, 6},
										{102, 4}};
	
	std::vector<Pair<int, int>> vec3 = {{1,   2},
											 {4,   5},
											 {6,   3},
											 {10,  10},
											 {16,  11},
											 {20,  15},
											 {100, 7},
											 {101, 6},
											 {102, 4}};
	
	std::vector<Pair<int, int>> vec4 = {{1,   800},
											 {2,   700},
											 {3,   600},
											 {4,   500},
											 {10,  80},
											 {20,  70},
											 {30,  60},
											 {40,  50},
											 {100, 8},
											 {200, 7},
											 {300, 6},
											 {400, 5}};
	
	Team team = Team(id, sport, nullptr);
};

class TeamWithContestantsFixture : public ::testing::Test
{
protected:
	int id = 20;
	
	Sport sport = Sport::SWIMMING;
	
	/**
	 * vector of (id, strength)
	 */
	std::vector<Pair<int, int>> contestantData = {{3,  5},
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
		for (const auto& pair : contestantData)
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
	for (const auto& pair : contestantData)
	{
		auto allContestantsBefore = team.all_contestants_to_vec();
		EXPECT_EQ(team.add_contestant(new Contestant(pair.get_first(), nullptr, sport, pair.get_second())), SUCCESS);
		int groupSize = team.get_size() / 3;
		for (const auto& group : team.contestantTrees)
		{
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

TEST_F(EmptyTeamFixture, TeamStengthMeasure)
{
	int i = 0;
	for (const auto& pair : vec3)
	{
		i++;
		if(i==9)
		{
			i = 0;
		}
		EXPECT_EQ(team.add_contestant(new Contestant(pair.get_first(), nullptr, sport, pair.get_second())), SUCCESS);
	}
	output_t<int> output = team.get_team_strength();
	EXPECT_EQ(output.status(), SUCCESS);
	EXPECT_EQ(27, output.ans());
	for (const auto& pair : vec3)
	{
		EXPECT_EQ(team.remove_contestant(pair.get_first()), SUCCESS);
	}
	for (const auto& pair : vec4)
	{
		i++;
		if(i==12)
		{
			i=0;
		}
		EXPECT_EQ(team.add_contestant(new Contestant(pair.get_first(), nullptr, sport, pair.get_second())), SUCCESS);
	}
	output_t<int> output2 = team.get_team_strength();
	EXPECT_EQ(output2.status(), SUCCESS);
	EXPECT_EQ(888, output2.ans());
}

TEST_F(EmptyTeamFixture, AuterityMeasure)
{
	for (const auto& pair : vec2)
	{
		auto allContestantsBefore = team.all_contestants_to_vec();
		EXPECT_EQ(team.add_contestant(new Contestant(pair.get_first(), nullptr, sport, pair.get_second())), SUCCESS);
	}
	output_t<int> output = team.austerity_measures();
	EXPECT_EQ(output.status(), SUCCESS);
	EXPECT_EQ(32, output.ans());
}

TEST_F(TeamWithContestantsFixture, AddContestat_Exists)
{
	for (const auto& pair : contestantData)
	{
		EXPECT_EQ(team.add_contestant(new Contestant(pair.get_first(), nullptr, Sport::SWIMMING, pair.get_second())),
				  FAILURE);
	}
}

TEST_F(TeamWithContestantsFixture, RemoveContestant)
{
	for (const auto& pair : contestantData)
	{
		auto allContestantsBefore = team.all_contestants_to_vec();
		EXPECT_EQ(team.remove_contestant(pair.get_first()), SUCCESS);
		int groupSize = team.get_size() / 3;
		for (const auto& group : team.contestantTrees)
		{
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
		allContestantsBefore.erase(
				std::remove_if(allContestantsBefore.begin(), allContestantsBefore.end(), [pair](Contestant contestant) {
					return contestant.id == pair.get_first();
				}), allContestantsBefore.end());
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

TEST_F(EmptyTeamFixture, RemoveContestant_NonExistent_EmptyTeam)
{
	for (const auto& pair : contestantData)
	{
		EXPECT_EQ(team.remove_contestant(pair.get_first()), FAILURE);
	}
}

TEST_F(TeamWithContestantsFixture, RemoveContestant_NonExistent)
{
	int maxId = (*std::max_element(contestantData.begin(), contestantData.end(), [](Pair<int, int> pair1,
																					Pair<int, int> pair2) { return pair1.get_first() < pair2.get_first(); })).get_first();
	EXPECT_EQ(team.remove_contestant(maxId + 1), FAILURE);
}









