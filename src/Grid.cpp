#include "Grid.hpp"

enum CalcWindowIndex;
Grid::Grid(int DispWidth, int DispHeight, int maxParticleSize)
    : m_width(DispWidth), m_height(DispHeight),
      m_cellSize(maxParticleSize * 2) {

  m_rows = ((m_width + (m_cellSize / 2)) / m_cellSize) + 2;
  //+2 for the case, then edge cell checks the particles in the next cell
  m_cols = ((m_height + (m_cellSize / 2)) / m_cellSize) + 2;
  //+2 for the case, then edge cell checks the particles in the next cell

  // Resize both grids
  m_grid.resize(m_rows);
  m_grid_new.resize(m_rows);
  for (int r = 0; r < m_rows; ++r) {
    m_grid[r].resize(m_cols);
    m_grid_new[r].resize(m_cols);
  }
}

void Grid::clear() {
  // clear current (m_grid) cells
  for (int r = 0; r < m_rows; ++r) {
    for (int c = 0; c < m_cols; ++c) {
      m_grid[r][c].clear();
    }
  }
}

int Grid::getCols() { return m_cols; }
int Grid::getRows() { return m_rows; }

void Grid::addParticle(Particle *particle, int gridNumberXY[2]) {
  int row = gridNumberXY[0];
  int col = gridNumberXY[1];
  row++;
  col++;
  // clamp just to be safe, that particle is not out of bounds
  if (row < 1)
    row = 1;
  if (row >= m_rows)
    row = m_rows - 1;
  if (col < 1)
    col = 1;
  if (col >= m_cols)
    col = m_cols - 1;
  if (particle->getType() != 1) {
    //   std::cout << "DEBUG: " << row << " " << col << std::endl;
  }
  m_grid_new[row][col].push_back(particle);
}

void Grid::addParticle(Particle *particle) {
  auto pos = particle->getPosition();
  int col = static_cast<int>(pos.x) / m_cellSize;
  int row = static_cast<int>(pos.y) / m_cellSize;
  col++;
  row++; // borders are "dummy" cells
  if (row < 1)
    row = 1;
  if (row >= m_rows - 2)
    row = m_rows - 2;
  if (col < 1)
    col = 1;
  if (col >= m_cols - 2)
    col = m_cols - 2;

  m_grid_new[row][col].push_back(particle);
}
void Grid::addParticles(std::vector<Particle *> particles) {
  for (auto p : particles) {
    addParticle(p);
  }
}
void Grid::updateGrid() {
  // Move m_grid_new into m_grid
  // Then re-init m_grid_new
  std::swap(m_grid, m_grid_new);
  // Re-allocate m_grid_new so it is empty but has correct structure
  m_grid_new.clear();
  m_grid_new.resize(m_rows);
  for (int r = 0; r < m_rows; ++r) {
    m_grid_new[r].resize(m_cols);
  }
}

std::vector<Particle *> &Grid::getCell(int row, int col) {
  // clamp
  row;
  col;
  if (row < 1)
    row = 1;
  if (row >= m_rows - 2)
    row = m_rows - 2;
  if (col < 1)
    col = 1;
  if (col >= m_cols - 2)
    col = m_cols - 2;

  return m_grid[row][col];
}

std::vector<Particle *> &Grid::getCell(int gridNumberXY[2]) {
  return getCell(gridNumberXY[0], gridNumberXY[1]);
}

// Return the 8 neighboring cells around the cell (r,c).
// We skip the center cell
std::array<std::vector<Particle *> *, 8>
Grid::getNeighbourCells(int gridNumberXY[2]) {
  std::array<std::vector<Particle *> *, 8> neighbors;
  int row = gridNumberXY[0];
  int col = gridNumberXY[1];

  // Offsets for 8 neighbors
  int index = 0;
  for (int dr = -1; dr <= 1; ++dr) {
    for (int dc = -1; dc <= 1; ++dc) {
      if (dr == 0 && dc == 0)
        continue; // skip the center
      neighbors[index++] = &getCell(row + dr, col + dc);
    }
  }
  return neighbors;
}

// Return the 9 cells (including center).
std::array<std::vector<Particle *> *, 9> Grid::get9Cells(int gridNumberXY[2]) {
  std::array<std::vector<Particle *> *, 9> cells;
  int row = gridNumberXY[0];
  int col = gridNumberXY[1];

  int index = 0;
  for (int dr = -1; dr <= 1; ++dr) {
    for (int dc = -1; dc <= 1; ++dc) {
      cells[index++] = &getCell(row + dr, col + dc);
    }
  }
  return cells;
}

// -------------------------------------------------
// m_calcWindow Implementation
// -------------------------------------------------

CalcWindow::CalcWindow(Grid &grid) : m_grid(grid) {
  // initialize the 9 pointers to nullptr
  for (auto &cellPtr : m_calcWindow) {
    cellPtr = nullptr;
  }
  m_gridNumberXY[0] = 1;
  m_gridNumberXY[1] = 1;
}

