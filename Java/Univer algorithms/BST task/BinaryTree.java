import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.NoSuchElementException;
import java.util.Scanner;

public class BinaryTree {

    private static Info rootOfWay = new Info(2147483647);
    private static Info leftOne = new Info(2147483647);
    private static Info leftTwo = new Info(2147483647);
    private static Info rightOne = new Info(2147483647);
    private static Info rightTwo = new Info(2147483647);
    private static ArrayList<Info> allWay = new ArrayList<>();
    private static ArrayList<Integer> output = new ArrayList<>();
    private static int size = 0;
    private Node root;
    private int result = -1;
    private static Boolean isRoot = false;
    private  static Boolean dnoo = false;

    public BinaryTree() {
        root = null;
    }

    public void addValue(Info value) {
        if (root == null)
            root = new Node(value);
        else
            addValue(root, value);
    }

    private void addValue(Node r, Info value) {
        int comp;
        comp = value.compareTo(r.value);
        if (comp == 0) {
        } else {
            if (comp > 0) {
                if (r.right == null) {
                    r.right = new Node(value);
                    r.right.father = r;
                }
                else
                    addValue(r.right, value);
            } else if (comp < 0) {
                if (r.left == null) {
                    r.left = new Node(value);
                    r.left.father = r;
                }
                else
                    addValue(r.left, value);
            }
        }
    }

    private static void leftRightRootData(Node r) {
        if (r != null) {
            leftRightRootData(r.left);
            leftRightRootData(r.right);
            if (r.left == null) {
                r.value.setLeft(0);
            } else {
                r.value.setLeft(Integer.max(r.left.value.getRight(), r.left.value.getLeft()) + 1);
            }
            if (r.right == null) {
                r.value.setRight(0);
            } else {
                r.value.setRight(Integer.max(r.right.value.getRight(), r.right.value.getLeft()) + 1);
            }
        }
    }

    private int height() {
        return Integer.max(root.value.getRight(), root.value.getLeft());
    }

    private void maxLength(Node r) {
        if (r.value.getLeft() + r.value.getRight() > result) {
            result = r.value.getLeft() + r.value.getRight();
        }
        if (r.left != null)
            maxLength(r.left);
        if (r.right != null)
            maxLength(r.right);
    }

    public void maxLengthMark() {
        maxLength(root);
        if (result == height()) {
            root.value.setMark(1);
            isRoot = true;
        } else if (result == height() + 1) {
            if (root.value.getLeft() == 0) {
              //  root.value.setMark(1);
                dnoo = true;
                maxLengthMark(root, result);
            }
            else {
                root.value.setMark(1);
                maxLengthMark(root, result);
            }
        } else {
            maxLengthMark(root, result);
        }
    }

    private void maxLengthMark(Node r, int max) {
        if (r != null) {
            if (r.value.getRight() + r.value.getLeft() == max) {
                r.value.setMark(1);
            }
            maxLengthMark(r.left, max);
            maxLengthMark(r.right, max);
        }
    }

    private static void minInfoMarked(Node r) {
        if (r != null) {
            minInfoMarked(r.left);
            if (r.value.getMark() == 1) {
                if (r.value.key < rootOfWay.getKey()) {
                    rootOfWay = r.value;
                }
            }
            minInfoMarked(r.right);
        }
    }

    private static void undoAllMarks(Node r) {
        if (r != null) {
            undoAllMarks(r.left);
            undoAllMarks(r.right);
            r.value.setMark(-1);
        }
    }

    private static void markPartOfTree(Node r, Info info) {
        if (r != null) {
            if (r.value.key == info.getKey()) {
                r.value.mark = 0;
                if (r.left != null)
                    r.left.value.mark = 1;
                if (r.right != null)
                    r.right.value.mark = 1;
            }
            if (r.value.mark != -1) {
                if (r.left != null)
                    r.left.value.mark = r.value.mark + 1;
                if (r.right != null)
                    r.right.value.mark = r.value.mark + 1;
            }
            markPartOfTree(r.left, info);
            markPartOfTree(r.right, info);
        }
    }

    private static void findMinOneLeft(Node r, Info info) {
        if (r != null) {
            findMinOneLeft(r.left, info);
            if (r.value.getMark() == info.left - 1) {
                if (r.left != null || r.right != null) {
                    if (r.value.getKey() < leftOne.getKey()) {
                        leftOne = r.value;
                    }
                }
            }
            findMinOneLeft(r.right, info);
        }
    }

