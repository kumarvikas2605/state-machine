# state-machine

We have taken 2 arrays:

one for state function pointers: int (* state[])(void) = { entry_state, foo_state, bar_state, exit_state};

And another one for state transition rules, i.e.: struct transition state_transitions []

Every state function returns the code(based on action performed by you). And then you lookup state transition table by state and return code to find the next state and then just execute that particular state function.
