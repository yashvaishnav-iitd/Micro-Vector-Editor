#include "parser.h"

#include <QColor>
#include <string>


//To extract the value of the "key" attribute
std::string Parser::getAttributes(const std::string &line , const std::string &key){
	// We look for the pattern: key="
	std::string searchKey = key + "=\"";

	int start = (int)line.find(searchKey);

	// If the key isn't in the line, just return an empty string
	if (start == -1) {
		return "";
	}

	// Move the pointer to the actual value starting after the quote
	start+= searchKey.length();

	// Find the closing quote
	int end = (int)line.find("\"", start);

	if (end==-1){
		return "";
	}
	else{
		// Cut out the substring between the two quotes
		return line.substr(start, end-start);}

}


//Helper shared by all shapes to set the common attributes like strokewidth, strokecolor, fillcolor
void Parser::setStyle (GraphicsObject* object, const std::string &line){

	//For Stroke Color
	std::string strokeColor = getAttributes(line,"stroke");			//stroke is the key which contains the strokeColor
	if (strokeColor!= ""){
		object->setStrokeColor(QColor(strokeColor.c_str()));		//used c_str() here because QColor does not takes string as an argument. It takes QString or nullterminated c-styled string
	}									// for ex- we have string x= "hello", c_str will return the pointer to "hello\0" (a null terminated c-styke string)

	//For Fill color
	std::string fillColor = getAttributes(line,"fill");
	if (fillColor == "" or fillColor== "none"){
		// If it's missing or says "none", we make it transparent
		object->setFillColor(Qt::transparent);
	}
	else{
		object->setFillColor(QColor(fillColor.c_str()));
	}

	//For Stroke width
	std::string strokeWidth = getAttributes(line, "stroke-width");
	if (strokeWidth != ""){
		// Convert the string numbers like "4" into an actual integer
		object->setStrokeWidth(std::stoi(strokeWidth));
	}

}



