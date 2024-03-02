//#define SUCCESS StatusType::SUCCESS
//#define FAILURE StatusType::FAILURE
#define SUITE OlympicsTest

//#define TEST_FRIENDS \
//    friend class SUITE_Constructor_Test;
#include "../Olympicsa1.h"
#include "../wet1util.h"
#include "gtest/gtest.h"
#include "algorithm"
//
//

class EmptyOlympicsFixture : public ::testing::Test
{
protected:
	Olympics olympics = Olympics();
	
	std::vector<Pair<int, int>> countryData = {{1,  2},
											   {3,  100},
											   {4,  200},
											   {5,  50},
											   {6,  300},
											   {7,  0},
											   {8,  150},
											   {9,  250},
											   {10, 180}};
};

class OlympicsWithCountriesFixture : public ::testing::Test
{
protected:
	Olympics olympics;
	
	std::vector<Pair<int, int>> countryData = {{1,  2},
											   {2,  10},
											   {3,  100},
											   {4,  200},
											   {5,  50},
											   {6,  300},
											   {7,  75},
											   {8,  150},
											   {9,  250},
											   {10, 180}};
	
	std::vector<std::tuple<int, int, Sport>> teamData = {{101, 1, Sport::BOULDERING},
														 {102, 1, Sport::ACROBATICS},
														 {103, 1, Sport::FOOTBALL},
														 {104, 2, Sport::SWIMMING},
														 {105, 2, Sport::SPINNING},
														 {106, 3, Sport::BOULDERING},
														 {107, 3, Sport::ACROBATICS},
														 {108, 3, Sport::FOOTBALL},
														 {109, 4, Sport::SWIMMING},
														 {110, 4, Sport::SPINNING},
														 {6,   6, Sport::SPINNING}};
	
	std::vector<std::tuple<int, int, Sport, int>> contestantData = {{1,  1, Sport::BOULDERING, 100},
																	{2,  1, Sport::ACROBATICS, 150},
																	{3,  1, Sport::FOOTBALL,   200},
																	{4,  1, Sport::SWIMMING,   120},
																	{5,  1, Sport::SPINNING,   180},
																	{6,  1, Sport::BOULDERING, 90},
																	{7,  1, Sport::ACROBATICS, 160},
																	{8,  1, Sport::FOOTBALL,   220},
																	{9,  1, Sport::SWIMMING,   140},
																	{10, 1, Sport::SPINNING,   200}};
	
	void SetUp() override
	{
		for (auto pair : countryData)
		{
			olympics.add_country(pair.get_first(), pair.get_second());
		}
	}
};

class OlympicsWithTeamsFixture : public ::testing::Test
{
protected:
	Olympics olympics = Olympics();
	
	std::vector<Pair<int, int>> countryData = {{1,  2},
											   {2,  10},
											   {3,  100},
											   {4,  200},
											   {5,  50},
											   {6,  300},
											   {7,  75},
											   {8,  150},
											   {9,  250},
											   {10, 180}};
	
	std::vector<std::tuple<int, int, Sport>> teamData = {{101, 1, Sport::BOULDERING},
														 {102, 1, Sport::ACROBATICS},
														 {103, 1, Sport::FOOTBALL},
														 {104, 2, Sport::SWIMMING},
														 {105, 2, Sport::SPINNING},
														 {106, 3, Sport::BOULDERING},
														 {107, 3, Sport::ACROBATICS},
														 {108, 3, Sport::FOOTBALL},
														 {109, 4, Sport::SWIMMING},
														 {110, 4, Sport::SPINNING},
														 {6,   6, Sport::SPINNING}};
	
	void SetUp() override
	{
		for (auto pair : countryData)
		{
			olympics.add_country(pair.get_first(), pair.get_second());
		}
		
		for (auto tup : teamData)
		{
			olympics.add_team(std::get<0>(tup), std::get<1>(tup), std::get<2>(tup));
		}
	}
};

class OlympicsWithContestantsFixture : public ::testing::Test
{
protected:
	Olympics olympics = Olympics();
	
