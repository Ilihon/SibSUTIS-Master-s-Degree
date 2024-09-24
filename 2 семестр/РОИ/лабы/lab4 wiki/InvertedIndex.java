package pdccourse.hw3;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.DataInput;
import java.io.DataOutput;
import java.io.File;
import java.io.FileReader;

import java.util.StringTokenizer;
import java.util.Map;
import java.util.Map.Entry;
import java.util.HashMap;
import java.util.List;
import java.util.ArrayList;
import java.util.LinkedHashMap;

import org.apache.hadoop.conf.Configuration;
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
import org.apache.hadoop.mapreduce.Partitioner;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.util.GenericOptionsParser;
import org.apache.hadoop.util.StringUtils;

public class InvertedIndex {

	public static class MPair implements WritableComparable<MPair> {

		private String word;
		private Integer tf;

		public void set(String word, Integer tf) {
			this.word = word;
			this.tf = tf;
		}

		public String getWord() {
			return word;
		}

		public Integer getTf() {
			return tf;
		}

		@Override
		public void readFields(DataInput in) throws IOException {
			word = Text.readString(in);
			tf = Integer.parseInt(Text.readString(in));
		}

		@Override
		public void write(DataOutput out) throws IOException {
			Text.writeString(out, word);
			Text.writeString(out, tf.toString());
		}

		@Override
		public int hashCode() {
			return word.hashCode();
		}

		@Override
		public String toString() {
			return word.toString();
		}

		@Override
		public int compareTo(MPair o) {
			if (!word.equals(o.word)) {
				return word.compareTo(o.word);
			} else {
				return (o.tf > tf ? 1 : -1);
			}
		}
	}

	public static class MPartitioner extends Partitioner<MPair, Text> {

		@Override
		public int getPartition(MPair pair, Text docid, int numOfPartitions) {
			return ( pair.getWord().hashCode() & Integer.MAX_VALUE ) % numOfPartitions;
		}

	}

	public static class MGroupComparator extends WritableComparator {

		public MGroupComparator() {
			super(MPair.class, true);
		}

		@Override
		public int compare(WritableComparable w1, WritableComparable w2) {
			if (w1 instanceof MPair && w2 instanceof MPair) {
				return ((MPair)w1).compareTo((MPair)w2);
			}
			return super.compare(w1, w2);
		}
	}

	public static class TokenizerMapper extends Mapper<Text, Text, MPair, Text> {

		private List<String> skipList = new ArrayList<String>();
		private long numRecords = 0;
		private Map<String, Map<String, Integer> > results = new HashMap<String, Map<String, Integer>>();
		private final MPair pair = new MPair();
		private final Text docid = new Text();

		@Override
		protected void setup(Context context) {
			String skipListFile = context.getConfiguration().get("invertedindex.skip-list");
			if (skipListFile != null) {
				loadSkipListFile(skipListFile);
			}
		}

		public void map(Text key, Text value, Context context) throws IOException, InterruptedException {

			String doc_id = key.toString();
			String text = value.toString();

			for (String pattern : skipList) {
				text = text.replaceAll(pattern, " ");
			}

			StringTokenizer itr = new StringTokenizer(text);
			String word;

			while (itr.hasMoreTokens()) {
				word = itr.nextToken();
				addResult(word, doc_id);
			}

			if ((++numRecords % 1000) == 0) {
				context.setStatus("Finished processing " + numRecords + " records");
				emitResults(context);
			}
		}

		private void loadSkipListFile(String skipListFile) {

			BufferedReader fis = null;
			try {
				fis = new BufferedReader(new FileReader(skipListFile));
				String pattern = null;
				while ((pattern = fis.readLine()) != null) {
					skipList.add(pattern);
				}
			} catch (IOException ioe) {
				System.err.println("Caught exception while loading skip file '" + skipListFile + "' : " + StringUtils.stringifyException(ioe));
			} finally {
				if (fis != null) {
					try {
						fis.close();
					} catch (IOException ioe) {
						System.err.println("Caught exception while closing skip file '" + skipListFile + "' : " + StringUtils.stringifyException(ioe));
					}
				}
			}
		}

		private void addResult(String word, String docid) {

			Map<String, Integer> counts = results.get(word);

			if (counts == null) {
				counts = new HashMap<String, Integer>();
				results.put(word, counts);
			}

			Integer count = counts.get(docid);
			if (count == null) {
				counts.put(docid, 1);
			} else {
				counts.put(docid, ++count);
			}
		}

		private void emitResults(Context context) throws IOException, InterruptedException {

			for (Entry<String, Map<String, Integer> > counts : results.entrySet()) {
				String word = counts.getKey();
				for (Entry<String, Integer> count : counts.getValue().entrySet()) {
					pair.set(word, count.getValue());
					docid.set(count.getKey());
					context.write(pair, docid);
				}
			}
			results.clear();
		}

		@Override
		public void cleanup(Context context) throws IOException, InterruptedException {
			emitResults(context);
		}
	}

	public static class IntSumReducer extends Reducer<MPair, Text, Text, Text> {

