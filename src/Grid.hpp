#ifndef Grid_HPP
#define Grid_HPP
#include "Particle.hpp"
#include <array>
#include <vector>
// This is function to maintain the grid with the particle pointers
//  now each grid cell has a vector of pointers to the particles
//  not memory efficient, as dense grid, but for now I am ussming that
//  is more CPU efficient than sorting the particles in the grid after each
//  frame to store them in dense array
enum CalcWindowIndex {
  TOP_LEFT = 0,
  TOP_CENTER = 1,
  TOP_RIGHT = 2,
  CENTER_LEFT = 3,
  CENTER = 4,
  CENTER_RIGHT = 5,
  BOTTOM_LEFT = 6,
  BOTTOM_CENTER = 7,
  BOTTOM_RIGHT = 8
};

class Grid {
public:
  Grid(int DispWidth, int DispHeight, int maxParticleSize);

  void addParticle(Particle *particle); // add particle to the new grid, old
                                        // grid is not updated

  // Adds a particle to the 'new' grid (m_grid_new) at a specific cell.
  void addParticle(Particle *particle, int m_gridNumberXY[2]);

  // Adds multiple particles by calling addParticle() on each.

  void addParticles(std::vector<Particle *> particles);

  // After all particles have been assigned to m_grid_new, swap it into m_grid.
  void updateGrid(); // swap old grid with new grid, and clear the old grid

  // Clears the CURRENT active grid m_grid (not m_grid_new).
  void clear();
  int getCols();
  int getRows();

  std::vector<Particle *> &getCell(int row, int col);
  std::vector<Particle *> &getCell(int gridNumberXY[2]);

  std::array<std::vector<Particle *> *, 8>
  getNeighbourCells(int m_gridNumberXY[2]); // 8 grids around the particle cell

  // Return references/pointers to the 9 cells (including the center)
  std::array<std::vector<Particle *> *, 9> get9Cells(int m_gridNumberXY[2]);
  std::vector<std::vector<std::vector<Particle *>>> m_grid;
  std::vector<std::vector<std::vector<Particle *>>> m_grid_new;

private:
  int m_width;    // Display width
  int m_height;   // Display height
  int m_cellSize; // 2*maxParticleSize(radius)
  int m_rows;
  int m_cols;
  // x y and particles vector
  // Each cell is a vector of pointers to Particle objects.

  // So m_grid is [rows][cols] -> vector<Particle*>
};
class CalcWindow {
public:
  explicit CalcWindow(Grid &grid);

  // Initialize the 3x3 window (centered at row,col)
  void InitWindow(int row, int col, bool shiftPriorityToRight = true);
  void InitWindow(int gridNumberXY[2], bool shiftPriority = true);
  // Shift window around for scanning
  void shiftLeft();
  void shiftRight();
  void shiftUp();
  void shiftDown();

  // "snake-like" iteration, to reuse the previous cells
  bool ShiftPriorityRight();
  bool ShiftPriorityLeft();
  bool Shift();
  // Access the array of pointers to neighbor cells
  std::array<std::vector<Particle *> *, 9> &getCalcWindow() {
    return m_calcWindow;
  }

  std::vector<Particle *> *getCell(CalcWindowIndex index);
  void setCellNumber(int m_gridNumberXY[2]);
  Grid &m_grid; // reference to the grid, to get the cells

private:
  int m_gridNumberXY[2];
  // Each of the 9 is a pointer to a vector<Particle*> in the grid.
  std::array<std::vector<Particle *> *, 9> m_calcWindow;
  bool m_movingRight;
  bool shiftPriorityToRight; // If true then ShiftPriorityRight else
                             // ShiftPriorityLeft
};
#endif