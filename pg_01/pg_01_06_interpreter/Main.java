import java.util.*;
import java.util.stream.IntStream;

public final class Main {
    private static final int MAX_CASES = 100;
    private static final int MAX_PROGRAM_LINES = 1000;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        Interpreter interpreter = new Interpreter();

        try {
            int numCases = readNumCases(scanner);
            validateNumCases(numCases);
            List<List<String>> allPrograms = readPrograms(scanner, numCases);
            processPrograms(interpreter, allPrograms);
        } catch (Exception e) {
            System.err.println("Error: " + e.getMessage());
            System.exit(1);
        }
    }

    private static int readNumCases(Scanner scanner) {
        while (scanner.hasNextLine()) {
            String line = scanner.nextLine().trim();
            if (!line.isEmpty()) {
                return Integer.parseInt(line);
            }
        }
        throw new NoSuchElementException("No test cases found");
    }

    private static void validateNumCases(int numCases) {
        if (numCases <= 0 || numCases > MAX_CASES) {
            throw new IllegalArgumentException("Number of cases must be between 1 and " + MAX_CASES);
        }
    }

    private static List<List<String>> readPrograms(Scanner scanner, int numCases) {
        List<List<String>> allPrograms = new ArrayList<>(numCases);
        for (int i = 0; i < numCases; i++) {
            skipEmptyLines(scanner);
            List<String> program = readProgram(scanner);
            validateProgramSize(program);
            allPrograms.add(program);
        }
        return allPrograms;
    }

    private static void skipEmptyLines(Scanner scanner) {
        while (scanner.hasNextLine()) {
            String line = scanner.nextLine().trim();
            if (!line.isEmpty()) {
                scanner = new Scanner(line); // Reset scanner with non-empty line
                break;
            }
        }
    }

    private static List<String> readProgram(Scanner scanner) {
        List<String> program = new ArrayList<>();
        while (scanner.hasNextLine()) {
            String line = scanner.nextLine().trim();
            if (line.isEmpty()) {
                break;
            }
            program.add(line);
        }
        return program;
    }

    private static void validateProgramSize(List<String> program) {
        if (program.size() > MAX_PROGRAM_LINES) {
            throw new IllegalStateException("Program exceeds maximum size of " + MAX_PROGRAM_LINES + " lines");
        }
    }

    private static void processPrograms(Interpreter interpreter, List<List<String>> programs) {
        for (int i = 0; i < programs.size(); i++) {
            interpreter.loadProgram(programs.get(i));
            System.out.println(interpreter.run());
            if (i < programs.size() - 1) {
                System.out.println();
            }
        }
    }
}

final class Interpreter {
    private static final int NUM_REGISTERS = 10;
    private static final int RAM_SIZE = 1000;
    private static final int MODULO = 1000;
    private static final int HALT_OPCODE = 1;
    private static final int MAX_INSTRUCTIONS = 10_000;

    private final int[] registers = new int[NUM_REGISTERS];
    private final int[] ram = new int[RAM_SIZE];
    private int programCounter = 0;
    private int instructionsExecuted = 0;

    public void loadProgram(List<String> program) {
        resetState();
        validateProgram(program);
        loadProgramIntoRam(program);
    }

    private void resetState() {
        Arrays.fill(registers, 0);
        Arrays.fill(ram, 0);
        programCounter = 0;
        instructionsExecuted = 0;
    }

    private void validateProgram(List<String> program) {
        Objects.requireNonNull(program, "Program cannot be null");
        if (program.size() > RAM_SIZE) {
            throw new IllegalArgumentException("Program exceeds RAM capacity");
        }
    }

    private void loadProgramIntoRam(List<String> program) {
        IntStream.range(0, program.size())
                .forEach(i -> ram[i] = parseInstruction(program.get(i)));
    }

