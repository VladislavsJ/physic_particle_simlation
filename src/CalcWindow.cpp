#include "CalcWindow.hpp"
// -------------------------------------------------
// m_calcWindow Implementation
// -------------------------------------------------
CalcWindow::CalcWindow(Grid &grid) : m_grid(grid) {
  // initialize the 9 pointers to nullptr
  for (auto &cellPtr : m_calcWindow) {
    cellPtr = nullptr;
  }
  m_gridNumberRowCol[0] = 1;
  m_gridNumberRowCol[1] = 1;
}

void CalcWindow::InitWindow(ThreadData td, bool shiftPriorityR) {
  m_gridNumberRowCol[0] = td.endRow;
  m_gridNumberRowCol[1] = td.endColl;
  shiftPriorityToRight = shiftPriorityR;
  m_movingRight = shiftPriorityR;
  // get all 9 cells
  auto allCells = m_grid.get9Cells(m_gridNumberRowCol);
  // store them
  for (int i = 0; i < 9; ++i) {
    m_calcWindow[i] = allCells[i];
  }
}
void CalcWindow::InitWindow(int row, int col) {
  m_gridNumberRowCol[0] = row;
  m_gridNumberRowCol[1] = col;
  auto allCells = m_grid.get9Cells(m_gridNumberRowCol);
  // store them
  for (int i = 0; i < 9; ++i) {
    m_calcWindow[i] = allCells[i];
  }
}

bool CalcWindow::Shift() {

  // std::cout << " Coodrdinate is " << (int)m_gridNumberRowCol[0] << " "
  //           << (int)m_gridNumberRowCol[1] << std::endl;
  /* LOGIC WAS CHANGED, ShiftPriorityRight and left are not used anymore
  if (shiftPriorityToRight) {
    return ShiftPriorityRight();
  } else {
    return ShiftPriorityLeft();
  }
  */
  return ShiftOnlyLeft();
}
std::vector<Particle *> *CalcWindow::getCell(CalcWindowIndex index) {
  return m_calcWindow[index];
}

// ALL this shif logic is needed to avoid memory allocation each time,
//  I can use 6 from 9 cells again.
//  InitWindow method (below in this file)
//  a bit slower 2070 vs 1950 particles,
//  but now my grid method is not really optimized
std::array<std::vector<Particle *> *, 9> &CalcWindow::getCalcWindow() {
  return m_calcWindow;
}
void CalcWindow::shiftLeft() {
  // Shift entire 9-cell window left using move()
  m_calcWindow[TOP_RIGHT] = std::move(m_calcWindow[TOP_CENTER]);
  m_calcWindow[TOP_CENTER] = std::move(m_calcWindow[TOP_LEFT]);
  m_calcWindow[TOP_LEFT] =
      &m_grid.getCell(m_gridNumberRowCol[0] - 1, m_gridNumberRowCol[1] - 2);

  m_calcWindow[CENTER_RIGHT] = std::move(m_calcWindow[CENTER]);
  m_calcWindow[CENTER] = std::move(m_calcWindow[CENTER_LEFT]);
  m_calcWindow[CENTER_LEFT] =
      &m_grid.getCell(m_gridNumberRowCol[0], m_gridNumberRowCol[1] - 2);

  m_calcWindow[BOTTOM_RIGHT] = std::move(m_calcWindow[BOTTOM_CENTER]);
  m_calcWindow[BOTTOM_CENTER] = std::move(m_calcWindow[BOTTOM_LEFT]);
  m_calcWindow[BOTTOM_LEFT] =
      &m_grid.getCell(m_gridNumberRowCol[0] + 1, m_gridNumberRowCol[1] - 2);
  m_gridNumberRowCol[1]--;
}

void CalcWindow::shiftRight() {

  // Shift entire 9-cell window right using move()
  m_calcWindow[TOP_LEFT] = std::move(m_calcWindow[TOP_CENTER]);
  m_calcWindow[TOP_CENTER] = std::move(m_calcWindow[TOP_RIGHT]);
  m_calcWindow[TOP_RIGHT] =
      &m_grid.getCell(m_gridNumberRowCol[0] - 1, m_gridNumberRowCol[1] + 2);

  m_calcWindow[CENTER_LEFT] = std::move(m_calcWindow[CENTER]);
  m_calcWindow[CENTER] = std::move(m_calcWindow[CENTER_RIGHT]);
  m_calcWindow[CENTER_RIGHT] =
      &m_grid.getCell(m_gridNumberRowCol[0], m_gridNumberRowCol[1] + 2);

  m_calcWindow[BOTTOM_LEFT] = std::move(m_calcWindow[BOTTOM_CENTER]);
  m_calcWindow[BOTTOM_CENTER] = std::move(m_calcWindow[BOTTOM_RIGHT]);
  m_calcWindow[BOTTOM_RIGHT] =
      &m_grid.getCell(m_gridNumberRowCol[0] + 1, m_gridNumberRowCol[1] + 2);
  m_gridNumberRowCol[1]++;
}

