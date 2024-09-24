#!/bin/sh

hdfs dfs -rm -r ./lab4/invertedindex-output
export HADOOP_CLIENT_OPTS="-Xms16g -Xmx16g $HADOOP_CLIENT_OPTS"
hadoop jar ./InvertedIndex.jar pdccourse.hw3.InvertedIndex -D mapreduce.job.reduces=4 ./lab4/ruwiki-20210301-pages-articles.xml ./lab4/invertedindex-output /home/ipa/mg211s04/lab4/invertedindex-input/top-word-count /home/ipa/mg211s04/lab4/invertedindex-input/counted-docs 4
