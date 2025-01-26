#ifndef PROFILER_H
#define PROFILER_H

#include <chrono>
#include <mutex>
#include <string>
#include <unordered_map>

class Profiler {
public:
  void start(const std::string &section) {
    std::lock_guard<std::mutex> lock(mutex_);
    startTimes_[section] = std::chrono::high_resolution_clock::now();
  }

  void stop(const std::string &section) {
    auto end = std::chrono::high_resolution_clock::now();
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = startTimes_.find(section);
    if (it != startTimes_.end()) {
      auto duration =
          std::chrono::duration<double, std::milli>(end - it->second).count();
      timings_[section] += duration;
      startTimes_.erase(it);
    }
  }

  double getTime(const std::string &section) const {
    auto it = timings_.find(section);
    if (it != timings_.end()) {
      return it->second;
    }
    return 0.0;
  }

private:
  std::unordered_map<std::string, double> timings_;
  std::unordered_map<std::string,
                     std::chrono::high_resolution_clock::time_point>
      startTimes_;
  mutable std::mutex mutex_;
};

#endif // PROFILER_H
