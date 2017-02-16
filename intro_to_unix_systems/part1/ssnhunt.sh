#!/bin/bash

if [ -f ./filePaths.txt ]
then
	rm ./filePaths.txt
fi
touch filePaths.txt

egrep -lsr '\s[[:digit:]][[:digit:]][[:digit:]]-[[:digit:]][[:digit:]]-[[:digit:]][[:digit:]][[:digit:]]\s' /usr >> filePaths.txt

if [ -f ./GZfiles.txt ]
then
	rm ./GZfiles.txt
fi
touch GZfiles.txt

find /usr -name '*.gz' -print >> GZfiles.txt

while read line; do
	gzip -dc "$line" | egrep -ls '[[:space:]][[:digit:]][[:digit:]][[:digit:]]-[[:digit:]][[:digit:]]-[[:digit:]][[:digit:]][[:digit:]][[:space:]]'
	if [ $? == 0 ]; then
		echo $line >> filePaths.txt
	fi
done < "GZfiles.txt"

if [ -f ./BZfiles.txt ]
then
	rm ./BZfiles.txt
fi
touch BZfiles.txt

find /usr -name '*.bz' -print >> BZfiles.txt
find /usr -name '*.bz2' -print >> BZfiles.txt

while read line; do
	bzcat "$line" | egrep -ls '[[:space:]][[:digit:]][[:digit:]][[:digit:]]-[[:digit:]][[:digit:]]-[[:digit:]][[:digit:]][[:digit:]][[:space:]]'
	if [ $? == 0 ]; then
		echo $line >> filePaths.txt
	fi
done < "BZfiles.txt"


########################
#	GET LINES IN FILE    #
########################

lines=`wc -l filePaths.txt | awk '{print $1}'`

########################
#	CREATE LATEX DOC     #
########################
if [ -f ./ssnReport.tex ]
then
	rm ./ssnReport.tex
fi
touch ssnReport.tex

echo "\\documentclass{article}" >> ssnReport.tex
echo "\\usepackage{listings}" >> ssnReport.tex

echo "\\usepackage{float}" >> ssnReport.tex
echo "\\restylefloat{table}" >> ssnReport.tex

echo "\\title{SSN Report from $HOSTNAME }" >> ssnReport.tex
echo "\\author{Matthew Rundle}" >> ssnReport.tex

echo "\\begin{document}" >> ssnReport.tex
echo "\\maketitle" >> ssnReport.tex
echo "Total number of SSN hits: $lines"
echo "\\begin{enumerate}" >> ssnReport.tex

while read line; do
	filename=`echo $line | awk -F/ '{print ($(NF))}'`
	echo "\item \textbf{$filename } ($line)" >> ssnReport.tex
done < "filePaths.txt"

echo "\\end{enumerate}" >> ssnReport.tex
echo "\\end{document}" >> ssnReport.tex

pdflatex ssnReport.tex
