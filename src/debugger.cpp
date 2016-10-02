#include "debugger.h"

#include <string>
#include <iostream>
#include <iomanip> // std::setfill // std::setw
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <vector>

#include "cpu.h"
#include "mem.h"

using namespace chu;
using namespace dbg;

static void print_help()
{
    using namespace std;

    cout << "===========" << endl;
    cout << "Comand List" << endl;
    cout << "===========" << endl;
    cout << "step [N] -- step N times" << endl;
    cout << "mem 0x<begin_in_hex> 0x<end_in_hex> -- prints a chunk of the memory from begin to end in hex." << endl;
    cout << "run -- run the rom without coming back to the debugger console." << endl;
    cout << "quit, exit -- exit ChipHuit" << endl;
    cout << "help -- show this" << endl;
    cout << "---------------------------" << endl;
}

static void print_instr(const cpu::Instruction *instr, const word addr)
{
    using namespace std;

    cout << "(0x" << hex << setfill('0') << setw(3) << addr << ") ";
    cout << instr->to_string() << endl;
}

Command *Debugger::run(const cpu::Cpu *cpu, const cpu::Instruction *last_instr, const mem::Memory *mem)
{
    switch (m_Command->type())
    {
    case CommandType::STEP:
        if (!static_cast<StepCommand *>(m_Command.get())->is_done())
        {
            print_instr(last_instr, cpu->m_PC-1);
            goto quit_loop;
        }
        break;
    case CommandType::RUN:
        goto quit_loop;
        break;
    default:
        break;
    }

    while (true)
    {
        std::string command_str;
        std::cout << ">";
        std::getline(std::cin, command_str);

        boost::trim(command_str);
        std::vector<std::string> cmd_tokens;
        boost::split(cmd_tokens, command_str, boost::is_any_of(" "));
        for (auto &param : cmd_tokens)
            boost::trim(param);

        if (parse(cmd_tokens))
        {
            switch (m_Command->type())
            {
                case CommandType::STEP:
                    {
                        print_instr(last_instr, cpu->m_PC-1);
                        goto quit_loop;
                    }
                    break;
                case CommandType::MEMORY:
                    {
                        auto mem_cmd = static_cast<MemCommand *>(m_Command.get());
                        mem->print_chunk(mem_cmd->begin(), mem_cmd->end());
                    }
                    break;
                case CommandType::RUN:
                    goto quit_loop;
                    break;
                case CommandType::CPU:
                    {
                        for (int i = 0; i < NUMBER_OF_GENREGS; i++)
                        {
                            std::cout << "V" << i << "       = 0x" << std::hex << int(cpu->m_GenRegs[i]) << std::endl;
                        }
                        std::cout << "PC       = 0x" << std::hex << int (cpu->m_PC      ) << std::endl;
                        std::cout << "SP       = 0x" << std::hex << int (cpu->m_SP      ) << std::endl;
                        std::cout << "FlagReg  = 0x" << std::hex << int (cpu->m_FlagReg ) << std::endl;
                        std::cout << "MemReg   = 0x" << std::hex << int (cpu->m_MemReg  ) << std::endl;
                        std::cout << "DelayReg = 0x" << std::hex << int (cpu->m_DelayReg) << std::endl;
                        std::cout << "SoundReg = 0x" << std::hex << int (cpu->m_SoundReg) << std::endl;
                    }
                    break;
                case CommandType::QUIT:
                    goto quit_loop;
                    break;
                case CommandType::ERROR:
                    std::cout << "***ERROR" << std::endl;
                    std::cout << "Unknown command: '" << command_str << "'" << std::endl;
                    print_help();
                    break;
                case CommandType::HELP:
                    print_help();
                    break;
            }
        }
    }
quit_loop:

    return m_Command.get();
}

bool Debugger::parse(std::vector<std::string> &cmd_tokens)
{
    m_Command = std::make_unique<Command>(CommandType::ERROR);
    bool success = true;
    if (cmd_tokens.size() > 0)
    {
        auto cmd_root = cmd_tokens[0];
        if (boost::iequals(cmd_root, "quit") || boost::iequals(cmd_root, "exit"))
            m_Command = std::make_unique<Command>(CommandType::QUIT);
        else if (boost::iequals(cmd_root, "step"))
        {
            unsigned int num = 0;
            if (cmd_tokens.size() == 2)
            {
                try
                {
                    num = boost::lexical_cast<unsigned int>(cmd_tokens[1]);
                }
                catch (...)
                {
                    std::cout << "Invalid parameter for command STEP." << std::endl;
                    success = false;
                }
            }
            else if (cmd_tokens.size() > 2)
            {
                std::cout << "Invalid number of arguments." << std::endl;
                success = false;
            }
            if (success)
                m_Command = std::make_unique<StepCommand>(num);
        }
        else if (boost::iequals(cmd_root, "mem"))
        {
            success = cmd_tokens.size() == 3;
            if (success)
            {
                try
                {
                    auto begin = std::stoul(cmd_tokens[1], nullptr, 16);
                    auto end = std::stoul(cmd_tokens[2], nullptr, 16);
                    if (begin < end)
                        m_Command = std::make_unique<MemCommand>(begin, end);
                    else
                        std::cout << "Begin can't be bigger than ending address." << std::endl;
                }
                catch (...)
                {
                    std::cout << "Invalid parameters for command MEM." << std::endl;
                    success = false;
                }
            }
            else
                std::cout << "Invalid number of arguments." << std::endl;
        }
        else if (boost::iequals(cmd_root, "run"))
            m_Command = std::make_unique<Command>(CommandType::RUN);
        else if (boost::iequals(cmd_root, "cpu"))
            m_Command = std::make_unique<Command>(CommandType::CPU);
    }
    return success;
}

bool StepCommand::is_done()
{
    if (m_Steps > 0)
        m_Steps--;
    return m_Steps == 0;
}
