package applications;
import data.MyPoint;
import sun.awt.image.ImageAccessException;

import javax.imageio.IIOImage;
import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.geom.GeneralPath;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.NoSuchElementException;
import java.util.Scanner;

/**
 * Created by andrejka on 12.12.15.
 */
public class Lab13Frame extends JFrame {
    private JButton redButton;
    private JButton greenButton;
    private JButton blueButton;
    private JButton openButton;
    private JButton saveFileButton;
    private JButton saveImageButton;
    private DrawPanel drawPanel = new DrawPanel();
    private Color color = new Color(255, 255,0);
    public class DrawPanel extends JPanel
    {
        private ArrayList<MyPoint> array;
        private GeneralPath polyline;
        int count = 0;
        @Override
        public Dimension getPreferredSize() {
            return new Dimension(1000, 1000);
        }

        public DrawPanel()
        {
            array = new ArrayList<MyPoint>();
            addMouseListener(new MouseAdapter() {
                @Override
                public void mousePressed(MouseEvent e) {
                    super.mousePressed(e);
                    getGraphics().setColor(color);
                }
            });
            addMouseListener(new MouseAdapter() {
                @Override
                public void mouseClicked(MouseEvent e) {
                    super.mouseClicked(e);
                    Graphics g = getGraphics();
                    g.setColor(color);
                    array.add(new MyPoint(e.getX(), e.getY(), color));
                    array.add(new MyPoint(-1, -1, Color.WHITE));
                    g.drawLine(e.getX(), e.getY(), e.getX(), e.getY());
                }
            });
            addMouseMotionListener(new MouseMotionAdapter() {
                @Override
                public void mouseDragged(MouseEvent e) {
                    if (count == 0)
                        array.add(new MyPoint(e.getX(), e.getY(), color));
                    count++;
                    super.mouseDragged(e);
                    getGraphics().setColor(color);
                    if (array.size() == 0)
                        array.add(new MyPoint(e.getX(), e.getY(), color));
                    if (array.get(array.size()-1).getX() != -1)
                    {
                        Graphics g = getGraphics();
                        g.setColor(color);
                        g.drawLine(array.get(array.size()-1).getX(),
                                array.get(array.size()-1).getY(), e.getX(), e.getY());
                    }
                    array.add(new MyPoint(e.getX(), e.getY(), color));
               //     paintComponent(getGraphics());
                }
            });
            addMouseListener(new MouseAdapter() {
                @Override
                public void mouseReleased(MouseEvent e) {
                    super.mouseReleased(e);
                    array.add(new MyPoint(e.getX(), e.getY(), color));
                    array.add(new MyPoint(-1, -1, Color.WHITE));
                    count = 0;
                }
            });
        }

        public void paintComponent(Graphics g) {
            super.paintComponent(g);
            Graphics2D graph = (Graphics2D) g;
            int start = 0;
            for (MyPoint i : array)
            {
                if(i.getX()!= -1 && i != array.get(array.size()-1))
                {
                    polyline = new GeneralPath(GeneralPath.WIND_EVEN_ODD);
                    if (array.get(start+1).getX() == -1)
                    {
                        graph.setColor(array.get(start).getColor());
                        polyline.moveTo(i.getX(), i.getY());
                        polyline.lineTo(i.getX(), i.getY());
                        graph.draw(polyline);
                        start++;
                    }
                    else
                    {
                        polyline.moveTo(i.getX(), i.getY());
                        polyline.lineTo(array.get(start+1).getX(), array.get(start+1).getY());
                        graph.setColor(array.get(start).getColor());
                        graph.draw(polyline);
                        start++;
                    }
                }
                else
                {
                    start++;
                }
            }
        }
    }
    public Lab13Frame()
    {
        super("Lab13");
        setSize(700, 500);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new GridBagLayout());
        add(new JScrollPane(drawPanel,
                        JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED,
                        JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED),
                new GridBagConstraints(0,0,1,1,1.0,10.0,
                        GridBagConstraints.CENTER, GridBagConstraints.BOTH,new Insets(0,0,0,0),0,0));
        JPanel buttonPanel = new JPanel();
        redButton = new JButton("Red");
        blueButton = new JButton("Blue");
        greenButton = new JButton("Green");
        openButton = new JButton("Open");
        saveFileButton = new JButton("Save to file");
        saveImageButton = new JButton("Save to image");
        buttonPanel.add(redButton);
        buttonPanel.add(greenButton);
        buttonPanel.add(blueButton);
        buttonPanel.add(openButton);
        buttonPanel.add(saveFileButton);
        buttonPanel.add(saveImageButton);
        add(buttonPanel, new GridBagConstraints(0,1,1,1,1.0,1.0,
                GridBagConstraints.CENTER,GridBagConstraints.BOTH,new Insets(10,10,10,10),0,0));
        redButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                color = new Color(255, 0, 0);
            }
        });
        greenButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                color = new Color(10, 255, 0);
            }
        });
        blueButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                color = new Color(8, 10, 100);
            }
        });
        saveFileButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                    JFileChooser fileChooser = new JFileChooser();
                    if (fileChooser.showSaveDialog(Lab13Frame.this)==JFileChooser.APPROVE_OPTION)
                    {
                        File file = fileChooser.getSelectedFile();
                            try
                            {
                                FileWriter out = new FileWriter(file);
                                out.write(Integer.toString(drawPanel.array.size())+"\n");
                                for(MyPoint i : drawPanel.array)
                                {
                                    out.write(i.getX()+" "+i.getY()+" "+Integer.toString(i.getColor().getRGB())+"\n");
                                }
                                out.close();
                            }
                            catch (IOException e){
                                JOptionPane.showMessageDialog(Lab13Frame.this, "Saving mistake");
                            }
                        }
                    }
            });
        saveImageButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                JFileChooser fileChooser = new JFileChooser();
                if (fileChooser.showSaveDialog(Lab13Frame.this) == JFileChooser.APPROVE_OPTION) {
                    File file = fileChooser.getSelectedFile();
                    try
                    {
                        BufferedImage bi = new BufferedImage(drawPanel.getWidth(), drawPanel.getHeight(), BufferedImage.TYPE_INT_RGB);
                        drawPanel.paint(bi.getGraphics());
                        ImageIO.write(bi, "JPEG", file);
                    }
                    catch (FileNotFoundException e) {
                        JOptionPane.showMessageDialog(Lab13Frame.this, "File did not find");
                    }
                    catch (IOException e) {
                        JOptionPane.showMessageDialog(Lab13Frame.this, "Directory is wrong");
                    }
                }
            }
        });
        openButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                JFileChooser fileChooser = new JFileChooser();
                if (fileChooser.showOpenDialog(Lab13Frame.this) == JFileChooser.APPROVE_OPTION) {
                    File file = fileChooser.getSelectedFile();
                    try
                    {
                        Scanner in = new Scanner(file);
                        int n = in.nextInt();
                        drawPanel.array = new ArrayList<>();
                        for (int i = 0; i < n; i++) {
                            drawPanel.array.add(new MyPoint(in.nextInt(), in.nextInt(), new Color(in.nextInt())));
                        }
                        in.close();
                        repaint();
                    }
                    catch (FileNotFoundException e) {
                        JOptionPane.showMessageDialog(Lab13Frame.this, "File did not find");
                    }
                    catch (NoSuchElementException e) {
                        JOptionPane.showMessageDialog(Lab13Frame.this, "The chosen file has wrong format");
                    }
                }
            }
        });
    }

    public static void main(String[] args) {
        Lab13Frame frame = new Lab13Frame();
        frame.setVisible(true);
    }
}
