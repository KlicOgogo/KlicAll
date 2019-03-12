package data;

import java.awt.*;

/**
 * Created by andrejka on 12.12.15.
 */
public class MyPoint {
    Color color;
    int x;
    int y;
    public MyPoint (int x1, int y1, Color c)
    {
        x = x1;
        y = y1;
        color = new Color(c.getRGB());
    }
    public String toString()
    {
        return x+" "+y+" "+color.toString();
    }
    public int getX()
    {
        return x;
    }

    public void setX(int x) {
        this.x = x;
    }

    public void setY(int y) {
        this.y = y;
    }

    public int getY() {
        return y;
    }

    public void setColor(Color color) {
        this.color = color;
    }

    public Color getColor() {
        return color;
    }
}

