import com.google.gson.Gson;
import com.google.gson.GsonBuilder;

import java.util.*;
import java.io.*;
import java.util.stream.Collectors;

public class MessageHistoryTools {

    public void add(ArrayList<Message> data) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Input author's name: ");
        String authorAdd = scanner.nextLine();
        System.out.println("Input the text of the message: ");
        String messageAdd = scanner.nextLine();
        data.add(new Message(UUID.randomUUID().toString(), messageAdd, authorAdd, System.currentTimeMillis()));
        scanner.close();
    }

    public void saveFile(ArrayList<Message> data) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Input file's name:");
        String fileName = scanner.next();
        try (Writer writer = new FileWriter(fileName)) {
            Gson gson = new GsonBuilder().create();
            gson.toJson(data, writer);
            writer.close();
        } catch (IOException exception) {
            System.out.println(exception.getMessage());
        }
    }

    public void loadFile(ArrayList<Message> data) {
        data.clear();
        Scanner scanner = new Scanner(System.in);
        System.out.println("Input file's name:");
        String fileName = scanner.next();
        try (Reader reader = new InputStreamReader(new FileInputStream(fileName))) {
            Gson gson = new GsonBuilder().create();
            Message[] messageAdd = gson.fromJson(reader, Message[].class);
            Collections.addAll(data, messageAdd);
            reader.close();
        } catch (IOException exception) {
            System.out.println(exception.getMessage());
        }
    }

    public void allHistory(ArrayList<Message> data) {
        ArrayList<Message> copy = new ArrayList<>(data.size());
        copy.addAll(data.stream().collect(Collectors.toList()));
        Collections.sort(copy);
        for (Message i : copy) {
            System.out.println(i.toString());
        }
    }

    public void removeId(ArrayList<Message> data) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Input id:");
        String id = scanner.next();
        for (Message i : data) {
            if (i.getId().equals(id)) {
                data.remove(i);
                break;
            }
        }
    }

}
