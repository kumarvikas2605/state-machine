#include<stdio.h>
#include<stdlib.h>


#define EXIT_STATE end
#define ENTRY_STATE entry
#define MAGIC_STATE 9999

// Handler functions for different states
int entry_state(void);
int foo_state(void);
int bar_state(void);
int exit_state(void);


/* array and enum below must be in sync */

// array of pointers to functions which will be invoked in-case an event occurs
int (* state[])(void) = { entry_state, foo_state, bar_state, exit_state};

// state codes
enum state_codes { entry, foo, bar, end};

// values that can be returned by state_functions
enum ret_codes { ok, fail, repeat};

// based on current state(i.e. src_state) and return code(retuned by state_fucntion: ret_code) transition to new state(i.e. dst_state) 
struct transition {
    enum state_codes src_state;
    enum ret_codes   ret_code;
    enum state_codes dst_state;
};

// array of valid src_state/ret_code/dst_code combinations 
struct transition state_transitions[] = {
    {entry, ok,     foo},
    {entry, fail,   end},
    {foo,   ok,     bar},
    {foo,   fail,   end},
    {foo,   repeat, foo},
    {bar,   ok,     end},
    {bar,   fail,   end},
    {bar,   repeat, foo}};


int move_to_next_state(uint state, uint ret_code);
int returnUndefBehavior(uint state, uint ret_code);

// returns return codes(on success) or -1(on failures)
int move_to_next_state(uint state, uint ret_code)  
{
    switch(state)
    {
        case entry:
            if(return == ok) {
                return foo;
            }
            else if (return == fail) {
                return end;
            }
			else {
				returnUndefBehavior(state, ret_code);
				break;
			}
		case foo:
            if(return == ok) {
                return bar;
            }
            else if (return == fail) {
                return end;
            }
			else if (return == repeat) {
                return foo;
			}
            else {
                returnUndefBehavior(state, ret_code);
                break;
			}
		case bar:
            if(return == ok) {
                return end;
            }
            else if (return == fail) {
                return end;
            }
			else if (return == repeat) {
                return foo;
            }
            else { 
                returnUndefBehavior(state, ret_code);
                break;
			}
		default:	
			returnUndefBehavior(state, ret_code);
			break; 
    }
}

int returnUndefBehavior(uint state, uint ret_code) {
	print("\n Unexpected return code(%d) for state(%d) \n", state, ret_code);
	return -1;
}

int main(int argc, char *argv[]) {
    enum state_codes cur_state = ENTRY_STATE;
    enum ret_codes rc;
    int (* state_fun)(void);

    for (;;) {
        state_fun = state[cur_state];
        rc = state_fun();
        if (EXIT_STATE == cur_state)
            break;
        cur_state = move_to_next_state(cur_state, rc);
		if (cur_state == MAGIC_STATE)
			exit();
    }

    return 0; 
}

int entry_state() {
	int static run = 0;
	printf("\n Inside %s, run(%d) \n", __FUNCTION__, run);
	if(run == 0) {
		// pre increment is more optimized than post increment	
		++run;
		return fail;	
	}
	else if(run == 1) {
		return ok;		
	}
}

int foo_state() {
    int static run = 0;
    printf("\n Inside %s, run(%d) \n", __FUNCTION__, run);
    if(run == 0) {
        // pre increment is more optimized than post increment
        ++run;
        return fail;
    }
	else if(run == 1) {
        ++run;
        return repreat;
    }
    else if(run == 2) {
        return ok;
    }
}

int bar_state() {
    int static run = 0;
    printf("\n Inside %s, run(%d) \n", __FUNCTION__, run);
    if(run == 0) {
        // pre increment is more optimized than post increment
        ++run;
        return fail;
    }
    else if(run == 1) {
		++run;
        return repreat;
    }
	else if(run == 2) {
        return ok;
    }
}

int exit_state() {
    printf("\n Inside %s, run(%d) \n", __FUNCTION__, run);
	// return magic number to mark end of the state
	return MAGIC_STATE;
    }
}

