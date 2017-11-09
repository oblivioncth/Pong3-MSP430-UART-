/**
 * Note: the map is drawn with extended ASCII chars, to view it properly
 * change translation in PuTTY:
 * Change Settings -> Window -> Translation
 * Then set the Remote character set to CP866
 *
 * "$tag play" will start the game.
 * "$tag help" will print information about the game.
 *
 *
 * @warning This game runs best at 16MHz or higher. See @ref hal_clock
 *
 *  Created on: May 05, 2017
 *      Author: Heimlich
 *
 */

#ifndef tag_GAME_H_
#define tag_GAME_H_

/** MUH_Init3 must be called before the game can be played
 *
 */
void tag_Init(void);

/** @} */

#endif /* tag_GAME_H_ */