void CalcWindow::shiftUp() {
  // Shift entire 9-cell window up using move()
  m_calcWindow[BOTTOM_LEFT] = std::move(m_calcWindow[CENTER_LEFT]);
  m_calcWindow[CENTER_LEFT] = std::move(m_calcWindow[TOP_LEFT]);
  m_calcWindow[TOP_LEFT] =
      &m_grid.getCell(m_gridNumberRowCol[0] - 2, m_gridNumberRowCol[1] - 1);

  m_calcWindow[BOTTOM_CENTER] = std::move(m_calcWindow[CENTER]);
  m_calcWindow[CENTER] = std::move(m_calcWindow[TOP_CENTER]);
  m_calcWindow[TOP_CENTER] =
      &m_grid.getCell(m_gridNumberRowCol[0] - 2, m_gridNumberRowCol[1]);

  m_calcWindow[BOTTOM_RIGHT] = std::move(m_calcWindow[CENTER_RIGHT]);
  m_calcWindow[CENTER_RIGHT] = std::move(m_calcWindow[TOP_RIGHT]);
  m_calcWindow[TOP_RIGHT] =
      &m_grid.getCell(m_gridNumberRowCol[0] - 2, m_gridNumberRowCol[1] + 1);
  m_gridNumberRowCol[0]--;
}

void CalcWindow::shiftDown() {
  // Shift entire 9-cell window down using move()
  m_calcWindow[TOP_LEFT] = std::move(m_calcWindow[CENTER_LEFT]);
  m_calcWindow[CENTER_LEFT] = std::move(m_calcWindow[BOTTOM_LEFT]);
  m_calcWindow[BOTTOM_LEFT] =
      &m_grid.getCell(m_gridNumberRowCol[0] + 2, m_gridNumberRowCol[1] - 1);

  m_calcWindow[TOP_CENTER] = std::move(m_calcWindow[CENTER]);
  m_calcWindow[CENTER] = std::move(m_calcWindow[BOTTOM_CENTER]);
  m_calcWindow[BOTTOM_CENTER] =
      &m_grid.getCell(m_gridNumberRowCol[0] + 2, m_gridNumberRowCol[1]);

  m_calcWindow[TOP_RIGHT] = std::move(m_calcWindow[CENTER_RIGHT]);
  m_calcWindow[CENTER_RIGHT] = std::move(m_calcWindow[BOTTOM_RIGHT]);
  m_calcWindow[BOTTOM_RIGHT] =
      &m_grid.getCell(m_gridNumberRowCol[0] + 2, m_gridNumberRowCol[1] + 1);
  m_gridNumberRowCol[0]++;
}

bool CalcWindow::ShiftOnlyLeft() { // ShiftOnlyLeft and getCalcPath code should
  // be changed together

  // DEBUG COUT
  // std::cout << m_gridNumberRowCol[0] << " " << m_gridNumberRowCol[1]
  //          << std::endl;
  if (m_gridNumberRowCol[1] > 1) {
    shiftLeft();
    return true;
  } else if (m_gridNumberRowCol[0] > 1) {
    // if one row is calculated, then
    // start from the next row end, and move left
    m_gridNumberRowCol[0]--;
    m_gridNumberRowCol[1] = m_grid.getCols() - 2;
    auto allCells = m_grid.get9Cells(m_gridNumberRowCol);
    for (int i = 0; i < 9; ++i) {
      m_calcWindow[i] = allCells[i];
    }
    return true;
  }
  throw std::runtime_error(
      "No more cells to calculate"); // if error occurs, means that expected
                                     // cell cnt and real one is not equal
  return false;
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
  // -RIGHT - (border)DOWN - LEFT - (border)DOWN - RIGHT
  // Attempt horizontal moves first
  if (m_movingRight) {
    if (m_gridNumberRowCol[1] < m_grid.getCols() - 2) {
      shiftRight();
      return true;
    } else if (m_gridNumberRowCol[0] < m_grid.getRows() - 2) {

      shiftDown();
      m_movingRight = false;
      return true;
    }
  } else {
    if (m_gridNumberRowCol[1] > 1) {
      shiftLeft();
      return true;
    } else if (m_gridNumberRowCol[0] < m_grid.getRows() - 2) {
      shiftDown();

      m_movingRight = true;
      return true;
    }
  }
  return false; // if not possible to move,(if no bugs, means that it is the end
                // of the grid)
}

