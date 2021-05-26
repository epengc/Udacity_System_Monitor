#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;
using std::size_t;
using std::map;
using std::stoi;
using std::stol;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}


// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
    string line;
    string key;
    string value;
    string kb;
    float memtotal=1;
    float memfree=1;
    std::ifstream filestream(kProcDirectory+kMeminfoFilename);
    if(filestream.is_open()){
        while(std::getline(filestream, line)){
            std::istringstream linestream(line);
            while(linestream>>key>>value>>kb){
                if(key=="MemTotal:"){
                    memtotal = stof(value);
                }
                if(key=="MemFree:"){
                    memfree = stof(value);
                }
            }
        }
    }
    float loadavg = (memtotal-memfree)/memtotal;
    return loadavg;
 }


// TODO: Read and return the system uptime
long LinuxParser::UpTime() {
    string line;
    string val;
    std::ifstream filestream(kProcDirectory+kUptimeFilename);
    if(filestream.is_open()){
        while(std::getline(filestream, line)){
            std::istringstream linestream(line);
            while(linestream>>val){
                return stoi(val);
            }
        }
    }
    return 0;
}


// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return LinuxParser::UpTime()*sysconf(_SC_CLK_TCK); }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) {
    string line;
    string item;
    vector<string> values;
    std::ifstream filestream(LinuxParser::kProcDirectory+to_string(pid)+kStatFilename);
    if(filestream.is_open()){
        std::getline(filestream, line);
        std::istringstream linestream(line);
        while(linestream>>item){
            values.push_back(item);
        }
    }
    long int actJif = 0;
    if(values.size()>21){
        // https://man7.org/linux/man-pages/man5/proc.5.html
        //
        // utime = Amount of time that this process has been scheduled in user mode.
        long int utime = stol(values[13]);
        // stime = Amount of time that this process has been scheduled in kernel mode.
        long int stime = stol(values[14]);
        // cutime = Amount of time that this process's waited-for children have been scheduled in user mode.
        long cutime = stol(values[15]);
        // cstime = Amount of time that this process's waited-for children have been scheduled in kernel mode.
        long cstime = stol(values[16]);
        actJif = utime+stime+cutime+cstime;
    }
    return actJif;
}

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() {
    vector<string> cpu_table = LinuxParser::CpuUtilization();
    long int actJif=0;
    for(int i=0; i<8; i++)i{
        actJif += stol(pu_table[0]);
    }
    return actJif;
    

// TODO: Read and return the number of idle jiffies for the system
    long LinuxParser::IdleJiffies() {
        vector<string> cpu_table = LinuxParser::CpuUtilization();
        long int idlJif = stol(cpu_table[CPUStates::kIdle_])+stol(cpu_table[CPUStates::kIOwait_]);
        return idlJif;
    }


// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() {
    string line;
    string str_cpu;
    string value;
    vector<string> values;
    std::ifstream filestream(kProcDirectory+kStatFilename);
    if(filestream.is_open()){
        while(std::getline(filestream, line)){
            std::istringstream linestream(line);
            linestream>>str_cpu;
            if (str_cpu=="cpu"){
                while(linestream>>value){
                    values.push_back(value);
                }
            }
        }
    }
    return values;
}


// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
    string line;
    string key;
    string val;
    std::ifstream filestream(kProcDirectory+kStatFilename);
    if(filestream.is_open()){
        while(std::getline(filestream, line)){
            std::istringstream linestream(line);
            while(linestream>>key>>val){
                if(key=="processes"){
                    return stoi(val);
                }
            }
        }
            
    }
    return 0;
}


// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
    string line;
    string key;
    string val;
    std::ifstream filestream(kProcDirectory+kStatFilename);
    if(filestream.is_open()){
        while(std::getline(filestream, line)){
            std::istringstream linestream(line);
            while(linestream>>key>>val){
                if(key=="procs_running"){
                    return stoi(val);
                }
            }
        }
    }
    return 0;
}


// TODO: Read and return the command associated with a process
string LinuxParser::Command(int pid) {
    string line;
    string value;
    std::ifstream filestream(kProcDirectory+to_string(pid)+kCmdlineFilename);
    if (filestream.is_open()){
        std::getline(filestream, line));
        return line;
        }
    return ""; 
}
    

// TODO: Read and return the memory used by a process
string LinuxParser::Ram(int pid) { 
    string line;
    string name;
    string value;
    std::ifstream filestream(kProcDirectory+to_string(pid)+kStatusFilename);
    if (filestream.is_open()){
        std::getline(filestream, line);
        std::istringstream linestream(line);
        while(linestream>>name){
            if (name=="VmSize:"){
                linestream>>value;
                return to_string(stof(value)/1024);
            }
        }
    
    }
    return string("0"); 
}


// TODO: Read and return the user ID associated with a process
string LinuxParser::Uid(int pid) {
    string line;
    string value;
    string name;
    std::ifstream filestream(kProcDirectory+to_string(pid)+kStatusFilename);
    if(filestream.is_open()){
        std::getline(filestream, line);
        std::istringstream linestream(line);
        while(linestream>>name){
            if(name=="Uid:"){
                linestream>>value;
                return value;
            }
        }
    }
    return string("");
}

// TODO: Read and return the user associated with a process
string LinuxParser::User(int pid) {
    string line;
    string name;
    string value;
    std::ifstream filestream(kPasswordPath){
        if(filestream.is_open()){
            std::getline(filestream, line);
            name = "x:"+Uid(pid);
            if(line.find(name)!=string::npos){
                return line.substr(0,line.find(name)-1);
            }
        }
    }
    return string("0");
}


// TODO: Read and return the uptime of a process
long LinuxParser::UpTime(int pid) {
    string line;
    string item;
    long int uptime{0};
    std::ifstream filestream(kProcDirectory+to_string(pid)+kStatFilename);
    if(filestream.is_open()){
        std::getline(filestream, line);
        std::istringstream linestream(line);
        int cout = 0;
        while(linestream>>item){
            if (cout==13){
                long int uptime{stol(item)};
                // Amount of time that this process has been scheduled in user mode,
                // measured in clock ticks :devided by sysconf(_SC_CLK_TCKSC_CLK_TCK).
                uptime /= sysconf(_SC_CLK_TCK);
                return uptime;
            }
            cout ++;
        }
    }
    return 0;
}



