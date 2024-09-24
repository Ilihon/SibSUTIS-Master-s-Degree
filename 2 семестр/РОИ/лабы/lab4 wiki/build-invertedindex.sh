#!/bin/sh

JARS=`yarn classpath`

javac -classpath $JARS -d classes InvertedIndex.java XmlInputFormat.java
jar -cvf InvertedIndex.jar -C classes .
