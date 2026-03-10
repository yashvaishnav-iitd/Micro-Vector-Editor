#ifndef GRAPHICS_OBJECT_H
#define GRAPHICS_OBJECT_H

#include <QPainter>
#include <QColor>
#include <string>

// This is the Abstract Base Class for all our shapes. 
// It defines the high-level structure that every shape (Circle, Rect, etc.) must follow.
class GraphicsObject{
	public:
		GraphicsObject();

		// Virtual destructor ensures that when we delete a shape through a base pointer, the correct child destructor is called.
		virtual ~GraphicsObject() = default ;
		
		// Pure virtual function: every shape must know how to draw itself on the QPainter.
		virtual void draw(QPainter& painter) const = 0;

		//Pure virtual function: every shape must be able to turn itself into an SVG string.
		virtual std::string toString() const = 0;

		//For Setting and getting drawing attributes
		// These are implemented in the base class because every shape has a color and width.
		QColor getStrokeColor() const;
		void setStrokeColor (const QColor &color);

		//Fill color
		QColor getFillColor() const;
		void setFillColor (const QColor &color);

		//Stroke width
		int getStrokeWidth() const;
		void setStrokeWidth (int width);

		//Pure virtual fucntion : Collision detection: used to check if a user clicked on the shape.
		virtual  bool contains(const QPoint &point) const = 0;

		//Pure virtual function : Moving
		virtual void move(int dx, int dy) = 0;

		//Handles the math of changing shape size based on the 8 selection handles.
		virtual void resize(int handle,int dx, int dy);

		// Returns the rectangle that surrounds the shape, used for the selection box
		virtual QRect getBoundingBox() const = 0;

		//Pure Virtal function : Used by the Undo/Redo system to snap the shape to a specific box.
		virtual void setBoundingBox(const QRect &rect, int handle = -1)=0;

		//Pure Virtual function for cloning:
		virtual std::unique_ptr<GraphicsObject> clone() const = 0;

		void copyStylesFrom(const GraphicsObject* other);		//Helper For copying the styles from a shape to clone

	protected:
		// These are 'protected' so that child classes can access them directly.
		//Attributes same for all shapes
		QColor strokeColor;
		QColor fillColor;
		int strokeWidth;
		
		//Helper for applying all the attributes
		void applyStyle (QPainter &painter) const;
};

#endif

