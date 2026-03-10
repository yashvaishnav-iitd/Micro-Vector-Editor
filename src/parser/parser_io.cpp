#include "parser.h"

#include <iostream>
#include <fstream>

// This function opens an SVG file and reconstructs our canvas from it.
void Parser::loadSVG (const std::string &filename, Canvas* canvas){

	std::ifstream file(filename);

	//For checkign if the file actually exists
	if (!file.is_open()){
		std::cerr << "Error: Could not open " << filename << std::endl;
		return;
	}

	std::string line;

	//Read it line by line using our custom sting logic
	while (std::getline(file,line)){

		// Simple string search to find tags
		// line.find() gives unsigned number and when the line is not found it gives std::string npos and that is a huge number so we write (int).
		//Converting to int solves these problems. It converts the number into a signed integer ready for comparison with '-1'. Also, the huge number is reduced to -1 so it can check if it is present or not
		if ((int)line.find("<rect") != -1) {
			parseRect(line, canvas);
		}
		else if ((int)line.find("<circle") != -1) {
			parseCircle(line, canvas);
		}
		else if ((int)line.find("<line") != -1) {
			parseLine(line, canvas);
		}
		else if ((int)line.find("<polyline") != -1) {
			parsePolyLine(line, canvas);
		}
		else if ((int)line.find("<polygon") != -1) {
			parsePolyLine(line, canvas);  //Treats polygons (hexagons included) as polylines for simplicity.
		}
		else if ((int)line.find("<text") != -1) {
    		parseText(line, canvas);
		}
	}
	
	file.close();	// Clean up the file handle.
}

// This function exports our current canvas shapes into a valid SVG file.
void Parser::saveSVG (const std::string &filename, const Canvas* canvas){
	
	std::ofstream file(filename);
	
	if (!file.is_open()) {
		std::cerr << "Error: Could not save to " << filename << std::endl;
		return;
	}

	// Every SVG needs this header boilerplate to be valid XML.
	file << "<?xml version=\"1.0\" standalone=\"no\"?>\n";
	file << "<svg width=\"800\" height=\"600\" xmlns=\"http://www.w3.org/2000/svg\">\n";

	// 3. Iterate through all shapes and ask them to print their SVG string
	const std::vector<std::unique_ptr<GraphicsObject>>& shapes = canvas->getShapes();
	for (size_t i = 0; i < shapes.size(); i++) {
		//Each shape knows how to format its own SVG tag.
		file << "  " << shapes[i]->toString() << "\n";
	}

	// 4. Close the SVG tag
	file << "</svg>";


	file.close();
}
