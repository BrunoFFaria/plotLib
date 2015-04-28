#!/bin/bash
# generate src/Makefile.am
#echo "Building Makefile.am"
#cd src
#CFILES=$(find base/ modules/ -name "*.c")
#HFILES=$(find base/ modules/ -name "*.h")
#CFILES=${CFILES//$'\n'/'\\n'}
#CFILES=${CFILES%$'\n'}
#HFILES=${HFILES//$'\n'/'\\n'}
#HFILES=${HFILES%$'\n'} 
#echo $CFILES $HFILES
# replace line in Makefile.am
#sed -i 's/^libplotlib_SOURCES = .*//' Makefile.am

# add new line to file
#echo "libplotlib_SOURCES=$CFILES $HFILES" >> Makefile.am
#echo "Done"

#cd ..

# call autoreconf in
autoreconf --force --install -I src/lib
