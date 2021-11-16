#!/bin/bash
echo "<html><head><title>Calepin</title><meta charset=\"UTF-8\"></head><body><table border=\"1\">"
cat telephone.txt | awk -F";" '{print "<tr><td>" $2 "</td><td>" $1 "</td><td>" $3 "</td></tr>" }' | sort
echo "</table></body></html>"
