import java.io.*;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;
import java.util.TreeMap;

public class MathLesson {
    public static void main(String[] args) {
        try {
            Scanner scanner = new Scanner(new File("input.txt"));
            TreeMap<Integer, Integer> all = new TreeMap<>();
            int n = scanner.nextInt();
            for (int i = 0; i < n*n; i++) {
                int t = scanner.nextInt();
                if (!all.containsKey(t)) {
                    all.put(t, 1);
                } else {
                    all.put(t, all.get(t)+1);
                }
            }
            scanner.close();
            ArrayList<Integer> result = new ArrayList<>();
            result.add(all.lastKey()/2);
            all.put(all.lastKey(), all.get(all.lastKey())-1);
            for (int i = 0; i < n-1; i++) {
                while (all.get(all.lastKey()) == 0) {
                    all.remove(all.lastKey());
                }
                int a = all.lastKey()-result.get(0);
                result.add(a);
                all.put(2*a, all.get(2*a)-1);
                for (int j = 0; j < result.size()-1; j++) {
                    all.put(result.get(j)+a, all.get(result.get(j)+a)-2);
                }
            }
            Collections.sort(result);
            FileWriter writer = new FileWriter(new File("output.txt"));
            for (int i = 0; i < n; i++) {
                writer.write(result.get(i).toString()+'\n');
            }
            writer.close();
        }
        catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        catch (IOException e) {
            e.printStackTrace();
        }
    }
}