	std::vector<Pair<int, int>> countryData = {{1,  2},
											   {2,  10},
											   {3,  100},
											   {4,  200},
											   {5,  50},
											   {6,  300},
											   {7,  75},
											   {8,  150},
											   {9,  250},
											   {10, 180}};
	
	std::vector<std::tuple<int, int, Sport, int>> contestantData = {{1,  1, Sport::BOULDERING, 100},
																	{2,  1, Sport::ACROBATICS, 150},
																	{3,  1, Sport::FOOTBALL,   200},
																	{4,  1, Sport::SWIMMING,   120},
																	{5,  1, Sport::SPINNING,   180},
																	{6,  1, Sport::BOULDERING, 90},
																	{7,  1, Sport::ACROBATICS, 160},
																	{8,  1, Sport::FOOTBALL,   220},
																	{9,  1, Sport::SWIMMING,   140},
																	{10, 1, Sport::SPINNING,   200}};
	
	void SetUp() override
	{
		for (auto pair : countryData)
		{
			olympics.add_country(pair.get_first(), pair.get_second());
		}
		
		for (auto tup : contestantData)
		{
			olympics.add_contestant(std::get<0>(tup), std::get<1>(tup), std::get<2>(tup), std::get<3>(tup));
		}
	}
};

//class OlympicsWithContestantsInTeamsFixture : public ::testing::Test
//{
//protected:
//	Olympics olympics = Olympics();
//
//	std::vector<Pair<int, int>> countryData = {{1,  2},
//											   {2,  10},
//											   {3,  100},
//											   {4,  200},
//											   {5,  50},
//											   {6,  300},
//											   {7,  75},
//											   {8,  150},
//											   {9,  250},
//											   {10, 180}};
//
//	std::vector<std::tuple<int, int, Sport>> teamData = {{101, 1, Sport::BOULDERING},
//														 {102, 1, Sport::ACROBATICS},
//														 {103, 1, Sport::FOOTBALL},
//														 {104, 2, Sport::SWIMMING},
//														 {105, 2, Sport::SPINNING},
//														 {106, 3, Sport::BOULDERING},
//														 {107, 3, Sport::ACROBATICS},
//														 {108, 3, Sport::FOOTBALL},
//														 {109, 4, Sport::SWIMMING},
//														 {110, 4, Sport::SPINNING}};
//
//	std::vector<std::tuple<int, int, int, Sport, int>> contestantData = {{1,  101, 1, Sport::BOULDERING, 100},
//																		 {1,  102, 1, Sport::ACROBATICS, 150},
//																		 {1,  103, 1, Sport::ACROBATICS, 150},
//																		 {2,  101, 1, Sport::ACROBATICS, 150},
//																		 {2,  102, 1, Sport::ACROBATICS, 150},
//																		 {2,  103, 1, Sport::ACROBATICS, 150},
//																		 {3,  104, 1, Sport::ACROBATICS, 150},
//																		 {3,  102, 1, Sport::FOOTBALL,   200},
//																		 {3,  101, 1, Sport::FOOTBALL,   200},
//																		 {4,  101, 1, Sport::SWIMMING,   120},
//																		 {4,  102, 1, Sport::SWIMMING,   120},
//																		 {4,  103, 1, Sport::SWIMMING,   120},
//																		 {5,  101, 1, Sport::SPINNING,   180},
//																		 {5,  105, 1, Sport::SPINNING,   180},
//																		 {5,  102, 1, Sport::SPINNING,   180},
//																		 {6,  101, 1, Sport::BOULDERING, 90},
//																		 {6,  102, 1, Sport::BOULDERING, 90},
//																		 {7,  104, 1, Sport::ACROBATICS, 160},
//																		 {7,  101, 1, Sport::ACROBATICS, 160},
//																		 {7,  105, 1, Sport::ACROBATICS, 160},
//																		 {8,  102, 1, Sport::FOOTBALL,   220},
//																		 {8,  103, 1, Sport::FOOTBALL,   220},
//																		 {8,  106, 1, Sport::FOOTBALL,   220},
//																		 {9,  101, 1, Sport::SWIMMING,   140},
//																		 {9,  107, 1, Sport::SWIMMING,   140},
//																		 {9,  108, 1, Sport::SWIMMING,   140},
//																		 {10, 109, 1, Sport::SPINNING,   200},
//																		 {10, 110, 1, Sport::SPINNING,   200}};
//
//	void SetUp() override
//	{
//		for (auto pair : countryData)
//		{
//			olympics.add_country(pair.get_first(), pair.get_second());
//		}
//
//		for (auto tup : teamData)
//		{
//			olympics.add_team(std::get<0>(tup), std::get<1>(tup), std::get<2>(tup));
//		}
//
//		for (auto tup : contestantData)
//		{
//			olympics.add_contestant(std::get<0>(tup), std::get<2>(tup), std::get<3>(tup), std::get<4>(tup));
//		}
//	}
//};

