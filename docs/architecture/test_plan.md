# Test plan    
  
## Testing objectives  
1. Check the correctness of all game modes (PvP, PvE, Campaign).  
2. Make sure that the cards (characters and abilities) are working as expected.  
3. Check the correctness of the playing field and the logic of victory.  
  
## Types of tests  
1. **Unit tests**:  
- Testing of individual classes (for example, `Character`, `Ability`, `Player`).  
2. **Integration tests**:  
- Testing the interaction between components (for example, players and the playing field).    
3. **System Tests**:  
- Testing the entire system in various modes.  
  
## Testing Scenarios  
1. **PvP mode**:  
- Checking the correctness of the players' moves.  
   - Checking the logic of victory.  
2. **PvE Mode**:  
- AI logic check.  
3. **Campaign Mode**:  
- Check progress on levels and story events.  
  
## Testing Tools  
- **Google Test**  