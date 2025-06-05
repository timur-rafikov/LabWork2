#include <gtest/gtest.h>
#include "../src/player.hpp"
#include "../src/characters.hpp"
#include "../src/abilities.hpp"
#include "../src/modes.hpp"
#include <memory>
#include <vector>

// Helper function to count non-empty slots on field
int countNonEmptySlots(const Player& player) {
    int count = 0;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (player.getCardType(i, j) != "EmptySlot") {
                count++;
            }
        }
    }
    return count;
}

// Unit Tests for Character Cards
TEST(CharacterCardTest, KnightInitialization) {
    Knight knight;
    EXPECT_EQ(knight.getType(), "Knight");
    EXPECT_EQ(knight.getHealth(), 8);
    EXPECT_EQ(knight.getDamage(), 4);
    EXPECT_EQ(knight.getHealAmount(), 0);
    EXPECT_EQ(knight.getDefenseBonus(), 0);
}

TEST(CharacterCardTest, ArcherInitialization) {
    Archer archer;
    EXPECT_EQ(archer.getType(), "Archer");
    EXPECT_EQ(archer.getHealth(), 5);
    EXPECT_EQ(archer.getDamage(), 3);
    EXPECT_EQ(archer.getHealAmount(), 0);
    EXPECT_EQ(archer.getDefenseBonus(), 0);
}

TEST(CharacterCardTest, MagicianInitialization) {
    Magician magician;
    EXPECT_EQ(magician.getType(), "Magician");
    EXPECT_EQ(magician.getHealth(), 4);
    EXPECT_EQ(magician.getDamage(), 5);
    EXPECT_EQ(magician.getHealAmount(), 0);
    EXPECT_EQ(magician.getDefenseBonus(), 1);
}

TEST(CharacterCardTest, HealerInitialization) {
    Healer healer;
    EXPECT_EQ(healer.getType(), "Healer");
    EXPECT_EQ(healer.getHealth(), 2);
    EXPECT_EQ(healer.getDamage(), 0);
    EXPECT_EQ(healer.getHealAmount(), 4);
    EXPECT_EQ(healer.getDefenseBonus(), 1);
}

TEST(CharacterCardTest, BerserkInitialization) {
    Berserk berserk;
    EXPECT_EQ(berserk.getType(), "Berserk");
    EXPECT_EQ(berserk.getHealth(), 8);
    EXPECT_EQ(berserk.getDamage(), 5);
    EXPECT_EQ(berserk.getHealAmount(), 0);
    EXPECT_EQ(berserk.getDefenseBonus(), 0);
}

TEST(CharacterCardTest, TakeDamageAndHeal) {
    Knight knight;
    knight.takeDamage(3);
    EXPECT_EQ(knight.getHealth(), 5);
    knight.heal(2);
    EXPECT_EQ(knight.getHealth(), 7);
}

TEST(CharacterCardTest, Reflection) {
    Knight knight;
    EXPECT_FALSE(knight.getReflection());
    knight.setReflection();
    EXPECT_TRUE(knight.getReflection());
    knight.takeDamage(5); // Should clear reflection
    EXPECT_FALSE(knight.getReflection());
}

// Unit Tests for Ability Cards
TEST(AbilityCardTest, HealthBonusInitialization) {
    HealthBonus healthBonus(3);
    EXPECT_EQ(healthBonus.getType(), "HealthBonus");
}

TEST(AbilityCardTest, DamageBonusInitialization) {
    DamageBonus damageBonus(2);
    EXPECT_EQ(damageBonus.getType(), "DamageBonus");
}

TEST(AbilityCardTest, CommonHealthBonusInitialization) {
    CommonHealthBonus commonHealthBonus(2);
    EXPECT_EQ(commonHealthBonus.getType(), "CommonHealthBonus");
}

