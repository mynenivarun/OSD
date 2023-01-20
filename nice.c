

#include <stdio.h>
main ()
{
printf ("original priority\n");
system ("ps -l"); /* Execute a ps 
*/
nice (0); /* Add 0 to my priority 
*/
printf ("running at priority 0\n");
system ("ps -l"); /* Execute 
another ps */
nice (10); /* Add 10 to my priority 
*/
printf ("running at priority 
10\n");
system ("ps -l"); /* Execute the 
last ps */
