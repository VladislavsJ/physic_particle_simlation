#include "Graphs_new.hpp"
#include <algorithm>
#include <string>

void Graph::updateData(float dataX, float dataY) {
  m_dataX.push_back(dataX);
  m_dataY.push_back(dataY);
  trimDataBuffers();
}

void Graph::trimDataBuffers() { // if data amount is too long, remove the oldest
                                // data
  const size_t currentSize = m_dataX.size();
  if (currentSize > MAX_POINTS) {
    const size_t removeCount = currentSize - MAX_POINTS;
    m_dataX.erase(m_dataX.begin(), m_dataX.begin() + removeCount);
    m_dataY.erase(m_dataY.begin(), m_dataY.begin() + removeCount);
  }
}

float Graph::findMaxValue(const std::vector<float> &data) {
  if (data.empty()) {
    return 0.0f;
  }
  return *std::max_element(data.begin(), data.end());
}

float Graph::findMinValue(const std::vector<float> &data) {
  if (data.empty()) {
    return 0.0f;
  }
  return *std::min_element(data.begin(), data.end());
}
float Graph::findMaxValueX() { return findMaxValue(m_dataX); }
float Graph::findMinValueY() { return findMinValue(m_dataY); }
float Graph::findMaxValueY() { return findMaxValue(m_dataY); }
float Graph::findMinValueX() { return findMinValue(m_dataX); }
