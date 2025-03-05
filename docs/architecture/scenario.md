# The scenario of user interaction with the game  
  
When starting, the player enters the menu. There are three modes to choose from:  
1. Mode **"Against AI"**  
	The single player game against the AI begins  
2. Mode **"Against the player"**  
	The game begins with two players on the same computer, who take turns  
3. Mode **"Campaigns"**  
	Campaign mode is launched (story, a series of AI battles and the final boss)  
  
The scenario of the "Versus-AI" mode:  
1. Players are randomly dealt cards  
2. The player's turn begins:  
	a) Selects a character card  
	b) We ask if he wants to choose an ability card  
	c) If not, then we put the card  
	d) If yes, then apply the ability and place the card  
3. The AI's move  
4. The game continues until the players have exposed all the character cards.  
5. Calculate the total health of the players.  
  
The scenario of the "Against the player" mode:  
1. Players are randomly dealt cards  
2. The player's turn begins:  
	a) Selects a character card  
	b) We ask if he wants to choose an ability card  
	c) If not, then we put the card  
	d) If yes, then apply the ability and place the card  
3. The second player's turn (hide the cards of the 1st and show the 2nd)  
4. The game continues until the players have exposed all the character cards.  
5. Calculate the total health of the players.  
  
The scenario of the Campaign mode:  
There will be a certain number of N episodes, consisting of:  
1. Message output (history)  
2. Running the "Versus-AI" scenario  
3. If the player has won, proceed to the next scenario, otherwise we will show that the player has lost and exit the menu.  