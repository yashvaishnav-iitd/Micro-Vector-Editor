#include "parser.h"
#include "text.h"

void Parser::parseText(const std::string &line, Canvas* canvas) {
    
    //Extract the position coordinates
    int x = std::stoi(getAttributes(line, "x"));
    int y = std::stoi(getAttributes(line, "y"));

    //Extract the font size. We check if it exists first to prevent crashes.
    std::string sizeStr = getAttributes(line, "font-size");
    
    int fontSize = 12; // Default size if none is found
    
    if (!sizeStr.empty()) {
        fontSize = std::stoi(sizeStr);
    }

    //Extract the actual text content between the tags
    // The content starts right after the first '>' and ends at '</text>'
    size_t start = line.find(">") + 1;
    size_t end = line.find("</text>");
    
    // Safety check to ensure we found valid tags
    std::string content = "";
    
    if (start != std::string::npos && end != std::string::npos) {
        
        content = line.substr(start, end - start);
    }

    //Create the Text object
    // We use a standard font family (Arial) but apply the parsed size.
    QFont font("Arial", fontSize);
    auto shape = std::make_unique<Text>(x, y, content, font);

    //Apply standard colors (fill usually sets the text color)
    setStyle(shape.get(), line);

    //Move the "finalised" "text" object to the canvas for drawing.
    canvas->addShape(std::move(shape));
}