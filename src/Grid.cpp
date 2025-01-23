#include "Grid.hpp"
enum CalcWindowIndex;
Grid::Grid(int DispWidth, int DispHeight, int maxParticleSize)
    : m_width(DispWidth), m_height(DispHeight),
      m_cellSize(maxParticleSize * 2) {

  m_rows = ((m_width + (m_cellSize / 2)) / m_cellSize) +
           2; // round up, as the grid should be bigger than the display
  // to avoid the case when the edges of the particles are not in the grid
  //+2 for the case, then edge cell checks the particles in the next cell
  m_cols = ((m_height + (m_cellSize / 2)) / m_cellSize) + 2;
  //+2 for the case, then edge cell checks the particles in the next cell

  // Resize the 3D vector, and clean data
  int innerSize = maxParticleSize / 10; // just start size for each cell
  // TODO3: Resize efficiency is not checked, as mentioned that resize
  //  is waste of time, as a compiler "knows better"

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
  if (row < 0)
    row = 0;
  if (row >= m_rows)
    row = m_rows - 1;
  if (col < 0)
    col = 0;
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
  if (row < 0)
    row = 0;
  if (row >= m_rows)
    row = m_rows - 1;
  if (col < 0)
    col = 0;
  if (col >= m_cols)
    col = m_cols - 1;
  if (particle->getType() != 1) {
    //  std::cout << "DEBUG: " << row << " " << col << std::endl;
  }
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
  m_grid = std::move(m_grid_new);

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
  if (row < 0)
    row = 0;
  if (row >= m_rows)
    row = m_rows - 1;
  if (col < 0)
    col = 0;
  if (col >= m_cols)
    col = m_cols - 1;

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

CalcWindow::CalcWindow(Grid &grid) : m_grid(grid), m_movingRight(true) {
  // initialize the 9 pointers to nullptr
  for (auto &cellPtr : m_calcWindow) {
    cellPtr = nullptr;
  }
  m_gridNumberXY[0] = 1;
  m_gridNumberXY[1] = 1;
}

void CalcWindow::InitWindow(int row, int col) {
  m_gridNumberXY[0] = row;
  m_gridNumberXY[1] = col;

  // get all 9 cells
  auto allCells = m_grid.get9Cells(m_gridNumberXY);
  // store them
  for (int i = 0; i < 9; ++i) {
    m_calcWindow[i] = allCells[i];
  }
}

/*
Other method, same result
void m_calcWindow::InitWindow(int gridNumberXY[2]) {
  m_gridNumberXY[0] = gridNumberXY[0];
  m_gridNumberXY[1] = gridNumberXY[1];

  m_calcWindow[TOP_LEFT] =
      &m_grid.getCell(m_gridNumberXY[0] - 1, m_gridNumberXY[1] - 1);
  m_calcWindow[TOP_CENTER] =
      &m_grid.getCell(m_gridNumberXY[0] - 1, m_gridNumberXY[1]);
  m_calcWindow[TOP_RIGHT] =
      &m_grid.getCell(m_gridNumberXY[0] - 1, m_gridNumberXY[1] + 1);
  m_calcWindow[CENTER_LEFT] =
      &m_grid.getCell(m_gridNumberXY[0], m_gridNumberXY[1] - 1);
  m_calcWindow[CENTER] = &m_grid.getCell(m_gridNumberXY[0], m_gridNumberXY[1]);
  m_calcWindow[CENTER_RIGHT] =
      &m_grid.getCell(m_gridNumberXY[0], m_gridNumberXY[1] + 1);
  m_calcWindow[BOTTOM_LEFT] =
      &m_grid.getCell(m_gridNumberXY[0] + 1, m_gridNumberXY[1] - 1);
  m_calcWindow[BOTTOM_CENTER] =
      &m_grid.getCell(m_gridNumberXY[0] + 1, m_gridNumberXY[1]);
  m_calcWindow[BOTTOM_RIGHT] =
      &m_grid.getCell(m_gridNumberXY[0] + 1, m_gridNumberXY[1] + 1);
}*/

void CalcWindow::setCellNumber(int gridNumberXY[2]) {
  m_gridNumberXY[0] = gridNumberXY[0];
  m_gridNumberXY[1] = gridNumberXY[1];
  InitWindow(m_gridNumberXY);
}
std::vector<Particle *> *CalcWindow::getCell(CalcWindowIndex index) {
  return m_calcWindow[index];
}
// TODO3: check if Shift logic if more efficient than naive approach
/*
void m_calcWindow::shiftLeft()
{
    // Example naive approach: just re-init at col - 1
    m_gridNumberXY[1] -= 1;
    InitWindow(m_gridNumberXY[0], m_gridNumberXY[1]);
}
*/
// ALL this shif logic is needed to avoid memory allocation each time,
//  I can use 6 from 9 cells again.
//  InitWindow method (below in this file)
//  a bit slower 2070 vs 1950 particles,
//  but now my grid method is not really optimized

void CalcWindow::shiftLeft() {

  // Shift entire 9-cell window left
  m_calcWindow[TOP_RIGHT] = m_calcWindow[TOP_CENTER];
  m_calcWindow[TOP_CENTER] = m_calcWindow[TOP_LEFT];
  m_calcWindow[TOP_LEFT] =
      &m_grid.getCell(m_gridNumberXY[0] - 1, m_gridNumberXY[1] - 2);

  m_calcWindow[CENTER_RIGHT] = m_calcWindow[CENTER];
  m_calcWindow[CENTER] = m_calcWindow[CENTER_LEFT];
  m_calcWindow[CENTER_LEFT] =
      &m_grid.getCell(m_gridNumberXY[0], m_gridNumberXY[1] - 2);

  m_calcWindow[BOTTOM_RIGHT] = m_calcWindow[BOTTOM_CENTER];
  m_calcWindow[BOTTOM_CENTER] = m_calcWindow[BOTTOM_LEFT];
  m_calcWindow[BOTTOM_LEFT] =
      &m_grid.getCell(m_gridNumberXY[0] + 1, m_gridNumberXY[1] - 2);
}

void CalcWindow::shiftRight() {
  // Shift entire 9-cell window right
  m_calcWindow[TOP_LEFT] = m_calcWindow[TOP_CENTER];
  m_calcWindow[TOP_CENTER] = m_calcWindow[TOP_RIGHT];
  m_calcWindow[TOP_RIGHT] =
      &m_grid.getCell(m_gridNumberXY[0] - 1, m_gridNumberXY[1] + 2);

  m_calcWindow[CENTER_LEFT] = m_calcWindow[CENTER];
  m_calcWindow[CENTER] = m_calcWindow[CENTER_RIGHT];
  m_calcWindow[CENTER_RIGHT] =
      &m_grid.getCell(m_gridNumberXY[0], m_gridNumberXY[1] + 2);

  m_calcWindow[BOTTOM_LEFT] = m_calcWindow[BOTTOM_CENTER];
  m_calcWindow[BOTTOM_CENTER] = m_calcWindow[BOTTOM_RIGHT];
  m_calcWindow[BOTTOM_RIGHT] =
      &m_grid.getCell(m_gridNumberXY[0] + 1, m_gridNumberXY[1] + 2);
}

void CalcWindow::shiftUp() {
  // Shift entire 9-cell window up
  m_calcWindow[BOTTOM_LEFT] = m_calcWindow[CENTER_LEFT];
  m_calcWindow[CENTER_LEFT] = m_calcWindow[TOP_LEFT];
  m_calcWindow[TOP_LEFT] =
      &m_grid.getCell(m_gridNumberXY[0] - 2, m_gridNumberXY[1] - 1);

  m_calcWindow[BOTTOM_CENTER] = m_calcWindow[CENTER];
  m_calcWindow[CENTER] = m_calcWindow[TOP_CENTER];
  m_calcWindow[TOP_CENTER] =
      &m_grid.getCell(m_gridNumberXY[0] - 2, m_gridNumberXY[1]);

  m_calcWindow[BOTTOM_RIGHT] = m_calcWindow[CENTER_RIGHT];
  m_calcWindow[CENTER_RIGHT] = m_calcWindow[TOP_RIGHT];
  m_calcWindow[TOP_RIGHT] =
      &m_grid.getCell(m_gridNumberXY[0] - 2, m_gridNumberXY[1] + 1);
}

void CalcWindow::shiftDown() {
  // Shift entire 9-cell window down
  m_calcWindow[TOP_LEFT] = m_calcWindow[CENTER_LEFT];
  m_calcWindow[CENTER_LEFT] = m_calcWindow[BOTTOM_LEFT];
  m_calcWindow[BOTTOM_LEFT] =
      &m_grid.getCell(m_gridNumberXY[0] + 2, m_gridNumberXY[1] - 1);

  m_calcWindow[TOP_CENTER] = m_calcWindow[CENTER];
  m_calcWindow[CENTER] = m_calcWindow[BOTTOM_CENTER];
  m_calcWindow[BOTTOM_CENTER] =
      &m_grid.getCell(m_gridNumberXY[0] + 2, m_gridNumberXY[1]);

  m_calcWindow[TOP_RIGHT] = m_calcWindow[CENTER_RIGHT];
  m_calcWindow[CENTER_RIGHT] = m_calcWindow[BOTTOM_RIGHT];
  m_calcWindow[BOTTOM_RIGHT] =
      &m_grid.getCell(m_gridNumberXY[0] + 2, m_gridNumberXY[1] + 1);
}
// Shift logic, right->right->border->down->left->left->border->down->right etc
// to use previous cells, to not to allocate memory each time
// fancy code, to be sure that it is not a problem during the debug stage.

bool CalcWindow::Shift() {
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
    if (m_gridNumberXY[1] > 0) {
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
//
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