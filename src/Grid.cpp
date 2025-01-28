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
