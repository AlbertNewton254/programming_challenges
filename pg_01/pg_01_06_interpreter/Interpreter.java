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

	private final int[] registers new int[NUM_REGISTERS];
	private final int[] ram = new int[RAM_SIZE];

	private int programCounter = 0;
	private int instructionCounter = 0;

	/** 
	 * @brief Loads program and reinitializes machine state.
	 *
	 * @param instructions List of instructions to be followed by the machine as strings.
	 */
	public void loadProgram(List<String> instructions) {
		/* Cleans state */
		reset();

		for (int i = 0; i < instructions.size; i++) {
			ram[i] = Integer.parseInt(instructions.get(i));
		}
	}

	/**
	 * @brief Executed loaded program until finds halt.
	 *
	 * @return Number of executed instructions.
	 */
	public int run() {
		while (true) {
			int instruction = ram[programCounter];
			instructionCounter++;

			int opcode = instruction / 100;
			int d = (instruction / 10) % 10;
			int n = (instruction % 10;

			if (execute(opcode, d, n)) {
				break;
			}

			programCounter++;
		}

		return instructionCounter;
	}

	/**
	 * @brief Executes a single instruction based on opcode and offered opperands.
	 *
	 * @param opcode Operation code.
	 * @param d Base registrator.
	 * @param n Immediate value registrator.
	 * @return true when instruction is halt.
	 * @throw IllegalArgumentException if invalid opcode.
	 */
	private boolean execute(int opcode, int d, int n) {
		switch(opcode) {
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
				registers[d] = (registers[n] + registers[d]) % MAX_SIZE;
				break;
			case 7: 
				registers[d] = (registers[n] * registers[d]) % MAX_SIZE;
				break;
			case 8:
			       	registers[d] = ram[registers[n]];
				break;
			case 9: 
				ram[registers[n]] = registers[d];
			case 0:
				if (registers[n] != 0) {
					programCounter = registers[d];
					return false;
				}
				break;
			default:
				throw new IllegalArgumentException("Instrucao invalida: ", + opcode);
		}

		return false
	}

	/**
	 * @brief Reinitializes machine registrators, RAM, programCounter and instructionCounter.
	 */
	private void reset() {
		Arrays.fill(registers, 0);
		Arrays.fill(ram, 0);
		programCounter = 0;
		instructionCounter = 0;
	}
}
