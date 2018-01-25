#!/usr/bin/perl -w
       use CGI qw/:standard/;
       print 
           header,
           start_html('Estacion Meteorologica'),
           h1('Informacion Estacion Meteorologica');
		$cpu_info="/var/www/html/./cpu";
           $devolucion_cpu = em(`$cpu_info`);
           print"<h1>CPU Info</h1>";
           my @values = split('\n', $devolucion_cpu);

        foreach my $val (@values) {
          print "$val\n";
          print "</BR>";
        }
	   #"CPU Info",p,
	   #em(`lscpu`),p,
	   print"<h1>Memoria</h1>";
	   $devolucion_mem = em(`cat /proc/meminfo`);
	   my @values1 = split('\n', $devolucion_mem);

        foreach my $val1 (@values1) {
          print "$val1\n";
          print "</BR>";
        }
	   print"<h1>uptime</h1>";
	   $devolucion_time = em(`uptime`);
	   my @values2 = split('\n', $devolucion_mem);

        foreach my $val2 (@values2) {
          print "$val2\n";
          print "</BR>";
        }
        
	
        print end_html;
