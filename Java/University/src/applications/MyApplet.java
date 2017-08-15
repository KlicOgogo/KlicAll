package applications;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

/**
 * Created by andrejka on 12.12.15.
 */
public class MyApplet extends JApplet {
    JButton button;
    int xCur;
    int yCur;
    public MyApplet()
    {
        super ();
        setSize(400, 400);
        setLayout(null);
        button = new JButton("My button");
        button.setLocation(100, 100);
        button.setSize(150, 50);
        add(button);
        addMouseMotionListener(new MouseMotionAdapter() {
            @Override
            public void mouseMoved(MouseEvent e) {
                super.mouseMoved(e);
                showStatus("x: "+e.getX() + " , y:" + e.getY());

            }

            @Override
            public void mouseDragged(MouseEvent e) {
                super.mouseDragged(e);
                showStatus("x: "+(e.getX()+button.getX()) + " , y:" + (e.getY()+button.getY()));
            }
        });
        addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                super.mouseClicked(e);
                button.setLocation(e.getX(), e.getY());
            }
        });
        button.addKeyListener(new KeyAdapter() {
            @Override
            public void keyTyped(KeyEvent e) {
                super.keyTyped(e);
                if (e.getKeyChar() == KeyEvent.VK_BACK_SPACE) {
                    if (button.getText().length() > 0)
                        button.setText(button.getText().substring(0, button.getText().length() - 1));
                }
                else
                    button.setText(button.getText()+((Character)e.getKeyChar()).toString());

            }
        });
        button.addMouseMotionListener(new MouseMotionAdapter() {
            @Override
            public void mouseMoved(MouseEvent e) {
                super.mouseMoved(e);
                showStatus("x:"+(e.getX()+button.getX())+", y:"+(e.getY()+button.getY()));
                xCur = e.getX();
                yCur = e.getY();
            }
            public void mouseDragged(MouseEvent e) {
                super.mouseDragged(e);
                if (e.isControlDown())
                {
                    button.setLocation(e.getX()-xCur+button.getX(), e.getY()-yCur+button.getY());
                    //showStatus("x: "+(e.getX()+button.getX()) + " , y:" + (e.getY()+button.getY()));
                }
                showStatus("x: "+(e.getX()+button.getX()) + " , y:" + (e.getY()+button.getY()));
            }
        });
    }

}
