package applications;

import data.*;
import javax.swing.*;
import javax.swing.text.DefaultFormatterFactory;
import javax.swing.text.NumberFormatter;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.io.File;
import java.io.FileWriter;
import java.text.NumberFormat;
import java.util.*;

public class Lab15Frame extends JFrame {

    private ArrayList<Toy> toys = new ArrayList<>();
    private DefaultListModel<String> listModel;
    private JList<String> list;
    public Lab15Frame(String title) {
        super(title);
        setSize(600,450);
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        listModel = new DefaultListModel<>();
        list = new JList<>(listModel);
        list.setFont(new Font("Ubuntu mono",Font.PLAIN,16));
        updateList();
        add(new JScrollPane(list,
                JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED,
                JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED));
        JPanel panel = new JPanel();
        JButton butOpen = new JButton("open");
        JButton butSave = new JButton("save");
        JButton butAdd = new JButton("add a toy");
        JButton butInput = new JButton("input ages");
        panel.add(butOpen);
        panel.add(butSave);
        panel.add(butAdd);
        panel.add(butInput);
        add(panel, BorderLayout.SOUTH);
        butOpen.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {

                JFileChooser fileChooser = new JFileChooser();
                if (fileChooser.showOpenDialog(Lab15Frame.this)==JFileChooser.APPROVE_OPTION) {
                    File file = fileChooser.getSelectedFile();
                    try {
                        Scanner in = new Scanner(file);
                        int n = in.nextInt();
                        toys.clear();
                        for (int i=0; i<n; i++) {
                            toys.add(new Toy(in.next(), in.nextInt(), in.nextInt(), in.nextInt()));
                        }
                        in.close();
                        updateList();
                    }
                    catch (AgeException e) {
                        JOptionPane.showMessageDialog(Lab15Frame.this, e.getMessage());
                    }
                    catch (CostException e){
                        JOptionPane.showMessageDialog(Lab15Frame.this, e.getMessage());
                    }
                    catch (Exception e) {
                        JOptionPane.showMessageDialog(Lab15Frame.this, "Reading from file failed.");
                    }
                }
            }
        });

        butSave.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                JFileChooser fileChooser = new JFileChooser();
                if (fileChooser.showSaveDialog(Lab15Frame.this)==JFileChooser.APPROVE_OPTION) {
                    File file = fileChooser.getSelectedFile();
                    try {
                        FileWriter out = new FileWriter(file);
                        out.write(toys.size()+"\n");
                        for (Iterator it = toys.iterator(); it.hasNext(); ) {
                            out.write(it.next()+"\n");
                        }
                        out.close();
                    }
                    catch (Exception e) {
                        JOptionPane.showMessageDialog(Lab15Frame.this, "Writing to file failed.");
                    }
                }
            }
        });

        butAdd.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                JTextField costField = new JTextField();
                JTextField nameField = new JTextField();
                JTextField maxField = new JTextField();
                JTextField minField = new JTextField();
                final JComponent[] inputs = new JComponent[] {
                        new JLabel("Name:"), nameField,
                        new JLabel("Cost:"), costField,
                        new JLabel("MinAge:"),  minField,
                        new JLabel("MaxAge:"), maxField
                };
                if (JOptionPane.showConfirmDialog(Lab15Frame.this, inputs,
                        "Input new toy", JOptionPane.OK_CANCEL_OPTION) == JOptionPane.YES_OPTION) {
                    try {
                        toys.add(new Toy(nameField.getText(),
                                Integer.parseInt(costField.getText()),
                                Integer.parseInt(minField.getText()),
                                Integer.parseInt(maxField.getText()) ));
                        updateList();
                    }
                    catch (NumberFormatException e) {
                        JOptionPane.showMessageDialog(Lab15Frame.this, "Wrong values.");
                    }
                    catch (AgeException e) {
                        JOptionPane.showMessageDialog(Lab15Frame.this, e.getMessage());
                    }
                    catch (CostException e){
                        JOptionPane.showMessageDialog(Lab15Frame.this, e.getMessage());
                    }
                }
            }
        });

        butInput.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                JTextField maxField = new JTextField();
                JTextField minField = new JTextField();
                final JComponent[] inputs = new JComponent[] {
                        new JLabel("MinAge:"),  minField,
                        new JLabel("MaxAge:"), maxField
                };
                if (JOptionPane.showConfirmDialog(Lab15Frame.this, inputs,
                        "Input ages", JOptionPane.OK_CANCEL_OPTION) == JOptionPane.YES_OPTION) {
                    try {
                        int max = Integer.parseInt(maxField.getText());
                        int min = Integer.parseInt(minField.getText());
                        ArrayList<Toy> required = new ArrayList<Toy>();
                        for (Iterator<Toy> it = toys.iterator(); it.hasNext(); )
                        {
                            Toy temp = it.next();
                            if (temp.getMaxAge() >= max && temp.getMinAge() <= min)
                                required.add(temp);
                        }
                        listModel.clear();
                        if (required.size() == 0)
                            listModel.addElement("");
                        else
                        {
                            Collections.sort(required, new CostComparator());
                            for (Iterator<Toy> it = required.iterator(); it.hasNext(); ) {
                                listModel.addElement(it.next().toString());
                            }
                        }

                    }
                    catch (NumberFormatException e) {
                        JOptionPane.showMessageDialog(Lab15Frame.this, "Wrong values.");
                    }
                }
                else
                    updateList();
            }
        });
    }
    private void updateList() {
        listModel.clear();
        if (toys.isEmpty()) {
            listModel.addElement("");
            return;
        }
        Collections.sort(toys);
        for (Iterator<Toy> it = toys.iterator(); it.hasNext(); ) {
            listModel.addElement(it.next().toString());
        }
    }

    public static void main(String[] args) {
        Lab15Frame frame = new Lab15Frame("Students");
        frame.setVisible(true);
    }

    class CostComparator implements Comparator<Toy> {
        @Override
        public int compare(Toy toy1, Toy toy2) {
            return toy1.getCost().compareTo(toy2.getCost());
        }
    }
}
