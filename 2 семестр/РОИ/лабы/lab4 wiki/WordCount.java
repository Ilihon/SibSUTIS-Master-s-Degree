package pdccourse.hw3;

import java.io.IOException;
import java.util.StringTokenizer;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.util.GenericOptionsParser;


public class WordCount {

	public static class TokenizerMapper extends Mapper<Text, Text, Text, IntWritable> {

		private final static IntWritable one = new IntWritable(1);
		private Text word = new Text();

		public void map(Text key, Text value, Context context) throws IOException, InterruptedException {
			StringTokenizer itr = new StringTokenizer(value.toString());
			while (itr.hasMoreTokens()) {
				//word.set(key.toString() + "@" + itr.nextToken());
				word.set(itr.nextToken());
				context.write(word, one);
			}
		}
	}

	public static class IntSumReducer extends Reducer<Text, IntWritable, Text, IntWritable> {

		private IntWritable result = new IntWritable();
		int sum = 0;

		public void reduce(Text key, Iterable<IntWritable> values, Context context) throws IOException, InterruptedException {
			sum = 0;
			for (IntWritable val : values) {
				sum += val.get();
			}
			result.set(sum);
			context.write(key, result);
		}
	}

	public static void main(String[] args) throws Exception {

		Configuration conf = new Configuration();
		String[] otherArgs = new GenericOptionsParser(conf, args).getRemainingArgs();
		if (otherArgs.length != 2) {
			System.err.println("Usage: wordcount <in> <out>");
			System.exit(2);
		}

		conf.set("mapreduce.input.keyvaluelinerecordreader.key.value.separator", " ");
		conf.setBoolean("exact.match.only", true);
		conf.set("io.serializations",
			"org.apache.hadoop.io.serializer.JavaSerialization,"
			+ "org.apache.hadoop.io.serializer.WritableSerialization");

		Job job = new Job(conf, "word count");
		job.setInputFormatClass(XmlInputFormat.class);
		job.setJarByClass(WordCount.class);

		job.setMapperClass(TokenizerMapper.class);

		//job.setCombinerClass(IntSumReducer.class);

		job.setReducerClass(IntSumReducer.class);
		job.setOutputKeyClass(Text.class);
		job.setOutputValueClass(IntWritable.class);

		FileInputFormat.addInputPath(job, new Path(otherArgs[0]));
		FileOutputFormat.setOutputPath(job, new Path(otherArgs[1]));

		boolean success = job.waitForCompletion(true);
		System.exit(success ? 0 : 1);
	}
}


