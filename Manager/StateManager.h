#pragma once

enum class AppState {
	LOGIN,
	MAIN_MENU,
    SETTINGS,
    IN_GAME,
    GAME_OVER
};

class StateManager {
public:
    static StateManager& getInstance();

    void setState(AppState newState);
    AppState getState() const;

private:
    AppState currentState;

    StateManager(); // Private constructor for Singleton pattern
};

