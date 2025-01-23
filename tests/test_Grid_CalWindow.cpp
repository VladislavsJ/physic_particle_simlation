#include "Grid.hpp"
#include "Particle.hpp"
#include <gtest/gtest.h>

// Example: A helper to quickly create Particles at given (x,y).
static Particle *makeParticle(float x, float y, float radius = 5.f) {
  auto *p = new Particle({x, y}, {0, 0}, radius);
  return p;
}

// TEST FIXTURE (optional, for reusability).
// You can also use simple TEST() macros directly.
class GridTest : public ::testing::Test {
protected:
  void SetUp() override {
    // Common setup for each test if needed
  }

  void TearDown() override {
    // Cleanup after each test
  }
};

TEST_F(GridTest, ConstructorAndDimensions) {
  // Suppose:
  //  DispWidth = 100, DispHeight = 80, maxParticleSize=5 => cellSize=10
  //  m_rows = ( (100 + 10/2) / 10 ) + 1 = ( (100+5)/10 ) + 1 = 10 + 1 = 11
  //  m_cols = ( (80 + 5) / 10 ) = 85/10 = 8
  Grid grid(100, 80, 5);

  EXPECT_EQ(grid.getRows(), 11);
  EXPECT_EQ(grid.getCols(), 8);
}

TEST_F(GridTest, AddParticleByPositionAndUpdate) {
  Grid grid(100, 80, 5);

  // Particle at (12, 12) => row=12/10=1, col=12/10=1
  Particle *p = makeParticle(12, 12);

  // Add the particle. This goes into m_grid_new
  grid.addParticle(p);

  // Before updateGrid(), m_grid is empty, m_grid_new has 1 particle in cell
  // (1,1).
  {
    // grid.getCell(...) reads from m_grid (the old grid),
    // so it should still be empty
    auto &cellOld = grid.getCell(1, 1);
    EXPECT_TRUE(cellOld.empty());
  }

  // Now update. This swaps m_grid_new -> m_grid
  grid.updateGrid();

  // Now, the cell(1,1) in m_grid should have our particle
  {
    auto &cell = grid.getCell(1, 1);
    ASSERT_EQ(cell.size(), 1u);
    EXPECT_EQ(cell[0], p);
  }
}

TEST_F(GridTest, AddParticleByExplicitCellAndUpdate) {
  Grid grid(100, 80, 5);

  Particle *p = makeParticle(0, 0);
  int cell[2] = {3, 2}; // row=3, col=2
  grid.addParticle(p, cell);

  // Before update: no particle in the old grid
  EXPECT_TRUE(grid.getCell(3, 2).empty());

  // After update
  grid.updateGrid();
  auto &theCell = grid.getCell(3, 2);
  ASSERT_EQ(theCell.size(), 1u);
  EXPECT_EQ(theCell[0], p);
}

TEST_F(GridTest, AddParticlesBulk) {
  Grid grid(100, 80, 5);

  // Create 3 particles with distinct positions
  Particle *p1 = makeParticle(10, 10);
  Particle *p2 = makeParticle(20, 10);
  Particle *p3 = makeParticle(10, 70);

  std::vector<Particle *> vp = {p1, p2, p3};
  grid.addParticles(vp);

  // update
  grid.updateGrid();

  // Check each is in the correct cell
  // cell for p1 => (1,1)
  auto &cell1 = grid.getCell(1, 1);
  EXPECT_EQ(cell1.size(), 1u);
  EXPECT_EQ(cell1[0], p1);

  // cell for p2 => (1,2)
  auto &cell2 = grid.getCell(1, 2);
  EXPECT_EQ(cell2.size(), 1u);
  EXPECT_EQ(cell2[0], p2);

  // cell for p3 => (7,1)
  auto &cell3 = grid.getCell(7, 1);
  EXPECT_EQ(cell3.size(), 1u);
  EXPECT_EQ(cell3[0], p3);
}

