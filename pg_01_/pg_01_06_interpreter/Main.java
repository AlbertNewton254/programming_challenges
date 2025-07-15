import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        Interpreter interpreter = new Interpreter();

        int numCases = readNumCases(scanner);
        List<List<String>> allPrograms = readPrograms(scanner, numCases);

        for (int i = 0; i < allPrograms.size(); i++) {
            interpreter.loadProgram(allPrograms.get(i));
            System.out.println(interpreter.run());
            if (i < allPrograms.size() - 1) System.out.println();
        }
    }

    private static int readNumCases(Scanner scanner) {
        while (scanner.hasNextLine()) {
            String line = scanner.nextLine().trim();
            if (!line.isEmpty()) return Integer.parseInt(line);
        }
        throw new NoSuchElementException("No cases found");
    }

    private static List<List<String>> readPrograms(Scanner scanner, int numCases) {
        List<List<String>> allPrograms = new ArrayList<>();
        for (int i = 0; i < numCases; i++) {
            while (scanner.hasNextLine() && scanner.nextLine().trim().isEmpty()) {}
            List<String> program = new ArrayList<>();
            while (scanner.hasNextLine()) {
                String line = scanner.nextLine().trim();
                if (line.isEmpty()) break;
                program.add(line);
            }
            allPrograms.add(program);
        }
        return allPrograms;
    }
}

class Interpreter {
    private static final int REGISTERS = 10, RAM = 1000, MOD = 1000;

    private final int[] registers = new int[REGISTERS];
    private final int[] ram = new int[RAM];
    private int pc = 0, instructionsExecuted = 0;

    public void loadProgram(List<String> program) {
        reset();
        for (int i = 0; i < program.size(); i++) {
            ram[i] = Integer.parseInt(program.get(i));
        }
    }

    public int run() {
        while (true) {
            int instr = ram[pc++];
            instructionsExecuted++;

            int opcode = instr / 100;
            int d = (instr / 10) % 10;
            int n = instr % 10;

            if (execute(opcode, d, n)) break;
        }
        return instructionsExecuted;
    }

    private boolean execute(int op, int d, int n) {
        switch (op) {
            case 1: return true; // halt
            case 2: registers[d] = n; break;
            case 3: registers[d] = (registers[d] + n) % MOD; break;
            case 4: registers[d] = (registers[d] * n) % MOD; break;
            case 5: registers[d] = registers[n]; break;
            case 6: registers[d] = (registers[d] + registers[n]) % MOD; break;
            case 7: registers[d] = (registers[d] * registers[n]) % MOD; break;
            case 8: registers[d] = ram[registers[n]]; break;
            case 9: ram[registers[n]] = registers[d]; break;
            case 0:
                if (registers[n] != 0) pc = registers[d];
                break;
            default:
                throw new IllegalArgumentException("Invalid opcode: " + op);
        }
        return false;
    }

    private void reset() {
        Arrays.fill(registers, 0);
        Arrays.fill(ram, 0);
        pc = 0;
        instructionsExecuted = 0;
    }
}

