//! System includes
#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <string>

//! VM Includes
#include "VMObjects.h"

//! Examples
#include "BasicAllocation.h"
#include "GCPause.h"
#include "NestedAllocation.h"
#include "RepeatedCollections.h"
#include "RetainedObjects.h"

namespace
{
using ExampleFn = std::function<void()>;

int PrintUsage(const std::string &p_strProgramName, const std::string &p_strErrorMessage = "")
{
    if (!p_strErrorMessage.empty())
    {
        std::cerr << "Error: " << p_strErrorMessage << "\n\n";
    }

    std::cout
        << "Garbage Collector Examples\n"
        << "Usage:\n"
        << "  " << p_strProgramName << " <example>\n"
        << "  " << p_strProgramName << " --list\n"
        << "  " << p_strProgramName << " --help\n\n"
        << "Examples:\n"
        << "  basic        Small allocation flow with two root objects\n"
        << "  nested       Nested pair allocations to show composed object graphs\n"
        << "  gc-pause     Triggers garbage collection using a low allocation threshold\n"
        << "  retained     Keeps a root alive across multiple GC pauses\n"
        << "  repeated     Repeats collect-and-reclaim cycles in one VM session\n"
        << "  all          Runs every example in sequence\n";

    return p_strErrorMessage.empty() ? 0 : 1;
}

int PrintExamplesList()
{
    std::cout
        << "Available examples:\n"
        << "  basic\n"
        << "  nested\n"
        << "  gc-pause\n"
        << "  retained\n"
        << "  repeated\n"
        << "  all\n";
    return 0;
}

void PrintSummary(const std::string &p_strExampleName)
{
    std::cout << "[summary] example=" << p_strExampleName
              << ", remaining_vm_objects=" << VMObject::m_ullCreatedInstances << '\n';

    if (VMObject::m_ullCreatedInstances == 0)
    {
        std::cout << "[summary] leak_check=pass\n";
    }
    else
    {
        std::cout << "[summary] leak_check=fail\n";
    }
}

int RunExample(const std::string &p_strExampleName, const ExampleFn &p_fnExample)
{
    std::cout << "== Running example: " << p_strExampleName << " ==\n";
    p_fnExample();
    PrintSummary(p_strExampleName);
    std::cout << '\n';
    return VMObject::m_ullCreatedInstances == 0 ? 0 : 2;
}
}

int main(int argc, char **argv)
{
    const std::string strProgramName = argc > 0 ? argv[0] : "gc_example";
    const std::map<std::string, ExampleFn> mapExamples{
        {"basic", BasicAllocation},
        {"nested", NestedObjects},
        {"gc-pause", GCPause},
        {"retained", RetainedObjectsAcrossCollections},
        {"repeated", RepeatedCollections}};

    if (argc < 2)
    {
        return PrintUsage(strProgramName, "missing example name");
    }

    const std::string strCommand = argv[1];
    if (strCommand == "--help" || strCommand == "-h")
    {
        return PrintUsage(strProgramName);
    }

    if (strCommand == "--list")
    {
        return PrintExamplesList();
    }

    if (strCommand == "all")
    {
        int iExitCode = 0;
        iExitCode = std::max(iExitCode, RunExample("basic", BasicAllocation));
        iExitCode = std::max(iExitCode, RunExample("nested", NestedObjects));
        iExitCode = std::max(iExitCode, RunExample("gc-pause", GCPause));
        iExitCode = std::max(iExitCode, RunExample("retained", RetainedObjectsAcrossCollections));
        iExitCode = std::max(iExitCode, RunExample("repeated", RepeatedCollections));
        return iExitCode;
    }

    const auto itExample = mapExamples.find(strCommand);
    if (itExample == mapExamples.end())
    {
        return PrintUsage(strProgramName, "unknown example '" + strCommand + "'");
    }

    return RunExample(itExample->first, itExample->second);
}
