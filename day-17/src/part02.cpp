/**
 * Day-17 - Part 02
 */
#include "include.hpp"

using namespace std::ranges::views;

enum class OpCode : uint8_t
{
    ADV,
    BXL,
    BST,
    JNZ,
    BXC,
    OUT,
    BDV,
    CDV
};

struct ProgramState
{
    uint64_t pc = 0;
    uint64_t reg_a;
    uint64_t reg_b;
    uint64_t reg_c;
    std::vector<uint8_t> instructions;

    friend std::ostream &operator<<(std::ostream &os, const ProgramState &state)
    {
        os << "PC: " << state.pc << ", "
           << "Reg A: " << state.reg_a << ", "
           << "Reg B: " << state.reg_b << ", "
           << "Reg C: " << state.reg_c;
        return os;
    }
};

static ProgramState parseInput(const std::vector<std::string> &inputLines)
{
    ProgramState state;
    std::regex registerRegex(R"(Register (\w): (\d+))");
    std::regex programRegex(R"(Program: ([\d,]+))");
    std::smatch match;

    for (const auto &line : inputLines)
    {
        if (std::regex_search(line, match, registerRegex))
        {
            char reg = match[1].str()[0];
            int value = std::stoi(match[2].str());
            switch (reg)
            {
            case 'A':
                state.reg_a = value;
                break;
            case 'B':
                state.reg_b = value;
                break;
            case 'C':
                state.reg_c = value;
                break;
            }
        }
        else if (std::regex_search(line, match, programRegex))
        {
            std::ranges::for_each(match[1].str() | split(','), [&](auto &&code)
                                  {
                                      for (auto operation : code)
                                      {
                                          auto codeNum = static_cast<uint8_t>(operation - '0');
                                          state.instructions.emplace_back(codeNum);
                                      } });
        }
    }
    return state;
}

static std::vector<uint8_t> out_stream;

using opFunction = void (*)(ProgramState &, uint8_t);

static constexpr inline uint64_t toComboOperand(ProgramState &state, const uint8_t operand)
{

    if (operand <= 3)
    {
        return operand;
    }

    else if (operand == 4)
    {
        return state.reg_a;
    }

    else if (operand == 5)
    {
        return state.reg_b;
    }

    else if (operand == 6)
    {
        return state.reg_c;
    }
    else
    {
        std::cout << "Invalid Combo Operand!!!!" << std::endl;
        exit(1);
    }
    return -1;
}

static constexpr void advOperation(ProgramState &state, const uint8_t operand)
{
    auto combo_op = toComboOperand(state, operand);
    state.reg_a = state.reg_a / std::pow(2, combo_op);
    state.pc += 2;
}

static constexpr void bxlOperation(ProgramState &state, const uint8_t operand)
{
    state.reg_b = state.reg_b xor (uint64_t) operand;
    state.pc += 2;
}

static constexpr void bstOperation(ProgramState &state, const uint8_t operand)
{
    auto combo_op = toComboOperand(state, operand);
    state.reg_b = combo_op % 8;
    state.pc += 2;
}

static constexpr void jnzOperation(ProgramState &state, const uint8_t operand)
{
    if (state.reg_a == 0)
    {
        state.pc += 2;
    }
    else
    {
        state.pc = operand;
    }
}

static constexpr void bxcOperation(ProgramState &state, const uint8_t operand)
{
    state.reg_b = state.reg_b xor state.reg_c;
    state.pc += 2;
}

static constexpr void outOperation(ProgramState &state, const uint8_t operand)
{
    auto combo_op = toComboOperand(state, operand) % 8;
    out_stream.emplace_back(combo_op);
    state.pc += 2;
}

static constexpr void bdvOperation(ProgramState &state, const uint8_t operand)
{
    auto combo_op = toComboOperand(state, operand);
    state.reg_b = state.reg_a / std::pow(2, combo_op);
    state.pc += 2;
}

static constexpr void cdvOperation(ProgramState &state, const uint8_t operand)
{
    auto combo_op = toComboOperand(state, operand);
    state.reg_c = state.reg_a / std::pow(2, combo_op);
    state.pc += 2;
}

static constexpr const std::array<opFunction, 8> operations{
    advOperation,
    bxlOperation,
    bstOperation,
    jnzOperation,
    bxcOperation,
    outOperation,
    bdvOperation,
    cdvOperation,
};

int64_t handlePart2(const std::vector<std::string> &inputLines)
{
    auto program = parseInput(inputLines);
    out_stream.clear();

    while (program.pc < program.instructions.size())
    {
        OpCode op = static_cast<OpCode>(program.instructions[program.pc]);
        uint8_t operand = program.instructions[program.pc + 1];

        // std::cout << "Op code: " << std::to_string(static_cast<uint8_t>(op)) << std::endl;
        operations[static_cast<uint8_t>(op)](program, operand);
        // std::cout << program << std::endl;
    }

    std::string result;
    for (size_t i = 0; i < out_stream.size(); ++i)
    {
        result += std::to_string(out_stream[i]);
        if (i != out_stream.size() - 1)
        {
            result += ',';
        }
    }

    return 0;
}