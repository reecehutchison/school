import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class FileService {
    private List<String> data = null;

    public FileService(String fileName) {
        File file = new File(fileName);
        try {
            Scanner scanner = new Scanner(file);
            ArrayList<String> values = new ArrayList<>();

            while (scanner.hasNext()) {
                values.add(scanner.next());
            }

            this.data = values;
        } catch (FileNotFoundException e) {
            System.out.println("Error: file not found creating FileService scanner: " + e);
        }
    }

    public List<String> getData() {
        return this.data;
    }
}
