#include <gtest/gtest.h>
#include "../src/player.hpp"
#include "../src/characters.hpp"
#include "../src/abilities.hpp"

TEST(PlayerTest, ConstructorTest) {
    Player player(1);
    EXPECT_EQ(player.getId(), 1);
    EXPECT_EQ(player.getDefCoef(), 0);
    EXPECT_FALSE(player.isCharEmpty());
    EXPECT_FALSE(player.isAbilEmpty());
    EXPECT_TRUE(player.isDeadCharEmpty());
}

TEST(PlayerTest, AddCharacterToHandTest) {
    Player player(1);
    player.addCharacterToHand(std::make_unique<Knight>());
    EXPECT_FALSE(player.isCharEmpty());
    EXPECT_EQ(player.getSizeHandChars(), 10);
}

TEST(PlayerTest, MoveCardToFieldTest) {
    Player player(1);
    player.addCharacterToHand(std::make_unique<Knight>());
    player.moveCardToField(player.popCharacterFromHand(9), 0, 0);
    EXPECT_EQ(player.getCardType(0, 0), "Knight");
}

TEST(PlayerTest, TakeDamageTest) {
    Player player(1);
    player.addCharacterToHand(std::make_unique<Knight>());
    player.moveCardToField(player.popCharacterFromHand(9), 0, 0);
    player.takeDamage(0, 0, 3);
    EXPECT_EQ(player.getCardType(0, 0), "Knight"); 
}

TEST(PlayerTest, HealingCharacterTest) {
    Player player(1);
    player.addCharacterToHand(std::make_unique<Knight>());
    player.moveCardToField(player.popCharacterFromHand(9), 0, 0);
    player.takeDamage(0, 0, 3);
    player.healingCharacter(0, 0, 2);
    EXPECT_EQ(player.getCardType(0, 0), "Knight");
}

TEST(PlayerTest, ReflectionTest) {
    Player player(1);
    player.addCharacterToHand(std::make_unique<Knight>());
    player.moveCardToField(player.popCharacterFromHand(9), 0, 0);
    player.setReflection(0, 0);
    EXPECT_TRUE(player.getReflection(0, 0));
}

TEST(PlayerTest, GetSumHealthOnFieldTest) {
    Player player(1);
    player.addCharacterToHand(std::make_unique<Knight>());
    player.moveCardToField(player.popCharacterFromHand(9), 0, 0);
    EXPECT_EQ(player.getSumHealthOnField(), 8); 
}

TEST(PlayerTest, ActivateCharacterCardTest) {
    Player player1(1);
    Player player2(2);
    player1.addCharacterToHand(std::make_unique<Knight>());
    testing::internal::CaptureStdout();
    player1.activateCharacterCard(player1, player2, 9, 0, false);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Knight"), std::string::npos); 
}

TEST(PlayerTest, ActivateAbilityCardTest) {
    Player player1(1);
    Player player2(2);
    player1.addAbilityToHand(std::make_unique<DefenceBonus>(2));
    testing::internal::CaptureStdout();
    player1.activateAbilityCard(player1, player2, 5, false);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("DefenceBonus"), std::string::npos);
}

TEST(PlayerTest, MoveCharacterToDeadTest) {
    Player player(1);
    player.addCharacterToHand(std::make_unique<Knight>());
    player.moveCardToField(player.popCharacterFromHand(9), 0, 0);
    player.takeDamage(0, 0, 10); 
    EXPECT_FALSE(player.isDeadCharEmpty()); 
}

TEST(PlayerTest, DamageReductionTest) {
    Player player(1);
    player.addDefence(20);
    EXPECT_EQ(player.damageReduction(100), 80);
}


int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}