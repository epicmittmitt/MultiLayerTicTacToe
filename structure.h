#include <stdexcept>
#include <vector>

using namespace std;

/*
  GridItem:
    Base interface for creating `Grid` and `Button` instances. Do *not*
    instantiate GridItem explicitly. It is for internal use only.

    Constructors:
      Default:
        Initializes a `GridItem` with a position of -1.
      position:
        Arguments:
          position:
            The initial position of the `GridItem`.

    Public methods:
      position():
        Returns:
          The position of the `GridItem`.

    Private fields:
      position:
        The position of the `GridItem`, from 0 to 8.
*/
class GridItem {
  public:
    GridItem() { position_ = -1; }
    GridItem(int position) { position_ = position; }
    int position() { return position_; }
	virtual ~GridItem() {};		//A non-virtual destructor will create undefined behavior

  protected:
    int position_;
};

/*
  Grid:
    An abstract grid of nine `GridItem` instances. All instances should be
    created with an initial position. You can place GridItems of any kind inside
    the grid.

    Constructors:
      Default:
        See `GridItem/Constructors/Default`.
        This constructor should only be used for creating the top-level `Grid`.
      position:
        Arguments:
          position:
            See `GridItem/Constructors/position`.
      position, items:
        Arguments:
          position:
            See `Grid/Constructors/position/Arguments/position`.
          items:
            A vector containing exactly nine `GridItem` instances. Any other
            size will throw an exception.

    Public methods:
      getItemAtPosition:
        Arguments:
          position:
            The position in question.
        Returns:
          The `GridItem` at the specified position.
      setItemAtPosition:
        Replaces the `GridItem` at the given position with the given `GridItem`.
        Arguments:
          position:
            The position of `GridItem` to replace.
          item:
            The `GridItem` that will replace the existing instance.
    
    Private fields:
      items:
        The internal vector containing an instance's items.
*/
class Grid : public GridItem {
  public:
    Grid() : GridItem() {}
    Grid(int position) : GridItem(position) {}
    Grid(int position, vector<GridItem*> items) : GridItem(position) {
        if (items.size() == 9) {
            items_ = items;
        } else {
            throw invalid_argument(
                "Parameter `items` expects a vector of size 9. Got "
                + items.size());
        }
    }
    GridItem* getItemAtPosition(int position) { return items_[position]; }
    void setItemAtPosition(int position, GridItem* item) {
        items_[position] = item;
    }
	virtual ~Grid() {
		/*for (size_t index = items_.size() - 1; index >= 0; --index) {
			delete items_[index];
		}*/
	}

  protected:
    vector<GridItem*> items_;	//In C++, these must be pointers, or else data will be sliced down to GridItem
};

/*
  Button:
    A button for selecting moves and such. Note: wxwidget buttons should be
    dynamically generated in the UI code based on the `Button` instances here.

    Enums:
      State:
        Defines a state for the `Button`. The locked state has been speerated
        into a seperate boolean.
    
    Constructors:
      Default:
        See `GridItem/Constructors/Default`.
        This constructor should not be used; all buttons should have a position.
      position:
        Arguments:
          position:
            See `GridItem/Constructors/position`.
      position, locked, state:
        Arguments:
          position:
            See `Button/Constructors/position/Arguments/position`.
          locked:
            Specifies whether the `Button` should be locked initially.
          state:
            Sets the intial state of the `Button`.
    
    Public methods:
      isLocked:
        Returns:
          A boolean specifying the Button's locked status.
      lock:
        Locks the `Button`.
      unlock:
        Unlocks the `Button`.
      getState:
        Returns:
          The current `State` of the `Button`.
      setState:
        Changes the state of the `Button`.
        Arguments:
          state:
            The Button's new `State`.

    Private fields:
      locked:
        The Button's locked status.
      state:
        The Button's ownership state.
*/
class Button : public GridItem {
  public:
    enum State { None, Red, Blue, Tie };
    Button() : GridItem() {}
    Button(int position) : GridItem(position) {}
    Button(int position, bool locked, State state) : GridItem(position) {
        locked_ = locked;
        state_ = state;
    }
    bool isLocked() { return locked_; }
    void lock() { locked_ = true; }
    void unlock() { locked_ = false; }
    State getState() { return state_; }
    void setState(State state) { state_ = state; }

  protected:
    bool locked_;
    State state_;
};