TEST(SUITE, Constructor)
{
	Olympics olympics = Olympics();
	EXPECT_EQ(olympics.contestants.get_size(), 0);
	EXPECT_EQ(olympics.teams.get_size(), 0);
	EXPECT_EQ(olympics.countries.get_size(), 0);
}

TEST_F(EmptyOlympicsFixture, AddCountry)
{
	int size = 0;
	for (auto pair : countryData)
	{
		EXPECT_EQ(olympics.add_country(pair.get_first(), pair.get_second()), StatusType::SUCCESS);
		++size;
		EXPECT_EQ(olympics.countries.get_size(), size);
	}
	for (auto pair : countryData)
	{
		auto res = olympics.countries.find(pair.get_first());
		EXPECT_EQ(res.status(), StatusType::SUCCESS);
		EXPECT_EQ(res.ans()->get_medals(), pair.get_second());
	}
}

TEST_F(OlympicsWithCountriesFixture, AddCountry_Existent)
{
	for (auto pair : countryData)
	{
		EXPECT_EQ(olympics.add_country(pair.get_first(), pair.get_second()), StatusType::FAILURE);
	}
}

TEST_F(EmptyOlympicsFixture, AddCountry_InvalidInput)
{
	EXPECT_EQ(olympics.add_country(0, 1), StatusType::INVALID_INPUT);
	EXPECT_EQ(olympics.add_country(-1, 2), StatusType::INVALID_INPUT);
	EXPECT_EQ(olympics.add_country(1, -1), StatusType::INVALID_INPUT);
	EXPECT_EQ(olympics.add_country(-5, -2), StatusType::INVALID_INPUT);
}

TEST_F(OlympicsWithCountriesFixture, RemoveCountry)
{
	for (auto pair : countryData)
	{
		EXPECT_EQ(olympics.remove_country(pair.get_first()), StatusType::SUCCESS);
	}
	for (auto pair : countryData)
	{
		EXPECT_EQ(olympics.countries.find(pair.get_first()).status(), StatusType::FAILURE);
	}
	
	EXPECT_EQ(olympics.countries.get_size(), 0);
}

TEST_F(OlympicsWithCountriesFixture, RemoveCountry_NonExistent)
{
	EXPECT_EQ(olympics.remove_country(std::max_element(countryData.begin(), countryData.end())->get_first() + 1),
			  StatusType::FAILURE);
}

TEST_F(EmptyOlympicsFixture, RemoveCountry_NonExistent_EmptyConutries)
{
	EXPECT_EQ(olympics.remove_country(1), StatusType::FAILURE);
}

TEST_F(OlympicsWithTeamsFixture, RemoveCountry_NonEmpty)
{
	for (auto tup : teamData)
	{
		Country* country = olympics.countries.find(std::get<1>(tup)).ans();
		EXPECT_EQ(olympics.remove_country(country->get_id()), StatusType::FAILURE);
	}
}

TEST_F(OlympicsWithCountriesFixture, RemoveCountry_InvalidData)
{
	EXPECT_EQ(olympics.remove_country(0), StatusType::INVALID_INPUT);
	EXPECT_EQ(olympics.remove_country(-1), StatusType::INVALID_INPUT);
}

