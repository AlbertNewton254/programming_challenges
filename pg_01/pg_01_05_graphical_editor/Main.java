import java.util.Scanner;

class Image {
    private final char[][] pixels;

    public Image(int width, int height) {
        pixels = new char[height][width];
        clear();
    }

    public void clear() {
        for (int y = 0; y < pixels.length; y++) {
            for (int x = 0; x < pixels[y].length; x++) {
                pixels[y][x] = 'O';
            }
        }
    }

    public void colorPixel(int x, int y, char c) {
        pixels[y - 1][x - 1] = c;
    }

    public void verticalLine(int x, int y1, int y2, char c) {
        int from = Math.min(y1, y2) - 1;
        int to = Math.max(y1, y2) - 1;
        for (int y = from; y <= to; y++) {
            pixels[y][x - 1] = c;
        }
    }

    public void horizontalLine(int x1, int x2, int y, char c) {
        int from = Math.min(x1, x2) - 1;
        int to = Math.max(x1, x2) - 1;
        for (int x = from; x <= to; x++) {
            pixels[y - 1][x] = c;
        }
    }

    public void fillRectangle(int x1, int y1, int x2, int y2, char c) {
        int yFrom = Math.min(y1, y2) - 1;
        int yTo = Math.max(y1, y2) - 1;
        int xFrom = Math.min(x1, x2) - 1;
        int xTo = Math.max(x1, x2) - 1;

        for (int y = yFrom; y <= yTo; y++) {
            for (int x = xFrom; x <= xTo; x++) {
                pixels[y][x] = c;
            }
        }
    }

    public void floodFill(int x, int y, char newColor) {
        int px = x - 1;
        int py = y - 1;
        char oldColor = pixels[py][px];
        if (oldColor == newColor) return;
        floodFillRecursive(px, py, oldColor, newColor);
    }

    private void floodFillRecursive(int x, int y, char oldColor, char newColor) {
        if (x < 0 || y < 0 || y >= pixels.length || x >= pixels[0].length) return;
        if (pixels[y][x] != oldColor) return;
        pixels[y][x] = newColor;
        floodFillRecursive(x + 1, y, oldColor, newColor);
        floodFillRecursive(x - 1, y, oldColor, newColor);
        floodFillRecursive(x, y + 1, oldColor, newColor);
        floodFillRecursive(x, y - 1, oldColor, newColor);
    }

    public void saveFile(String name) {
        System.out.println(name);
        for (char[] row : pixels) {
            System.out.println(new String(row));
        }
    }
}

class CommandParser {
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
        if (line == null || line.isEmpty()) return;

        String[] tokens = line.trim().split("\\s+");
        if (tokens.length == 0) return;

        char cmd = tokens[0].charAt(0);

        try {
            switch (cmd) {
                case CMD_INIT:
                    initImage(tokens);
                    break;
                case CMD_CLEAR:
                    clearImage();
                    break;
                case CMD_COLOR_PIXEL:
                    colorPixel(tokens);
                    break;
                case CMD_VERTICAL:
                    verticalLine(tokens);
                    break;
                case CMD_HORIZONTAL:
                    horizontalLine(tokens);
                    break;
                case CMD_RECTANGLE:
                    fillRectangle(tokens);
                    break;
                case CMD_FILL:
                    floodFill(tokens);
                    break;
                case CMD_SAVE:
                    saveImage(line);
                    break;
                case CMD_EXIT:
                    System.exit(0);
                    break;
                default:
                    // Ignore command
            }
        } catch (Exception e) {
            // Ignore invalid line
        }
    }

    private void initImage(String[] tokens) {
        if (tokens.length < 3) return;
        int m = Integer.parseInt(tokens[1]);
        int n = Integer.parseInt(tokens[2]);
        image = new Image(m, n);
    }

    private void clearImage() {
        if (image != null) image.clear();
    }

    private void colorPixel(String[] tokens) {
        if (tokens.length < 4 || image == null) return;
        int x = Integer.parseInt(tokens[1]);
        int y = Integer.parseInt(tokens[2]);
        char c = tokens[3].charAt(0);
        image.colorPixel(x, y, c);
    }

    private void verticalLine(String[] tokens) {
        if (tokens.length < 5 || image == null) return;
        int x = Integer.parseInt(tokens[1]);
        int y1 = Integer.parseInt(tokens[2]);
        int y2 = Integer.parseInt(tokens[3]);
        char c = tokens[4].charAt(0);
        image.verticalLine(x, y1, y2, c);
    }

    private void horizontalLine(String[] tokens) {
        if (tokens.length < 5 || image == null) return;
        int x1 = Integer.parseInt(tokens[1]);
        int x2 = Integer.parseInt(tokens[2]);
        int y = Integer.parseInt(tokens[3]);
        char c = tokens[4].charAt(0);
        image.horizontalLine(x1, x2, y, c);
    }

    private void fillRectangle(String[] tokens) {
        if (tokens.length < 6 || image == null) return;
        int x1 = Integer.parseInt(tokens[1]);
        int y1 = Integer.parseInt(tokens[2]);
        int x2 = Integer.parseInt(tokens[3]);
        int y2 = Integer.parseInt(tokens[4]);
        char c = tokens[5].charAt(0);
        image.fillRectangle(x1, y1, x2, y2, c);
    }

    private void floodFill(String[] tokens) {
        if (tokens.length < 4 || image == null) return;
        int x = Integer.parseInt(tokens[1]);
        int y = Integer.parseInt(tokens[2]);
        char c = tokens[3].charAt(0);
        image.floodFill(x, y, c);
    }

    private void saveImage(String line) {
        if (image == null) return;
        String name = line.length() > 2 ? line.substring(2).trim() : "";
        image.saveFile(name);
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

