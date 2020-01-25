# Group 1 - Fitness Tracker

## Tentative Rating
Above Average Difficulty for a Complete Product. Simply detecting steps and ticking a counter (pedometer) would be average level.

## Comments
 - Your prototype plan is not really clear. You need to have stages and you haven't explicitly described them. I suggest you first see if you can actually detect steps at a reasonable success rate. There are tutorials online for this and I believe previous ECE first year classes have done this.
 - Average speed can't really be calculated without either height information (to estimate stride) or location information. I guess you can approximate it though, and that's reasonable. Use average heights for males/females.\
 - Keeping track of time is a whole other piece of code in your system. Keep that in mind. I do not believe there is an API to give you the current time! You will have to synchronize with a computer and measure differentials yourself!
 - No specific hardware listed. You will need an accelerometer for sure.

## Mark
10 / 10