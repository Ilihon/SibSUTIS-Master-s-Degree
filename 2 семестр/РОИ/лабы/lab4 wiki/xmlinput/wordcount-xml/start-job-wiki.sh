#!/bin/sh

hadoop jar ./wordcount.jar pdccourse.hw3.WordCount -D mapreduce.job.reduces=1 ./lab4/ruwiki-20210301-pages-articles.xml ./lab4/out1

