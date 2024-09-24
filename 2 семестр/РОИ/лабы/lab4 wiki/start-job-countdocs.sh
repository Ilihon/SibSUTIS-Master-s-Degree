#!/bin/sh

hdfs dfs -rm -r ./lab4/countdocs-output
export HADOOP_CLIENT_OPTS="-Xms16g -Xmx16g $HADOOP_CLIENT_OPTS"
hadoop jar ./CountDocs.jar pdccourse.hw3.CountDocs -D mapreduce.job.reduces=1 ./lab4/ruwiki-20210301-pages-articles.xml ./lab4/countdocs-output
