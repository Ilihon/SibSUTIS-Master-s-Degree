package mapred.graphanalysis;

import java.io.BufferedReader;
import java.io.DataInput;
import java.io.DataOutput;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;
import java.util.StringTokenizer;
import java.util.TreeMap;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.conf.Configured;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.io.WritableComparable;
import org.apache.hadoop.io.WritableComparator;
import org.apache.hadoop.io.WritableUtils;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.input.KeyValueTextInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.mapreduce.lib.output.TextOutputFormat;
import org.apache.hadoop.util.StringUtils;
import org.apache.hadoop.util.Tool;
import org.apache.hadoop.util.ToolRunner;

public class TopUsers extends Configured implements Tool {

	 /*
	 * MAPPER
	 */
	 public static class CountMapper extends Mapper<Text, Text, Text, LongWritable> {

	 	private TreeMap<Long, String> tmap;

		@Override
		public void setup(Context context) throws IOException, InterruptedException {

			tmap = new TreeMap<Long, String>();
		}

		public void map(Text key, Text value, Context context) throws IOException, InterruptedException {

			String user_id = key.toString();
			Long followers_count = Long.parseLong(value.toString());
			tmap.put(followers_count, user_id);
			if (tmap.size() > 50) {
				tmap.remove(tmap.firstKey());
			}
		}

		@Override
		protected void cleanup(Context context) throws IOException, InterruptedException {
			for (Map.Entry<Long, String> entry : tmap.entrySet()) {
				context.write(new Text(entry.getValue()), new LongWritable(entry.getKey()));
			}
		}
	 }

	 /*
	 * REDUCER
	 */
	 public static class CountReducer extends Reducer<Text, LongWritable, Text, LongWritable> {

	 	private TreeMap<Long, String> tmap;

	 	@Override
		public void setup(Context context) throws IOException, InterruptedException {
			tmap = new TreeMap<Long, String>();
		}

	 	public void reduce(Text key, Iterable<LongWritable> values, Context context) throws IOException, InterruptedException {

	 		String user_id = key.toString();
			long count = 0;

			for (LongWritable val : values) {
				count = val.get();
			}

			tmap.put(count, user_id);

			if (tmap.size() > 50) {
				tmap.remove(tmap.firstKey());
			}
		}

		@Override
		public void cleanup(Context context) throws IOException, InterruptedException {

			for (Map.Entry<Long, String> entry : tmap.entrySet()) {
				context.write(new Text(entry.getValue()), new LongWritable(entry.getKey()));
			}
		}
	}

	/*
	* APPLICATION
	*/
	public int run(String[] args) throws Exception {

		Configuration conf = getConf();

		if (args.length != 2) {
			System.err.println("Usage: CountFollowers <input_path> <output_path>");
			System.exit(2);
		}

		Job job = new Job(conf);
		job.setJarByClass(TopUsers.class);
		job.setJobName("Top users");

		job.setMapperClass(CountMapper.class);
		//job.setMapOutputKeyClass(Text.class);
		//job.setMapOutputValueClass(IntWritable.class);

		//job.setCombinerClass(CountReducer.class);
		//job.setSortComparatorClass(BigramComparator.class);

		job.setReducerClass(CountReducer.class);
		job.setOutputKeyClass(Text.class);
		job.setOutputValueClass(LongWritable.class);

		job.setInputFormatClass(KeyValueTextInputFormat.class);
		job.setOutputFormatClass(TextOutputFormat.class);

		FileInputFormat.addInputPath(job, new Path(args[0]));
		FileOutputFormat.setOutputPath(job, new Path(args[1]));

		boolean success = job.waitForCompletion(true);
		return success ? 0 : 1;
	}

	public static void main(String[] args) throws Exception {

		int ret = ToolRunner.run(new TopUsers(), args);
		System.exit(ret);
	}
}
