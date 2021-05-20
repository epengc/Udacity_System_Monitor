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

constexpr int TIME_TO_SLEEP = 200; 

void Processor::SetCPUSTATES(){
    cpustates_ = LinuxParser::CpuStates(); 
}


vector<map<CPUStates, double>> Processor::GetCPUSTATES() const {return cpustates_;}


// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
    vector<map<CPUStates, double>> cpustates;
    vector<map<CPUStates, double>> cpustates_delta;
    double cpu_sum = 0;
    double cpu_sum_delta = 0;
    SetCPUSTATES();
    cpustates = GetCPUSTATES();
    sleep_for(std::chrono::milliseconds(TIME_TO_SLEEP));
    SetCPUSTATES();
    cpustates_delta = GetCPUSTATES();
    for(int i=0; i<7; ++i){
        cpu_sum += cpustates[0][(CPUStates)i];
        cpu_sum_delta += cpustates_delta[0][(CPUStates)i];
    }
    double loadavg = ((cpu_sum-cpustates[0][(CPUStates)3])-(cpu_sum_delta-cpustates_delta[0][(CPUStates)3]))/(cpu_sum-cpu_sum_delta);
    return loadavg;
    }