void CalcWindow::InitWindow(int row, int col, bool shiftPriorityR) {
  m_gridNumberXY[0] = row;
  m_gridNumberXY[1] = col;
  shiftPriorityToRight = shiftPriorityR;
  m_movingRight = shiftPriorityR;
  // get all 9 cells
  auto allCells = m_grid.get9Cells(m_gridNumberXY);
  // store them
  for (int i = 0; i < 9; ++i) {
    m_calcWindow[i] = allCells[i];
  }
}
void CalcWindow::InitWindow(int gridNumberXY[2], bool shiftPriority) {
  InitWindow(gridNumberXY[0], gridNumberXY[1], shiftPriority);
}
bool CalcWindow::Shift() {
  if (shiftPriorityToRight) {
    return ShiftPriorityRight();
  } else {
    return ShiftPriorityLeft();
  }
}
std::vector<Particle *> *CalcWindow::getCell(CalcWindowIndex index) {
  return m_calcWindow[index];
}

// ALL this shif logic is needed to avoid memory allocation each time,
//  I can use 6 from 9 cells again.
//  InitWindow method (below in this file)
//  a bit slower 2070 vs 1950 particles,
//  but now my grid method is not really optimized

void CalcWindow::shiftLeft() {
  // Shift entire 9-cell window left using move()
  m_calcWindow[TOP_RIGHT] = std::move(m_calcWindow[TOP_CENTER]);
  m_calcWindow[TOP_CENTER] = std::move(m_calcWindow[TOP_LEFT]);
  m_calcWindow[TOP_LEFT] =
      &m_grid.getCell(m_gridNumberXY[0] - 1, m_gridNumberXY[1] - 2);

  m_calcWindow[CENTER_RIGHT] = std::move(m_calcWindow[CENTER]);
  m_calcWindow[CENTER] = std::move(m_calcWindow[CENTER_LEFT]);
  m_calcWindow[CENTER_LEFT] =
      &m_grid.getCell(m_gridNumberXY[0], m_gridNumberXY[1] - 2);

  m_calcWindow[BOTTOM_RIGHT] = std::move(m_calcWindow[BOTTOM_CENTER]);
  m_calcWindow[BOTTOM_CENTER] = std::move(m_calcWindow[BOTTOM_LEFT]);
  m_calcWindow[BOTTOM_LEFT] =
      &m_grid.getCell(m_gridNumberXY[0] + 1, m_gridNumberXY[1] - 2);
}

void CalcWindow::shiftRight() {
  // Shift entire 9-cell window right using move()
  m_calcWindow[TOP_LEFT] = std::move(m_calcWindow[TOP_CENTER]);
  m_calcWindow[TOP_CENTER] = std::move(m_calcWindow[TOP_RIGHT]);
  m_calcWindow[TOP_RIGHT] =
      &m_grid.getCell(m_gridNumberXY[0] - 1, m_gridNumberXY[1] + 2);

  m_calcWindow[CENTER_LEFT] = std::move(m_calcWindow[CENTER]);
  m_calcWindow[CENTER] = std::move(m_calcWindow[CENTER_RIGHT]);
  m_calcWindow[CENTER_RIGHT] =
      &m_grid.getCell(m_gridNumberXY[0], m_gridNumberXY[1] + 2);

  m_calcWindow[BOTTOM_LEFT] = std::move(m_calcWindow[BOTTOM_CENTER]);
  m_calcWindow[BOTTOM_CENTER] = std::move(m_calcWindow[BOTTOM_RIGHT]);
  m_calcWindow[BOTTOM_RIGHT] =
      &m_grid.getCell(m_gridNumberXY[0] + 1, m_gridNumberXY[1] + 2);
}

void CalcWindow::shiftUp() {
  // Shift entire 9-cell window up using move()
  m_calcWindow[BOTTOM_LEFT] = std::move(m_calcWindow[CENTER_LEFT]);
  m_calcWindow[CENTER_LEFT] = std::move(m_calcWindow[TOP_LEFT]);
  m_calcWindow[TOP_LEFT] =
      &m_grid.getCell(m_gridNumberXY[0] - 2, m_gridNumberXY[1] - 1);

  m_calcWindow[BOTTOM_CENTER] = std::move(m_calcWindow[CENTER]);
  m_calcWindow[CENTER] = std::move(m_calcWindow[TOP_CENTER]);
  m_calcWindow[TOP_CENTER] =
      &m_grid.getCell(m_gridNumberXY[0] - 2, m_gridNumberXY[1]);

  m_calcWindow[BOTTOM_RIGHT] = std::move(m_calcWindow[CENTER_RIGHT]);
  m_calcWindow[CENTER_RIGHT] = std::move(m_calcWindow[TOP_RIGHT]);
  m_calcWindow[TOP_RIGHT] =
      &m_grid.getCell(m_gridNumberXY[0] - 2, m_gridNumberXY[1] + 1);
}