		private Map<String, Map<String, Integer> > results = new HashMap<String, Map<String, Integer> >();
		private Map<String, Long> DD = new HashMap<String, Long>();

		private final Text word = new Text();
		private final Text docid = new Text();

		private long numRecords = 0;
		static double D;
		static int N;


		@Override
		public void setup(Context context) throws IOException, InterruptedException {

			N = Integer.parseInt(context.getConfiguration().get("invertedindex.N"));

			BufferedReader fis = null;
			StringBuilder resultStringBuilder = new StringBuilder();
			String DFile = context.getConfiguration().get("invertedindex.D");
			try {
				fis = new BufferedReader(new FileReader(DFile));
				String pattern = null;
				pattern = fis.readLine();
				D = Double.parseDouble(pattern);
			} catch (IOException ioe) {
				System.err.println("Caught exception while loading skip file '" + DFile + "' : " + StringUtils.stringifyException(ioe));
			} finally {
				if (fis != null) {
					try {
						fis.close();
					} catch (IOException ioe) {
						System.err.println("Caught exception while closing skip file '" + DFile + "' : " + StringUtils.stringifyException(ioe));
					}
				}
			}
		}

		public void reduce(MPair key, Iterable<Text> values, Context context) throws IOException, InterruptedException {
			String docid = "";
			for (Text val : values) {
				docid = val.toString();
			}
			addResult(key.getWord(), docid, key.getTf());
			if ((numRecords % 1000) == 0) {
				context.setStatus("Reduce: Finished processing " + numRecords + " records");
				emitResults(context);
			}
		}

		private void addResult(String word, String docid, Integer tf) {
			Map<String, Integer> counts = results.get(word);
			if (counts == null) {
				counts = new LinkedHashMap<String, Integer>();
				results.put(word, counts);
				++numRecords;
			}
			Integer count = counts.get(docid);
			if (count == null) {
				if (counts.size() < 20) {
					counts.put(docid, tf);
				}
			} else {
				counts.put(docid, count + tf);
			}
			Long dd = DD.get(word);
			if (dd == null) {
				DD.put(word, (long)tf);
			} else {
				DD.put(word, dd + tf);
			}
		}

		private void emitResults(Context context) throws IOException, InterruptedException {
			for (Entry<String, Map<String, Integer> > counts : results.entrySet()) {
				String wr = counts.getKey();
				word.set(wr);
				Long dd = DD.get(wr);
				Double idf = Math.abs(Math.log(D / dd));
				String text = /*dd.toString() + " : " + Double.toString(D)  + " : " + idf.toString() + " : " + Math.log(D / dd) +*/ " [";
				int limit_counter = 0;
				for (Entry<String, Integer> count : counts.getValue().entrySet()) {
					if (limit_counter == N){
						continue;
					}
					text += "<" + count.getKey() + ", " + Double.valueOf(count.getValue() * idf).toString() + ">, ";
					limit_counter++;
				}
				text = text.substring(0, text.length() - 2);
				text += "]";
				docid.set(text);
				context.write(word, docid);
			}
			results.clear();
			DD.clear();
		}

		@Override
		protected void cleanup(Context context) throws IOException, InterruptedException {
			emitResults(context);
		}
	}

	public static void main(String[] args) throws Exception {

		Configuration conf = new Configuration();
		String[] otherArgs = new GenericOptionsParser(conf, args).getRemainingArgs();
		if (otherArgs.length != 5) {
			System.err.println("Usage: invertedindex <in> <out> <skip_list> <d> <docs_output_limit>");
			System.exit(2);
		}

		conf.set("invertedindex.skip-list", otherArgs[2]);
		conf.set("invertedindex.D", otherArgs[3]);
		conf.set("invertedindex.N", otherArgs[4]);
		conf.set("mapreduce.input.keyvaluelinerecordreader.key.value.separator", " ");
		conf.setBoolean("exact.match.only", true);
		conf.set("io.serializations",
			"org.apache.hadoop.io.serializer.JavaSerialization,"
			+ "org.apache.hadoop.io.serializer.WritableSerialization");

		Job job = new Job(conf, "build inverted index");
		job.setInputFormatClass(XmlInputFormat.class);
		job.setJarByClass(InvertedIndex.class);

		job.setMapperClass(TokenizerMapper.class);
		job.setMapOutputKeyClass(MPair.class);
		job.setMapOutputValueClass(Text.class);

		//job.setCombinerClass(IntSumReducer.class);
		job.setPartitionerClass(MPartitioner.class);
		job.setSortComparatorClass(MGroupComparator.class);
		//job.setGroupingComparatorClass(MGroupComparator.class);

		job.setReducerClass(IntSumReducer.class);
		job.setOutputKeyClass(Text.class);
		job.setOutputValueClass(Text.class);

		FileInputFormat.addInputPath(job, new Path(otherArgs[0]));
		FileOutputFormat.setOutputPath(job, new Path(otherArgs[1]));

		boolean success = job.waitForCompletion(true);
		System.exit(success ? 0 : 1);
	}
}
