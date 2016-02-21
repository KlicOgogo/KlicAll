import java.io.IOException;
import java.util.*;
import java.text.SimpleDateFormat;
import java.text.ParseException;

public class MessageMain {
    public static void main(String[] args) {
        try {
            ArrayList<Message> searchUsed;
            MessageTools workTool = new MessageTools();
            Scanner scanner = new Scanner(System.in);
            String help = "For working with chat tools run these commands typing a proper number: \n" +
                    "1 - adding a message \t \t" +
                    "2 - saving to file \t \t" +
                    "3 - loading from file \n" +
                    "4 - observing history \t \t" +
                    "5 - deleting by id \t \t" +
                    "6 - searching by author \n" +
                    "7 - searching by expression  \t \t" +
                    "8 - searching by regular expression \n" +
                    "9 - observing history in time interval \t \t" +
                    "10 - help \t \t" +
                    "11 - quit \n";
            String run = "Type your command: \n";
            System.out.println(help);
            int quit = 0;
            while (quit == 0) {
                System.out.println(run);
                String command = scanner.next();
                switch (command) {
                    case "1":
                        workTool.add();
                        break;
                    case "2": {
                        System.out.println("Input file's name:");
                        String fileName = scanner.next();
                        workTool.saveFile(fileName);
                        break;
                    }
                    case "3": {
                        System.out.println("Input file's name:");
                        String fileName = scanner.next();
                        workTool.loadFile(fileName);
                        break;
                    }
                    case "4":
                        workTool.allHistory();
                        break;
                    case "5":
                        System.out.println("Input id:");
                        String id = scanner.next();
                        workTool.removeId(id);
                        break;
                    case "6":
                        System.out.println("Input author's name:");
                        String author = scanner.next();
                        searchUsed = workTool.searchAuthor(author);
                        for (
                                Message i : searchUsed) {
                            System.out.println(i.toString());
                        }
                        searchUsed.clear();
                        break;
                    case "7":
                        System.out.println("Input the expression:");
                        String expression = scanner.next();
                        searchUsed = workTool.searchExpression(expression);
                        for (Message i : searchUsed) {
                            System.out.println(i.toString());
                        }
                        searchUsed.clear();
                        break;
                    case "8":
                        System.out.println("Input the regular expression:");
                        String regExpression = scanner.next();
                        searchUsed = workTool.searchRegExpression(regExpression);
                        for (Message i : searchUsed) {
                            System.out.println(i.toString());
                        }
                        searchUsed.clear();
                        break;
                    case "10":
                        System.out.println(help);
                        break;
                    case "11":
                        scanner.close();
                        quit = 1;
                        break;
                    case "9":
                        scanner.nextLine();
                        System.out.println("Input 2 dates: lower and upper in format dd/MM/yyyy HH:mm:ss in 2 lines:");
                        SimpleDateFormat format = new SimpleDateFormat("dd/MM/yyyy HH:mm:ss");
                        Date lowerDate = format.parse(scanner.nextLine());
                        Date upperDate = format.parse(scanner.nextLine());
                        searchUsed = workTool.historyIntervals(lowerDate, upperDate);
                        for (Message i : searchUsed) {
                            System.out.println(i.toString());
                        }
                        searchUsed.clear();
                        break;
                }
            }
        } catch (IOException exception) {
            System.out.println(exception.getMessage());
        } catch (ParseException exception) {
            System.out.println(exception.getMessage() + "  ");
        }
    }
}
