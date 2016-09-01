## mail-log-search
Old, pre-logstash era web interface to query logs from qmail and postfix servers

### Warning
This is old, unmaintained, legacy code.

Back in the days before tools like Splunk and Logstash were available, as a sysadmin for a company providing email hosting services, I would routinely have to trace emails manually by logging into servers and running grep/awk commands on logfiles. Hence I build a web interface where one could just input email addresses and get complete logs of mails involving those addresses, ordered by email.

The interface was build using C and HTML templates with some back-end shell scripts.

### Dependencies
#### libflate (C-Library for HTML Templating)
#### cgic (C-Library that implements the CGI protocol)
