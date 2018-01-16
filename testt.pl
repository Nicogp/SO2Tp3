#!/usr/bin/perl -w
       use CGI qw/:standard/;
       print 
           header,
           start_html('Estacion Meteorologica'),
           h1('Estacion Meteorologica'),
           start_form,
           "Ver informacion",p,
           submit('Informacion del Sistema'),
	   submit('Descarga'),
	   submit('Promedio'),
	   submit('Precipitacion Mensual'),
	   submit('Precipitacion Diaria'),p,
	   textfield('estacion','',25,20),
           end_form,
           hr,"\n";
        if (param('Informacion del Sistema')) {
		$cpu_info="/var/www/hiawatha/./cpu";
           print em(`$cpu_info`),p,
	   #"CPU Info",p,
	   #em(`lscpu`),p,
	   "Memoria",p,
	   em(`cat /proc/meminfo`),p,
	   "UpTime",p,
	   em(`uptime`),p,;
        }
	if(param('Descarga')){
		$com = param('estacion');
		$des="/var/www/hiawatha/./descarga ${com}";
		system("$des");
		if($?==1){
			print "si",p;
		}
		else{
			#print $res,p;
			print "no",p;
		}
	   print $com,p;
	}
	if(param('Promedio')){
		print "Promedio",p;
		$com = param('estacion');
		$pro="/var/www/hiawatha/./promedio ${com}";
		print em(`$pro`);
	}
	if(param('Precipitacion Mensual')){
	   	print "Precipitacion Mensual",p;
		$com = param('estacion');
		$men="/var/www/hiawatha/./mensual ${com}";
		print em(`$men`),p;
		
		
	}
	if(param('Precipitacion Diaria')){
	   print "Precipitacion Diaria",p;
		$com = param('estacion');
		$dia="/var/www/hiawatha/./diario ${com}";
		print em(`$dia`),p;
		
	}
	
        print end_html;


