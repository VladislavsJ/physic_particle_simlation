
#include "Grid.hpp"

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

  std::array<std::vector<Particle *> *, 9> &getCalcWindow();

  std::vector<Particle *> *getCell(CalcWindowIndex index);
  void setCellNumber(int m_gridNumberRowCol[2]);
  Grid &m_grid; // reference to the grid, to get the cells
  int m_gridNumberRowCol[2];
  // std::vector < pair<int, int>> getThreadCells(int threadId, );

private:
  // Each of the 9 is a pointer to a vector<Particle*> in the grid.
  std::array<std::vector<Particle *> *, 9> m_calcWindow;
  bool m_movingRight;
  bool shiftPriorityToRight; // If true then ShiftPriorityRight else
                             // ShiftPriorityLeft

  // std::vector<pair<int, int>> RowCol; // To get all cell list, for each
  // thread
};
