#!/bin/sh

hdfs dfs -rm -r ./lab4/test/wordcount-output
hadoop jar ./WordCount.jar pdccourse.hw3.WordCount -D mapreduce.job.reduces=1 ./lab4/test.xml ./lab4/test/wordcount-output