TEST_F(OlympicsWithCountriesFixture, AddTeam)
{
	for (auto tup : teamData)
	{
		EXPECT_EQ(olympics.add_team(std::get<0>(tup), std::get<1>(tup), std::get<2>(tup)), StatusType::SUCCESS);
	}
	for (auto tup : teamData)
	{
		auto res = olympics.teams.find(std::get<0>(tup));
		ASSERT_EQ(res.status(), StatusType::SUCCESS);
		Team* team = res.ans();
		Country* country = olympics.countries.find(std::get<1>(tup)).ans();
		EXPECT_EQ(team->get_country(), country);
	}
}

TEST_F(OlympicsWithCountriesFixture, AddTeam_CountryNonExistent)
{
	Country* maxIdCountry = olympics.countries.find(
			std::max_element(countryData.begin(), countryData.end())->get_first()).ans();
	
	EXPECT_EQ(olympics.add_team(1, maxIdCountry->get_id() + 1, Sport::SPINNING), StatusType::FAILURE);
}

TEST_F(OlympicsWithTeamsFixture, AddTeam_ExistentTeam)
{
	for (auto tup : teamData)
	{
		EXPECT_EQ(olympics.add_team(std::get<0>(tup), std::get<1>(tup), std::get<2>(tup)), StatusType::FAILURE);
	}
}

TEST(SUITE, AddTeam_InvalidInput)
{
	Olympics olympics;
	EXPECT_EQ(olympics.add_team(-1, 5, Sport::SPINNING), StatusType::INVALID_INPUT);
	EXPECT_EQ(olympics.add_team(1, 0, Sport::SPINNING), StatusType::INVALID_INPUT);
	EXPECT_EQ(olympics.add_team(0, 4, Sport::SPINNING), StatusType::INVALID_INPUT);
	EXPECT_EQ(olympics.add_team(0, 0, Sport::SPINNING), StatusType::INVALID_INPUT);
	EXPECT_EQ(olympics.add_team(-2, -4, Sport::SPINNING), StatusType::INVALID_INPUT);
}

TEST_F(OlympicsWithTeamsFixture, RemoveTeam)
{
	for (auto tup : teamData)
	{
		EXPECT_EQ(olympics.remove_team(std::get<0>(tup)), StatusType::SUCCESS);
		EXPECT_EQ(olympics.teams.find(std::get<0>(tup)).status(), StatusType::FAILURE);
	}
}

TEST_F(OlympicsWithTeamsFixture, RemoveTeam_NonExistent)
{
	EXPECT_EQ(olympics.remove_team(1), StatusType::FAILURE);
}

TEST(SUITE, RemoveTeam_InvalidData)
{
	Olympics olympics;
	EXPECT_EQ(olympics.remove_team(0), StatusType::INVALID_INPUT);
	EXPECT_EQ(olympics.remove_team(-1), StatusType::INVALID_INPUT);
}

//TEST_F(OlympicsWithContestantsInTeamsFixture, RemoveTeam_NonEmpty)
//{
//	for (auto tup : teamData)
//	{
//		Country* country = olympics.countries.find(std::get<1>(tup)).ans();
//		EXPECT_EQ(olympics.remove_country(country->get_id()), StatusType::FAILURE);
//	}
//}

TEST_F(OlympicsWithCountriesFixture, AddContestant)
{
	for (auto tup : contestantData)
	{
		EXPECT_EQ(olympics.add_contestant(std::get<0>(tup), std::get<1>(tup), std::get<2>(tup), std::get<3>(tup)),
				  StatusType::SUCCESS);
	}
	for (auto tup : contestantData)
	{
		EXPECT_EQ(olympics.contestants.find(std::get<0>(tup)).status(), StatusType::SUCCESS);
		EXPECT_EQ(olympics.countries.find(std::get<1>(tup)).ans()->contestants.find(std::get<0>(tup)).status(),
				  StatusType::SUCCESS);
	}
}