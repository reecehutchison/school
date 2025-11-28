import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
/*
  \/________________
 /     _____________)
/     /     /   \ |
\/\/\/     (O) (O)|          YABBA DABBA DOOOOOOOOOOOOOoo....
  |           ------,
  |  _       ______/
  | (_      /   \  \
  |        /  ___\_ \
  |        \      / /
__|_________\______/
\______________\./__\
 /     .       | \  |
 \    /_\   .  |  \ |\
 |`\       /_\ |   \| \
 */
public class FileService {
    private List<String> data = null;

    public FileService(String fileName) {
        File file = new File(fileName);
        try {
            Scanner scanner = new Scanner(file);
            ArrayList<String> values = new ArrayList<>();

            while (scanner.hasNext()) {
                char s[] = scanner.next().toCharArray();
                if (s[0] == '#') {
                    continue;
                }
                values.add(new String(s));
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
