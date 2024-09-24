#!/bin/sh

hdfs dfs -rm -r ./lab4/invertedindex-output
hadoop jar ./InvertedIndex.jar pdccourse.hw3.InvertedIndex -D mapreduce.job.reduces=4 ./lab4/wordcount-output/part-r-00000 ./lab4/invertedindex-output ./lab4/topwordcount-output/part-r-00000 ./lab4/countdocs-output/part-r-00000

