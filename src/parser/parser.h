#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <memory>
#include "canvas.h"


// This class handles all the File I/O for SVG
class Parser{
	public :
		//static used so that i don't have to create the object parser instead i can directly use the class

		//returns the value of the attribute named "key" from a XML line
        static std::string getAttributes(const std::string &tag, const std::string &key);

		//Reads an SVG file and loads the shapes on the canvas
		static void loadSVG(const std::string& filename, Canvas* canvas);

        //Writes the current canvas file in SVG format and saves it in the SVG file
        static void saveSVG( const std::string& filename, const Canvas* canvas);

	private:

		// Helper to apply stroke/fill/width to any shape
		static void setStyle (GraphicsObject* shape, const std::string &line);

		//Helpers to parse specific tags from a XML line
		static void parseCircle(const std::string &line , Canvas* canvas);

		static void parseRect(const std::string &line , Canvas* canvas); //Rounded rectangle also has the same tag <rect> so we will modify this internally and use this itself for rounded rect

		static void parseLine(const std::string &line , Canvas* canvas);

		static void parsePolyLine(const std::string &line , Canvas* canvas);
		
		// Hexagons are saved as <polygon> or <polyline> in SVG, so we parse them as a set of points.
		static void parseHexagon(const std::string &line , Canvas* canvas); 
		
		static void parseText(const std::string &line, Canvas* canvas);
};

#endif