bool CalcWindow::ShiftPriorityLeft() { // LEFT-(border)UP-RIGHT-(border)UP-LEFT
  // Attempt horizontal moves first
  if (!m_movingRight) {
    if (m_gridNumberRowCol[1] > 1) {
      shiftLeft();
      return true;
    } else if (m_gridNumberRowCol[0] > 1) {
      shiftUp();
      m_movingRight = true;
      return true;
    }
  } else {
    if (m_gridNumberRowCol[1] < m_grid.getCols() - 2) {
      shiftRight();
      return true;
    } else if (m_gridNumberRowCol[0] > 1) {
      shiftUp();
      m_movingRight = false;
      return true;
    }
  }
  return false;
}
// I need two methods, first check if next cell is "neighbour", if yes, then
// reuse cells, if not, then get all 9 cells, it will make fragmented cells more
// efficient,
std::vector<std::pair<int, int>>
CalcWindow::getCalcPath(int threadId, ThreadData td, int CellCnt) {

  int RowCol[2];
  RowCol[0] = td.startRow;
  RowCol[1] = td.startColl;
  std::vector<std::pair<int, int>> CellCoordinates;
  int CellToCalculate = CellCnt;
  // this is the same shifting logic like in SHIFT, but I need to store all the
  // cells to make efficinet multithread cell sharing
  // and error-safe,
  // I will transfer this pairs to other threads if they finish earlier

  while (CellToCalculate-- > 0) {
    CellCoordinates.push_back(std::make_pair(RowCol[0], RowCol[1]));
    if (RowCol[1] < m_grid.getCols() - 2) {
      RowCol[1]++;
      continue;
    } else if (RowCol[0] < m_grid.getRows() - 2) {

      RowCol[0]++;
      RowCol[1] = 1;
    } else {
      break;
    }
  }
  if (CellCoordinates.size() == 0) {
    throw std::invalid_argument("no cells to compute");
  } else if (CellCoordinates.size() != CellCnt) {
    throw std::invalid_argument("cacl cell vector is not equal to CellCnt");
  }
  return CellCoordinates;
  // if not possible to move, return false
}

// Not so fancy  Shift() logic, +- 5% less  total efficiency
/*
bool CalcWindow::Shift() {
  // If we are moving right:
  // std::cout << "m_gridNumberRowCol[0]: " << m_gridNumberRowCol[0]
  //          << " m_gridNumberRowCol[1]: " << m_gridNumberRowCol[1] <<
std::endl; if (m_gridNumberRowCol[0] >= 10) {
    // std::cout << "m_gridNumberRowCol[0]: " << m_gridNumberRowCol[0];
  }

  if (m_movingRight) {
    // If there's room to move one column right:
    if (m_gridNumberRowCol[1] < m_grid.getCols() - 1) {
      m_gridNumberRowCol[1]++;
      InitWindow(m_gridNumberRowCol[0], m_gridNumberRowCol[1]);
      return true;
    }
    // Otherwise move one row down if possible,
    // then flip direction to "moving left"
    else if (m_gridNumberRowCol[0] < m_grid.getRows() - 1) {
      m_gridNumberRowCol[0]++;
      m_movingRight = false;
      InitWindow(m_gridNumberRowCol[0], m_gridNumberRowCol[1]);
      return true;
    }
  }
  // If we are moving left:
  else {
    if (m_gridNumberRowCol[1] > 0) {
      m_gridNumberRowCol[1]--;
      InitWindow(m_gridNumberRowCol[0], m_gridNumberRowCol[1]);
      return true;
    } else if (m_gridNumberRowCol[0] < m_grid.getRows() - 1) {
      m_gridNumberRowCol[0]++;
      m_movingRight = true;
      InitWindow(m_gridNumberRowCol[0], m_gridNumberRowCol[1]);
      return true;
    }
  }

  // If neither is possible, we're at the bottom
  return false;
}


*/