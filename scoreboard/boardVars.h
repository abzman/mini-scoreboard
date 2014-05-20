/* boardVars.h defines all the basic scoreboard variables for the program */

short homeScore = 0;
short awayScore = 0;

short period = 1;

/* Initial time is the starting second count at
 * the begining of the program given by gettimeofday()
 * 
 * Elapsed time is the elapsed time since when
 * the program has hit the setup( tv ) routine
 */
long int initialTime;
long int elapsedTime = 0;

long int curTimeOutTime = 0;
bool timeOut = 0;

struct bClock {
	long int curTime;	/* seconds */
	long int lastMin;  /* last minimum clock time to judge differences from */
	long int maxTime;  /* ex) 900 for the main clock */
	bool running;
};

struct bClock clocks[6];
/* clocks are in seconds

	Game Clock	0
	Global Clock	1
	Home Penalty 1	2
	Home Penalty 2	3
	Away Penalty 1	4
	Away Penalty 2	5
*/

const short NORMAL_MODE = 0;
const short PAUSED_MODE = 1;
const short SPECIAL_MODE = 2;
short boardState = 1;
