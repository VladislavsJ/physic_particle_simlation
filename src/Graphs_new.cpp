#include "Graphs_new.hpp"
#include <algorithm> // for std::max_element, std::min_element
#include <string>

void Graph::updateData(float dataX, float dataY) {
  m_dataX.push_back(dataX);
  m_dataY.push_back(dataY);
  trimDataBuffers();
}

void Graph::trimDataBuffers() { // if data is too big, remove the oldest data
  if (m_dataX.size() > MAX_POINTS) {
    m_dataX.erase(m_dataX.begin(), m_dataX.end() - MAX_POINTS);
  }
  if (m_dataY.size() > MAX_POINTS) {
    m_dataY.erase(m_dataY.begin(), m_dataY.end() - MAX_POINTS);
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
