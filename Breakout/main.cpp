/**
 * Breakout begins with eight rows of bricks, with each two rows a different color. 
 * The color order from the bottom up is yellow, green, orange and red. 
 * Using a single ball, the player must knock down as many bricks as possible by using the walls and/or the paddle 
 * below to ricochet the ball against the bricks and eliminate them. 
 * If the player's paddle misses the ball's rebound, he or she loses a turn. 
 * The player has three turns to try to clear two screens of bricks. 
 * Yellow bricks earn one point each, green bricks earn three points, 
 * orange bricks earn five points and the top-level red bricks score seven points each. 
 * The paddle shrinks to one-half its size after the ball has broken through the red row and hit the upper wall. 
 * Ball speed increases at specific intervals: after four hits, after twelve hits, and after making contact with the orange and red rows.
 *
 * The maximum score achievable for one player is 896; this is done by eliminating two screens of bricks worth 448 points each. 
 * Once the second screen of bricks is destroyed, the ball in play harmlessly bounces off empty walls until the player relinquishes the game, 
 * as no additional screens are provided. However, a secret way to score beyond the 896 maximum is to play the game in two-player mode. 
 * If "Player One" completes the first screen on his or her third and last ball, then immediately and deliberately allows the ball to "drain," 
 * Player One's second screen is transferred to "Player Two" as a third screen, 
 * allowing Player Two to score a maximum of 1,344 points if he is adept enough to keep the third ball in play that long. 
 * Once the third screen is eliminated, the game is over. The games go on each time you complete a "level."
 * 14 brick par ligne
 */

 #include "game.h"

 int main(){
 	Game game;

 	if(!game.init())
 		return EXIT_FAILURE;

 	game.run();

 	return EXIT_SUCCESS;
 }