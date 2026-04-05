#ifndef GAMESTATE_H
#define GAMESTATE_H

/**
 * @brief Enum representing all possible game states in the Simon game.
 */
typedef enum {
    SIMON_GENERATE,       /**< Generate the next step in the Simon sequence */
    SIMON_PLAY_ON,        /**< Turn on LED/sound for the current step */
    SIMON_PLAY_OFF,       /**< Turn off LED/sound after a step */
    AWAITING_INPUT,       /**< Wait for user input (button press or UART) */
    HANDLE_INPUT,         /**< Process user input, check timing */
    HANDLE_PRESS_CASE,    /**< Special handling when button is pressed too early */
    EVALUATE_INPUT,       /**< Compare user input with the generated sequence */
    SUCCESS_STATE,        /**< Player successfully completed sequence */
    FAIL_STATE,           /**< Player input was incorrect */
    NAME_INPUT,           /**< Collect player's name for highscore */
    FINISH_NAME_INPUT,    /**< Finish name input and store highscore */
    DISP_SCORE,           /**< Display player's score on 7-segment display */
    AFTER_SCORE           /**< Leave a blank for while before next round */
} Game_State;

#endif
