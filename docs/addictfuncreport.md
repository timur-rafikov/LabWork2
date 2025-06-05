# Additional Functionality Report: Multiple Game Modes

## Overview

The game supports **three distinct gameplay modes**, enhancing its flexibility and user engagement. These are:

1. **Player vs Player (PvP)**
2. **Player vs AI (PvE)**
3. **Campaign Mode**

Each mode builds upon the shared mechanics, while offering different objectives and control schemes.

---

## Game Modes Description

### 1. Player vs Player (PvP)

- Both players are human-controlled.
- Players manually choose and activate cards from their hands.
- Field placement, abilities, and strategy are handled by the users.
- Useful for local competitive play.

### 2. Player vs AI (PvE)

- One player is controlled by a human, the other by AI.
- The AI uses special logic to choose and play cards via `activateAI()` methods.
- The game differentiates behavior based on an `ai` flag in several key methods.
  
Example:
```cpp
if (!ai)
    handCharacters[index]->activate(owner, opponent, row);
else
    handCharacters[index]->activateAI(owner, opponent, row);
```

- Ideal for training or casual single-player sessions.

### 3. Campaign Mode

- A structured progression mode where the player advances through predefined AI opponents.
- Each campaign level can include unique configurations:
  - Special AI behaviors
  - Pre-set field conditions
  - Restrictions on card types or abilities
- Designed to offer increasing difficulty and narrative-style engagement.
- Typically implemented via a game loop that updates AI strength and rules per level.

---

## Supporting Functionalities

- **AI logic integration**: AI cards use `activateAI()` for automated behavior.
- **Dynamic field handling**: Field can be printed from either player's perspective via `printField(reverse)`.
- **Smart hand display**: `printHand(ai)` controls what is revealed to the player based on AI control.