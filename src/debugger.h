#pragma once

#include <string>
#include <vector>
#include <memory>

#include "cpu.h"
#include "instr.h"
#include "macros.h"

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
        STEP, QUIT, ERROR, MEMORY, HELP, RUN, CPU
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

    class MemCommand : public Command
    {
    public:
        MemCommand(unsigned int begin, unsigned int end)
            : Command(CommandType::MEMORY), m_Begin(begin), m_End(end) {}
        unsigned int begin() const { return m_Begin; }
        unsigned int end() const { return m_End; }
    private:
        unsigned int m_Begin;
        unsigned int m_End;
    };

    class Debugger
    {
    public:
        Debugger() : m_Command(std::make_unique<Command>()) {}
        const Command &run(const cpu::Cpu &cpu, const mem::Memory &mem);
        void print_help();

    private:
        bool parse(std::vector<std::string> &cmd_tokens);
        void print_instr(const cpu::Cpu &cpu);

    private:
        std::unique_ptr<Command> m_Command;
    };
} // end of namespace dbg
} // end of namespace chu
