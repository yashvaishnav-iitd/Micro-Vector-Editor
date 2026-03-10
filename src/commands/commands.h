#ifndef COMMANDS_H
#define COMMANDS_H


// This is the Abstract Base Class for the Command Pattern.
// It allows us to treat every user action (like drawing or moving) as a single object that can be stored in a list.
class Command{

	public:

		// Virtual destructor ensures that child commands (like AddCommand or MoveCommand) are cleaned up properly when removed from the history stack.
		virtual ~Command() = default;

		// Pure virtual: This runs the actual action for the first time, or when the user hits 'Redo'.
		virtual void execute() = 0;

		// Pure virtual: This reverses the action, when the user hits 'Undo'.
		virtual void undo() = 0;

};


#endif
