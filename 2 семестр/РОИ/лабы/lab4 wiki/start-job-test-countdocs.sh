#!/bin/sh

hdfs dfs -rm -r ./lab4/test/countdocs-output
hadoop jar ./CountDocs.jar pdccourse.hw3.CountDocs -D mapreduce.job.reduces=1 ./lab4/test.xml ./lab4/test/countdocs-output
