#!/bin/sh

JARS=`yarn classpath`

javac -classpath $JARS -d classes TopWordCount.java XmlInputFormat.java
jar -cvf TopWordCount.jar -C classes .
