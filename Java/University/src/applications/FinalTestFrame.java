package applications;

import data.*;
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.io.*;
import java.util.*;

/**
 * Created by andrejka on 22.12.15.
 */
public class FinalTestFrame extends JFrame {
    private ArrayList<ForestTree> array = new ArrayList<>();
    private DefaultListModel<String> listModel;
    private JList<String> list;
    FinalTestFrame()
    {
        super(new String("Final test frame"));
        setSize(300,450);
        setResizable(false);
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        initMenu();
        listModel = new DefaultListModel<>();
        list = new JList<>(listModel);
        list.setFont(new Font("Ubuntu mono",Font.PLAIN,16));
        updateList();
        add(new JScrollPane(list,
                JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED,
                JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED));
    }

    private void initMenu()
    {
        JMenuBar menuBar = new JMenuBar();
        menuBar.setLayout(new BoxLayout(menuBar, BoxLayout.PAGE_AXIS));
        JMenuItem openItem = new JMenuItem("Open a file", KeyEvent.VK_O);
        menuBar.add(openItem);
        JMenuItem saveItem = new JMenuItem("Save as", KeyEvent.VK_S);
        menuBar.add(saveItem);
        JMenuItem addItem = new JMenuItem("Фяфя", KeyEvent.VK_A);
        menuBar.add(addItem);
        setJMenuBar(menuBar);
        openItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {

                JFileChooser fileChooser = new JFileChooser();
                if (fileChooser.showOpenDialog(FinalTestFrame.this)==JFileChooser.APPROVE_OPTION) {
                    File file = fileChooser.getSelectedFile();
                    try {
                        Scanner in = new Scanner(file);
                        int n = in.nextInt();
                        //students.clear();
                        for (int i=0; i<n; i++) {
                            //students.add(new Student(in.nextInt(), in.next(), in.nextInt(), in.nextInt()));
                        }
                        in.close();
                        updateList();
                    }
                    catch (Exception e) {
                        JOptionPane.showMessageDialog(FinalTestFrame.this, "Reading from file failed.");
                    }
                }
            }
        });

        saveItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                JFileChooser fileChooser = new JFileChooser();
                if (fileChooser.showSaveDialog(FinalTestFrame.this)==JFileChooser.APPROVE_OPTION) {
                    File file = fileChooser.getSelectedFile();
                    try {
                        FileWriter out = new FileWriter(file);
                        out.write(array.size()+"\n");
                        for (Iterator it = array.iterator(); it.hasNext(); ) {
                            out.write(it.next()+"\n");
                        }
                        out.close();
                    }
                    catch (Exception e) {
                        JOptionPane.showMessageDialog(FinalTestFrame.this, "Writing to file failed.");
                    }
                }
            }
        });

        addItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                JTextField idField = new JTextField();
                JTextField nameField = new JTextField();
                JTextField courseField = new JTextField();
                JTextField groupField = new JTextField();
                final JComponent[] inputs = new JComponent[] {
                        new JLabel("ID:"), idField,
                        new JLabel("Surname:"), nameField,
                        new JLabel("Course:"), courseField,
                        new JLabel("Group:"), groupField
                };
                if (JOptionPane.showConfirmDialog(FinalTestFrame.this, inputs,
                        "Input new student", JOptionPane.OK_CANCEL_OPTION) == JOptionPane.YES_OPTION) {
                    try {
                        //array.add(new Student(Integer.parseInt(idField.getText()),
                          //      nameField.getText(),
                            //    Integer.parseInt(courseField.getText()),
                              //  Integer.parseInt(groupField.getText()) ));
                        updateList();
                    } catch (NumberFormatException e) {
                        JOptionPane.showMessageDialog(FinalTestFrame.this, "Wrong values.");
                    }
                }
            }
        });
    }

    private void updateList() {
        listModel.clear();
        if (array.isEmpty()) {
            listModel.addElement("<html><body><b>Nothing to show.");
            return;
        }
        Collections.sort(array, new NameComparator());
        ArrayList<ForestTree> array1 = new ArrayList<>();
        for (int i=0; i<array.size(); i++) {
            String name = array.get(i).getName();
            if ( (i!=0 && array.get(i-1).getName().compareTo(name)==0) ||
                    (i!=array.size()-1 && array.get(i+1).getName().compareTo(name)==0) ) {
                array1.add(array.get(i));
            }
        }
        if (array1.isEmpty()) {
            listModel.addElement("<html><body><b>Nothing to show.");
            return;
        }
        Collections.sort(array1);
        listModel.addElement("<html><body><b>" +
                "crs/gr&nbsp name&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp id");
        for (Iterator<ForestTree> it = array1.iterator(); it.hasNext(); ) {
            listModel.addElement(it.next().toString());
        }
    }

    public static void main(String[] args)
    {
        FinalTestFrame frame = new FinalTestFrame();
        frame.setVisible(true);
    }

    class NameComparator implements Comparator<ForestTree>
    {
        @Override
        public int compare(ForestTree st1, ForestTree st2) {
            return st1.getName().compareTo(st2.getName());
        }
    }
}
