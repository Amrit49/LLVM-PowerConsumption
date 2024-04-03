public class Main {
    public static void main(String[] args) {
        int num = 10;
        if (num > 5) {
            System.out.println("Number is greater than 5.");
        } else {
            System.out.println("Number is less than or equal to 5.");
        }

        int i = 0;
        while (i < 5) {
            System.out.println("While loop iteration: " + i);
            i++;
            int j = 0;
            while (j < 5) {
                System.out.println("While loop iteration: " + j);
                j++;
            }
        }

        for (int j = 0; j < 5; j++) {
            System.out.println("For loop iteration: " + j);
        }

        int a = 5;
        int b = 3;
        int result = (a * b) + (a / b);

        System.out.println("Result of arithmetic expression: " + result);
    }
}
