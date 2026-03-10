#include "canvas.h"
#include "add_shape_command.h"
#include "change_color_command.h"
#include <QPainter>


// The constructor sets up all our default values when the app starts.
Canvas::Canvas(QWidget *parent) : QWidget(parent),
	currentTool(ToolType::None), currentStrokeColor(Qt::black), currentFillColor(Qt::transparent),	currentStrokeWidth(2),
	isDrawing(false), isMoving(false), isResizing(false), currentHandle(-1), startPoint(0,0), currentPoint(0,0), lastMousePoint(0,0){

	QPalette pale = palette();
	// Setting the background to white so it actually looks like a drawing canvas.
	pale.setColor (QPalette::Window , Qt::white);
	setAutoFillBackground(true);
	setPalette(pale);
}

Canvas::~Canvas() {}

// This is the most important function for rendering. Qt calls this whenever update() is used.
void Canvas::paintEvent(QPaintEvent *event){
	Q_UNUSED(event); //I was getting warnings while compiling

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);	// Makes the lines look smooth rather than pixelated
	
	// First, draw all the permanent shapes that are stored in our vector.
	for (const auto &shape : shapes) {
		shape->draw(painter);
	}
	// Next, draw all the potential shapes that follows the mouse while we are still dragging.
	if (tempShape) {
		tempShape->draw(painter);
	}
	// If a user has clicked a shape, we need to draw the selection box and handles on top.
	if (selectedShape){
		// Get the rectangular area that perfectly fits the shape.
		QRect bbox = selectedShape->getBoundingBox();

		// We draw a blue dashed line slightly larger than the shape so it's easy to see.
		QPen dashedPen (Qt::blue ,1 , Qt::DashLine);
		painter.setPen(dashedPen);
		painter.setBrush(Qt::NoBrush);
		painter.drawRect(bbox.adjusted(-2,-2,2,2));

		// Now draw the 8 little white squares (handles) used for resizing.
		painter.setPen(Qt::blue);
		painter.setBrush(Qt::white);

		// Get the coordinates for all 8 handles based on the current bounding box.
		std::vector<QRect> handles = getHandles(bbox);
		
		for (const auto & han: handles){
			painter.drawRect(han);		// Actually paint each handle square.
		}
	}
}


