import java.util.List;

public class Main {
    public static void main(String args[]) {
        final String fileName = "./cs3790/assignment5/data.text";

        FileService fs = new FileService(fileName);
        List<String> arr = fs.getData();

        for (String e : arr) {
            System.out.println(e);
        }
    }
}
