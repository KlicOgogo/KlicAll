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
                    workTool.searchAuthor(author);
                } else if (command.equals("searchByExpression")) {
                    String expression = scan.next();
                    workTool.searchExpression(expression);
                } else if (command.equals("searchByRegExpression")) {
                    String regExpression = scan.next();
                    workTool.searchExpression(regExpression);
                } else if (command.equals("help")) {
                    System.out.println(help);
                } else if (command.equals("quit")) {
                    scan.close();
                    quit = 1;
                }
            }
           /*
            //output = workTool.historySendingTime(new LocalDateTime(new LocalDate(2014, 10, 10), new LocalTime(22, 10, 10, 0)),
                    new LocalDateTime(new LocalDate(2016, 10, 10), new LocalTime(22, 10, 10, 0)));
            LocalDateTime l = new LocalDateTime(2015, 10, 10, 10, 10, 10, 0);
            System.out.println(output.toString());
*/
        } catch (IOException exception) {
            System.out.println(exception.getMessage());
        }
    }
}
