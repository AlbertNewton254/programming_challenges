import java.util.Scanner;

/**
 * Represents a simple bitmap image using a 2D character grid.
 * <p>This class provides basic image manipulation operations such as:
 * <ul>
 *   <li>Clearing the image</li>
 *   <li>Coloring individual pixels</li>
 *   <li>Drawing vertical and horizontal lines</li>
 *   <li>Filling rectangles</li>
 *   <li>Flood fill (similar to a paint bucket tool)</li>
 *   <li>Saving the image to standard output</li>
 * </ul>
 *
 * <p>Coordinates are 1-based, with (1,1) at the top-left corner.
 *
 * @author Miguel
 */
class Image {
    private final char[][] pixels;

    public Image(int m, int n) {
        pixels = new char[n][m];
        clear();
    }

    public void clear() {
        for (int i = 0; i < pixels.length; i++) {
            for (int j = 0; j < pixels[i].length; j++) {
                pixels[i][j] = 'O';
            }
        }
    }

    public void colorPixel(int x, int y, char c) {
        pixels[y - 1][x - 1] = c;
    }

    public void verticalLine(int x, int y1, int y2, char c) {
        for (int i = Math.min(y1, y2) - 1; i <= Math.max(y1, y2) - 1; i++) {
            pixels[i][x - 1] = c;
        }
    }

    public void horizontalLine(int x1, int x2, int y, char c) {
        for (int i = Math.min(x1, x2) - 1; i <= Math.max(x1, x2) - 1; i++) {
            pixels[y - 1][i] = c;
        }
    }

    public void fillRectangle(int x1, int y1, int x2, int y2, char c) {
        for (int i = Math.min(y1, y2) - 1; i <= Math.max(y1, y2) - 1; i++) {
            for (int j = Math.min(x1, x2) - 1; j <= Math.max(x1, x2) - 1; j++) {
                pixels[i][j] = c;
            }
        }
    }

    public void floodFill(int x, int y, char newColor) {
        char oldColor = pixels[y - 1][x - 1];
        if (oldColor == newColor) return;
        fill(x - 1, y - 1, oldColor, newColor);
    }

    private void fill(int x, int y, char oldColor, char newColor) {
        if (x < 0 || x >= pixels[0].length || y < 0 || y >= pixels.length) return;
        if (pixels[y][x] != oldColor) return;
        pixels[y][x] = newColor;
        fill(x + 1, y, oldColor, newColor);
        fill(x - 1, y, oldColor, newColor);
        fill(x, y + 1, oldColor, newColor);
        fill(x, y - 1, oldColor, newColor);
    }

    public void saveFile(String name) {
        System.out.println(name);
        for (char[] row : pixels) {
            for (char c : row) {
                System.out.print(c);
            }
            System.out.println();
        }
    }
}

/**
 * Main class that interprets commands and manipulates the image accordingly.
 */
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
                        return;
                    }
                    default:
                        /* Ignore unknown commands */
                        break;
                }
            } catch (Exception e) {
                /* Optionally log error for debugging */
                // System.err.println("Error processing line: " + line);
            }
        }
    }
}
