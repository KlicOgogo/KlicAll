package applications;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class Lab14Frame extends JFrame {

    public Lab14Frame(String title) {
        super(title);
        setSize(700,650);
        setResizable(false);
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        JTabbedPane tabbedPane = new JTabbedPane();
        tabbedPane.addTab("Lists", new Card1());
        tabbedPane.addTab("Buttons", new Card2());
        tabbedPane.addTab("Sweety radio", new Card3());
        add(tabbedPane);
    }

    class Card1 extends JPanel {
        private DefaultListModel<String> leftListModel = new DefaultListModel<>();
        private JList<String> leftList = new JList<>(leftListModel);
        private DefaultListModel<String> rightListModel = new DefaultListModel<>();
        private JList<String> rightList = new JList<>(rightListModel);
        public Card1() {
            setLayout(new BorderLayout());
            JPanel central = new JPanel();
            central.setLayout(new BorderLayout());
            JButton right = new JButton("->");
            central.add(right, BorderLayout.NORTH);
            JButton left = new JButton("<-");
            central.add(left, BorderLayout.SOUTH);
            add(central, BorderLayout.CENTER);

            leftList.setFont(new Font(getFont().getFontName(), Font.PLAIN, 26));
            add(new JScrollPane(leftList,
                    JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED,
                    JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED), BorderLayout.WEST);
            rightList.setFont(new Font(getFont().getFontName(), Font.PLAIN, 26));
            add(new JScrollPane(rightList,
                    JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED,
                    JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED), BorderLayout.EAST);

            final String[] strings = new String[]{"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven"
            };
            for (String i : strings) {
                leftListModel.addElement(i);
            }
            right.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent actionEvent) {
                    if (!leftList.isSelectionEmpty()) {
                        rightListModel.addElement(leftList.getSelectedValue());
                        leftListModel.remove(leftList.getSelectedIndex());
                    }
                }
            });
            left.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent actionEvent) {
                    if (!rightList.isSelectionEmpty()) {
                        leftListModel.addElement(rightList.getSelectedValue());
                        rightListModel.remove(rightList.getSelectedIndex());
                    }
                }
            });
        }
    }

    class Card2 extends JPanel implements MouseListener {
        private static final int N = 4;
        private String tempText;
        private Color defBtnColor;
        public Card2() {
            setLayout(new GridLayout(N,N));
            for (int i = 0; i < N; i++)
                for (int j=0; j<N; j++) {
                    JButton temp = new JButton();
                    temp.setText(Integer.toString(i*N+j+1));
                    temp.addMouseListener(this);
                    add(temp);
                }
        }
        @Override
        public void mouseEntered(MouseEvent e) {
            defBtnColor = ((JButton) e.getSource()).getBackground();
            ((JButton) e.getSource()).setBackground(Color.BLUE);
        }
        @Override
        public void mouseExited(MouseEvent e) {
            ((JButton) e.getSource()).setBackground(defBtnColor);
        }
        @Override
        public void mousePressed(MouseEvent e) {
            if (e.getButton()==MouseEvent.BUTTON1) {
                tempText = ((JButton) e.getSource()).getText();
                ((JButton) e.getSource()).setText("Clicked!");
            }
        }
        @Override
        public void mouseReleased(MouseEvent e) {
            if (e.getButton()==MouseEvent.BUTTON1)
                ((JButton) e.getSource()).setText(tempText);
        }
        @Override
        public void mouseClicked(MouseEvent e) {
        }
    }

    class Card3 extends JPanel {
        public Card3() {
            setBackground(new Color(175,238,238));
            ButtonGroup radioGroup = new ButtonGroup();
            final String[] str = new String[] {
                    "1", "2", "3", "4"};
            final ImageIcon[] icons = new ImageIcon[] {
                    new ImageIcon("1.png"),
                    new ImageIcon("2.png"),
                    new ImageIcon("3.png"),
                    new ImageIcon("4.png"),
                    new ImageIcon("5.png")
            };
            Font font = new Font(getFont().getName(), Font.BOLD, 30);
            for (String i : str) {
                JRadioButton temp = new JRadioButton(i);
                temp.setFont(font);
                temp.setIcon(icons[0]);
                temp.setSelectedIcon(icons[1]);
                temp.setDisabledIcon(icons[2]);
                temp.setRolloverIcon(icons[3]);
                temp.setPressedIcon(icons[4]);
                radioGroup.add(temp);
                add(temp);
            }
        }
    }

    public static void main(String[] args) {
        Lab14Frame frame = new Lab14Frame("Frame");
        frame.setVisible(true);
    }
}
