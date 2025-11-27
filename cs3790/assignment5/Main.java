import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Main {
    public static void main(String args[]) {
        final String fileName = "./cs3790/assignment5/data.text";
        FileService fs = new FileService(fileName);
        List<String> arr = fs.getData();
        SimSystem ss = new SimSystem(arr);
        Scanner scanner = new Scanner(System.in);

        System.out.println("~ Bankers Algorithm Sim ~\n");
        ss.sysPrint();
        System.out.println();

        // TODO: validate inputs and handle exceptions
        int inputProcess = 99999;
        while (inputProcess >= 0) {
            System.out.print("Enter a process (int): ");
            inputProcess = scanner.nextInt();
            if (inputProcess < 0) {
                break;
            }

            List<Integer> inputResources = new ArrayList<Integer>();
            for (int i = 0; i < ss.getResourceCount(); i++) {
                System.out.print("Enter a value for " + (char)('A' + i) + ": ");
                inputResources.add(scanner.nextInt());
            }

            // bankers
            // alter if safe

            System.out.println();
            ss.sysPrint();
            System.out.println();
        }

        System.out.println("Thank you for using the Bankers Algorithm Sim, Goodbye");
    }
}
