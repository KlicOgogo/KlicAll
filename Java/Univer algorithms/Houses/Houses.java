import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;

public class Houses {
    static Double k = 100.0;
    public static double gaussian (Line line1, Line line2, MyPoint house, MyPoint point1, MyPoint point2) {
        if (line1.getA()*line2.getB()-line2.getA()*line1.getB() == 0) {
            if (line1.getB()*line2.getC()-line2.getB()*line1.getC() == 0) {
                if (house.getX() < Integer.max(point1.getX(), point2.getX()) && house.getX() > Integer.min(point1.getX(), point2.getX())-5) {
                    return house.getX()+1;
                } else {
                    return -6;
                }
            }
            else {
                return -6;
            }
        }
        else {
            return (line1.getC()*line2.getB()-line1.getB()*line2.getC())/(line1.getA()*line2.getB()-line2.getA()*line1.getB());
        }
    }

    public static boolean intersects (MyPoint point1, MyPoint point2, MyPoint house) {
        double p1 = gaussian(new Line(point2.getY()-point1.getY(), point1.getX()-point2.getX(),
                -point2.getX()*point1.getY()+point2.getY()*point1.getX()), new Line(-1, 1, -house.getX()+house.getY()), house, point1, point2);
        if (p1 > house.getX() && p1 < house.getX()+5 && p1 > Integer.min(point1.getX(), point2.getX()) && p1 < Integer.max(point1.getX(), point2.getX())) {
            return true;
        }
        double p2 = gaussian (new Line(point2.getY()-point1.getY(), point1.getX()-point2.getX(),
                -point2.getX()*point1.getY()+point2.getY()*point1.getX()), new Line(1, 1, house.getX()+house.getY()+5), house, point1, point2);
        if (p2 > house.getX() && p2 < house.getX()+5 && p2 > Integer.min(point1.getX(), point2.getX()) && p2 < Integer.max(point1.getX(), point2.getX())) {
            return true;
        }
        return false;
    }

    public static boolean intersectsAll (MyPoint point1, MyPoint point2, ArrayList<MyPoint> houses) {
        for (int i = 0; i < houses.size(); i++) {
            if (intersects (point1, point2, houses.get(i))) {
                return true;
            }
        }
        return false;
    }

    public static void dijkstra(Double[][] distances, int dim, int[] path) {
        ArrayList<Dijkstra> ok = new ArrayList<>();
        ok.add(new Dijkstra(0, 0.0));
        ArrayList<Dijkstra> nok = new ArrayList<>();
        for (int i = 1; i < dim; i++) {
            nok.add(new Dijkstra(i, 200000000.0));
        }
        for (int y = 0; y < dim-1; y++) {
            for (Dijkstra i:nok) {
                if (i.getMinDist() > ok.get(ok.size()-1).getMinDist()+distances[ok.get(ok.size()-1).getNum()][i.getNum()]) {
                    i.setMinDist(ok.get(ok.size()-1).getMinDist()+distances[ok.get(ok.size()-1).getNum()][i.getNum()]);
                    path[i.getNum()] = ok.get(ok.size()-1).getNum();
                }
            }
            Double min = 2100000000.0;
            int index = -1;
            int index2 = -1;
            for (Dijkstra i: nok) {
                if (i.getMinDist() < min) {
                    min = i.getMinDist();
                    index = i.getNum();
                    index2 = nok.indexOf(i);
                }
            }
            ok.add(new Dijkstra(index, min));
            nok.remove(index2);
        }
        for (Dijkstra i:ok) {
            if (i.getNum() == dim-1) {
                k =  i.getMinDist();
            }
        }
    }

