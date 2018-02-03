#!/usr/bin/perl 
#-l

########################################################
#
# Código de ejemplo del tutorial: "Upload de archivos"
#
# Creado por: Uriel Lizama
# Todos los derechos reservado.
#
# http://perlenespanol.com/
#
#########################################################
use CGI qq(:all);
use strict;
use CGI::Carp qw(fatalsToBrowser);
use CGI;
require("cgi-lib.pl"); #<-- Incluimos la librería. 
use CGI qw/:standard/;

my %Input;

my $query = new CGI;
my @pairs = $query->param;

foreach my $pair(@pairs){
$Input{$pair} = $query->param($pair);
}


#Directorio donde queremos estacionar los archivos
my $dir = "/var/www/html/";

#Array con extensiones de archivos que podemos recibir
my @extensiones = ('ko');

my $nombre_modulo = $Input{'uploadmodulo'};
my $command="sudo insmod ";
my $useradd = "/usr/bin/insmod";


recepcion_de_archivo(); #Iniciar la recepcion del archivo

#TODO SALIO BIEN
print "Content-type: text/html\n\n";
print "<h1>El archivo fue recibido correctamente</h1>\n";
print em(`sudo insmod $nombre_modulo`);
#system ("sudo insmod nombre_modulo");
#if ($?) {
#   print "command failed: $!\n";
#}
my $devolucion = em(`dmesg | tail`);
my @values = split('\n', $devolucion);
foreach my $val (@values) {
    print "$val\n";
    print "</BR>";
}
#print em(`dmesg | tail`);

exit(1);


sub recepcion_de_archivo{

my $nombre_en_servidor = $Input{'uploadmodulo'};
$nombre_en_servidor =~ s/ /_/gi;
print "nombre_en_servidor $nombre_en_servidor";
print "<br>";
$nombre_en_servidor =~ s!^.*(\\|\/)!!;
print "nombre_en_servidor2 $nombre_en_servidor";

my $extension_correcta = 0;

foreach (@extensiones){
if($nombre_en_servidor =~ /\.$_$/i){
$extension_correcta = 1;
last;
}
}


if($extension_correcta){

#Abrimos el nuevo archivo
open (OUTFILE, ">$dir/$nombre_en_servidor") || die "No se puedo crear el archivo";
binmode(OUTFILE); #Para no tener problemas en Windows

#Transferimos byte por byte el archivo
while (my $bytesread = read($Input{'uploadmodulo'}, my $buffer, 1024)) {
print OUTFILE $buffer;
}

#Cerramos el archivo creado
close (OUTFILE);

}else{
print "Content-type: text/html\n\n";
print "<h1>Extension incorrecta</h1>";
print "Sólo se reciben archivo con extension:";
print join(",", @extensiones);
exit(0);
}


} #sub recepcion_de_archivo