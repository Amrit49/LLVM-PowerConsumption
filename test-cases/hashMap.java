import java.util.ArrayList;
import java.util.HashMap;

public class Main {
    public static void main(String[] args) {
        // Creating a HashMap to store ArrayLists of integers
        HashMap<String, ArrayList<Integer>> map = new HashMap<>();

        // Creating and populating ArrayLists
        ArrayList<Integer> list1 = new ArrayList<>();
        list1.add(10);
        list1.add(20);
        list1.add(30);

        ArrayList<Integer> list2 = new ArrayList<>();
        list2.add(40);
        list2.add(50);

        // Inserting ArrayLists into the HashMap
        map.put("list1", list1);
        map.put("list2", list2);

        // Retrieving ArrayLists from the HashMap and printing their elements
        System.out.println("Elements of list1:");
        for (int num : map.get("list1")) {
            System.out.println(num);
        }

        System.out.println("Elements of list2:");
        for (int num : map.get("list2")) {
            System.out.println(num);
        }
    }
}
