import java.util.Scanner;
import java.util.Objects;

final class Image {
    private final char[][] pixels;
    private final int width;
    private final int height;

    public Image(int width, int height) {
        this.width = validateDimension(width, "Width");
        this.height = validateDimension(height, "Height");
        this.pixels = new char[height][width];
        clear();
    }

    private int validateDimension(int value, String name) {
        if (value <= 0) {
            throw new IllegalArgumentException(name + " must be positive");
        }
        return value;
    }

    public void clear() {
        for (char[] row : pixels) {
            Arrays.fill(row, 'O');
        }
    }

    public void colorPixel(int x, int y, char c) {
        validateCoordinates(x, y);
        pixels[y - 1][x - 1] = c;
    }

    public void verticalLine(int x, int y1, int y2, char c) {
        validateCoordinates(x, y1);
        validateCoordinates(x, y2);
        int from = Math.min(y1, y2) - 1;
        int to = Math.max(y1, y2) - 1;
        for (int y = from; y <= to; y++) {
            pixels[y][x - 1] = c;
        }
    }

    public void horizontalLine(int x1, int x2, int y, char c) {
        validateCoordinates(x1, y);
        validateCoordinates(x2, y);
        int from = Math.min(x1, x2) - 1;
        int to = Math.max(x1, x2) - 1;
        for (int x = from; x <= to; x++) {
            pixels[y - 1][x] = c;
        }
    }

    public void fillRectangle(int x1, int y1, int x2, int y2, char c) {
        validateCoordinates(x1, y1);
        validateCoordinates(x2, y2);
        int yFrom = Math.min(y1, y2) - 1;
        int yTo = Math.max(y1, y2) - 1;
        int xFrom = Math.min(x1, x2) - 1;
        int xTo = Math.max(x1, x2) - 1;

        for (int y = yFrom; y <= yTo; y++) {
            Arrays.fill(pixels[y], xFrom, xTo + 1, c);
        }
    }

    public void floodFill(int x, int y, char newColor) {
        validateCoordinates(x, y);
        int px = x - 1;
        int py = y - 1;
        char oldColor = pixels[py][px];
        if (oldColor == newColor) return;
        floodFillRecursive(px, py, oldColor, newColor);
    }

    private void floodFillRecursive(int x, int y, char oldColor, char newColor) {
        if (x < 0 || y < 0 || y >= height || x >= width) return;
        if (pixels[y][x] != oldColor) return;
        pixels[y][x] = newColor;
        floodFillRecursive(x + 1, y, oldColor, newColor);
        floodFillRecursive(x - 1, y, oldColor, newColor);
        floodFillRecursive(x, y + 1, oldColor, newColor);
        floodFillRecursive(x, y - 1, oldColor, newColor);
    }

    private void validateCoordinates(int x, int y) {
        if (x < 1 || x > width || y < 1 || y > height) {
            throw new IllegalArgumentException(
                String.format("Coordinates (%d, %d) out of bounds", x, y));
        }
    }

    public void saveFile(String name) {
        Objects.requireNonNull(name, "Filename cannot be null");
        System.out.println(name);
        for (char[] row : pixels) {
            System.out.println(row);
        }
    }
}

final class CommandParser {
    private static final char CMD_INIT = 'I';
    private static final char CMD_CLEAR = 'C';
    private static final char CMD_COLOR_PIXEL = 'L';
    private static final char CMD_VERTICAL = 'V';
    private static final char CMD_HORIZONTAL = 'H';
    private static final char CMD_RECTANGLE = 'K';
    private static final char CMD_FILL = 'F';
    private static final char CMD_SAVE = 'S';
    private static final char CMD_EXIT = 'X';

    private Image image;

    public void processCommand(String line) {
        if (line == null || line.isEmpty()) {
            return;
        }

        String[] tokens = line.trim().split("\\s+");
        if (tokens.length == 0) {
            return;
        }

        char cmd = tokens[0].charAt(0);

        try {
            switch (cmd) {
                case CMD_INIT -> initImage(tokens);
                case CMD_CLEAR -> clearImage();
                case CMD_COLOR_PIXEL -> colorPixel(tokens);
                case CMD_VERTICAL -> verticalLine(tokens);
                case CMD_HORIZONTAL -> horizontalLine(tokens);
                case CMD_RECTANGLE -> fillRectangle(tokens);
                case CMD_FILL -> floodFill(tokens);
                case CMD_SAVE -> saveImage(line);
                case CMD_EXIT -> System.exit(0);
                default -> {} // Ignore unknown commands
            }
        } catch (Exception e) {
            System.err.println("Error processing command: " + e.getMessage());
        }
    }

    private void initImage(String[] tokens) {
        if (tokens.length < 3) {
            throw new IllegalArgumentException("I command requires 2 parameters");
        }
        int m = Integer.parseInt(tokens[1]);
        int n = Integer.parseInt(tokens[2]);
        image = new Image(m, n);
    }

    private void clearImage() {
        if (image == null) {
            throw new IllegalStateException("Image not initialized");
        }
        image.clear();
    }

    private void colorPixel(String[] tokens) {
        validateImageAndTokens(tokens, 4);
        int x = Integer.parseInt(tokens[1]);
        int y = Integer.parseInt(tokens[2]);
        char c = validateColor(tokens[3]);
        image.colorPixel(x, y, c);
    }

    private void verticalLine(String[] tokens) {
        validateImageAndTokens(tokens, 5);
        int x = Integer.parseInt(tokens[1]);
        int y1 = Integer.parseInt(tokens[2]);
        int y2 = Integer.parseInt(tokens[3]);
        char c = validateColor(tokens[4]);
        image.verticalLine(x, y1, y2, c);
    }

    private void horizontalLine(String[] tokens) {
        validateImageAndTokens(tokens, 5);
        int x1 = Integer.parseInt(tokens[1]);
        int x2 = Integer.parseInt(tokens[2]);
        int y = Integer.parseInt(tokens[3]);
        char c = validateColor(tokens[4]);
        image.horizontalLine(x1, x2, y, c);
    }

    private void fillRectangle(String[] tokens) {
        validateImageAndTokens(tokens, 6);
        int x1 = Integer.parseInt(tokens[1]);
        int y1 = Integer.parseInt(tokens[2]);
        int x2 = Integer.parseInt(tokens[3]);
        int y2 = Integer.parseInt(tokens[4]);
        char c = validateColor(tokens[5]);
        image.fillRectangle(x1, y1, x2, y2, c);
    }

    private void floodFill(String[] tokens) {
        validateImageAndTokens(tokens, 4);
        int x = Integer.parseInt(tokens[1]);
        int y = Integer.parseInt(tokens[2]);
        char c = validateColor(tokens[3]);
        image.floodFill(x, y, c);
    }

    private void saveImage(String line) {
        if (image == null) {
            throw new IllegalStateException("Image not initialized");
        }
        String name = line.length() > 2 ? line.substring(2).trim() : "";
        image.saveFile(name);
    }

    private void validateImageAndTokens(String[] tokens, int requiredLength) {
        if (image == null) {
            throw new IllegalStateException("Image not initialized");
        }
        if (tokens.length < requiredLength) {
            throw new IllegalArgumentException(
                String.format("Command requires %d parameters", requiredLength - 1));
        }
    }

    private char validateColor(String token) {
        if (token.length() != 1) {
            throw new IllegalArgumentException("Color must be a single character");
        }
        return token.charAt(0);
    }
}

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        CommandParser parser = new CommandParser();

        while (scanner.hasNextLine()) {
            String line = scanner.nextLine();
            parser.processCommand(line);
        }
    }
}