    private int parseInstruction(String line) {
        try {
            int instruction = Integer.parseInt(line.trim());
            if (instruction < 0 || instruction >= MODULO) {
                throw new IllegalArgumentException("Invalid instruction: " + instruction);
            }
            return instruction;
        } catch (NumberFormatException e) {
            throw new IllegalArgumentException("Invalid instruction format: " + line, e);
        }
    }

    public int run() {
        while (instructionsExecuted <= MAX_INSTRUCTIONS) {
            int instruction = fetchInstruction();
            if (executeInstruction(instruction)) {
                break;
            }
        }
        if (instructionsExecuted > MAX_INSTRUCTIONS) {
            throw new IllegalStateException("Maximum instruction limit exceeded");
        }
        return instructionsExecuted;
    }

    private int fetchInstruction() {
        if (programCounter < 0 || programCounter >= RAM_SIZE) {
            throw new IllegalStateException("Program counter out of bounds");
        }
        return ram[programCounter++];
    }

    private boolean executeInstruction(int instruction) {
        int opcode = instruction / 100;
        int d = (instruction / 10) % 10;
        int n = instruction % 10;

        instructionsExecuted++;

        switch (opcode) {
            case HALT_OPCODE: return true;
            case 2: setRegister(d, n); break;
            case 3: addToRegister(d, n); break;
            case 4: multiplyRegister(d, n); break;
            case 5: copyRegister(d, n); break;
            case 6: addRegisters(d, n); break;
            case 7: multiplyRegisters(d, n); break;
            case 8: loadFromRam(d, n); break;
            case 9: storeToRam(d, n); break;
            case 0: jumpIfNotZero(d, n); break;
            default: throw new IllegalArgumentException("Invalid opcode: " + opcode);
        }
        return false;
    }

    private void setRegister(int reg, int value) {
        validateRegister(reg);
        registers[reg] = value % MODULO;
    }

    private void addToRegister(int reg, int value) {
        validateRegister(reg);
        registers[reg] = (registers[reg] + value) % MODULO;
    }

    private void multiplyRegister(int reg, int value) {
        validateRegister(reg);
        registers[reg] = (registers[reg] * value) % MODULO;
    }

    private void copyRegister(int dest, int src) {
        validateRegister(dest);
        validateRegister(src);
        registers[dest] = registers[src] % MODULO;
    }

    private void addRegisters(int dest, int src) {
        validateRegister(dest);
        validateRegister(src);
        registers[dest] = (registers[dest] + registers[src]) % MODULO;
    }

    private void multiplyRegisters(int dest, int src) {
        validateRegister(dest);
        validateRegister(src);
        registers[dest] = (registers[dest] * registers[src]) % MODULO;
    }

    private void loadFromRam(int reg, int addrReg) {
        validateRegister(reg);
        validateRegister(addrReg);
        int address = registers[addrReg];
        validateRamAddress(address);
        registers[reg] = ram[address] % MODULO;
    }

    private void storeToRam(int reg, int addrReg) {
        validateRegister(reg);
        validateRegister(addrReg);
        int address = registers[addrReg];
        validateRamAddress(address);
        ram[address] = registers[reg] % MODULO;
    }

    private void jumpIfNotZero(int reg, int testReg) {
        validateRegister(reg);
        validateRegister(testReg);
        if (registers[testReg] != 0) {
            programCounter = registers[reg];
            validateProgramCounter();
        }
    }

    private void validateRegister(int reg) {
        if (reg < 0 || reg >= NUM_REGISTERS) {
            throw new IllegalArgumentException("Invalid register: " + reg);
        }
    }

    private void validateRamAddress(int address) {
        if (address < 0 || address >= RAM_SIZE) {
            throw new IllegalArgumentException("RAM address out of bounds: " + address);
        }
    }

    private void validateProgramCounter() {
        if (programCounter < 0 || programCounter >= RAM_SIZE) {
            throw new IllegalStateException("Program counter out of bounds: " + programCounter);
        }
    }
}
