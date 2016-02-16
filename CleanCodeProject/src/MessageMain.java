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
            String help = "For working with chat tools run these commands typing a proper number: \n" +
                    "1 - adding a message  \t" +
                    "2 - saving to file  \t" +
                    "3 - loading from file  \n" +
                    "4 - observing history  \t" +
                    "5 - deleting by id \t" +
                    "6 - searching by author \n" +
                    "7 - searching by expression  \t" +
                    "8 - searching by regular expression \n" +
                    "9 - observing history in time interval \t" +
                    "10 - help \t" +
                    "11 - quit \n";
            String run = "Type your command: \n";
            System.out.println(help);
            int quit = 0;
            while (quit == 0) {
                System.out.println(run);
                String command = scan.next();
                if (command.equals("1")) {
                    workTool.addMessage();
                } else if (command.equals("2")) {
                    System.out.println("Input file's name:");
                    String fileName = scan.next();
                    workTool.toFile(fileName);
                } else if (command.equals("3")) {
                    System.out.println("Input file's name:");
                    String fileName = scan.next();
                    workTool.loadFromFile(fileName);
                } else if (command.equals("4")) {
                    workTool.watchAll();
                } else if (command.equals("5")) {
                    System.out.println("Input id:");
                    String id = scan.next();
                    workTool.removeById(id);
                } else if (command.equals("6")) {
                    System.out.println("Input author's name:");
                    String author = scan.next();
                    forUseSearchMethods = workTool.searchAuthor(author);
                    for (Message i : forUseSearchMethods) {
                        System.out.println(i.toString());
                    }
                    forUseSearchMethods.clear();
                } else if (command.equals("7")) {
                    System.out.println("Input the expression:");
                    String expression = scan.next();
                    forUseSearchMethods = workTool.searchExpression(expression);
                    for (Message i : forUseSearchMethods) {
                        System.out.println(i.toString());
                    }
                    forUseSearchMethods.clear();
                } else if (command.equals("8")) {
                    System.out.println("Input the regular expression:");
                    String regExpression = scan.next();
                    forUseSearchMethods = workTool.searchExpression(regExpression);
                    for (Message i : forUseSearchMethods) {
                        System.out.println(i.toString());
                    }
                    forUseSearchMethods.clear();
                } else if (command.equals("10")) {
                    System.out.println(help);
                } else if (command.equals("11")) {
                    scan.close();
                    quit = 1;
                } else if (command.equals("9")) {
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
