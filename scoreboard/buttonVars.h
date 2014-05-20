/* this header defines basic button methods and variables */

const short NUM_BUTTONS = 12;
const short MIN_HOLD_COUNT = 8;		/* minimum number of counts for a button that is pressed to be considered "held" */
const short MAX_DOUBLE_PRESS_COUNT = 4; /* maximum number of counts in-between presses for the second press to be considered a "double press" */

/* struct to hold basic button values */
struct Button {
	bool raw_state;		/* state of the actual hardware */
	bool pressed;			/* used for soft button presses and releases used for single-button presses*/
	bool held;				/* true if button has exceeded MAX_HOLD_TIME */
	int holdCount; 			/* How long the state of the button has remained true, i.e. "held" */
	int releaseCount;		/* used to count time in-between presses for double presses */
	bool secondPress;		/* becomes true on the second press of a double press move within the required time-frame*/
};

struct Button buttons[12];

void buttonUpdate();

/*
button array index mapping

button		|array index
---------------------------
manpause	|1
period +	|2
period -	|3
home score+	|4
home score-	|5
home pen 1	|6
home pen 2	|7
away score+	|8
away score-	|9
away pen 1	|10
away pen 2	|11
*/
