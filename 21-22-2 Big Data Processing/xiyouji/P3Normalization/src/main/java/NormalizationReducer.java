import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Reducer;

import java.io.IOException;
import java.text.DecimalFormat;
import java.util.ArrayList;

public class NormalizationReducer extends Reducer<Text,ValuePair, Text, Text>
{
    @Override
    protected void reduce(Text key, Iterable<ValuePair> values, Context context) throws IOException, InterruptedException {
//        System.out.println("——————");
//        System.out.println(key.getCharacter_1());
//        System.out.println(key.getCharacter_2());
        int sum = 0;//所有边权和
        int num = 0;//共现人物数量
        ArrayList<ValuePair> tmp_values = new ArrayList<>();
        for (ValuePair it: values) {
            sum += it.getValue();
            ++num;
            tmp_values.add(new ValuePair(it));
        }

        String pairs = new String("[");
        DecimalFormat decimalFormat= new DecimalFormat( "0.#####" ); //构造方法的字符格式这里如果小数不足2位,会以0补足
        int index = 0;
        for (ValuePair it :tmp_values){
            ++index;
            if(index < num)
                pairs += it.getName() + "，" + decimalFormat.format((float) it.getValue()/sum) + "|";
            else
                pairs += it.getName() + "，" + decimalFormat.format((float) it.getValue()/sum) + "]";
        }
        context.write(key,new Text(pairs));
    }

}
