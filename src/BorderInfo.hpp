#ifndef BORDER_INFO_HPP
#define BORDER_INFO_HPP

#include <cstdint>
#include <iostream>

// Enum to define the borders with bit positions
enum Border : uint8_t {
    BORDER_NONE   = 0x00,        // No border
    BORDER_TOP    = 0x08,        // Top border (bit 3)
    BORDER_BOTTOM = 0x04,        // Bottom border (bit 2)
    BORDER_LEFT   = 0x02,        // Left border (bit 1)
    BORDER_RIGHT  = 0x01         // Right border (bit 0)
};

const uint8_t ANY_BORDER_MASK = 0x80; // Any border touched (bit 7)

class BorderInfo {
private:
    uint8_t data; // 1-byte storage for borders
    void setAnyBorderFlag();
    void clearAnyBorderFlag();

public:

    BorderInfo();
    void setBorder(Border border);

    // Clear a specific border
    void clearBorder(Border border);

    // Check if a specific border is touched
    bool isBorderSet(Border border) const;

    // Check if any border is touched
    bool isAnyBorderSet() const;

    uint8_t getRawData() const;

    // Set the raw byte
    void setRawData(uint8_t raw);

    // Display  (debug)
    void display() const;
};

#endif // BORDER_INFO_HPP
