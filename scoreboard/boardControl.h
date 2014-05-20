/*
   Returns the Clock Value for the specified clockNum in
   a 4-element char (allocated by the caller).
   Numeric, not ASCII.
   MM:SS
   E.g. { 0x00, 0x01, 0x02, 0x03 } is 01:23

   Game Clock     - clock 0
   Global Clock   - clock 1
   Home Penalty 1 - clock 2
   Home Penalty 2 - clock 3
   Away Penalty 1 - clock 4
   Away Penalty 2 - clock 5 */
void getClock( short clockNum, char clockData[] );

/* Returns the current score as
   in a 2 char string value (allocated by the caller)
   Numeric, not ASCII (0x0 0x0 = a score of 0)
   0 -> home
   1 -> away
   0 0                       */
void getScore( short scoreNum, char scoreData[] );

/* returns the current period
   of the game as a short for
   one of three possibilities
   1 - first period
   2 - second period
   0 - overtime             */
short getPeriod();

/* Provides high-level code opportunity to make updates
   internally (track button press changes, update clocks,
   etc).

   tv is the time value returned by gettimeofday().

   buttonPressed is a 12-element array (sized by the caller--
   do not free it) with elements mapping as follows:

button		|array index
---------------------------
start		|0
pause		|1
period +	|2
period -	|3
home score+	|4
home socre-	|5
home pen 1	|6
home pen 2	|7
away score+	|8
away score-	|9
away pen 1	|10
away pen 2	|11

   The specified button element is 1 when the button is pressed
   and 0 when the button is not pressed.
*/
void periodicUpdate( struct timeval tv, char buttonPressed[] );
