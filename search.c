# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <ctype.h>
# include <errno.h>
# include <cgic.h>
# include <flate.h>

int cgiMain(void)
{
	char email_add[128], action[16], command[128], buffer[4], logfile[32];
	int i, len, period;

	cgiHeaderContentType("text/html");			/* outputs the HTTP header      */
	templateSetFile("/var/www/html/logsearch.html");	/* external HTML template       */
	cgiFormStringNoNewlines("action", action, 32);		/* record the form action       */
	cgiFormStringNoNewlines("email_address", email_add, sizeof(email_add));
	cgiFormStringNoNewlines("period", buffer, sizeof(buffer));

	if (strcmp(action, "Search") == 0) {

		/* Check for Junk input	*/
		len = strlen(email_add);

                /* If email address is left blank, throw an error	*/
                if (len == 0) {
			templateSetVar("blank_addr", "");
			goto print;
                }

                /* check for blanks in email address	*/
                for (i = 0 ; i < len ; i++) {
                        if (isspace(email_add[i])) {
                                templateSetVar("bad_addr", "");
				goto print;
                        }
                }

		/* if all is well, proceed*/

		/* determine the logfile to use based on the period selected	*/
		strcpy(logfile, "/var/log/maillog");
		period = atoi(buffer);
		if (period != 0) {
			if (period == 7) {
				templateSetVar("duration", "1 week");
				templateSetVar("too_old", "");
				goto print;
                        }
			strcat(logfile, ".");
			strcat(logfile, buffer);

			/* check whether a log file that old actually exists	*/
			if (access(logfile, F_OK) != 0) {
				templateSetVar("no_logfile", "");
				goto print;
			}
		}

		bzero(command, sizeof(command));
		strcpy(command, "sudo /usr/local/bin/maillog-search.sh ");
		strcat(command, email_add);
		strcat(command, " ");
		strcat(command, logfile);
		strcat(command, " 2>&1 > /tmp/logsearch.txt");
		if (system(command) == -1) {
			templateSetFile("/var/www/html/error_logsearch.html");
			goto print;
		}
		templateSetVar("success", "");
	} else {
		templateSetVar("form","");
	}

print:	templatePrint();
	return 0;
}
