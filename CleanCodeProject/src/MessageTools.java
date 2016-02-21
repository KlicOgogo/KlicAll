import com.google.gson.Gson;
import com.google.gson.GsonBuilder;

import java.util.*;
import java.io.*;
import java.util.stream.Collectors;

public class MessageTools {
    private ArrayList<Message> data;

    public MessageTools() {
        data = new ArrayList<>();
    }

    public void add() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Input author's name: ");
        String authorAdd = scanner.nextLine();
        System.out.println("Input the text of the message: ");
        String messageAdd = scanner.nextLine();
        data.add(new Message(UUID.randomUUID().toString(), messageAdd, authorAdd, System.currentTimeMillis()));
    }

    public void saveFile(String fileName) throws IOException {
        Writer writer = new FileWriter(fileName);
        Gson gson = new GsonBuilder().create();
        gson.toJson(data, writer);
        writer.close();
    }

    public void loadFile(String fileName) throws IOException {
        data.clear();
        Reader reader = new InputStreamReader(new FileInputStream(fileName));
        Gson gson = new GsonBuilder().create();
        Message[] messageAdd = gson.fromJson(reader, Message[].class);
        Collections.addAll(data, messageAdd);
        reader.close();
    }

    public void allHistory() {
        ArrayList<Message> copy = new ArrayList<>(data.size());
        copy.addAll(data.stream().collect(Collectors.toList()));
        Collections.sort(copy);
        for (Message i : copy) {
            System.out.println(i.toString());
        }
    }

    public void removeId(String id) {
        for (Message i : data) {
            if (i.getId().equals(id)) {
                data.remove(i);
                break;
            }
        }
    }

    public ArrayList<Message> searchAuthor(String author) {
        return data.stream().filter(i -> i.getAuthor().equals(author)).collect(Collectors.toCollection(ArrayList::new));
    }

    public ArrayList<Message> searchExpression(String expression) {
        return data.stream().filter(i -> i.getMessage().contains(expression)).collect(Collectors.toCollection(ArrayList::new));
    }

    public ArrayList<Message> searchRegExpression(String regExpression) {
        return data.stream().filter(i -> i.getMessage().matches(regExpression)).collect(Collectors.toCollection(ArrayList::new));
    }

    public ArrayList<Message> historyIntervals(Date lowerDate, Date upperDate) {
        return data.stream().filter(i -> (i.getDate().after(lowerDate)) && (i.getDate().before(upperDate))).collect(Collectors.toCollection(ArrayList::new));
    }

}
