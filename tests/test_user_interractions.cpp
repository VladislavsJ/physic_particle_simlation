#include <SFML/Graphics.hpp>
#include <gtest/gtest.h>

#include "../src/BorderInfo.hpp"
#include "../src/Graphs_new.hpp"
#include "../src/Particle.hpp"
#include "../src/ParticleSystem.hpp"
#include "../src/Physics.hpp"
#include "../src/Renderer.hpp"
#include "../src/Vector2D.hpp"
#include "../src/global_var.hpp"
#include "../src/graphical_items.hpp"
#include "../src/simulation_examples.hpp"
#include "../src/user_interactions_new.hpp"
#include "../src/user_interface.hpp"

// Adjust this enum to match your actual InteractionType definition.
// Example:
enum class InteractionType;

class UserInteractionsTest : public ::testing::Test {
protected:
  UserInteractions userInteractions;
  ParticleSystem particleSystem;
  sf::RenderWindow window;

  virtual void SetUp() override {
    // Create (not copy) the SFML window directly here.
    window.create(sf::VideoMode(800, 600), "Test Window", sf::Style::Default);

    // Initialize UI (sliders, buttons, etc.)
    userInteractions.initUI();
  }

  virtual void TearDown() override { window.close(); }
};

/**
 * Helper function to simulate a mouse button press event.
 * @param button the sf::Mouse::Button you want to simulate
 * @param x, y   the coordinates for the event
 */
static sf::Event createMousePressEvent(sf::Mouse::Button button, int x, int y) {
  sf::Event event;
  event.type = sf::Event::MouseButtonPressed;
  event.mouseButton.button = button;
  event.mouseButton.x = x;
  event.mouseButton.y = y;
  return event;
}

/**
 * Helper function to simulate a mouse move event.
 * @param x, y - coordinates for the event
 */
static sf::Event createMouseMoveEvent(int x, int y) {
  sf::Event event;
  event.type = sf::Event::MouseMoved;
  event.mouseMove.x = x;
  event.mouseMove.y = y;
  return event;
}

/**
 * Example test: Check if clicking a button toggles it on the first time,
 * and toggles it off the second time.
 */
TEST_F(UserInteractionsTest, ButtonTogglesOnOff) {
  // Make sure we actually have a button in the user interface.
  auto buttonsPair = userInteractions.getButtons_Interact();
  ASSERT_FALSE(buttonsPair.empty())
      << "No buttons found. Ensure initUI() or test setup adds buttons.";

  // For simplicity, grab the first button in the vector
  auto &firstButtonPair = buttonsPair[0];
  auto &firstButton = firstButtonPair.first;

  // Coordinates roughly at the button’s position
  int clickX =
      static_cast<int>(firstButton.start_point.x + firstButton.iconSizeX / 2);
  int clickY =
      static_cast<int>(firstButton.start_point.y + firstButton.iconSizeY / 2);

  // 1) Simulate a left mouse press on the button
  sf::Event clickEvent = createMousePressEvent(sf::Mouse::Left, clickX, clickY);
  userInteractions.handleEvent(clickEvent, window, particleSystem);

  // Now the button should be "pressed == true"
  buttonsPair = userInteractions.getButtons_Interact();
  EXPECT_TRUE(buttonsPair[0].first.pressed)
      << "Button should be pressed after first click.";

  // 2) Simulate a second left mouse press on the button
  userInteractions.handleEvent(clickEvent, window, particleSystem);

  // Button should toggle off
  buttonsPair = userInteractions.getButtons_Interact();
  EXPECT_FALSE(buttonsPair[0].first.pressed)
      << "Button should be toggled off after second click.";
}

/**
 * Test: Check that moving the slider sets the current interaction to "SlideBar"
 * (or whichever InteractionType indicates a slider interaction),
 * and that we can see some effect on the system (e.g., new slider value).
 */
TEST_F(UserInteractionsTest, SlidebarChangesInteraction) {
  // Make sure we have at least one slider in the UI.
  auto sliders = userInteractions.getSliders();
  ASSERT_FALSE(sliders.empty())
      << "No sliders found. Ensure initUI() or test setup adds sliders.";

  // Pick the first slider
  Slidebar &slider = sliders[0];

  // We simulate moving the mouse over the slider and pressing the left button.
  int sliderCenterX =
      static_cast<int>(slider.getSlidebarX() + slider.getSlidebarLength() / 2);
  int sliderCenterY =
      static_cast<int>(slider.getSlidebarY() + slider.getSlidebarWidth() / 2);

  // Move event: position the mouse in the slider region
  sf::Event moveEvent = createMouseMoveEvent(sliderCenterX, sliderCenterY);
  userInteractions.handleEvent(moveEvent, window, particleSystem);

  // Click event: press the mouse
  sf::Event clickEvent =
      createMousePressEvent(sf::Mouse::Left, sliderCenterX, sliderCenterY);
  userInteractions.handleEvent(clickEvent, window, particleSystem);

  // Check if current interaction is recognized as SlideBar
  EXPECT_EQ(userInteractions.getCurrentInteractionType(),
            InteractionType::Slider)
      << "Current interaction type should be SlideBar after moving the slider.";

  // Optionally, you can check if the slider's internal value changed.
  float sliderVal = slider.getCurrentValue();
  // If minValue=0, maxValue=100, the middle is ~50.
  EXPECT_NEAR(sliderVal, 50.0f, 1e-1)
      << "Slider value is expected to be near midpoint after moving mouse to "
         "center.";
}

/**
 * (Optional) Example test to verify right-click logic, if needed.
 */
TEST_F(UserInteractionsTest, RightClickBehavior) {
  // If your handleEvent does something special on right-click:
  int x = 300;
  int y = 300;
  sf::Event rightClickEvent = createMousePressEvent(sf::Mouse::Right, x, y);

  // Before click (assuming default is InteractionType::None)
  EXPECT_EQ(userInteractions.getCurrentInteractionType(), InteractionType::None)
      << "Default interaction should be None.";

  // After right-click
  userInteractions.handleEvent(rightClickEvent, window, particleSystem);

  // Check if something changed, e.g.:
  // EXPECT_EQ(userInteractions.getCurrentInteractionType(),
  // InteractionType::RemoveParticle);
}
