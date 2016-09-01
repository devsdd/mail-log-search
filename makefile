all: pmlsearch.cgi download_logs.cgi

pmlsearch.cgi:	search.c
	gcc -g -Wall search.c -lcgic -lflate -o pmlsearch.cgi

download_logs.cgi:	download_logs.c
	gcc -g -Wall download_logs.c -lcgic -lflate -o download_logs.cgi

install: pmlsearch.cgi download_logs.cgi maillog-search.sh
	sudo cp pmlsearch.cgi download_logs.cgi /var/www/cgi-bin/
	sudo cp logsearch.html error_logsearch.html /var/www/html/
	sudo cp maillog-search.sh /usr/local/bin/

clean:
	rm -f pmlsearch.cgi download_logs.cgi
