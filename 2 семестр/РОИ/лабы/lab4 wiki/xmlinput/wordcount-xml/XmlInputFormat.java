/**
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

 //
 // This file is modifed version of XmlInputFormat from Apache Mahout
 // Mikhail Kurnosov, 2014
 //

package pdccourse.hw3;

import java.io.IOException;

import com.google.common.base.Charsets;
import com.google.common.io.Closeables;
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.FSDataInputStream;
import org.apache.hadoop.fs.FileSystem;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.DataOutputBuffer;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.InputSplit;
import org.apache.hadoop.mapreduce.RecordReader;
import org.apache.hadoop.mapreduce.TaskAttemptContext;
import org.apache.hadoop.mapreduce.lib.input.FileSplit;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * Reads records that are delimited by a specific begin/end tag.
 */
public class XmlInputFormat extends FileInputFormat {
    
    private static final Logger log = LoggerFactory.getLogger(XmlInputFormat.class);

    @Override
    public RecordReader<Text, Text> createRecordReader(InputSplit split, TaskAttemptContext context) {
        try {
            return new XmlRecordReader((FileSplit)split, context.getConfiguration());
        } catch (IOException ioe) {
            log.warn("Error while creating XmlRecordReader", ioe);
            return null;
        }
    }

    /**
    * XMLRecordReader class to read through a given xml document to output xml blocks as records as specified
    * by the start tag and end tag
    * 
    */
    public static class XmlRecordReader extends RecordReader<Text, Text> {

        private final byte[] keyStartTag;
        private final byte[] keyEndTag;
        private final byte[] valueStartTag;
        private final byte[] valueEndTag;
        private final long start;
        private final long end;
        private final FSDataInputStream fsin;
        private final DataOutputBuffer buffer = new DataOutputBuffer();
        private Text currentKey;
        private Text currentValue;

        public XmlRecordReader(FileSplit split, Configuration conf) throws IOException {
            
            // Key & value tags in Wikipedia XML dump
            keyStartTag = "<id>".getBytes(Charsets.UTF_8);
            keyEndTag = "</id>".getBytes(Charsets.UTF_8);
            valueStartTag = "<text".getBytes(Charsets.UTF_8);
            valueEndTag = "</text>".getBytes(Charsets.UTF_8);
            
            // Open the file and seek to the start of the current split
            start = split.getStart();
            end = start + split.getLength();
            Path file = split.getPath();
            FileSystem fs = file.getFileSystem(conf);
            fsin = fs.open(split.getPath());
            fsin.seek(start);
        }

        //
        // boolean next(Text key, Text value):
        //
        // Some splits can cross records. In such case a record is stored in 2 splits.
        // For example:
        //
        // Split 0:
        //   <text>
        //     sdfsdfsdfsdf
        //     sdfsdfsdf
        // -------
        // Split 1:
        //     sdfsdfsdf
        //     sdfsdfs
        //   </text>
        //   <text>
        //     sdfasdfasdf
        //   <text> 
        //
        // Output:
        //   key: string "<id>key<id>"
        //   value: string "<text>value</text>"
        //
        private boolean next(Text key, Text value) throws IOException {
            // Skip part of incomplete record (if split cross record)
            if (fsin.getPos() < end && readUntilMatch(keyStartTag, false)) {
                // Read article id (<id>id</id>)
                try {
                    if (readUntilMatch(keyEndTag, true)) {
                        key.set(buffer.getData(), 0, buffer.getLength() - keyEndTag.length);
                    }
                } finally {
                    buffer.reset();
                }
                // Read article content (<text>content</text>)
                if (fsin.getPos() < end && readUntilMatch(valueStartTag, false)) {
                    try {
                        if (readUntilMatch(valueEndTag, true)) {
                            value.set(buffer.getData(), 0, buffer.getLength() - valueEndTag.length);
                            return true;
                        }
                    } finally {
                        buffer.reset();
                    }
                }
            }
            return false;
        }

        @Override
        public void close() throws IOException {
            Closeables.close(fsin, true);
        }

        @Override
        public float getProgress() throws IOException {
            return (fsin.getPos() - start) / (float) (end - start);
        }

        private boolean readUntilMatch(byte[] match, boolean withinBlock) throws IOException {
            int i = 0;
            while (true) {
                int b = fsin.read();
                // End of file
                if (b == -1)
                    return false;

                // Save to buffer
                if (withinBlock)
                    buffer.write(b);

                // Check matching
                if (b == match[i]) {
                    i++;
                    if (i >= match.length) {
                        return true;
                    }                        
                } else {
                    i = 0;
                }
                if (!withinBlock && i == 0 && fsin.getPos() >= end) {
                    return false;
                }
            }
        }

        @Override
        public Text getCurrentKey() throws IOException, InterruptedException {
            return currentKey;
        }

        @Override
        public Text getCurrentValue() throws IOException, InterruptedException {
            return currentValue;
        }

        @Override
            public void initialize(InputSplit split, TaskAttemptContext context) throws IOException, InterruptedException {
        }

        @Override
        public boolean nextKeyValue() throws IOException, InterruptedException {
            currentKey = new Text();
            currentValue = new Text();
            return next(currentKey, currentValue);
        }
    }
}
