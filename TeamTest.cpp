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

std::vector<std::vector<Pair<int, int>>> divideContestants(const std::vector<Contestant>& contestants);

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
	
	Team emptyTeam = Team(id, sport, nullptr);
	Team team = Team(id, sport, nullptr);
	Team team2 = Team(id, sport, nullptr);
};

class TeamWithContestantsFixture : public ::testing::Test
{
protected:
	int id = 20;
	
	Sport sport = Sport::SWIMMING;
	
	Country* country = new Country(1, 1000);
	/**
	 * vector of (id, strength)
	 */
	std::vector<Pair<int, int>> contestantData = {{3,  5},
												  {4,  70},
												  {1,  10},
												  {7,  4},
												  {6,  60},
												  {10, 50},
												  {8,  80},
												  {30, 13},
												  {2,  70},
												  {5,  70},
												  {11, 30}};
	
	Team team = Team(id, sport, country);
	
	void SetUp() override
	{
		for (const auto& pair : contestantData)
		{
			team.add_contestant(new Contestant(pair.get_first(), nullptr, sport, pair.get_second()));
		}
	}
};

class TeamUniteTest : public TeamWithContestantsFixture
{
protected:
	Team team2 = Team(id + 1, sport, country);
	
	Team teamWithDuplicate = Team(id + 2, sport, country);
	
	Team teamWithDifferentCountry = Team(id + 3, sport, new Country(2, 200));
	Team teamWithDifferenSport = Team(id + 4, Sport((static_cast<int>(sport) + 1 ) % 5), new Country(3, 300));
	
	std::vector<Pair<int, int>> team2ContestantData = {{12, 20},
													   {13, 30},
													   {14, 40},
													   {15, 50},
													   {16, 60},
													   {17, 70},
													   {18, 80},
													   {19, 90},
													   {20, 100},
													   {21, 110},
													   {22, 120},
													   {23, 130},
													   {24, 140}};
	std::vector<Pair<int, int>> teamWithDuplicateContestantData = {{3,  5},
																   {4,  70},
																   {20, 60},
																   {21, 50},
																   {25, 70},
																   {26, 80},
																   {27, 90},
																   {28, 100},
																   {29, 110},
																   {30, 120}};
	
