#ifndef REPORT_H
#define REPORT_H

#include "Profiler.hpp"
#include <iomanip>
#include <iostream>

class Report {
public:
  Report(const Profiler &profiler) : profiler_(profiler) {}

  void generate() const {
    std::cout << "---- Profiling Report ----\n";
    std::cout << std::left << std::setw(30) << "Section" << std::right
              << std::setw(15) << "Time (ms)" << "\n";
    std::cout << "--------------------------------------------\n";

    // Assuming Profiler has a method to retrieve all timings
    // If not, you may need to add such a method
    // For simplicity, let's assume we know the sections
    const std::vector<std::string> sections = {
        "apply_gravity", "particle_update",      "update_border_speed",
        "updateGrid",    "InitWindow",           "collision_handling",
        "addParticle",   "collision_handlingnew"};

    for (const auto &section : sections) {
      std::cout << std::left << std::setw(30) << section << std::right
                << std::setw(15) << profiler_.getTime(section) << "\n";
    }

    std::cout << "------------------------------\n";
  }

private:
  const Profiler &profiler_;
};

#endif // REPORT_H
