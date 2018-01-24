#!/usr/bin/perl

#push(@INC,"/var/opt/ncsa/httpd/cgi-bin"); 
require("cgi-lib.pl"); #<-- Incluimos la librería. 
use CGI qw/:standard/;
&ReadParse; #<-- Separamos las variables. 

$nombre = $in{'variable'}; #<-- Asignamos los valores que 
#$edad = $in{'edad'};      nos enviaron a las variables
#$equipo = $in{'equipo'};  para utilizarlos. 
#$email = $in{'email'}; 

print &PrintHeader; #<-- Imprimimos el Header. 


       print 
           #header,
           start_html('Estacion Meteorologica'),
           h1('DESCARGAR ESTACION');
        $pro="./descarga $nombre";    
        $devoluvion = em(`$pro`);
        $ruta = "$nombre".".txt";
        print $ruta;
        open(FILE, "<", $ruta);
        binmode(FILE);

        $size = -s $ruta;

        $datos;

        read(FILE, $datos, $size);

        close(FILE);

        print "<H3>MODULOS DEL SISTEMA</H3>";
        $archivo = "Estacion"."$ruta";
		print "<A HREF="$ruta" download>DESCARGAR</A>";
    
        print end_html;
#print "<HTML>\n"; 
#print "<HEAD>\n"; 
#print "<TITLE>Aprendiendo CGI-Segundo Ejercicio</TITLE>\n"; 
#print "</HEAD>\n"; 
#print "<BODY>\n"; 
#print "<H3>\n"; 
#print "La variable requerida es ",$nombre,"<BR>\n"; 
#print "Tenés ",$edad," años y sos simpatizante de ",$equipo,"<BR>\n"; 
#print "Si alguien quisiera escribirte tu email es: ",$email,"<BR>\n"); 
#print "<H3>\n"; 
#print "</BODY></HTML>\n"; 