#!/bin/sh

JARS=`yarn classpath`

javac -classpath $JARS -d classes WordCount.java XmlInputFormat.java
jar -cvf WordCount.jar -C classes .
