#include "text.h"
#include <QFontMetrics>
#include <sstream>

Text::Text(int x, int y, const std::string &content, const QFont &f)
    : x(x), y(y), content(content), font(f) {}

void Text::draw(QPainter& painter) const {
    applyStyle(painter); // Sets color
    
    painter.setFont(font); // Sets the size/family
    
    // Draw the text at position (x,y). (Here, y is the baseline)
    painter.drawText(x, y, QString::fromStdString(content));
}

std::string Text::toString() const {
    std::stringstream ss;

    // We save the font-size so it looks the same when re-opened
    ss << "<text x=\"" << x << "\" y=\"" << y << "\" ";
    ss << "font-size=\"" << font.pointSize() << "\" ";
    // Check if the fill is transparent
    if (getFillColor() == Qt::transparent) {
        ss << "fill=\"none\" ";
    } else {
        ss << "fill=\"" << getFillColor().name().toStdString() << "\" ";
    }
    ss << "stroke=\"none\" >"; // Text mostly has fill, no stroke
    
    ss << content << "</text>";
    
    return ss.str();
}

// For checking if the user clicked on the letters
bool Text::contains(const QPoint &point) const {
    return getBoundingBox().contains(point);
}

//Moving the text
void Text::move(int dx, int dy) {
    x += dx;
    y += dy;
}

// Calculates the invisible box around the text using the font metrics
QRect Text::getBoundingBox() const {
    QFontMetrics fm(font);
    
    // Width: Real width of the text (this is safe, width doesn't cause vertical explosion)
    int w = fm.horizontalAdvance(QString::fromStdString(content));
    
    // Height: FORCE it to be exactly the pixel size. 
    // Do NOT ask QFontMetrics for the height.
    int h = font.pixelSize();
    if (h < 10) h = 10; // Safety floor

    // Position: We assume the box starts at (x, y - ascent)
    // This perfectly covers the letters.
    return QRect(x, y - fm.ascent(), w, h);
}


//Scale logic
void Text::setBoundingBox(const QRect &rect, int handle) {
    Q_UNUSED(handle);

    // 1. Normalize (handle dragging backwards)
    QRect safeRect = rect.normalized();
    
    // 2. Get the user's requested height
    int newHeight = safeRect.height();
    
    // 3. Safety Clamp
    if (newHeight < 10) newHeight = 10;

    // 4. DIRECT ASSIGNMENT
    // If user drags box to 50px, Font becomes 50px.
    // Since getBoundingBox() above returns exactly 50px, 
    // the next frame will see "50", not "60". Explosion stopped.
    font.setPixelSize(newHeight);

    // 5. Update Position
    x = safeRect.left();
    
    // 6. Update Baseline
    QFontMetrics fm(font);
    y = safeRect.top() + fm.ascent();
}

std::unique_ptr<GraphicsObject> Text::clone() const {
    auto newText = std::make_unique<Text>(x, y, content, font);
    newText->copyStylesFrom(this);
    return newText;
}