#pragma once

enum class AppState {
	LOGIN,
	MAIN_MENU,
    GAME
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