TEST(AbilityCardTest, DefenceBonusInitialization) {
    DefenceBonus defenceBonus(1);
    EXPECT_EQ(defenceBonus.getType(), "DefenceBonus");
}

TEST(AbilityCardTest, ReflectionDamageInitialization) {
    ReflectionDamage reflectionDamage;
    EXPECT_EQ(reflectionDamage.getType(), "ReflectionDamage");
}

TEST(AbilityCardTest, CardTheftInitialization) {
    CardTheft cardTheft;
    EXPECT_EQ(cardTheft.getType(), "CardTheft");
}

TEST(AbilityCardTest, FireBallInitialization) {
    FireBall fireBall(4, 2);
    EXPECT_EQ(fireBall.getType(), "FireBall");
}

TEST(AbilityCardTest, ShieldRowBonusInitialization) {
    ShieldRowBonus shieldRowBonus;
    EXPECT_EQ(shieldRowBonus.getType(), "ShieldRowBonus");
}

TEST(AbilityCardTest, RageBonusInitialization) {
    RageBonus rageBonus;
    EXPECT_EQ(rageBonus.getType(), "RageBonus");
}

// Player Class Tests
TEST(PlayerTest, Initialization) {
    Player player(1);
    EXPECT_EQ(player.getId(), 1);
    EXPECT_FALSE(player.isCharEmpty());
    EXPECT_FALSE(player.isAbilEmpty());
    EXPECT_TRUE(player.isDeadCharEmpty());
    EXPECT_EQ(countNonEmptySlots(player), 0);
}

TEST(PlayerTest, CardManagement) {
    Player player(1);
    int initialCharCount = player.getSizeHandChars();
    int initialAbilCount = player.getSizeHandAbils();
    
    // Test popping character card
    auto charCard = player.popCharacterFromHand(0);
    EXPECT_EQ(player.getSizeHandChars(), initialCharCount - 1);
    
    // Test popping ability card
    auto abilCard = player.popAbilityFromHand(0);
    EXPECT_EQ(player.getSizeHandAbils(), initialAbilCount - 1);
    
    // Test adding cards back
    player.addCharacterToHand(std::move(charCard));
    player.addAbilityToHand(std::move(abilCard));
    EXPECT_EQ(player.getSizeHandChars(), initialCharCount);
    EXPECT_EQ(player.getSizeHandAbils(), initialAbilCount);
}

TEST(PlayerTest, FieldManagement) {
    Player player(1);
    auto knight = std::make_unique<Knight>();
    
    // Place card on field
    player.moveCardToField(std::move(knight), 0, 0);
    EXPECT_EQ(player.getCardType(0, 0), "Knight");
    EXPECT_EQ(countNonEmptySlots(player), 1);
    
    // Test damage and healing
    player.takeDamage(0, 0, 3);
    EXPECT_EQ(player.getCardHealth(0, 0), 5); // Knight has 8 health initially
    
    player.healingCharacter(0, 0, 2);
    EXPECT_EQ(player.getCardHealth(0, 0), 7);
}

TEST(PlayerTest, DefenseMechanics) {
    Player player(1);
    player.addDefence(10);
    EXPECT_EQ(player.getDefCoef(), 10);
    
    // Test damage reduction
    int reducedDamage = player.damageReduction(20);
    EXPECT_EQ(reducedDamage, 18); // 20 * (1 - 0.10) = 18
    
    player.addDefence(-5);
    EXPECT_EQ(player.getDefCoef(), 5);
}

TEST(PlayerTest, ReflectionMechanics) {
    Player player(1);
    auto knight = std::make_unique<Knight>();
    player.moveCardToField(std::move(knight), 0, 0);
    
    EXPECT_FALSE(player.getReflection(0, 0));
    player.setReflection(0, 0);
    EXPECT_TRUE(player.getReflection(0, 0));
}

