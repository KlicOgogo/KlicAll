import java.io.IOException;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.LocalTime;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.TimeZone;
import java.util.Scanner;


/**
 * Created by andrejka on 16.2.16.
 */
public class MessageMain {
    public static void main(String[] args) {
        try {
            ArrayList<Message> forUseSearchMethods = new ArrayList<>();
            MessageTools workTool = new MessageTools();
            Scanner scan = new Scanner(System.in);
            String help = "For working with chat tools run these commands: \n" +
                    "addMessage  \n" +
                    "writeToFile <String filename>  \n" +
                    "openFromFile <String filename>  \n" +
                    "watchHistory  \n" +
                    "deleteById <Integer id>  \n" +
                    "searchByAuthor <String author>  \n" +
                    "searchByExpression <String expression> \n" +
                    "searchByRegExpression <String regExpression> \n" +
                    "watchHistoryBySendingTime <time (year, month, day, hour, minute, second, millisecond), time> \n" +
                    "help \n" +
                    "quit \n";
            String run = "Type your command: \n";
            System.out.println(help);
            int quit = 0;
            while (quit == 0) {
                System.out.println(run);
                String command = scan.next();
                if (command.equals("addMessage")) {
                    workTool.addMessage();
                } else if (command.equals("writeToFile")) {
                    String fileName = scan.next();
                    workTool.toFile(fileName);
                } else if (command.equals("openFromFile")) {
                    String fileName = scan.next();
                    workTool.loadFromFile(fileName);
                } else if (command.equals("watchHistory")) {
                    workTool.watchAll();
                } else if (command.equals("deleteById")) {
                    int id = scan.nextInt();
                    workTool.removeById(id);
                } else if (command.equals("searchByAuthor")) {
                    String author = scan.next();
                    forUseSearchMethods = workTool.searchAuthor(author);
                    for (Message i : forUseSearchMethods) {
                        System.out.println(i.toString());
                    }
                    forUseSearchMethods.clear();
                } else if (command.equals("searchByExpression")) {
                    String expression = scan.next();
                    forUseSearchMethods = workTool.searchExpression(expression);
                    for (Message i : forUseSearchMethods) {
                        System.out.println(i.toString());
                    }
                    forUseSearchMethods.clear();
                } else if (command.equals("searchByRegExpression")) {
                    String regExpression = scan.next();
                    forUseSearchMethods = workTool.searchExpression(regExpression);
                    for (Message i : forUseSearchMethods) {
                        System.out.println(i.toString());
                    }
                    forUseSearchMethods.clear();
                } else if (command.equals("help")) {
                    System.out.println(help);
                } else if (command.equals("quit")) {
                    scan.close();
                    quit = 1;
                }
            }
        } catch (IOException exception) {
            System.out.println(exception.getMessage());
        }
    }
}
