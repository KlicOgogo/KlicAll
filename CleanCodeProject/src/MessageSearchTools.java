import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.Scanner;
import java.util.stream.Collectors;

public class MessageSearchTools {

    public void searchAuthor(ArrayList<Message> data, Scanner scanner) {
        System.out.println("Input author's name:");
        String author = scanner.next();
        ArrayList<Message> findMessages = data.stream().filter(i -> i.getAuthor().equals(author)).collect(Collectors.toCollection(ArrayList::new));
        for (
                Message i : findMessages) {
            System.out.println(i.toString());
        }
    }

    public void searchExpression(ArrayList<Message> data, Scanner scanner) {
        System.out.println("Input the expression:");
        String expression = scanner.next();
        ArrayList<Message> findMessages = data.stream().filter(i -> i.getMessage().contains(expression)).collect(Collectors.toCollection(ArrayList::new));
        for (
                Message i : findMessages) {
            System.out.println(i.toString());
        }
    }

    public void searchRegExpression(ArrayList<Message> data, Scanner scanner) {
        System.out.println("Input the regular expression:");
        try {
            String regExpression = scanner.next();
            ArrayList<Message> findMessages = data.stream().filter(i -> i.getMessage().matches(regExpression)).collect(Collectors.toCollection(ArrayList::new));
            for (
                    Message i : findMessages) {
                System.out.println(i.toString());
            }
        } catch (Exception exception) {
            System.out.println(exception.getMessage());
        }
    }

    public void historyIntervals(ArrayList<Message> data, Scanner scanner) {
        try {
            scanner.nextLine();
            System.out.println("Input 2 dates: lower and upper in format dd/MM/yyyy HH:mm:ss in 2 lines:");
            SimpleDateFormat format = new SimpleDateFormat("dd/MM/yyyy HH:mm:ss");
            Date lowerDate = format.parse(scanner.nextLine());
            Date upperDate = format.parse(scanner.nextLine());
            ArrayList<Message> findMessages = data.stream().filter(i -> (i.getDate().after(lowerDate)) && (i.getDate().before(upperDate))).collect(Collectors.toCollection(ArrayList::new));
            for (
                    Message i : findMessages) {
                System.out.println(i.toString());
            }
        } catch (ParseException exception) {
            System.out.println(exception.getMessage());
        }
    }

}