TEST(PlayerTest, DeadCharacters) {
    Player player(1);
    auto knight = std::make_unique<Knight>();
    player.moveCardToField(std::move(knight), 0, 0);
    
    // Kill the knight
    player.takeDamage(0, 0, 10);
    EXPECT_EQ(player.getSizeDeadChars(), 1);
    EXPECT_EQ(countNonEmptySlots(player), 0);
    
    // Revive from dead
    auto deadChar = player.popDeadCharacter(0);
    EXPECT_EQ(deadChar->getType(), "Knight");
    EXPECT_EQ(player.getSizeDeadChars(), 0);
}

// Integration Tests
TEST(IntegrationTest, CharacterActivation) {
    Player player1(1);
    Player player2(2);
    
    // Place a knight for player1
    auto knight = std::make_unique<Knight>();
    player1.moveCardToField(std::move(knight), 0, 0);
    
    // Place an archer for player2
    auto archer = std::make_unique<Archer>();
    player2.moveCardToField(std::move(archer), 0, 0);

    std::istringstream fakeInput("0\n");
    std::streambuf* originalCin = std::cin.rdbuf();
    std::cin.rdbuf(fakeInput.rdbuf()); 
    
    // Activate knight's attack
    player1.activateCharacterCard(player1, player2, 0, 1, false);

    std::cin.rdbuf(originalCin);
    
    // Check if archer took damage
    EXPECT_LT(player2.getCardHealth(0, 0), 5); // Archer starts with 5 health
}

TEST(IntegrationTest, AbilityActivation) {
    Player player1(1);
    Player player2(2);
    
    // Place a knight for player2
    auto knight = std::make_unique<Knight>();
    player2.moveCardToField(std::move(knight), 0, 0);
    
    // Add damage bonus to player1
    auto damageBonus = std::make_unique<DamageBonus>(3);
    player1.addAbilityToHand(std::move(damageBonus));
    
    // Activate damage bonus
    player1.activateAbilityCard(player1, player2, 0, false);
    
    // Check if knight took damage
    auto knightCard = dynamic_cast<CharacterCard*>(player2.popCharacterFromHand(0).get());
    EXPECT_LT(knightCard->getHealth(), 8); // Knight starts with 8 health
}

TEST(IntegrationTest, FullGameSimulation) {
    Player player1(1);
    Player player2(2);
    
    // Simulate a few turns
    for (int i = 0; i < 3; i++) {
        if (!player1.isCharEmpty()) {
            auto card = player1.popCharacterFromHand(0);
            player1.moveCardToField(std::move(card), 0, i % 2);
        }
        
        if (!player2.isCharEmpty()) {
            auto card = player2.popCharacterFromHand(0);
            player2.moveCardToField(std::move(card), 0, i % 2);
        }
    }
    
    // Check that both players have cards on field
    EXPECT_GT(countNonEmptySlots(player1), 0);
    EXPECT_GT(countNonEmptySlots(player2), 0);
    
    // Check health sums
    EXPECT_GT(player1.getSumHealthOnField(), 0);
    EXPECT_GT(player2.getSumHealthOnField(), 0);
}

// Edge Case Tests
TEST(EdgeCaseTest, EmptyFieldDamage) {
    Player player(1);
    testing::internal::CaptureStdout();
    player.takeDamage(0, 0, 10);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Miss"), std::string::npos);
}

TEST(EdgeCaseTest, EmptyHandOperations) {
    Player player(1);
    while (!player.isCharEmpty()) {
        player.popCharacterFromHand(0);
    }
    
    EXPECT_THROW(player.popCharacterFromHand(0), std::out_of_range);
}

TEST(EdgeCaseTest, InvalidFieldPositions) {
    Player player(1);
    EXPECT_FALSE(player.isEmptySlot(-1, 0));
    EXPECT_FALSE(player.isEmptySlot(0, -1));
    EXPECT_FALSE(player.isEmptySlot(2, 0));
    EXPECT_FALSE(player.isEmptySlot(0, 4));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}