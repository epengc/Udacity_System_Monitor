#include "processor.h"
#include "linux_parser.h"
#include <vector>
#include <map>
#include <thread>
#include <chrono>

using std::map;
using std::vector;
using std::this_thread::sleep_for;
using LinuxParser::CPUStates;

constexpr int TIME_TO_SLEEP = 100; 


// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
    float loadavg;
    long actJif = LinuxParser::ActiveJiffies();
    long idlJif = LinuxParser::IdleJiffies();
    sleep_for(std::chrono::milliseconds(TIME_TO_SLEEP));
    actJif -= LinuxParser::ActiveJiffies();
    idlJif -= LinuxParser::IdleJiffiles();
    loadavg = static_cast<float>(actJif)/(actJif+idlJif);
    return loadavg;
    }


