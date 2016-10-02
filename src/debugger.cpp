#include "debugger.h"

#include <string>
#include <iostream>
#include <sstream>
#include <iomanip> // std::setfill // std::setw
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <vector>

#include "cpu.h"

using namespace chu;
using namespace dbg;

static void print_instr(const cpu::Instruction *instr, const word addr)
{
    using namespace std;

    cout << "(0x" << hex << setfill('0') << setw(3) << addr << ") ";
    cout << instr->to_string() << endl;
}

Command *Debugger::run(const cpu::Cpu *cpu, const cpu::Instruction *last_instr)
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
                case CommandType::PRINT_MEMORY:
                    break;
                case CommandType::QUIT:
                    goto quit_loop;
                    break;
                case CommandType::ERROR:
                    std::cout << "Unknown command: '" << command_str << "'" << std::endl;
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
                    std::cout << "Invalid parameter for command STEP" << std::endl;
                    success = false;
                }
            }
            if (success)
                m_Command = std::make_unique<StepCommand>(num);
        }
    }
    return success;
}

bool StepCommand::is_done()
{
    if (m_Steps > 0)
        m_Steps--;
    return m_Steps == 0;
}
