import java.util.*;

/**
 * @class Main
 * @brief Instantiates virtual machine as object of class Interpreter.
 *
 * @author Miguel
 */
public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        Interpreter interpreter = new Interpreter();

        int numCases = 0;
        List<List<String>> allPrograms = new ArrayList<>();

        /* Reads number of cases */	
        while (scanner.hasNextLine()) {
            String line = scanner.nextLine().trim();
            if (!line.isEmpty()) {
                numCases = Integer.parseInt(line);
                break;
            }
        }

        int currentCase = 0;
        while (currentCase < numCases) {
            List<String> program = new ArrayList<>();

            /* Skips line between cases */
            while (scanner.hasNextLine()) {
                String line = scanner.nextLine();
                if (!line.trim().isEmpty()) {
                    program.add(line.trim());
                    break;
                }
            }

            /* Reads program instructions */
            while (scanner.hasNextLine()) {
                String line = scanner.nextLine().trim();
                if (line.isEmpty()) break;
                program.add(line);
            }

            allPrograms.add(program);
            currentCase++;
        }

        /* Executes all files */
        for (int i = 0; i < allPrograms.size(); i++) {
            interpreter.loadProgram(allPrograms.get(i));
            int executedInstructions = interpreter.run();
            System.out.println(executedInstructions);
            if (i < allPrograms.size() - 1) {
                System.out.println(); // Blank line between cases
            }
        }
    }
}

/**
 * @class Interpreter
 * @brief Simulates virtual machine with 10 registers and 1000 RAM positions.
 *
 * This class implements a virtual machine capable of interpret 3 digit instructions in Assembly style.
 *
 * Registers and RAM are bounded to values between 0 and 999, and arithmetic have modular overflow (mod 1000).
 *
 * Supported commands include charge, arithmetic, access to memory and conditional jumps.
 */
class Interpreter {
    private static final int NUM_REGISTERS = 10;
    private static final int RAM_SIZE = 1000;
    private static final int MAX_SIZE = 1000;

    private final int[] registers = new int[NUM_REGISTERS];
    private final int[] ram = new int[RAM_SIZE];

    private int programCounter = 0;
    private int instructionCounter = 0;

    public void loadProgram(List<String> instructions) {
        reset();
        for (int i = 0; i < instructions.size(); i++) {
            ram[i] = Integer.parseInt(instructions.get(i));
        }
    }

    public int run() {
        while (true) {
            int instruction = ram[programCounter];
            instructionCounter++;

            int opcode = instruction / 100;
            int d = (instruction / 10) % 10;
            int n = instruction % 10;

            if (execute(opcode, d, n)) {
                break;
            }

            programCounter++;
        }
        return instructionCounter;
    }

    private boolean execute(int opcode, int d, int n) {
        switch (opcode) {
            case 1:
                return true;
            case 2:
                registers[d] = n;
                break;
            case 3:
                registers[d] = (registers[d] + n) % MAX_SIZE;
                break;
            case 4:
                registers[d] = (registers[d] * n) % MAX_SIZE;
                break;
            case 5:
                registers[d] = registers[n];
                break;
            case 6:
                registers[d] = (registers[d] + registers[n]) % MAX_SIZE;
                break;
            case 7:
                registers[d] = (registers[d] * registers[n]) % MAX_SIZE;
                break;
            case 8:
                registers[d] = ram[registers[n]];
                break;
            case 9:
                ram[registers[n]] = registers[d];
                break;
            case 0:
                if (registers[n] != 0) {
                    programCounter = registers[d] - 1;
                }
                break;
            default:
                throw new IllegalArgumentException("Invalid instruction: " + opcode);
        }

        return false;
    }

    private void reset() {
        Arrays.fill(registers, 0);
        Arrays.fill(ram, 0);
        programCounter = 0;
        instructionCounter = 0;
    }
}

