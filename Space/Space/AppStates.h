#pragma once

// Enumeration representing different states of the game
enum AppState {

	// State to take us to the main menu
	STATE_MAIN_MENU,
	// State to play the game
	STATE_GAME,
	// State to take us to the steps pages
	STATE_STEPS,
	// State to exit the game
	STATE_EXIT,
	// State for information anout the planets
	STATE_GAME_BOOK,
	// State when the game finished
	STATE_END,
	// State for the tasks of the plantes
	STATE_TASKS
};