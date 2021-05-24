#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:

  void Pid();
  int Pid()const;                               // TODO: See src/process.cpp

  void User();
  std::string User()const;                      // TODO: See src/process.cpp

  void Command();
  std::string Command()const;                   // TODO: See src/process.cpp

  void CpuUtilization();
  float CpuUtilization()const;                  // TODO: See src/process.cpp

  void Ram();
  std::string Ram()const;                       // TODO: See src/process.cpp

  void UpTime();
  long int UpTime()const;                       // TODO: See src/process.cpp

  bool operator<(Process const& a) const;  // TODO: See src/process.cpp

  // TODO: Declare any necessary private members
 private:
  int pid_;
  std::string user_;
  std::string command_;
  float cpuutilization_;
  std::string ram_;
  long int uptime_;
};

#endif