    private static void findMinTwoLeft(Node r, Info info) {
        if (r != null) {
            findMinTwoLeft(r.left, info);
            if (r.value.getMark() == info.left) {
                if (r.value.getKey() < leftTwo.getKey()) {
                    leftTwo = r.value;
                }
            }
            findMinTwoLeft(r.right, info);
        }
    }

    private static void undoLeftMarks(Node r, Info info) {
        if (r != null) {
            if (r.value.key < info.getKey() && r.value.mark != -1)
                r.value.mark = -1;
            undoLeftMarks(r.left, info);
            undoLeftMarks(r.right, info);
        }
    }

    private static void findMinOneRight(Node r, Info info) {
        if (r != null) {
            findMinOneRight(r.left, info);
            if (r.value.getMark() == info.right - 1) {
                if (r.left != null || r.right != null) {
                    if (r.value.key < rightOne.key) {
                        rightOne = r.value;
                    }
                }
            }
            findMinOneRight(r.right, info);
        }
    }

    private static void findMinTwoRight(Node r, Info info) {
        if (r != null) {
            findMinTwoRight(r.left, info);
            if (r.value.getMark() == info.right) {
                if (r.value.getKey() < rightTwo.key) {
                    rightTwo = r.value;
                }
            }
            findMinTwoRight(r.right, info);
        }
    }

    private static void properMark(Node r, Info info) {
        if (r != null) {
            if (info.getKey() < r.value.getKey()) {
                if (r.left != null) {
                    r.left.value.mark = 1;
                    properMark(r.left, info);
                }
            }
            if (info.getKey() > r.value.getKey()) {
                if (r.right != null) {
                    r.right.value.mark = 1;
                    properMark(r.right, info);
                }
            } else
                return;
        }
    }

    private static void findWay(Node r, Info infoFather, Info infoSon) {
        if (r != null) {
            if (r.value == infoFather) {
                r.value.mark = 1;
                properMark(r, infoSon);
                return;
            }
            findWay(r.left, infoFather, infoSon);
            findWay(r.right, infoFather, infoSon);
        }
    }

    private static void leftRootRightMarks(Node r) {
        if (r != null) {
            leftRootRightMarks(r.left);
            if (r.value.mark == 1) {
                allWay.add(r.value);
            }
            leftRootRightMarks(r.right);
        }
    }

    private static void deleteItem(Node startNode, int key)
    {
        if(startNode == null)
            throw new NoSuchElementException();
        if(startNode.value.key > key)
            deleteItem(startNode.left, key);
        else if(startNode.value.key < key)
            deleteItem(startNode.right, key);
        else {
            if(startNode.left != null && startNode.right != null) {
                Node successor = findMin(startNode.right);
                startNode.value.key = successor.value.key;
                deleteItem(successor, successor.value.key);
            }
            else if(startNode.left != null) {
                replaceNodeInParent(startNode, startNode.left);
                size--;
            }
            else if(startNode.right != null) {
                replaceNodeInParent(startNode, startNode.right);
                size--;
            }
            else
            {
                replaceNodeInParent(startNode, null);
                size--;
            }
        }
    }
    private static Node findMin(Node startNode)
    {
        Node currentNode = startNode;
        while (currentNode.left != null)
            currentNode = currentNode.left;
        return currentNode;
    }

    private static void replaceNodeInParent(Node node, Node source)
    {
        if(node != null)
            if(node.father != null && node == node.father.left)
                node.father.left = source;
            else
                node.father.right = source;
        if(source != null)
            source.father = node.father;
    }

    private static void output(Node r) {
        if (r != null) {
            output.add(r.value.getKey());
            output(r.left);
            output(r.right);
        }
    }

    private static void countAll(Node r) {
        if (r != null) {
            countAll(r.left);
            countAll(r.right);
            size++;
        }
    }

    private static void rootRightLeft(Node r) {
        if (r != null) {
            System.out.println(r.value.getKey());
            rootRightLeft(r.right);
            rootRightLeft(r.left);
        }
    }

