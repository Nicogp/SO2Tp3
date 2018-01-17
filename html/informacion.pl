#!/usr/bin/perl -w
       use CGI qw/:standard/;
       print 
           header,
           start_html('Estacion Meteorologica'),
           h1('Informacion Estacion Meteorologica');
		$cpu_info="/var/www/html/./cpu";
           print em(`$cpu_info`),p,
	   #"CPU Info",p,
	   #em(`lscpu`),p,
	   "Memoria",p,
	   em(`cat /proc/meminfo`),p,
	   "UpTime",p,
	   em(`uptime`),p,;
        
	
        print end_html;
