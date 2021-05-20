#ifndef PROCESSOR_H
#define PROCESSOR_H
#include <vector>
#include "linux_parser.h"
#include <map>
using std::vector;
using std::map;
using LinuxParser::CPUStates;

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp
  void SetCPUSTATES();
  vector<map<CPUStates, double>> GetCPUSTATES() const;
  // TODO: Declare any necessary private members
 private:
  vector<map<CPUStates, double>> cpustates_;
};

#endif
