#ifndef TEXT_H
#define TEXT_H

#include "graphics_object.h"
#include <QFont>

// This class handles user-entered text on the canvas.
class Text : public GraphicsObject {
    public:
        // Constructor: We need the position (x, y), the actual string content, 
        // and the font style (size, family) to draw it correctly.
        Text(int x, int y, const std::string &content, const QFont &font);

        //Overrides
        void draw(QPainter& painter) const override;            // Uses QPainter::drawText to render the string.

        std::string toString() const override;                  // Generates the SVG <text> tag: <text x="10" y="20">Hello</text>

        bool contains(const QPoint &point) const override;      // Uses QFontMetrics to calculate the "invisible box" around the text so we know if the user clicked on it

        void move(int dx, int dy) override;                     // Moves the text anchor point.

        QRect getBoundingBox() const override;                  // Returns the tight rectangle around the text pixels.

        // Allows the user to move and resize the text by dragging selection handles.
        void setBoundingBox(const QRect &rect, int handle) override;

        // For setting and getting the font content
        void setContent(const std::string &s);
        std::string getContent() const;

        std::unique_ptr<GraphicsObject> clone() const override;     //For creating a clone text

    private:
        int x, y;            // The bottom-left baseline origin of the text
        std::string content;    // The text string itself
        QFont font;          // Stores size, bold, italic, family, etc.
};

#endif