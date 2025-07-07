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
public class Image {
    private final char[][] pixels;

    /**
     * Constructs a new image with the given width and height.
     *
     * @param m the number of columns (width)
     * @param n the number of rows (height)
     */
    public Image(int m, int n) {
        pixels = new char[n][m]; // rows = n, cols = m
        clear();
    }

    /**
     * Clears the image by setting all pixels to 'O'.
     */
    public void clear() {
        for (int i = 0; i < pixels.length; i++) {
            for (int j = 0; j < pixels[i].length; j++) {
                pixels[i][j] = 'O';
            }
        }
    }

    /**
     * Colors a single pixel at the specified coordinates.
     *
     * @param x the column (1-based)
     * @param y the row (1-based)
     * @param c the color character
     */
    public void colorPixel(int x, int y, char c) {
        pixels[y - 1][x - 1] = c;
    }

    /**
     * Draws a vertical line in the specified column between two rows.
     *
     * @param x  the column (1-based)
     * @param y1 the starting row (1-based)
     * @param y2 the ending row (1-based)
     * @param c  the color character
     */
    public void verticalLine(int x, int y1, int y2, char c) {
        for (int i = Math.min(y1, y2) - 1; i <= Math.max(y1, y2) - 1; i++) {
            pixels[i][x - 1] = c;
        }
    }

    /**
     * Draws a horizontal line in the specified row between two columns.
     *
     * @param x1 the starting column (1-based)
     * @param x2 the ending column (1-based)
     * @param y  the row (1-based)
     * @param c  the color character
     */
    public void horizontalLine(int x1, int x2, int y, char c) {
        for (int i = Math.min(x1, x2) - 1; i <= Math.max(x1, x2) - 1; i++) {
            pixels[y - 1][i] = c;
        }
    }

    /**
     * Fills a rectangular region with the specified color.
     *
     * @param x1 the starting column (1-based)
     * @param y1 the starting row (1-based)
     * @param x2 the ending column (1-based)
     * @param y2 the ending row (1-based)
     * @param c  the color character
     */
    public void fillRectangle(int x1, int y1, int x2, int y2, char c) {
        for (int i = Math.min(y1, y2) - 1; i <= Math.max(y1, y2) - 1; i++) {
            for (int j = Math.min(x1, x2) - 1; j <= Math.max(x1, x2) - 1; j++) {
                pixels[i][j] = c;
            }
        }
    }

    /**
     * Performs a flood fill starting from the given pixel.
     * Replaces all connected pixels of the same color with the new color.
     *
     * @param x        the starting column (1-based)
     * @param y        the starting row (1-based)
     * @param newColor the new color character
     */
    public void floodFill(int x, int y, char newColor) {
        char oldColor = pixels[y - 1][x - 1];
        if (oldColor == newColor) return;
        fill(x - 1, y - 1, oldColor, newColor);
    }

    /**
     * Recursive helper for flood fill.
     *
     * @param x        the column (0-based)
     * @param y        the row (0-based)
     * @param oldColor the color to replace
     * @param newColor the replacement color
     */
    private void fill(int x, int y, char oldColor, char newColor) {
        if (x < 0 || x >= pixels[0].length || y < 0 || y >= pixels.length) return;
        if (pixels[y][x] != oldColor) return;
        pixels[y][x] = newColor;
        fill(x + 1, y, oldColor, newColor);
        fill(x - 1, y, oldColor, newColor);
        fill(x, y + 1, oldColor, newColor);
        fill(x, y - 1, oldColor, newColor);
    }

    /**
     * Prints the image to standard output with a given name.
     *
     * @param name the name or label to print before the image
     */
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

