import java.awt.*;
import java.awt.event.*;
import java.io.FileNotFoundException;
import java.io.IOException;
import javax.swing.*;

public class Display extends JFrame
{
    private JButton linBut;
    private JButton expBut;
    private JButton saveIn;
    private JButton countSum;
    private JTextField nFile;
    private JTextArea elems;
    private JTextArea elems1;
    private JTextField getOne;
    private JTextField getDiff;
    private JTextField getN;
    private JLabel lF;
    private JLabel lD;
    private JLabel lC;
    private JLabel iFile;
    private JLabel elements;
    private Series obj;
    public Display()
    {
        super("Series");
        setSize(500, 200);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        linBut = new JButton("Liner");
        expBut = new JButton("Exponential");
        saveIn = new JButton("Save");
        countSum = new JButton("Count sum");
        lF = new JLabel("first");
        lD = new JLabel("difference");
        lC = new JLabel("count");
        nFile = new JTextField(10);
        elems = new JTextArea();
        elems1 = new JTextArea();
        getOne = new JTextField(5);
        getDiff = new JTextField(5);
        getN = new JTextField(5);
        JPanel butPanel = new JPanel(new FlowLayout());
        butPanel.add(linBut);
        butPanel.add(expBut);
        butPanel.add(saveIn);
        butPanel.add(countSum);
        add(butPanel,BorderLayout.SOUTH);
        JPanel textPanel = new JPanel(new FlowLayout());
        textPanel.add(lF);
        textPanel.add(getOne);
        textPanel.add(lD);
        textPanel.add(getDiff);
        textPanel.add(lC);
        textPanel.add(getN);
        add(textPanel,BorderLayout.NORTH);
        iFile = new JLabel("Name of file to enter");
        Box boxw=Box.createVerticalBox();
        boxw.add(iFile);
        boxw.add(nFile);
        add(boxw,BorderLayout.WEST);
        elements = new JLabel("Output");
        Box boxe = Box.createVerticalBox();
        boxe.add(elements);
        boxe.add(elems);
        boxe.add(elems1);
        add(boxe,BorderLayout.EAST);
        setVisible(true);
        initListeners();
    }
    private void initListeners() throws NumberFormatException
    {
        linBut.addActionListener(new ActionListener() {

            public void actionPerformed(ActionEvent e) {
                String n = getN.getText();
                String o = getOne.getText();
                String d = getDiff.getText();
                try
                {
                    obj = new Liner(Double.parseDouble(o),Double.parseDouble(d),Integer.parseInt(n));
                    elems.setText(obj.toString());
                }
                catch (NumberFormatException pe)
                {
                    JOptionPane.showMessageDialog(null,"Conversion mistake " +pe.getMessage());
                }
            }
        } );
        expBut.addActionListener(new ActionListener() {

            @Override
            public void actionPerformed(ActionEvent e) {
                // TODO Auto-generated method stub
                String n = getN.getText();
                String o = getOne.getText();
                String d = getDiff.getText();
                try
                {
                    obj = new Exponential(Double.parseDouble(o),Double.parseDouble(d),Integer.parseInt(n));
                    elems1.setText(obj.toString());
                }
                catch (NumberFormatException pe)
                {
                    JOptionPane.showMessageDialog(null,"Conversion mistake "+ pe.getMessage());
                }
            }
        });
        saveIn.addActionListener(new ActionListener() {

            @Override
            public void actionPerformed(ActionEvent e) {
                // TODO Auto-generated method stub
                String f = nFile.getText();
                String n = getN.getText();
                try
                {
                    obj.toFile(f);
                }

                catch (FileNotFoundException exc)
                {
                    JOptionPane.showMessageDialog(null, "File mistake!"+ exc.getClass().getName());
                }

                catch (IOException exc) {
                    JOptionPane.showMessageDialog(null, "IO mistake!"+ exc.getClass().getName());
                }
                catch (NumberFormatException pe)
                {
                    JOptionPane.showMessageDialog(null,"Conversion mistake "+ pe.getMessage());
                }
                catch (RuntimeException ie)
                {
                    JOptionPane.showMessageDialog(null,"Wrong file name "+ ie.getMessage() + ie.getClass().getName());
                }
            }
        });

        countSum.addActionListener(new ActionListener() {

            public void actionPerformed(ActionEvent e) {
                String n = getN.getText();
                String o = getOne.getText();
                String d = getDiff.getText();
                try
                {
                    obj = new Liner(Double.parseDouble(o),Double.parseDouble(d),Integer.parseInt(n));
                    elems.setText(((Double)obj.countSum()).toString());
                    obj = new Exponential(Double.parseDouble(o),Double.parseDouble(d),Integer.parseInt(n));
                    elems1.setText(((Double)obj.countSum()).toString());
                }
                catch (NumberFormatException pe)
                {
                    JOptionPane.showMessageDialog(null,"Conversion mistake " +pe.getMessage());
                }
            }
        } );
    }

    public static void main(String[] args)
    {
        Display disp = new Display();
    }
}