import java.io.IOException;
import java.util.*;
import java.text.SimpleDateFormat;
import java.text.ParseException;


/**
 * Created by andrejka on 16.2.16.
 */
public class MessageMain {
    public static void main(String[] args) {
        try {
            ArrayList<Message> forUseSearchMethods;
            MessageTools workTool = new MessageTools();
            Scanner scan = new Scanner(System.in);
            String help = "For working with chat tools run these commands: \t" +
                    "addMessage  \t" +
                    "toFile <String filename>  \t" +
                    "fromFile <String filename>  \n" +
                    "history  \t" +
                    "deleteId <Integer id>  \t" +
                    "searchAuthor <String author>  \n" +
                    "searchExp <String expression> \t" +
                    "searchRegExp <String regExpression> \t" +
                    "historyIntervals \t" +
                    "help \t" +
                    "quit \n";
            String run = "Type your command: \n";
            System.out.println(help);
            int quit = 0;
            while (quit == 0) {
                System.out.println(run);
                String command = scan.next();
                if (command.equals("addMessage")) {
                    workTool.addMessage();
                } else if (command.equals("toFile")) {
                    String fileName = scan.next();
                    workTool.toFile(fileName);
                } else if (command.equals("fromFile")) {
                    String fileName = scan.next();
                    workTool.loadFromFile(fileName);
                } else if (command.equals("history")) {
                    workTool.watchAll();
                } else if (command.equals("deleteId")) {
                    String id = scan.next();
                    workTool.removeById(id);
                } else if (command.equals("searchAuthor")) {
                    String author = scan.next();
                    forUseSearchMethods = workTool.searchAuthor(author);
                    for (Message i : forUseSearchMethods) {
                        System.out.println(i.toString());
                    }
                    forUseSearchMethods.clear();
                } else if (command.equals("searchExp")) {
                    String expression = scan.next();
                    forUseSearchMethods = workTool.searchExpression(expression);
                    for (Message i : forUseSearchMethods) {
                        System.out.println(i.toString());
                    }
                    forUseSearchMethods.clear();
                } else if (command.equals("searchRegExp")) {
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
                } else if (command.equals("historyIntervals")) {
                    scan.nextLine();
                    System.out.println("Input 2 dates: lower and upper in format dd/MM/yyyy HH:mm:ss in 2 lines:");
                    SimpleDateFormat format = new SimpleDateFormat("dd/MM/yyyy HH:mm:ss");
                    Date lowerDate = format.parse(scan.nextLine());
                    Date upperDate = format.parse(scan.nextLine());
                    forUseSearchMethods = workTool.historySendingTime(lowerDate, upperDate);
                    for (Message i : forUseSearchMethods) {
                        System.out.println(i.toString());
                    }
                    forUseSearchMethods.clear();
                }
            }
        } catch (IOException exception) {
            System.out.println(exception.getMessage());
        } catch (ParseException exception) {
            System.out.println(exception.getMessage());
        }
    }
}
