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

void CalcWindow::InitWindow(int row, int col, bool shiftPriorityR) {
  m_gridNumberRowCol[0] = row;
  m_gridNumberRowCol[1] = col;
  shiftPriorityToRight = shiftPriorityR;
  m_movingRight = shiftPriorityR;
  // get all 9 cells
  auto allCells = m_grid.get9Cells(m_gridNumberRowCol);
  // store them
  for (int i = 0; i < 9; ++i) {
    m_calcWindow[i] = allCells[i];
  }
}
void CalcWindow::InitWindow(int gridNumberXY[2], bool shiftPriority) {
  InitWindow(gridNumberXY[0], gridNumberXY[1], shiftPriority);
}
bool CalcWindow::Shift() {

  // std::cout << " Coodrdinate is " << (int)m_gridNumberRowCol[0] << " "
  //           << (int)m_gridNumberRowCol[1] << std::endl;
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
  // -RIGHT - DOWN - LEFT - DOWN - RIGHT
  // Attempt horizontal moves first
  if (m_movingRight) {
    if (m_gridNumberRowCol[1] < m_grid.getCols() - 2) {
      shiftRight();
      m_gridNumberRowCol[1]++;
      return true;
    } else if (m_gridNumberRowCol[0] < m_grid.getRows() - 2) {

      shiftDown();
      m_gridNumberRowCol[0]++;
      m_movingRight = false;
      return true;
    }
  } else {
    if (m_gridNumberRowCol[1] > 1) {
      shiftLeft();
      m_gridNumberRowCol[1]--;
      return true;
    } else if (m_gridNumberRowCol[0] < m_grid.getRows() - 2) {
      shiftDown();
      m_gridNumberRowCol[0]++;

      m_movingRight = true;
      return true;
    }
  }
  return false; // if not possible to move,(if no bugs, means that it is the end
                // of the grid)
}

bool CalcWindow::ShiftPriorityLeft() { // LEFT-UP-RIGHT-UP-LEFT
  // Attempt horizontal moves first
  if (!m_movingRight) {
    if (m_gridNumberRowCol[1] > 1) {
      shiftLeft();
      m_gridNumberRowCol[1]--;
      return true;
    } else if (m_gridNumberRowCol[0] > 1) {
      shiftUp();
      m_gridNumberRowCol[0]--;

      m_movingRight = true;
      return true;
    }
  } else {
    if (m_gridNumberRowCol[1] < m_grid.getCols() - 2) {
      shiftRight();
      m_gridNumberRowCol[1]++;
      return true;
    } else if (m_gridNumberRowCol[0] > 1) {
      shiftUp();
      m_gridNumberRowCol[0]--;

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