    public static void main(String[] args) {
        try {
            Scanner scanner = new Scanner(new File("input.in"));
            final int N = scanner.nextInt();
            ArrayList<MyPoint> points = new ArrayList<>();
            ArrayList<MyPoint> houses = new ArrayList<>();
            points.add(new MyPoint (0, 0));
            for (int i = 0; i < N; i++) {
                int x = scanner.nextInt();
                int y = scanner.nextInt();
                points.add(new MyPoint(x, y));
                houses.add(new MyPoint(x, y));
                points.add(new MyPoint(x+5, y));
                points.add(new MyPoint(x, y+5));
                points.add(new MyPoint(x+5, y+5));
            }
            scanner.close();
            points.add(new MyPoint(100, 100));
            int[][] matrix = new int[4*N+2][4*N+2];
            Double[][] distances = new Double[4*N+2][4*N+2];
            for (int i = 0; i < 4*N+2; i++)
                for (int j = 0; j < 4*N+2; j++) {
                    if (i == j) {
                        matrix[i][j] = 0;
                        distances[i][j] = 2000000000.0;
                    }
                    else {
                        if (intersectsAll(points.get(i), points.get(j), houses)) {
                            matrix[i][j] = 0;
                            distances[i][j] = 2000000000.0;
                        }
                        else {
                            matrix[i][j] = 1;
                            distances[i][j] = Math.sqrt(Math.pow(points.get(i).getX()-points.get(j).getX(), 2)+
                            Math.pow(points.get(i).getY()-points.get(j).getY(), 2));
                        }
                    }
                }
            FileWriter writer = new FileWriter(new File("output.out"));
            int[] path = new int[4*N+2];
            for (int i = 0; i < 4*N+2; i++)
                path[i] = -1;
            dijkstra(distances, 4*N+2, path);
            Integer l = (int)(k*100);
            Double ans;
            if (l %10 <= 4) {
                l-= l%10;
                ans = Double.parseDouble(l.toString() )/100;
            }
            else {
                l+=10-l%10;
                ans = Double.parseDouble(l.toString() )/100;
            }
            writer.write (ans.toString()+'\n');
            int i = 4*N+1;
            ArrayList<MyPoint> result = new ArrayList<>();
            result.add(new MyPoint(100,100));
            while (path[i]!=-1) {
                result.add(points.get(path[i]));
                i = path[i];
            }
            for (int j = result.size()-1; j>-1; j--) {
                writer.write(result.get(j).toString()+" ");
            }
            writer.close();
            for (int c = 0; c < 4*N+2; c++) {
                for (int j = 0; j < 4 * N + 2; j++) {
                    System.out.print(matrix[c][j]+" ");
                }
                System.out.println();
            }
            /*for (int i = 0; i < 4*N+2; i++) {
                for (int j = 0; j < 4 * N + 2; j++) {
                    System.out.print(distances[i][j]+" ");
                }
                System.out.println();
            }*/
        }
        catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static class Dijkstra {
        private int num;
        private Double minDist;
        public Dijkstra(int n, Double d) {
            num = n;
            minDist = d;
        }
        public void setMinDist( Double d) {
            minDist = d;
        }
        public Double getMinDist() {
            return minDist;
        }
        public int getNum() {
            return num;
        }
        public void setNum(int n) {
            num = n;
        }
    }

    public static class Line {
        private double a;
        private double b;
        private double c;
        public Line(double a1, double b1, double c1) {
            a = a1;
            b = b1;
            c = c1;
        }
        public double getA() {
            return a;
        }
        public double getB() {
            return b;
        }
        public double getC() {
            return c;
        }
        public void onNumber(double num) {
            if (num != 0) {
                a = a / num;
                b = b / num;
                c = c / num;
            }
        }
        public void lineOnNumber(double num, Line line) {
            a = a + num*line.getA();
            b = b + num*line.getB();
            c = c + num*line.getC();
        }
    }

    public static class MyPoint {
        private int x;
        private int y;
        public MyPoint(int x1, int y1) {
            x = x1;
            y = y1;
        }
        public int getX() {
            return x;
        }

        public int getY() {
            return y;
        }
        public String toString() {
            return "("+x+";"+y+")";
        }
    }
}
