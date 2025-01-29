
#ifndef CALC_WINDOW_HPP
#define CALC_WINDOW_HPP

#include "Grid.hpp"
#include "PS_ThreadManager.hpp"
#include <utility>
struct ThreadData;
class CalcWindow {

public:
  explicit CalcWindow(Grid &grid);

  // Initialize the 3x3 window (centered at row,col)
  void InitWindow(ThreadData td, bool shiftPriorityToRight = true);
  void InitWindow(int row, int col);
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

  std::array<std::vector<Particle *> *, 9> &getCalcWindow();

  std::vector<Particle *> *getCell(CalcWindowIndex index);
  void setCellNumber(int m_gridNumberRowCol[2]);
  Grid &m_grid; // reference to the grid, to get the cells
  int m_gridNumberRowCol[2];
  std::vector<std::pair<int, int>> getCalcPath(int threadId, ThreadData td,
                                               int CellCnt);
  bool ShiftOnlyLeft();

private:
  // Each of the 9 is a pointer to a vector<Particle*> in the grid.
  std::array<std::vector<Particle *> *, 9> m_calcWindow;
  bool m_movingRight;
  bool shiftPriorityToRight; // If true then ShiftPriorityRight else
};

#endif // CALC_WINDOW_HPP
