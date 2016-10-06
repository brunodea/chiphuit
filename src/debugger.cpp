#include "debugger.h"

#include <string>
#include <sstream>
#include <iostream>
#include <iomanip> // std::setfill // std::setw
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <vector>

#include "cpu.h"
#include "mem.h"

using namespace chu;
using namespace dbg;

void Debugger::print_help()
{
    using namespace std;

    cout << "==================" << std::endl;
    cout << "Comand List" << std::endl;
    cout << "==================" << std::endl;
    cout << "step [N]\n\t\t-- step N times" << std::endl;
    cout << "mem 0x<begin_in_hex> 0x<end_in_hex>\n\t\t-- prints a chunk of the memory from begin to end in hex." << std::endl;
    cout << "run\n\t\t-- run the rom without coming back to the debugger console." << std::endl;
    cout << "quit, exit\n\t\t-- exit ChipHuit" << std::endl;
    cout << "help\n\t\t-- show this" << std::endl;
    cout << "---------------------------" << std::endl;
}

void Debugger::print_instr(const cpu::Instruction &instr)
{
    using namespace std;

    cout << "(" << hex << showbase << setfill('0') << setw(3) << m_LastAddr << ") ";
    cout << instr.to_string() << std::endl;
}

const Command &Debugger::run(const cpu::Cpu &cpu, const cpu::Instruction &last_instr, const mem::Memory &mem)
{
    switch (m_Command->type())
    {
    case CommandType::STEP:
        if (!static_cast<StepCommand *>(m_Command.get())->is_done())
        {
            print_instr(last_instr);
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
        std::cout << "> ";
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
                        print_instr(last_instr);
                        goto quit_loop;
                    }
                    break;
                case CommandType::MEMORY:
                    {
                        auto mem_cmd = static_cast<MemCommand *>(m_Command.get());
                        mem.print_chunk(mem_cmd->begin(), mem_cmd->end());
                    }
                    break;
                case CommandType::RUN:
                    goto quit_loop;
                    break;
                case CommandType::CPU:
                    {
                        std::stringstream regs_ss;
                        for (int i = 0; i < NUMBER_OF_GENREGS; i++)
                        {
                            regs_ss << std::setfill(' ') << std::setw(5) << "V" << std::hex << i;
                        }
                        const auto regs = regs_ss.str();
                        const std::string gentitle = "Generic Registers";
                        std::cout << gentitle << std::setfill('-') <<
                            std::setw(regs.length()-gentitle.length()+1) << '\n';
                        std::cout << regs << std::endl;
                        for (int i = 0; i < NUMBER_OF_GENREGS; i++)
                        {
                            std::cout << std::setfill(' ') << std::setw(6)
                                << std::hex << std::showbase << int(cpu.m_GenRegs[i]);
                        }
                        const std::string spectitle = "Special Registers";
                        std::cout << std::endl << spectitle << std::setfill('-') <<
                            std::setw(regs.length()-spectitle.length()+1) << '\n';
                        const auto w = 9;
                        std::cout
                            << std::setfill(' ') << std::setw(9) << "PC"
                            << std::setfill(' ') << std::setw(9) << "SP"
                            << std::setfill(' ') << std::setw(9) << "FlagReg"
                            << std::setfill(' ') << std::setw(9) << "MemReg"
                            << std::setfill(' ') << std::setw(9) << "DelayReg"
                            << std::setfill(' ') << std::setw(9) << "SoundReg"
                            << std::endl
                            << std::setfill(' ') << std::setw(9) << std::hex << std::showbase << int (cpu->m_PC)
                            << std::setfill(' ') << std::setw(9) << std::hex << std::showbase << int (cpu->m_SP)
                            << std::setfill(' ') << std::setw(9) << std::hex << std::showbase << int (cpu->m_FlagReg)
                            << std::setfill(' ') << std::setw(9) << std::hex << std::showbase << int (cpu->m_MemReg)
                            << std::setfill(' ') << std::setw(9) << std::hex << std::showbase << int (cpu->m_DelayReg)
                            << std::setfill(' ') << std::setw(9) << std::hex << std::showbase << int (cpu->m_SoundReg)
                            << std::endl;
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
    m_LastAddr = cpu.m_PC;
    return *m_Command;
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