    public static void main(String[] args) {
        try {
            Scanner scanner = new Scanner(new File("tst.in"));
            BinaryTree tree = new BinaryTree();
            while (scanner.hasNextInt()) {
                Info fileInfo = new Info(scanner.nextInt());
                tree.addValue(fileInfo);
            }
            rootRightLeft(tree.root);
            countAll(tree.root);
            if (size == 0) {
                FileWriter writer = new FileWriter(new File("tst.out"));
                writer.write("");
                return;
            }
            if (size == 1)
            {
                FileWriter writer = new FileWriter(new File("tst.out"));
                writer.write(tree.root.value.key.toString()+'\n');
                writer.close();
                return;
            }
            leftRightRootData(tree.root);
            tree.maxLengthMark();
            minInfoMarked(tree.root);
            if (isRoot) {
                undoAllMarks(tree.root);
                markPartOfTree(tree.root, rootOfWay);
                if (tree.root.value.left > tree.root.value.right) {
                    findMinTwoLeft(tree.root, rootOfWay);
                    findWay(tree.root, tree.root.value, leftTwo);
                }
                else {
                    findMinTwoRight(tree.root, rootOfWay);
                    findWay(tree.root, tree.root.value, rightTwo);
                }
                leftRootRightMarks(tree.root);
                if (allWay.size() % 2 != 0) {
                    deleteItem(tree.root, allWay.get(allWay.size() / 2).key);
                }
                output(tree.root);
                FileWriter writer = new FileWriter(new File("tst.out"));
                for (Integer i : output) {
                    writer.write(i.toString()+'\n');
                }
                writer.close();
                rootOfWay = new Info(2147483647);
                leftOne = new Info(2147483647);
                leftTwo = new Info(2147483647);
                rightOne = new Info(2147483647);
                rightTwo = new Info(2147483647);
                allWay.clear();
                output.clear();
                size = 0;
                isRoot = false;
                return;
            }

            undoAllMarks(tree.root);
            markPartOfTree(tree.root, rootOfWay);
            findMinOneLeft(tree.root, rootOfWay);
            findMinTwoLeft(tree.root, rootOfWay);
            undoLeftMarks(tree.root, rootOfWay);
            findMinOneRight(tree.root, rootOfWay);
            findMinTwoRight(tree.root, rootOfWay);
            undoAllMarks(tree.root);
            if (dnoo) {
                Info leftTwo1 = leftTwo;
                Info rightOne1 = rightOne;
                int r1l2 = leftTwo1.key+rightOne1.key;
                Info leftOne1 = leftOne;
                Info rightTwo1 = rightTwo;
                int r2l1= leftOne1.key+rightTwo1.key;
                markPartOfTree(tree.root, tree.root.value);
                findMinTwoRight(tree.root, tree.root.value);
                int rr2 = tree.root.value.key+rightTwo.key;
                undoAllMarks(tree.root);
                if (Integer.min(rr2, Integer.min(r1l2, r2l1)) == rr2) {
                    findWay(tree.root, tree.root.value, rightTwo);
                    leftRootRightMarks(tree.root);
                    if (allWay.size() % 2 != 0) {
                        deleteItem(tree.root, allWay.get(allWay.size() / 2).key);
                    }

                } else if (Integer.min(rr2, Integer.min(r1l2, r2l1)) == r2l1 && r2l1 < Integer.min(r1l2, rr2)) {
                    findWay(tree.root, rootOfWay, leftOne1);
                    findWay(tree.root, rootOfWay, rightTwo1);
                    leftRootRightMarks(tree.root);
                    if (allWay.size() % 2 != 0) {
                        deleteItem(tree.root, allWay.get(allWay.size() / 2).key);
                    }

                } else if (Integer.min(rr2, Integer.min(r1l2, r2l1)) == r1l2 && r1l2 < Integer.min(r2l1, rr2)) {
                    findWay(tree.root, rootOfWay, leftTwo1);
                    findWay(tree.root, rootOfWay, rightOne1);
                    leftRootRightMarks(tree.root);
                    if (allWay.size() % 2 != 0) {
                        deleteItem(tree.root, allWay.get(allWay.size() / 2).key);
                    }
                }
                else if (Integer.max(rr2, Integer.max(r1l2, r2l1)) == rr2 && rr2 > Integer.max(r2l1, r1l2)) {
                    findWay(tree.root, rootOfWay, leftOne1);
                    findWay(tree.root, rootOfWay, rightTwo1);
                    leftRootRightMarks(tree.root);
                    if (allWay.size() % 2 != 0) {
                        int key1 = allWay.get(allWay.size() / 2).key;
                        allWay.clear();
                        undoAllMarks(tree.root);
                        findWay(tree.root, rootOfWay, leftTwo1);
                        findWay(tree.root, rootOfWay, rightOne1);
                        leftRootRightMarks(tree.root);
                        if (key1 == allWay.get(allWay.size() / 2).key) {
                            deleteItem(tree.root, key1);
                        }
                    }
                }
                else if (Integer.max(rr2, Integer.max(r1l2, r2l1)) == r1l2 && r1l2 > Integer.max(r2l1, rr2)) {
                    findWay(tree.root, rootOfWay, leftOne1);
                    findWay(tree.root, rootOfWay, rightTwo1);
                    leftRootRightMarks(tree.root);
                    if (allWay.size() % 2 != 0) {
                        int key1 = allWay.get(allWay.size() / 2).key;
                        allWay.clear();
                        undoAllMarks(tree.root);
                        findWay(tree.root, rootOfWay, tree.root.value);
                        findWay(tree.root, rootOfWay, rightTwo);
                        leftRootRightMarks(tree.root);
                        if (key1 == allWay.get(allWay.size() / 2).key) {
                            deleteItem(tree.root, key1);
                        }
                    }
                }
                else if (Integer.max(rr2, Integer.max(r1l2, r2l1)) == r2l1 && r2l1 > Integer.max(r1l2, rr2)) {
                    findWay(tree.root, rootOfWay, leftTwo1);
                    findWay(tree.root, rootOfWay, rightOne1);
                    leftRootRightMarks(tree.root);
                    if (allWay.size() % 2 != 0) {
                        int key1 = allWay.get(allWay.size() / 2).key;
                        allWay.clear();
                        undoAllMarks(tree.root);
                        findWay(tree.root, rootOfWay, tree.root.value);
                        findWay(tree.root, rootOfWay, rightTwo);
                        leftRootRightMarks(tree.root);
                        if (key1 == allWay.get(allWay.size() / 2).key) {
                            deleteItem(tree.root, key1);
                        }
                    }
                }
                output(tree.root);
                FileWriter writer = new FileWriter(new File("tst.out"));
                for (Integer i : output) {
                    writer.write(i.toString()+'\n');
                }
                writer.close();
                rootOfWay = new Info(2147483647);
                leftOne = new Info(2147483647);
                leftTwo = new Info(2147483647);
                rightOne = new Info(2147483647);
                rightTwo = new Info(2147483647);
                allWay.clear();
                output.clear();
                size = 0;
                dnoo = false;
                return;
            }
            if (leftOne.key + rightTwo.getKey() > leftTwo.key + rightOne.getKey()) {
                    findWay(tree.root, rootOfWay, leftTwo);
                    findWay(tree.root, rootOfWay, rightOne);
                    leftRootRightMarks(tree.root);
                    if (allWay.size() % 2 != 0) {
                        deleteItem(tree.root, allWay.get(allWay.size() / 2).key);
                    }
            }
            else if (leftOne.key + rightTwo.getKey() < leftTwo.key + rightOne.getKey()) {
                    findWay(tree.root, rootOfWay, leftOne);
                    findWay(tree.root, rootOfWay, rightTwo);
                    leftRootRightMarks(tree.root);
                    if (allWay.size() % 2 != 0) {
                        deleteItem(tree.root, allWay.get(allWay.size() / 2).key);
                    }
            }
            else {
                    findWay(tree.root, rootOfWay, leftOne);
                    findWay(tree.root, rootOfWay, rightTwo);
                    leftRootRightMarks(tree.root);
                    if (allWay.size() % 2 != 0) {
                        int key1 = allWay.get(allWay.size() / 2).key;
                        allWay.clear();
                        undoAllMarks(tree.root);
                        findWay(tree.root, rootOfWay, leftTwo);
                        findWay(tree.root, rootOfWay, rightOne);
                        leftRootRightMarks(tree.root);
                        if (allWay.size() % 2 != 0 && key1 == allWay.get(allWay.size() / 2).key) {
                            deleteItem(tree.root, key1);
                        }
                    }
            }
            output(tree.root);
            FileWriter writer = new FileWriter(new File("tst.out"));
            for (Integer i : output) {
                writer.write(i.toString()+'\n');
            }
            writer.close();
            rootOfWay = new Info(2147483647);
            leftOne = new Info(2147483647);
            leftTwo = new Info(2147483647);
            rightOne = new Info(2147483647);
            rightTwo = new Info(2147483647);
            allWay.clear();
            output.clear();
            size = 0;
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public class Node {
        Info value;
        Node left, right, father;

        public Node(Info obj) {
            value = obj;
            father = left = right = null;
        }
    }

    public static class Info implements Comparable {
        private Integer key;
        private Integer left;
        private Integer right;
        private Integer mark;

        public Info(int key2) {
            key = key2;
            left = -1;
            right = -1;
            mark = -1;
        }

        public void setLeft(int left2) {
            left = left2;
        }

        public void setRight(int right2) {
            right = right2;
        }

        public void setMark(int mark2) {
            mark = mark2;
        }

        public int getKey() {
            return key;
        }

        public int getLeft() {
            return left;
        }

        public int getRight() {
            return right;
        }

        public int getMark() {
            return mark;
        }

        public int compareTo(Object obj) {
            return key.compareTo(((Info) obj).getKey());
        }

        public String toString() {
            return key.toString();
        }
    }
}
