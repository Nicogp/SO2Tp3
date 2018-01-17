#!/usr/local/bin/perl
#
#   hello_s.pl-- simple "hello, world" program to demonstrate basic
#       CGI output.
#

# Print the CGI response header, required for all HTML output
# Note the extra \n, to send the blank line
print "Content-type: text/html\n\n" ;

# Print the HTML response page to STDOUT
print <<EOF ;
<html>
<head><title>CGI Results</title></head>
<body>
<h1>Hello, world.</h1>
</body>
</html>
EOF

exit ;