void CalcWindow::shiftDown() {
  // Shift entire 9-cell window down using move()
  m_calcWindow[TOP_LEFT] = std::move(m_calcWindow[CENTER_LEFT]);
  m_calcWindow[CENTER_LEFT] = std::move(m_calcWindow[BOTTOM_LEFT]);
  m_calcWindow[BOTTOM_LEFT] =
      &m_grid.getCell(m_gridNumberXY[0] + 2, m_gridNumberXY[1] - 1);

  m_calcWindow[TOP_CENTER] = std::move(m_calcWindow[CENTER]);
  m_calcWindow[CENTER] = std::move(m_calcWindow[BOTTOM_CENTER]);
  m_calcWindow[BOTTOM_CENTER] =
      &m_grid.getCell(m_gridNumberXY[0] + 2, m_gridNumberXY[1]);

  m_calcWindow[TOP_RIGHT] = std::move(m_calcWindow[CENTER_RIGHT]);
  m_calcWindow[CENTER_RIGHT] = std::move(m_calcWindow[BOTTOM_RIGHT]);
  m_calcWindow[BOTTOM_RIGHT] =
      &m_grid.getCell(m_gridNumberXY[0] + 2, m_gridNumberXY[1] + 1);
}

// Shift logic, right->right->border->down->left->left->border->down->right etc
// to use previous cells, to not to allocate memory each time
// fancy code, to be sure that it is not a problem during the debug stage.

// I need ShiftPriorityRight and ShiftPriorityLeft
//  becaune in MPI version, idea is that some cells had more particles than
//  others and if 2 threads start from left and right then if one ended earlier
//  I can add more cells to compute.
//  it is not perfect solution, as there is around 10 threads, most particles
//  are on the bottom (thanks to the gravity) but it is a good start,

bool CalcWindow::ShiftPriorityRight() {
  // Attempt horizontal moves first
  if (m_movingRight) {
    if (m_gridNumberXY[1] < m_grid.getCols() - 1) {
      shiftRight();
      m_gridNumberXY[1]++;
      return true;
    } else if (m_gridNumberXY[0] < m_grid.getRows() - 1) {
      m_gridNumberXY[0]++;
      shiftDown();
      m_movingRight = false;
      return true;
    }
  } else {
    if (m_gridNumberXY[1] > 1) {
      shiftLeft();
      m_gridNumberXY[1]--;
      return true;
    } else if (m_gridNumberXY[0] < m_grid.getRows() - 1) {
      m_gridNumberXY[0]++;
      shiftDown();
      m_movingRight = true;
      return true;
    }
  }
  return false; // if not possible to move,(if no bugs, means that it is the end
                // of the grid)
}

bool CalcWindow::ShiftPriorityLeft() {
  // Attempt horizontal moves first
  if (!m_movingRight) {
    if (m_gridNumberXY[1] > 1) {
      shiftLeft();
      m_gridNumberXY[1]--;
      return true;
    } else if (m_gridNumberXY[0] < m_grid.getRows() - 1) {
      m_gridNumberXY[0]++;
      shiftDown();
      m_movingRight = true;
      return true;
    }
  } else {
    if (m_gridNumberXY[1] < m_grid.getCols() - 1) {
      shiftRight();
      m_gridNumberXY[1]++;
      return true;
    } else if (m_gridNumberXY[0] < m_grid.getRows() - 1) {
      m_gridNumberXY[0]++;
      shiftDown();
      m_movingRight = false;
      return true;
    }
  }
  return false; // if not possible to move,(if no bugs, means that it is the end
                // of the grid)
}
// Not so fancy  Shift() logic, +- 5% less efficient
/*
bool CalcWindow::Shift() {
  // If we are moving right:
  // std::cout << "m_gridNumberXY[0]: " << m_gridNumberXY[0]
  //          << " m_gridNumberXY[1]: " << m_gridNumberXY[1] << std::endl;
  if (m_gridNumberXY[0] >= 10) {
    // std::cout << "m_gridNumberXY[0]: " << m_gridNumberXY[0];
  }

  if (m_movingRight) {
    // If there's room to move one column right:
    if (m_gridNumberXY[1] < m_grid.getCols() - 1) {
      m_gridNumberXY[1]++;
      InitWindow(m_gridNumberXY[0], m_gridNumberXY[1]);
      return true;
    }
    // Otherwise move one row down if possible,
    // then flip direction to "moving left"
    else if (m_gridNumberXY[0] < m_grid.getRows() - 1) {
      m_gridNumberXY[0]++;
      m_movingRight = false;
      InitWindow(m_gridNumberXY[0], m_gridNumberXY[1]);
      return true;
    }
  }
  // If we are moving left:
  else {
    if (m_gridNumberXY[1] > 0) {
      m_gridNumberXY[1]--;
      InitWindow(m_gridNumberXY[0], m_gridNumberXY[1]);
      return true;
    } else if (m_gridNumberXY[0] < m_grid.getRows() - 1) {
      m_gridNumberXY[0]++;
      m_movingRight = true;
      InitWindow(m_gridNumberXY[0], m_gridNumberXY[1]);
      return true;
    }
  }

  // If neither is possible, we're at the bottom
  return false;
}


*/