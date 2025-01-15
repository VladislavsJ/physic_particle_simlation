#ifndef GRAPHS_HPP
#define GRAPHS_HPP

#include <SFML/Graphics.hpp>
#include <vector>
# include "Renderer.hpp"

class Graph {
public:
Graph() = default;

    // Initialization method
    bool init(int inStartX, int inStartY, int inSizeX, int inSizeY, 
              float inValXMin = 0, float inValYMin = 0,
              float inValXMax = 0, float inValYMax = 0) {
        // Initialize member variables
        m_graphDrawStartX = inStartX;// start coordinates for the graph
        m_graphDrawStartY = inStartY;

        m_graphSizeX = inSizeX;//graph size
        m_graphSizeY = inSizeY;

        m_valXmin = inValXMin;
        m_valYmin = inValYMin;
        m_valXmax = inValXMax;
        m_valYmax = inValYMax;


        // Validate input parameters
        if (m_graphSizeX <= 0 || m_graphSizeY <= 0) {
            return false;
        }

        m_dataX.reserve(MAX_POINTS);
        m_dataY.reserve(MAX_POINTS);

        // Clear any existing data
        m_dataX.clear();
        m_dataY.clear();

        return true;
    }


    // Destructor
    ~Graph() = default;

    //bool init();

    // Push new measurements
    void updateData(float dataX, float dataY);
    // Render the graph may not be needed
    void render();
    float findMaxValueX();
    float findMinValueY();
    float findMaxValueY();
    float findMinValueX();
    // Poll events
    void pollEvents();
        // Axis ranges
    float m_valXmin;
    float m_valYmin;
    float m_valXmax;
    float m_valYmax;

    // Graph drawing area
    int m_graphDrawStartX;
    int m_graphDrawStartY;
    int m_graphSizeX;
    int m_graphSizeY; 
    //TODO1: graph_new and Renderer are strongly connected, maybe they should be merged, 
    //graph rendering should be done in the graph class
    std::vector<float> m_dataX;  // Store X values
    std::vector<float> m_dataY;  // Store Y values

private:

    // Max points we want to store for the graph
    static const size_t MAX_POINTS = 2000;

    // Drawing helper
    void drawLineGraph(const std::vector<float>& data, float maxValue, 
                       float offsetX, float offsetY, float width, float height, 
                       sf::Color color, bool isInteger = false);
    float findMaxValue(const std::vector<float>& data);
    float findMinValue(const std::vector<float>& data);
    void trimDataBuffers();
};

#endif
