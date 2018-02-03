#!/usr/bin/perl

#push(@INC,"/var/opt/ncsa/httpd/cgi-bin"); 
require("cgi-lib.pl"); #<-- Incluimos la librería. 
use CGI qw/:standard/;
&ReadParse; #<-- Separamos las variables. 

$nombre = $in{'remmodulo'}; #<-- Asignamos los valores que 
#$edad = $in{'edad'};      nos enviaron a las variables
#$equipo = $in{'equipo'};  para utilizarlos. 
#$email = $in{'email'}; 

print &PrintHeader; #<-- Imprimimos el Header. 


       print 
           #header,
           start_html('Estacion Meteorologica'),
           h1('REMOVER MODULO DE ESTACION');
        em(`sudo rmmod $nombre`);
        my $devolucion = em(`dmesg | tail`);
        my @values = split('\n', $devolucion);
        foreach my $val (@values) {
            print "$val\n";
            print "</BR>";
        }
        
    
        print end_html;