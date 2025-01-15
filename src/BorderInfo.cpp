#include "BorderInfo.hpp"

BorderInfo::BorderInfo() : data(0) {}

void BorderInfo::setAnyBorderFlag() {
    data |= ANY_BORDER_MASK;
}

void BorderInfo::clearALL() {
    data = 0;
}

void BorderInfo::setBorder(Border border) {
    data |= border;        // Set the specified border bit
    setAnyBorderFlag();    // Ensure the 'any border' flag is set
}

// Public method: Clear a specific border
void BorderInfo::clearBorder(Border border) {
    data &= ~border;       // Clear the specified border bit
    // If no borders are touched, clear the 'any border' flag
    if ((data & 0x0F) == 0) {
        clearALL();
    }
}

bool BorderInfo::isBorderSet(Border border) const {
    return (data & border) != 0;
}

bool BorderInfo::isAnyBorderSet() const {
    return (data & ANY_BORDER_MASK) != 0;
}


uint8_t BorderInfo::getRawData() const {
    return data;
}

void BorderInfo::setRawData(uint8_t raw) {
    data = raw;
}
void BorderInfo::update_border_state(Vector2D pos, int fieldSizeX, int fieldSizeY, int fieldstartX, int fieldstartY) {
    clearALL();
    if (pos.x <= fieldstartX) {
        setBorder(BORDER_LEFT);
    } else if (pos.x >= fieldSizeX) {
        setBorder(BORDER_RIGHT);
    }
    if (pos.y <= fieldstartY) {
        setBorder(BORDER_TOP);
    } else if (pos.y >= fieldSizeY) {
        setBorder(BORDER_BOTTOM);
    }
}

// Display (debugging)
void BorderInfo::display() const {
    std::cout << "Any Border Flag: " << (isAnyBorderSet() ? "Yes" : "No") << "\n";
    if (isAnyBorderSet()) {
        std::cout << "Borders touched: ";
        if (isBorderSet(BORDER_TOP))    std::cout << "Top ";
        if (isBorderSet(BORDER_BOTTOM)) std::cout << "Bottom ";
        if (isBorderSet(BORDER_LEFT))   std::cout << "Left ";
        if (isBorderSet(BORDER_RIGHT))  std::cout << "Right ";
        std::cout << "\n";
    }
}
