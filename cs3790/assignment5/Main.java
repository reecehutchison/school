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

        // TODO: validate inputs and handle exceptions
        int inputProcess = 99999;
        while (inputProcess >= 0) {
            System.out.print("Enter a process (int): ");
            inputProcess = scanner.nextInt();
        }

        System.out.println("Thank you for using the Bankers Algorithm Sim, Goodbye");
    }
}
