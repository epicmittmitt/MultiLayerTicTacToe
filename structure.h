#if !defined(__STRUCTURE_H__)
#define __STRUCTURE_H__

#include <stdexcept>
#include <vector>



using namespace std;

class GridItem;
class Grid;
class Button;

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
    enum State { None, Red, Blue, Tie };
    GridItem() : state_(GridItem::State::None) { position_ = -1; } // The three is the top layer grid item
    GridItem(int position) : state_(GridItem::State::None){ position_ = position; }
    int position() { return position_; }
	  virtual ~GridItem() {};		//A non-virtual destructor will create undefined behavior
    State getState() { return state_; }
    void setState(State state) { state_ = state; }
    virtual Grid* getParent() { return nullptr; }

  protected:
    int position_;
    State state_;
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
    Grid() : GridItem(), parent(nullptr) {}
    Grid(int position) : GridItem(position), parent(nullptr) {}
    Grid(int position, Grid* caller) : GridItem(position), parent(caller) {}
    Grid(int position, vector<GridItem*> items) : parent(nullptr) {
        Grid(position);
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
    Grid* getParent() { return parent; }
	  virtual ~Grid() {
		/*for (size_t index = items_.size() - 1; index >= 0; --index) {
			delete items_[index];
		}*/
	}
	  Grid* parent;

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
    Button() : GridItem(), locked_(false), parent(nullptr) {}
    Button(int position, Grid* caller) : GridItem(position), locked_(false), parent(caller) {} // buttons should always be in layer 0
    Button(int position, bool locked, State state, Grid* caller) : GridItem(position), parent(caller) {
        // Button(position);
        locked_ = locked;
        state_ = state;
    }
    bool isLocked() { return locked_; }
    void lock() { locked_ = true; }
    void unlock() { locked_ = false; }
    Grid* getParent() { return parent; }
    Grid* parent;

  protected:
    bool locked_;
};

#endif