	void SetUp() override
	{
		TeamWithContestantsFixture::SetUp(); // Call base fixture's SetUp
		
		for (const auto& pair : team2ContestantData)
		{
			team2.add_contestant(new Contestant(pair.get_first(), nullptr, sport, pair.get_second()));
		}
		
		
		for (const auto& pair : teamWithDuplicateContestantData)
		{
			teamWithDuplicate.add_contestant(new Contestant(pair.get_first(), nullptr, sport, pair.get_second()));
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
		auto allContestantsBefore = emptyTeam.all_contestants_to_vec();
		EXPECT_EQ(emptyTeam.add_contestant(new Contestant(pair.get_first(), nullptr, sport, pair.get_second())), SUCCESS);
		int groupSize = emptyTeam.get_size() / 3;
		for (const auto& group : emptyTeam.contestantTrees)
		{
			ASSERT_TRUE(group.is_valid());
			ASSERT_LE(group.get_size(), groupSize + 1);
			ASSERT_GE(group.get_size(), groupSize);
		}
		for (int i = 0; i < SUB_GROUPS - 1; ++i)
		{
			auto res1 = emptyTeam.contestantTrees[i].get_max();
			auto res2 = emptyTeam.contestantTrees[i + 1].get_min();
			if (res1.status() == SUCCESS && res2.status() == SUCCESS)
			{
				EXPECT_LT(res1.ans()->id, res2.ans()->id);
			}
		}
		allContestantsBefore.push_back(Contestant(pair.get_first(), nullptr, Sport::BOULDERING, pair.get_second()));
		for (auto contestant : allContestantsBefore)
		{
			int counter = 0;
			for (const auto& group : emptyTeam.contestantTrees)
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
		if (i == 9)
		{
			i = 0;
		}
		EXPECT_EQ(emptyTeam.add_contestant(new Contestant(pair.get_first(), nullptr, sport, pair.get_second())), SUCCESS);
	}
	output_t<int> output = emptyTeam.get_team_strength();
	EXPECT_EQ(output.status(), SUCCESS);
	EXPECT_EQ(27, output.ans());
	for (const auto& pair : vec3)
	{
		EXPECT_EQ(emptyTeam.remove_contestant(pair.get_first()), SUCCESS);
	}
	for (const auto& pair : vec4)
	{
		i++;
		if (i == 12)
		{
			i = 0;
		}
		EXPECT_EQ(emptyTeam.add_contestant(new Contestant(pair.get_first(), nullptr, sport, pair.get_second())), SUCCESS);
	}
	output_t<int> output2 = emptyTeam.get_team_strength();
	EXPECT_EQ(output2.status(), SUCCESS);
	EXPECT_EQ(888, output2.ans());
}

TEST_F(EmptyTeamFixture, AuterityMeasure)
{
	for (const auto& pair : vec2)
	{
		auto allContestantsBefore = emptyTeam.all_contestants_to_vec();
		EXPECT_EQ(emptyTeam.add_contestant(new Contestant(pair.get_first(), nullptr, sport, pair.get_second())), SUCCESS);
	}
	output_t<int> output = emptyTeam.austerity_measures();
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
		EXPECT_EQ(emptyTeam.remove_contestant(pair.get_first()), FAILURE);
	}
}

TEST_F(TeamWithContestantsFixture, RemoveContestant_NonExistent)
{
	int maxId = (*std::max_element(contestantData.begin(), contestantData.end(), [](Pair<int, int> pair1,
																					Pair<int, int> pair2) { return pair1.get_first() < pair2.get_first(); })).get_first();
	EXPECT_EQ(team.remove_contestant(maxId + 1), FAILURE);
}

TEST_F(EmptyTeamFixture, AddContestant_Strength)
{
	int counter = 0;
	std::vector<Pair<int, int>> contestantsEntered;
	std::vector<Pair<int, int>> first;
	std::vector<Pair<int, int>> second;
	std::vector<Pair<int, int>> third;
	std::vector<Pair<int, int>> thirds[3] = {third, first, second};
	int max[3] = {0, 0, 0};
	for (const auto& pair : contestantData)
	{
		emptyTeam.add_contestant(new Contestant(pair.get_first(), nullptr, Sport::SWIMMING, pair.get_second()));
		contestantsEntered.push_back(pair);
		counter++;
		std::sort(contestantsEntered.begin(), contestantsEntered.end());
		
		
		int strength = 0;
		if (counter % 3 == 0)
		{
			for (int i = 0; i < 3; ++i)
			{
				for (int j = 0; j < contestantsEntered.size() / 3; ++j)
				{
					thirds[i].push_back(contestantsEntered[i * (contestantsEntered.size() / 3) + j]);
				}
			}
			for (int i = 0; i < 3 && i < contestantsEntered.size(); ++i)
			{
				max[i] = std::max_element(thirds[i].begin(), thirds[i].end(), [](const Pair<int, int>& p1,
																				 const Pair<int, int>& p2) { return p1.get_second() < p2.get_second(); })->get_second();
			}
			strength = max[0] + max[1] + max[2];
		}
		ASSERT_EQ(emptyTeam.get_team_strength(), strength);
	}
}

TEST_F(TeamWithContestantsFixture, RemoveContestant_Strength)
{
	int counter = team.get_size();
	std::vector<Contestant> contestantsRemoved = team.all_contestants_to_vec();
	std::vector<Pair<int, int>> first;
	std::vector<Pair<int, int>> second;
	std::vector<Pair<int, int>> third;
	std::vector<std::vector<Pair<int, int>>> thirds = {third, first, second};
	int max[3] = {0, 0, 0};
	for (const auto& pair : contestantData)
	{
		team.remove_contestant(pair.get_first());
		contestantsRemoved.erase(
				std::remove_if(contestantsRemoved.begin(), contestantsRemoved.end(), [pair](Contestant contestant) {
					return contestant.id == pair.get_first();
				}), contestantsRemoved.end());;
		counter--;
		std::sort(contestantsRemoved.begin(), contestantsRemoved.end(), [](Contestant c1, Contestant c2) {
			return c1.id < c2.id;
		});
		
		
		int strength = 0;
		if (counter % 3 == 0)
		{
			
			thirds = divideContestants(contestantsRemoved);
			
			for (int i = 0; i < 3 && i < contestantsRemoved.size(); ++i)
			{
				max[i] = std::max_element(thirds[i].begin(), thirds[i].end(), [](const Pair<int, int>& p1,
																				 const Pair<int, int>& p2) { return p1.get_second() < p2.get_second(); })->get_second();
			}
			strength = max[0] + max[1] + max[2];
		}
		ASSERT_EQ(team.get_team_strength(), strength);
	}
}


TEST_F(TeamUniteTest, SameCountryAndSport)
{
	EXPECT_EQ(SUCCESS, team.unite(&team2));
}

TEST_F(TeamUniteTest, DifferentCountries)
{
	EXPECT_EQ(FAILURE, team.unite(&teamWithDifferentCountry));
}

TEST_F(TeamUniteTest, DifferentSports)
{
	EXPECT_EQ(FAILURE, team.unite(&teamWithDifferenSport));
}

TEST_F(TeamUniteTest, OverlappingPlayers)
{
	EXPECT_EQ(SUCCESS, team.unite(&teamWithDuplicate));
}

TEST_F(TeamUniteTest, NoOverlappingPlayers)
{
	EXPECT_EQ(SUCCESS, team.unite(&team2));
}

std::vector<std::vector<Pair<int, int>>> divideContestants(const std::vector<Contestant>& contestants)
{
	std::vector<std::vector<Contestant>> dividedGroups(3);
	std::vector<std::vector<Pair<int, int>>> res(3);
	int groupSize = contestants.size() / 3;
	
	// Copy contestants to a temporary vector to allow shuffling
	std::vector<Contestant> tempContestants = contestants;
	
	// Divide contestants into three groups
	for (int i = 0; i < 3; ++i)
	{
		dividedGroups[i].reserve(groupSize);
		std::copy_n(tempContestants.begin() + i * groupSize, groupSize, std::back_inserter(dividedGroups[i]));
		for (auto contestant : dividedGroups[i])
		{
			res[i].push_back({contestant.id, contestant.get_strength()});
		}
	}
	return res;
}

TEST_F(EmptyTeamFixture, GetContestantStrength)
{
	for (const auto& pair : vec)
	{
		EXPECT_EQ(team.add_contestant(new Contestant(pair.get_first(), nullptr, sport, pair.get_second())), SUCCESS);
	}
	for (const auto& pair : vec2)
	{
		EXPECT_EQ(team.add_contestant(new Contestant(pair.get_first(), nullptr, sport, pair.get_second())), SUCCESS);
	}
	for (const auto& pair : vec)
	{
		EXPECT_EQ(emptyTeam.add_contestant(new Contestant(pair.get_first(), nullptr, sport, pair.get_second())),
				  SUCCESS);
	}
	for (const auto& pair : vec2)
	{
		EXPECT_EQ(team2.add_contestant(new Contestant(pair.get_first(), nullptr, sport, pair.get_second())), SUCCESS);
	}
	
	emptyTeam.unite(&team2);
	auto vec1 = emptyTeam.all_contestants_to_vec();
	auto vec2 = team.all_contestants_to_vec();
	assert(vec1.size() == vec2.size());
	for (int i = 0; i < vec1.size(); ++i)
	{
		EXPECT_EQ(vec1[i].id, vec2[i].id);
		EXPECT_EQ(vec1[i].get_strength(), vec2[i].get_strength());
	}
	
}



