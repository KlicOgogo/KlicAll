import java.util.*;

public class MessageMain {
    public static void main(String[] args) {
        ArrayList<Message> messages = new ArrayList<>();
        MessageHistoryTools historyTool = new MessageHistoryTools();
        MessageSearchTools searchTool = new MessageSearchTools();
        Scanner scanner = new Scanner(System.in);
        final String help = "For working with chat tools run these commands typing a proper number: \n" +
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
        final String run = "Type your command: \n";
        System.out.println(help);
        int quit = 0;
        while (quit == 0) {
            System.out.println(run);
            String command = scanner.next();
            switch (command) {
                case "1":
                    historyTool.add(messages, scanner);
                    break;
                case "2": {
                    historyTool.saveFile(messages, scanner);
                    break;
                }
                case "3": {
                    historyTool.loadFile(messages, scanner);
                    break;
                }
                case "4":
                    historyTool.allHistory(messages);
                    break;
                case "5":
                    historyTool.removeId(messages, scanner);
                    break;
                case "6":
                    searchTool.searchAuthor(messages, scanner);
                    break;
                case "7":
                    searchTool.searchExpression(messages, scanner);
                    break;
                case "8":
                    searchTool.searchRegExpression(messages, scanner);
                    break;
                case "9":
                    searchTool.historyIntervals(messages, scanner);
                    break;
                case "10":
                    System.out.println(help);
                    break;
                case "11":
                    scanner.close();
                    quit = 1;
                    break;
            }
        }
    }
}
