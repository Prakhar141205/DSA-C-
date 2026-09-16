/* Write a program to read the data from the file and add some text in the end of the file

*/
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class Main {
    public static void main(String[] args) {
        try {
            // StandardOpenOption.APPEND works exactly like mode='a' in Python
            Files.writeString(Paths.get("output.txt"), "\nHii I am Prakhar Sharma", StandardOpenOption.CREATE, StandardOpenOption.APPEND);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
