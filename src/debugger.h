#pragma once

#include <string>
#include <vector>
#include <memory>

#include "cpu.h"
#include "instr.h"

namespace chu
{
namespace cpu
{
    class Cpu;
    class Instruction;
} // end of namespace cpu

namespace dbg
{
    class Command;

    enum class CommandType
    {
        STEP, QUIT, ERROR, PRINT_MEMORY
    };

    class Debugger
    {
    public:
        Debugger() : m_Command(std::make_unique<Command>()) {}
        Command *run(const cpu::Cpu *cpu, const cpu::Instruction *last_instr);

    private:
        bool parse(std::vector<std::string> &cmd_tokens);

    private:
        std::unique_ptr<Command> m_Command;
    };

    class Command
    {
    public:
        Command() : m_Type(CommandType::ERROR) {}
        Command(const CommandType type) : m_Type(type) {}

        CommandType type() const { return m_Type; }

    private:
        CommandType m_Type;
    };

    class StepCommand : public Command 
    {
    public:
        StepCommand(unsigned int steps) : Command(CommandType::STEP), m_Steps(steps) {}
        bool is_done();
    private:
        unsigned int m_Steps;
    };

} // end of namespace dbg
} // end of namespace chu
