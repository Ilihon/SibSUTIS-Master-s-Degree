#!/bin/sh

hdfs dfs -rm -r ./lab4/topwordcount-output
hadoop jar ./TopWordCount.jar pdccourse.hw3.TopWordCount -D mapreduce.job.reduces=1 ./lab4/wordcount-output/part-r-00000 ./lab4/topwordcount-output
