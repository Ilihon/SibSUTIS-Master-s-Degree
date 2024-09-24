#!/bin/sh

hdfs dfs -rm -r ./lab4/wordcount-output
export HADOOP_CLIENT_OPTS="-Xms16g -Xmx16g $HADOOP_CLIENT_OPTS"
hadoop jar ./WordCount.jar pdccourse.hw3.WordCount -D mapreduce.job.reduces=1 ./lab4/ruwiki-20210301-pages-articles.xml ./lab4/wordcount-output
