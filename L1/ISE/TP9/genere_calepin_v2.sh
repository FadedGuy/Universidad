#!/bin/bash
echo "--- Transformation du fichier telephone.txt en telephone.html ---"
echo "<html><head><title>Calepin</title><meta charset=\"UTF-8\"></head><body><table border=\"1\">" > telephone.html
cat telephone.txt | awk -F";" '{print "<tr><td>" $2 "</td><td>" $1 "</td><td>" $3 "</td></tr>" }' >> telephone.html
echo "</table></body></html>" >> telephone.html
