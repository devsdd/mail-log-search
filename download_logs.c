# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdlib.h>
# include <flate.h>

//	# include <ctype.h>
//	# include <errno.h>
//	# include <glob.h>
//	# include <cgic.h>

int main(void)
{
	FILE *fp;
	int c;      /* each character to be spit out  */
	int filesize;
	struct stat statbuf;

	if (stat("/tmp/logsearch.txt", &statbuf) == -1) {
		templateSetFile("/var/www/html/error_logsearch.html");
		templatePrint();
		return EXIT_FAILURE;
	}

	filesize = statbuf.st_size;
	printf("Content-Type: text/plain\r\n");
	printf("Content-Length: %d\r\n\r\n", filesize);

	if (filesize == 0) {
		printf("No mails to/from that address on the selected day.");
	} else {
		fp = fopen("/tmp/logsearch.txt", "r");
		while((c = fgetc(fp)) != EOF) {
			fputc(c, stdout);
		}
		fclose(fp);
	}

	return 0;
}
