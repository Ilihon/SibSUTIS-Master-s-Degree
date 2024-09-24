#!/bin/sh

hdfs dfs -rm -r ./lab4/wordcount-output
hadoop jar ./WordCount.jar pdccourse.hw3.WordCount -D mapreduce.job.reduces=1 ./lab4/enwiki-20210301-pages-articles.xml.bz2 ./lab4/wordcount-output
