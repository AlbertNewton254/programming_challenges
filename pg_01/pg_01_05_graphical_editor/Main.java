import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        Image image = null;

        while (sc.hasNextLine()) {
            String line = sc.nextLine().trim();
            if (line.isEmpty()) continue;

            char command = line.charAt(0);
            String[] tokens = line.split("\\s+");

            try {
                switch (command) {
                    case 'I': {
                        if (tokens.length < 3) break;
                        int m = Integer.parseInt(tokens[1]);
                        int n = Integer.parseInt(tokens[2]);
                        image = new Image(m, n);
                        break;
                    }
                    case 'C': {
                        if (image != null) image.clear();
                        break;
                    }
                    case 'L': {
                        if (tokens.length < 4) break;
                        int x = Integer.parseInt(tokens[1]);
                        int y = Integer.parseInt(tokens[2]);
                        char c = tokens[3].charAt(0);
                        image.colorPixel(x, y, c);
                        break;
                    }
                    case 'V': {
                        if (tokens.length < 5) break;
                        int x = Integer.parseInt(tokens[1]);
                        int y1 = Integer.parseInt(tokens[2]);
                        int y2 = Integer.parseInt(tokens[3]);
                        char c = tokens[4].charAt(0);
                        image.verticalLine(x, y1, y2, c);
                        break;
                    }
                    case 'H': {
                        if (tokens.length < 5) break;
                        int x1 = Integer.parseInt(tokens[1]);
                        int x2 = Integer.parseInt(tokens[2]);
                        int y = Integer.parseInt(tokens[3]);
                        char c = tokens[4].charAt(0);
                        image.horizontalLine(x1, x2, y, c);
                        break;
                    }
                    case 'K': {
                        if (tokens.length < 6) break;
                        int x1 = Integer.parseInt(tokens[1]);
                        int y1 = Integer.parseInt(tokens[2]);
                        int x2 = Integer.parseInt(tokens[3]);
                        int y2 = Integer.parseInt(tokens[4]);
                        char c = tokens[5].charAt(0);
                        image.fillRectangle(x1, y1, x2, y2, c);
                        break;
                    }
                    case 'F': {
                        if (tokens.length < 4) break;
                        int x = Integer.parseInt(tokens[1]);
                        int y = Integer.parseInt(tokens[2]);
                        char c = tokens[3].charAt(0);
                        image.floodFill(x, y, c);
                        break;
                    }
                    case 'S': {
                        if (tokens.length < 2) break;
                        String name = line.substring(2).trim();
                        if (image != null) image.saveFile(name);
                        break;
                    }
                    case 'X': {
                        return; // Exit the program
                    }
                    default:
                        // Ignore unknown commands
                        break;
                }
            } catch (Exception e) {
                // Optionally print error for debugging
                // System.err.println("Error processing line: " + line);
            }
        }
    }
}
