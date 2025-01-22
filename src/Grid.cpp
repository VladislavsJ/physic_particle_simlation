#include "Grid.hpp"

Grid::Grid(int DispWidth, int DispHeight, int maxParticleSize)
    : m_width(DispWidth), m_height(DispHeight),
      m_cellSize(maxParticleSize * 2) {

  m_rows = ((m_width + (m_cellSize / 2)) / m_cellSize) +
           1; // round up, as the grid should be bigger than the display
  // to avoid the case when the edges of the particles are not in the grid
  //+1 for the case, then edge cell checks the particles in the next cell
  m_cols = (m_height + (m_cellSize / 2)) / m_cellSize;
  //+1 for the case, then edge cell checks the particles in the next cell

  // Resize the 3D vector, and clean data
  int innerSize = maxParticleSize / 10; // just start size for each cell
  // TODO3: Resize efficiency is not checked, as mentioned that resize
  //  is waste of time, as a compiler "knows better"
  m_grid.resize(m_rows);
  for (int i = 0; i < m_rows; ++i) {
    m_grid[i].resize(m_cols);
    for (int j = 0; j < m_cols; ++j) {
      m_grid[i][j].resize(innerSize,
                          nullptr); // Resize innermost vector with a specific
                                    // size and initialize with nullptr
    }
  }
  m_grid_new.resize(m_rows);
  for (int i = 0; i < m_rows; ++i) {
    m_grid_new[i].resize(m_cols);
    for (int j = 0; j < m_cols; ++j) {
      m_grid_new[i][j].resize(
          innerSize, nullptr); // Resize innermost vector with a specific size
                               // and initialize with nullptr
    }
  }
}
int Grid::getCols() { return m_cols; }
int Grid::getRows() { return m_rows; }
// REMEMBER: there is no additional items, grid edges should have different
// logic
Grid::clear() {
  for (int i = 0; i < m_rows; ++i) {
    for (int j = 0; j < m_cols; ++j) {
      m_grid[i][j].clear();
    }
  }
}
void Grid::addParticle(Particle *particle, int gridNumberXY[2]) {
  m_grid_new[gridNumberXY[0]][gridNumberXY[1]].push_back(particle);
}
void Grid::addParticle(Particle *particle) {
  int m_gridNumberXY[2];
  m_gridNumberXY[0] = particle->getPosition().x / m_cellSize;
  m_gridNumberXY[1] = particle->getPosition().y / m_cellSize;
  m_grid_new[gridNumberXY[0]][gridNumberXY[1]].push_back(particle);
}
void Grid::addParticles(std::vector<Particle *> particles) {
  for (auto particle : particles) {
    addParticle(particle);
  }
}
void Grid::updateGrid() {
  m_grid = move(m_grid_new);
  clear();
}
std::vector<Particle *> &Grid::getCell(int m_gridNumberXY[2]) {
  return m_grid[m_gridNumberXY[0]][m_gridNumberXY[1]];
}
std::array<std::vector<Particle *>, 8>
Grid::getNeighboursCells(int m_gridNumberXY[2]) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      neighbours[i * 3 + j] = &getNeighboursInCell(m_gridNumberXY[0] + i - 1,
                                                   m_gridNumberXY[1] + j - 1);
    }
  }
}
CalcWindow::CalcWindow(Grid &grid) : m_grid(grid) {
  for (int i = 0; i < 9; i++) {
    CalcWindow[i] = nullptr;
  }
}
std::array<std::vector<Particle *>, 9> &CalcWindow::getCalcWindow() {
  return CalcWindow;
}
void CalcWindow::setCellNumber(int gridNumberXY[2]) {
  m_gridNumberXY[0] = gridNumberXY[0];
  m_gridNumberXY[1] = gridNumberXY[1];
  InitWindow(m_gridNumberXY);
}
std::vector<Particle *> &CalcWindow::getCell(CalcWindowIndex index) {
  return CalcWindow[index];
}
void CalcWindow::InitWindow(int gridNumberXY[2]) {
  m_gridNumberXY[0] = gridNumberXY[0];
  m_gridNumberXY[1] = gridNumberXY[1];

  CalcWindow[TOP_LEFT] =
      &m_grid.getCell(m_gridNumberXY[0] - 1, m_gridNumberXY[1] - 1);
  CalcWindow[TOP_CENTER] =
      &m_grid.getCell(m_gridNumberXY[0] - 1, m_gridNumberXY[1]);
  CalcWindow[TOP_RIGHT] =
      &m_grid.getCell(m_gridNumberXY[0] - 1, m_gridNumberXY[1] + 1);
  CalcWindow[CENTER_LEFT] =
      &m_grid.getCell(m_gridNumberXY[0], m_gridNumberXY[1] - 1);
  CalcWindow[CENTER] = &m_grid.getCell(m_gridNumberXY[0], m_gridNumberXY[1]);
  CalcWindow[CENTER_RIGHT] =
      &m_grid.getCell(m_gridNumberXY[0], m_gridNumberXY[1] + 1);
  CalcWindow[BOTTOM_LEFT] =
      &m_grid.getCell(m_gridNumberXY[0] + 1, m_gridNumberXY[1] - 1);
  CalcWindow[BOTTOM_CENTER] =
      &m_grid.getCell(m_gridNumberXY[0] + 1, m_gridNumberXY[1]);
  CalcWindow[BOTTOM_RIGHT] =
      &m_grid.getCell(m_gridNumberXY[0] + 1, m_gridNumberXY[1] + 1);
}

