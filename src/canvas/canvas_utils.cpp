#include "canvas.h"
#include "graphics_object.h"

// Geometry Helper for calculating 8 resize handles that appear around a selected shape
std::vector<QRect> Canvas::getHandles(const QRect& bbox) const {
	std::vector<QRect> handles(8);
	int s = 8;		// Handle size (8x8 pixels)
	int hs = s / 2;		// Half size for centering

	// Top Row (Left, Center, Right)
	handles[0] = QRect(bbox.left() - hs, bbox.top() - hs, s, s);			// Top-Left corner
	handles[1] = QRect(bbox.center().x() - hs, bbox.top() - hs, s, s);		// Top-Middle
	handles[2] = QRect(bbox.right() - hs, bbox.top() - hs, s, s);			// Top-Right corner

	// Middle Row (Right, Left)
	handles[3] = QRect(bbox.right() - hs, bbox.center().y() - hs, s, s);	// Right-Middle
	handles[7] = QRect(bbox.left() - hs, bbox.center().y() - hs, s, s);		// Left-Middle

	// Bottom Row (Left, Center, Right)
	handles[6] = QRect(bbox.left() - hs, bbox.bottom() - hs, s, s);			// Bottom-Left corner
	handles[5] = QRect(bbox.center().x() - hs, bbox.bottom() - hs, s, s);	// Bottom-Middle
	handles[4] = QRect(bbox.right() - hs, bbox.bottom() - hs, s, s);		// Bottom-Right corner

	return handles;
}

//Helper for cut()
std::unique_ptr<GraphicsObject> Canvas::extractShapeInternal(GraphicsObject* target) {
    // 1. Loop through your vector of unique_ptrs
    for (auto it = shapes.begin(); it != shapes.end(); ++it) {
        
        // 2. Compare the raw pointer inside the unique_ptr to your target
        if (it->get() == target) {
            
            // 3. Move the ownership out of the vector into a temporary variable
            std::unique_ptr<GraphicsObject> ptr = std::move(*it);
            
            // 4. Remove the empty slot from the vector
            shapes.erase(it);
            
            // 5. If the shape we just removed was the selected one, clear selection
            // Note: Using your state structure 'st'
            if (target == selectedShape) {
                selectedShape = nullptr;
                isMoving = false;
                isResizing = false;
            }
            
            // 6. Redraw and return the shape so the Cut command can use it
            update();
            return ptr;
        }
    }
    return nullptr; // Shape wasn't found
}