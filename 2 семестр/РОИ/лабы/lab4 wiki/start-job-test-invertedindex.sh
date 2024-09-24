#!/bin/sh

hdfs dfs -rm -r ./lab4/test/invertedindex-output
hadoop jar ./InvertedIndex.jar pdccourse.hw3.InvertedIndex -D mapreduce.job.reduces=1 ./lab4/test.xml ./lab4/test/invertedindex-output /home/ipa/mg211s04/lab4/test/top-word-count /home/ipa/mg211s04/lab4/test/counted-docs 1

