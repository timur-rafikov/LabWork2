# Test Report

## General Information
- **Testing Framework:** Google Test (gtest)
- **Test Types:** Unit tests, Integration tests, Edge case tests
- **Tested Components:** CharacterCard classes, AbilityCard classes, Player class, and interactions between them

---

## Unit Tests

### CharacterCard Tests
Tested the initialization and behavior of all character types:
- `Knight`, `Archer`, `Magician`, `Healer`, `Berserk`

Additional behavior:
- Health management (damage and healing)
- `Reflection` mechanic (setting and clearing after damage)

### AbilityCard Tests
Verified the correct type and initialization of all ability cards:
- `HealthBonus`, `DamageBonus`, `CommonHealthBonus`, `DefenceBonus`, `ReflectionDamage`, `CardTheft`, `FireBall`, `ShieldRowBonus`, `RageBonus`

### Player Class Tests
Tested the following functionalities:
- Initialization of the player
- Card management in hand (pop, add, check size)
- Field management (move card to field, check type, take damage, heal)
- Defense mechanics: coefficient-based damage reduction
- Reflection mechanic per field slot
- Dead character handling (move to dead, revive from dead)

---

## Integration Tests

### Character Activation
- Simulated a `Knight` attacking an `Archer`
- Validated that damage is applied correctly to the opponent's character

### Ability Activation
- Used `DamageBonus` ability card
- Verified that the target character receives appropriate damage

### Full Game Simulation
- Simulated several turns of both players placing characters on the field
- Verified:
  - Non-empty slots after placements
  - Total health sum across field characters

---

## Edge Case Tests

### Damage on Empty Field
- Verified that applying damage to an empty slot outputs "Miss" as expected

### Empty Hand Operations
- Attempted to pop character from empty hand
- Confirmed that `std::out_of_range` exception is thrown

### Invalid Field Positions
- Tested field position validation with negative and out-of-bound indices
- Confirmed that all invalid positions return `false`

---

## Summary
- **All tests compiled and passed successfully**
