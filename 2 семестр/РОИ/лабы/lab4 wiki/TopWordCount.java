package pdccourse.hw3;

import java.io.IOException;
import java.util.StringTokenizer;

import java.util.Map;
import java.util.Map.Entry;
import java.util.TreeMap;

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
import org.apache.hadoop.mapreduce.lib.input.KeyValueTextInputFormat;


public class TopWordCount {

	public static class TokenizerMapper extends Mapper<Text, Text, Text, LongWritable> {

		private TreeMap<Long, String> tmap;

		@Override
		public void setup(Context context) throws IOException, InterruptedException {
			tmap = new TreeMap<Long, String>();
		}

		public void map(Text key, Text value, Context context) throws IOException, InterruptedException {
			
			String word = key.toString();
			Long count = Long.parseLong(value.toString());
			tmap.put(count, word);
			if (tmap.size() > 20) {
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
	 
	public static class IntSumReducer extends Reducer<Text, LongWritable, Text, LongWritable> {
	
		private TreeMap<Long, String> tmap;
	
		@Override
		public void setup(Context context) throws IOException, InterruptedException {
			tmap = new TreeMap<Long, String>();
		}

		public void reduce(Text key, Iterable<LongWritable> values, Context context) throws IOException, InterruptedException {
		
			String word = key.toString();
			long count = 0;
			for (LongWritable val : values) {
				count = val.get();
			}
		 
			tmap.put(count, word);
			if (tmap.size() > 20) {
				tmap.remove(tmap.firstKey());
			}
		}

		@Override
		public void cleanup(Context context) throws IOException, InterruptedException {
			
			context.write(new Text("\\P{L}+"), null);
			for (Map.Entry<Long, String> entry : tmap.entrySet()) {
				String txt = "\\s" + entry.getValue() + "\\s";
				//String txt = entry.getValue();
				context.write(new Text(txt), null);
			}
			
		}
	}

	public static void main(String[] args) throws Exception {
	
		Configuration conf = new Configuration();
		String[] otherArgs = new GenericOptionsParser(conf, args).getRemainingArgs();
		
		if (otherArgs.length != 2) {
			System.err.println("Usage: TopWordCount <in> <out>");
			System.exit(2);
		}

		conf.set("mapreduce.input.keyvaluelinerecordreader.key.value.separator", "\t");
		conf.setBoolean("exact.match.only", true);
		conf.set("io.serializations",
			"org.apache.hadoop.io.serializer.JavaSerialization,"
			+ "org.apache.hadoop.io.serializer.WritableSerialization");

		Job job = new Job(conf, "top word count");
		job.setInputFormatClass(KeyValueTextInputFormat.class);
		job.setJarByClass(TopWordCount.class);
		
		job.setMapperClass(TokenizerMapper.class);
		job.setMapOutputKeyClass(Text.class);
		job.setMapOutputValueClass(LongWritable.class);
		
		//job.setCombinerClass(IntSumReducer.class);
		job.setReducerClass(IntSumReducer.class);
		
		job.setOutputKeyClass(Text.class);
		job.setOutputValueClass(LongWritable.class);
		
		FileInputFormat.addInputPath(job, new Path(otherArgs[0]));
		FileOutputFormat.setOutputPath(job, new Path(otherArgs[1]));
		
		System.exit(job.waitForCompletion(true) ? 0 : 1);
	}
}