void CalcWindow::ShiftLeft(std::vector<Particle *>[3]) {
  CalcWindow[CENTER_LEFT] =
      CalcWindow[CENTER]; // TODO3: does move() is useful there?
  CalcWindow[CENTER] = CalcWindow[CENTER_RIGHT];
  CalcWindow[CENTER_RIGHT] =
      &m_grid.getCell(m_gridNumberXY[0], m_gridNumberXY[1] + 1);
  CalcWindow[TOP_LEFT] = CalcWindow[TOP_CENTER];
  CalcWindow[TOP_CENTER] = CalcWindow[TOP_RIGHT];
  CalcWindow[TOP_RIGHT] =
      &m_grid.getCell(m_gridNumberXY[0] - 1, m_gridNumberXY[1] + 1);
  CalcWindow[BOTTOM_LEFT] = CalcWindow[BOTTOM_CENTER];
  CalcWindow[BOTTOM_CENTER] = CalcWindow[BOTTOM_RIGHT];
  CalcWindow[BOTTOM_RIGHT] =
      &m_grid.getCell(m_gridNumberXY[0] + 1, m_gridNumberXY[1] + 1);
}
void CalcWindow::ShiftRight(std::vector<Particle *>[3]) {
  CalcWindow[CENTER_RIGHT] =
      CalcWindow[CENTER]; // TODO3: does move() is useful there?
  CalcWindow[CENTER] = CalcWindow[CENTER_LEFT];
  CalcWindow[CENTER_LEFT] =
      &m_grid.getCell(m_gridNumberXY[0], m_gridNumberXY[1] - 1);
  CalcWindow[TOP_RIGHT] = CalcWindow[TOP_CENTER];
  CalcWindow[TOP_CENTER] = CalcWindow[TOP_LEFT];
  CalcWindow[TOP_LEFT] =
      &m_grid.getCell(m_gridNumberXY[0] - 1, m_gridNumberXY[1] - 1);
  CalcWindow[BOTTOM_RIGHT] = CalcWindow[BOTTOM_CENTER];
  CalcWindow[BOTTOM_CENTER] = CalcWindow[BOTTOM_LEFT];
  CalcWindow[BOTTOM_LEFT] =
      &m_grid.getCell(m_gridNumberXY[0] + 1, m_gridNumberXY[1] - 1);
}
void CalcWindow::ShiftUp(std::vector<Particle *>[3]) {
  CalcWindow[TOP_CENTER] =
      CalcWindow[CENTER]; // TODO3: does move() is useful there?
  CalcWindow[CENTER] = CalcWindow[BOTTOM_CENTER];
  CalcWindow[BOTTOM_CENTER] =
      &m_grid.getCell(m_gridNumberXY[0] + 1, m_gridNumberXY[1]);
  CalcWindow[TOP_LEFT] = CalcWindow[CENTER_LEFT];
  CalcWindow[CENTER_LEFT] = CalcWindow[BOTTOM_LEFT];
  CalcWindow[BOTTOM_LEFT] =
      &m_grid.getCell(m_gridNumberXY[0] + 1, m_gridNumberXY[1] - 1);
  CalcWindow[TOP_RIGHT] = CalcWindow[CENTER_RIGHT];
  CalcWindow[CENTER_RIGHT] = CalcWindow[BOTTOM_RIGHT];
  CalcWindow[BOTTOM_RIGHT] =
      &m_grid.getCell(m_gridNumberXY[0] + 1, m_gridNumberXY[1] + 1);
}
void CalcWindow::ShiftDown(std::vector<Particle *>[3]) {
  CalcWindow[BOTTOM_CENTER] =
      CalcWindow[CENTER]; // TODO3: does move() is useful there?
  CalcWindow[CENTER] = CalcWindow[TOP_CENTER];
  CalcWindow[TOP_CENTER] =
      &m_grid.getCell(m_gridNumberXY[0] - 1, m_gridNumberXY[1]);
  CalcWindow[BOTTOM_LEFT] = CalcWindow[CENTER_LEFT];
  CalcWindow[CENTER_LEFT] = CalcWindow[TOP_LEFT];
  CalcWindow[TOP_LEFT] =
      &m_grid.getCell(m_gridNumberXY[0] - 1, m_gridNumberXY[1] - 1);
  CalcWindow[BOTTOM_RIGHT] = CalcWindow[CENTER_RIGHT];
  CalcWindow[CENTER_RIGHT] = CalcWindow[TOP_RIGHT];
  CalcWindow[TOP_RIGHT] =
      &m_grid.getCell(m_gridNumberXY[0] - 1, m_gridNumberXY[1] + 1);
}
// Shift logic, right->right->border->down->left->left->border->down->right etc
// to use previous cells, to not to allocate memory each time
bool CalcWindow::Shift() {
  if (m_gridNumberXY[0] == 0) {
    if (m_gridNumberXY[1] == 0) {
      ShiftRight();
      return true;
    }
  }
  return false;
}
bool CalcWindow::Shift() {
  static bool movingRight = true;
  // Attempt horizontal moves first
  if (movingRight) {
    if (m_gridNumberXY[1] < m_grid.getCols() - 1) {
      ShiftRight();
      m_gridNumberXY[1]++;
      return true;
    } else if (m_gridNumberXY[0] < m_grid.getRows() - 1) {
      m_gridNumberXY[0]++;
      movingRight = false;
      return true;
    }
  } else {
    if (m_gridNumberXY[1] > 0) {
      ShiftLeft();
      m_gridNumberXY[1]--;
      return true;
    } else if (m_gridNumberXY[0] < m_grid.getRows() - 1) {
      m_gridNumberXY[0]++;
      movingRight = true;
      return true;
    }
  }
  return false; // if not possible to move,(if no bugs, means that it is the end
                // of the grid)
}