package pdccourse.hw3;

import java.io.IOException;
import java.util.StringTokenizer;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.util.GenericOptionsParser;

public class CountDocs {

	public static class TokenizerMapper extends Mapper<Text, Text, Text, IntWritable> {

		private final static IntWritable one = new IntWritable(1);

		public void map(Text key, Text value, Context context) throws IOException, InterruptedException {
			context.write(key, one);
		}

	}

	public static class IntSumReducer extends Reducer<Text, IntWritable, LongWritable, Text> {

		private IntWritable result = new IntWritable();

		public void reduce(Text key, Iterable<IntWritable> values, Context context) throws IOException, InterruptedException {
			int sum = 0;
			for (IntWritable val : values) {
				sum += val.get();
			}
			result.set(sum);
		}

		@Override
		public void cleanup(Context context) throws IOException, InterruptedException {
			context.write(new LongWritable(result.get()), null);
		}
	}

	public static void main(String[] args) throws Exception {
		
		Configuration conf = new Configuration();
		String[] otherArgs = new GenericOptionsParser(conf, args).getRemainingArgs();

		if (otherArgs.length != 2) {
			System.err.println("Usage: CountDocs <in> <out>");
			System.exit(2);
		}

		//conf.set("mapreduce.input.keyvaluelinerecordreader.key.value.separator", " ");
		conf.setBoolean("exact.match.only", true);
		conf.set("io.serializations",
			"org.apache.hadoop.io.serializer.JavaSerialization,"
			+ "org.apache.hadoop.io.serializer.WritableSerialization");
		
		Job job = new Job(conf, "count docs");
		job.setInputFormatClass(XmlInputFormat.class);
		job.setJarByClass(CountDocs.class);
			
		job.setMapperClass(TokenizerMapper.class);
		job.setMapOutputKeyClass(Text.class);
		job.setMapOutputValueClass(IntWritable.class);
			
		//job.setCombinerClass(IntSumReducer.class);
		job.setReducerClass(IntSumReducer.class);
			
		job.setOutputKeyClass(LongWritable.class);
		job.setOutputValueClass(Text.class);

		FileInputFormat.addInputPath(job, new Path(otherArgs[0]));
		FileOutputFormat.setOutputPath(job, new Path(otherArgs[1]));

		System.exit(job.waitForCompletion(true) ? 0 : 1);
	}
}