TEST_F(GridTest, Clear) {
  Grid grid(100, 80, 5);
  // Add some particles to the grid
  Particle *p = makeParticle(45, 45);
  grid.addParticle(p);
  grid.updateGrid();
  // Now the active grid (m_grid) has 1 particle in some cell

  // Confirm we have 1 particle somewhere
  int row = 4; // 45/10 => 4
  int col = 4; // 45/10 => 4
  EXPECT_FALSE(grid.getCell(row, col).empty());

  // Clear the active grid
  grid.clear();
  EXPECT_TRUE(grid.getCell(row, col).empty());
}

TEST_F(GridTest, GetCellClamp) {
  // If we request a negative row or col that is out of bounds,
  // it should be clamped to 0. Similarly for row >= rows, col >= cols.
  Grid grid(100, 80, 5);
  // The valid row range is [0..10], col range is [0..7] from earlier

  // Negative row/col => should clamp to (0,0)
  auto &cell1 = grid.getCell(-1, -10);
  // Then we add a test particle to see if we can detect it later
  Particle *p1 = makeParticle(0, 0);
  cell1.push_back(p1);

  // Request the same cell via normal in-range coordinates: (0,0).
  auto &cell2 = grid.getCell(0, 0);
  ASSERT_EQ(cell2.size(), 1u);
  EXPECT_EQ(cell2[0], p1);

  // Very large row/col => clamp to the maximum (10, 7).
  auto &cell3 = grid.getCell(9999, 9999);
  Particle *p2 = makeParticle(99, 99);
  cell3.push_back(p2);

  // Should find p2 in the (10,7) cell
  auto &cell4 = grid.getCell(10, 7);
  ASSERT_EQ(cell4.size(), 1u);
  EXPECT_EQ(cell4[0], p2);
}

TEST_F(GridTest, GetNeighbourCells) {
  Grid grid(100, 80, 5);
  grid.updateGrid(); // So that any structural changes are consistent.

  // let's pick a cell in the middle, e.g. row=4, col=3
  int center[2] = {4, 3};

  auto neighbors = grid.getNeighbourCells(center);
  ASSERT_EQ(neighbors.size(), 8u);

  // The 8 offsets in row,col are:
  // (3,2),(3,3),(3,4),
  // (4,2),      (4,4),
  // (5,2),(5,3),(5,4)

  // Let's confirm each pointer is consistent
  // For instance, neighbors[0] should correspond to (3,2)
  // The order is: the code loops dr = -1..+1, dc = -1..+1 skipping center.
  // So typically the neighbor cells are:
  //  index=0 => (3,2)
  //  index=1 => (3,3)
  //  index=2 => (3,4)
  //  index=3 => (4,2)
  //  index=4 => (4,4)
  //  index=5 => (5,2)
  //  index=6 => (5,3)
  //  index=7 => (5,4)

  // We can do quick checks:
  // Insert a unique particle in each neighbor and see if it shows up.
  std::vector<Particle *> testPs;
  for (int i = 0; i < 8; i++) {
    Particle *p = makeParticle(0, 0);
    testPs.push_back(p);
    neighbors[i]->push_back(p);
  }
  // Now read back directly from the grid
  // e.g. row=3, col=2 => neighbors[0]
  EXPECT_EQ(grid.getCell(3, 2).size(), 1u);
  EXPECT_EQ(grid.getCell(3, 2)[0], testPs[0]);
  EXPECT_EQ(grid.getCell(3, 3).size(), 1u);
  EXPECT_EQ(grid.getCell(3, 3)[0], testPs[1]);
  // etc...
  EXPECT_EQ(grid.getCell(3, 4)[0], testPs[2]);
  EXPECT_EQ(grid.getCell(4, 2)[0], testPs[3]);
  EXPECT_EQ(grid.getCell(4, 4)[0], testPs[4]);
  EXPECT_EQ(grid.getCell(5, 2)[0], testPs[5]);
  EXPECT_EQ(grid.getCell(5, 3)[0], testPs[6]);
  EXPECT_EQ(grid.getCell(5, 4)[0], testPs[7]);
}

TEST_F(GridTest, Get9Cells) {
  Grid grid(100, 80, 5);
  grid.updateGrid();

  int center[2] = {4, 3};
  auto nineCells = grid.get9Cells(center);
  ASSERT_EQ(nineCells.size(), 9u);

  // The 9 offsets in (row, col) are:
  // (3,2), (3,3), (3,4)
  // (4,2), (4,3), (4,4)
  // (5,2), (5,3), (5,4)
  //
  // We'll similarly place 9 distinct Particles:
  std::vector<Particle *> testPs(9);
  for (int i = 0; i < 9; i++) {
    testPs[i] = makeParticle(0.f, 0.f);
    nineCells[i]->push_back(testPs[i]);
  }

  // Now check if they match
  EXPECT_EQ(grid.getCell(3, 2).size(), 1u);
  EXPECT_EQ(grid.getCell(3, 2)[0], testPs[0]);
  EXPECT_EQ(grid.getCell(3, 3)[0], testPs[1]);
  EXPECT_EQ(grid.getCell(3, 4)[0], testPs[2]);
  EXPECT_EQ(grid.getCell(4, 2)[0], testPs[3]);
  EXPECT_EQ(grid.getCell(4, 3)[0], testPs[4]);
  EXPECT_EQ(grid.getCell(4, 4)[0], testPs[5]);
  EXPECT_EQ(grid.getCell(5, 2)[0], testPs[6]);
  EXPECT_EQ(grid.getCell(5, 3)[0], testPs[7]);
  EXPECT_EQ(grid.getCell(5, 4)[0], testPs[8]);
}

/*
 * (OPTIONAL) Tests for CalcWindow
 * If you want to verify CalcWindow's shifting logic and so on,
 * here's a straightforward approach:
 */

class CalcWindowTest : public ::testing::Test {
protected:
  Grid *gridPtr;
  CalcWindow *windowPtr;

  void SetUp() override {
    gridPtr = new Grid(100, 80, 5);
    // We can add some dummy particles if needed
    gridPtr->updateGrid(); // finalize the structure
    windowPtr = new CalcWindow(*gridPtr);
  }

  void TearDown() override {
    delete windowPtr;
    delete gridPtr;
  }
};

TEST_F(CalcWindowTest, InitWindow) {
  // Initialize around (row=4, col=3)
  windowPtr->InitWindow(4, 3);
  auto &cells = windowPtr->getCalcWindow();

  ASSERT_EQ(cells.size(), 9u);
  // The 9 cells should correspond to row in [3..5], col in [2..4]
  // We can push a known particle into, say, top-left (which is index=0).
  Particle *p = makeParticle(0, 0);
  cells[0]->push_back(p);

  // That top-left cell is (3,2)
  auto &cell = gridPtr->getCell(3, 2);
  ASSERT_EQ(cell.size(), 1u);
  EXPECT_EQ(cell[0], p);
}

TEST_F(CalcWindowTest, ShiftMovement) {
  // By default, it starts at (0,0)
  // Let's do a simple loop of shifting right until we can no longer shift
  int countSteps = 0;
  while (windowPtr->Shift()) {
    countSteps++;
  }
  // We expect that we eventually run out of columns, then try to move down,
  // etc., until we exhaust rows. The code for Shift stops at the bottom.
  //
  // With the grid of size 11 rows x 8 columns, the "snake" iteration
  // would move us across all columns in row0, down, across row1, etc.
  // Let's do a rough bound check:
  EXPECT_GE(countSteps, 1); // definitely > 1
}

/*
    Add more tests for shiftLeft(), shiftRight(), shiftUp(), shiftDown() if
    you specifically rely on that partial cell reuse logic.
*/

// A main is usually provided by Google Test automatically (via gtest_main).
// But if needed explicitly:
//
// int main(int argc, char **argv) {
//     ::testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
// }
