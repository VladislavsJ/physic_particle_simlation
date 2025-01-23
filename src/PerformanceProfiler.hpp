#pragma once
#include <chrono>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

class PerformanceProfiler {
public:
  struct TimingEntry {
    std::string name;
    long long total_time = 0;
    int call_count = 0;
  };

  static PerformanceProfiler &getInstance() {
    static PerformanceProfiler instance;
    return instance;
  }

  class ScopedTimer {
  public:
    ScopedTimer(const std::string &name)
        : m_name(name), m_start(std::chrono::high_resolution_clock::now()) {}

    ~ScopedTimer() {
      auto end = std::chrono::high_resolution_clock::now();
      auto duration =
          std::chrono::duration_cast<std::chrono::microseconds>(end - m_start)
              .count();
      getInstance().addTiming(m_name, duration);
    }

  private:
    std::string m_name;
    std::chrono::high_resolution_clock::time_point m_start;
  };

  void addTiming(const std::string &name, long long duration) {
    auto &entry = m_timings[name];
    entry.name = name;
    entry.total_time += duration;
    entry.call_count++;
  }

  void printReport() {
    std::cout << "Performance Report:\n";
    std::cout << "---------------------\n";
    for (const auto &[name, entry] : m_timings) {
      double avg_time =
          static_cast<double>(entry.total_time) / entry.call_count;
      std::cout << name << ":\n"
                << "  Total Time: " << entry.total_time << " µs\n"
                << "  Calls: " << entry.call_count << "\n"
                << "  Avg Time: " << avg_time << " µs\n\n";
    }
  }

  void reset() { m_timings.clear(); }

private:
  PerformanceProfiler() = default;
  std::unordered_map<std::string, TimingEntry> m_timings;
};

// Macro for easier scoped timing
#define PROFILE_SCOPE(name)                                                    \
  PerformanceProfiler::ScopedTimer timer_##__LINE__(name)
#define PROFILE_FUNCTION() PROFILE_SCOPE(__FUNCTION__)