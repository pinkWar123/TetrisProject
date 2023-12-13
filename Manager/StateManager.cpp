// StateManager.cpp
#include "StateManager.h"

StateManager::StateManager() : currentState(AppState::LOGIN) {}

StateManager& StateManager::getInstance() {
    static StateManager instance;
    return instance;
}

void StateManager::setState(AppState newState) {
    currentState = newState;
}

AppState StateManager::getState() const {
    return currentState;
}