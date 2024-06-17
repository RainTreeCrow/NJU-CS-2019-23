import org.apache.hadoop.io.*;
import org.apache.hadoop.mapreduce.Mapper;

import java.io.IOException;
import java.util.HashMap;
import java.util.HashSet;


public class NormalizationMapper extends Mapper<LongWritable, Text, Text, ValuePair> {

    private HashMap<String, String> nicknames = new HashMap<>();

    private HashMap<String,String[]> uniMap = new HashMap<>();

    private ValuePair value_pair = new ValuePair();

    @Override
    protected void map(LongWritable key, Text value, Context context) throws IOException, InterruptedException {
        //1.获取一行数据 course.tbl
        String line = value.toString();
        String[] splits = line.split("\t");

        int times = Integer.parseInt(splits[1]);
        String[] names = splits[0].split("<|，|>");
        String key_name = names[1];
        String value_name = names[2];

        System.out.println("——————————");
        System.out.println(key_name);
        System.out.println(value_name);
        System.out.println(times);

        value_pair.setValue(times);
        value_pair.setName(value_name);

        context.write(new Text(key_name),value_pair);

    }
}
