#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
void Process::Pid(int pid){this->pid_=pid;}

int Process::Pid() const { return this->pid_; }

// TODO: Return this process's CPU utilization
void Process::CpuUtilization(float cpuutilization){ return cpuutilization_; }

float Process::CpuUtilization() const { return this->cpuutilization_; }

// TODO: Return the command that generated this process
void Process::Command(string command){ this->command_=command; }

string Process::Command() const { return this->command_; }

// TODO: Return this process's memory utilization
void Process::Ram(string ram){ this->ram_=ram; }

string Process::Ram() const { return this->ram_; }

// TODO: Return the user (name) that generated this process
void Process::User(string user){ this->user_=user; }

string Process::User() const { return this->user_; }

// TODO: Return the age of this process (in seconds)
void Process::UpTime(long int uptime){ this->uptime_=uptime; }

long int Process::UpTime() { return this->uptime_; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }




