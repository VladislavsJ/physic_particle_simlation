#include "CalcWindow.hpp"
#include "Grid.hpp"
#include "Particle.hpp"
#include <gtest/gtest.h>
static Particle *makeParticle(float x, float y, float radius = 5.f) {
  return new Particle({x, y}, {0, 0}, radius);
}

// This test fixture sets up a small Grid (so we can track shifts).
class CalcWindowShiftTest : public ::testing::Test {
protected:
  Grid *gridPtr = nullptr;
  CalcWindow *windowPtr = nullptr;

  void SetUp() override {
    /*
     * We choose:
     *   maxParticleSize = 10 => cellSize = 20.
     *   DispWidth = 60, DispHeight = 60.
     *
     * So:
     *   m_rows = ((width + cellSize/2) / cellSize) + 1
     *           = ((60 + 10) / 20) + 1
     *           = (70 / 20) + 1
     *           = 3 + 1
     *           = 4
     *
     *   m_cols = (height + cellSize/2) / cellSize
     *           = (60 + 10) / 20
     *           = 70/20
     *           = 3
     *
     * => The grid is 4 rows (0..3) x 3 columns (0..2).
     */
    gridPtr = new Grid(60, 60, 10);

    // We call updateGrid() so that the internal m_grid structure is set up.
    // (Strictly speaking, it's already sized in the ctor, but often we do
    // an update to simulate real usage.)
    gridPtr->updateGrid();

    windowPtr = new CalcWindow(*gridPtr);
    // By default, CalcWindow starts at (row=0, col=0), movingRight = true.
    // You can confirm or change that by reading the constructor code.
  }

  void TearDown() override {
    delete windowPtr;
    delete gridPtr;
  }
};

/*
 * We'll do a step-by-step check of the "snake-like" Shift() movement
 * until Shift() returns false (meaning we reached the bottom).
 *
 * Because we have 4 rows (0..3) and 3 columns (0..2),
 * the path of (row,col) should be:
 *
 *  Start: (0,0), movingRight=true  (not returned by Shift() yet, it's the
 * initial) SHIFT #1  => (0,1) SHIFT #2  => (0,2)
 *    * can't move further right, so we go down one row, flip direction:
 *  SHIFT #3  => (1,2), now movingRight=false
 *  SHIFT #4  => (1,1)
 *  SHIFT #5  => (1,0)
 *    * can't move further left, so we go down one row, flip direction:
 *  SHIFT #6  => (2,0), now movingRight=true
 *  SHIFT #7  => (2,1)
 *  SHIFT #8  => (2,2)
 *    * can't move further right, so we go down one row, flip direction:
 *  SHIFT #9  => (3,2), now movingRight=false
 *  SHIFT #10 => (3,1)
 *  SHIFT #11 => (3,0)
 *    * can't move left or down (already at row=3 which is the last),
 *  SHIFT #12 => returns false
 *
 * We'll store each “post-shift” position and compare to the expected sequence.
 */
TEST_F(CalcWindowShiftTest, SnakeLikeShifts) {
  // Our expected path of (row, col) after each call to Shift():
  std::vector<std::pair<int, int>> expected = {
      {0, 1}, {0, 2},         // then down + flip
      {1, 2}, {1, 1}, {1, 0}, // then down + flip
      {2, 0}, {2, 1}, {2, 2}, // then down + flip
      {3, 2}, {3, 1}, {3, 0}  // then can't move further => next Shift is false
  };

  std::vector<std::pair<int, int>> actual;

  // Keep shifting until false.
  while (windowPtr->Shift()) {
    // After each shift, read the new row & col from windowPtr
    // We can glean it by re-initializing or by storing row/col in CalcWindow.
    // We'll just re-init logic here:
    auto c = windowPtr->getCalcWindow();
    // The center cell is always c[CalcWindowIndex::CENTER] => c[4].
    // We can guess row/col by referencing one of the 9 pointers
    // or we can store it in an accessor. Since the code doesn't have
    // getCurrentRow() or getCurrentCol(), we'll do a short hack:
    //
    // Easiest approach: Add a small method to CalcWindow:
    //     int getRow() const { return m_gridNumberXY[0]; }
    //     int getCol() const { return m_gridNumberXY[1]; }
    //
    // For demonstration, let's just replicate that:

    // We'll mimic "private friend access" for the test:
    // In normal production code, you'd add a getter.
    // But here let's define a local lambda that extracts row/col from the
    // *center cell pointer* if we want. We have to be careful:
    // The center cell pointer is &grid.getCell(row, col).
    // There's no direct standard way to see which row/col that vector is from
    // except by pointer comparisons. We'll do the simpler approach:
    // just add a helper in the test fixture by searching for which row/col
    // matches c[CENTER].

    int foundRow = -1;
    int foundCol = -1;
    // we know we have 4 rows, 3 cols => let's brute force:
    for (int r = 0; r < 4; r++) {
      for (int col = 0; col < 3; col++) {
        if (&gridPtr->getCell(r, col) == c[CalcWindowIndex::CENTER]) {
          foundRow = r;
          foundCol = col;
          break;
        }
      }
      if (foundRow >= 0)
        break;
    }

    // record it
    actual.push_back({foundRow, foundCol});
  }

  // Now we compare 'actual' with 'expected'.
  ASSERT_EQ(actual.size(), expected.size());

  for (size_t i = 0; i < expected.size(); i++) {
    EXPECT_EQ(actual[i].first, expected[i].first)
        << "Mismatch in row at step " << i;
    EXPECT_EQ(actual[i].second, expected[i].second)
        << "Mismatch in col at step " << i;
  }
}

/*
 * We can also do a shorter "boundary test" that checks each step individually
 * if you prefer. But the above approach captures the entire path once.
 */
