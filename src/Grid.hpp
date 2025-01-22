#ifndef Grid_HPP
#define Grid_H
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
  TOP_CENTER,
  TOP_RIGHT,
  CENTER_LEFT,
  CENTER,
  CENTER_RIGHT,
  BOTTOM_LEFT,
  BOTTOM_CENTER,
  BOTTOM_RIGHT
};

class Grid {
public:
  Grid(int DispWidth, int DispHeight, int maxParticleSize);
  void addParticle(Particle *particle); // add particle to the new grid, old
                                        // grid is not updated

  // every time then this function is called, caller know the position of the
  // particle

  void addParticles(
      std::vector<Particle *>
          particles); // add particles to the new grid, old grid is not updated
  void addParticle(Particle *particle,
                   int m_gridNumberXY[2]); // will add particle to the specific
                                           // cell in new grid
  void updateGrid(); // swap old grid with new grid, and clear the old grid
  void clear();
  int getCols();
  int getRows();
  // TODO3: Check the pointer and particle copy efficieny, maybe I should use
  // reference std::vector<Particle*>& getNeighboursInCell(int
  // m_gridNumberXY[2]); // particle is in the grid
  std::array<std::vector<Particle *>, 8> &
  getNeighboursCells(int m_gridNumberXY[2]); // 8 grids around the particle
  std::array<std::vector<Particle *>, 9> &get9Cells(Pint m_gridNumberXY[2]);
  std::vector<Particle *> &getCell(int m_gridNumberXY[2]);

private:
  // int getGridSize();
  int m_width;
  int m_height;
  int m_cellSize; // 2*maxParticleSize(radius)
  int m_rows;
  int m_cols;
  // x y and particles vector
  std::vector<std::vector<std::vector<*Particle>>>
      m_grid; // 3D vector, each cell contains a vector of particles pointers
  std::vector < std::vector <
      std::vector<*Particle> m_grid_new; // 3D vector, each cell contains a
                                         // vector of particles pointers
};

class CalcWindow {
public:
  std::vector<Particle *> CalcWindow[9] std::array<std::vector<Particle *>, 9> &
  getCalcWindow();
  void InitWindow(int m_gridNumberXY[2]); // XY is the middle coordinate
  // if there is more than 1 thread to calculate the forces, then each thread
  // should have its own CalcWindow
  void shiftRight(std::vector<Particle *>[3]);
  void shiftLeft(std::vector<Particle *>[3]);
  void shiftUp(std::vector<Particle *>[3]);
  void shiftDown(std::vector<Particle *>[3]);
  void setCellNumber(int m_gridNumberXY[2]);
  bool Shift();
  // Shift logic, right->right->border->down->left->left->border->down->right
  // etc to use previous cells, to not to allocate memory each time

  std::vector<Particle *> getCell(CalcWindowIndex);

private:
  int m_gridNumberXY[2];
  std::array<std::vector<Particle *>, 8>
      neighbours; // to not to allocate memory each time
  Grid m_grid &;  // reference to the grid, to get the cells
};
enum CalcWindowIndex {
  TOP_LEFT = 0,
  TOP_CENTER,
  TOP_RIGHT,
  CENTER_LEFT,
  CENTER,
  CENTER_RIGHT,
  BOTTOM_LEFT,
  BOTTOM_CENTER,
  BOTTOM_RIGHT,
  COUNT // Helper to represent the total number of entries
};
#endif