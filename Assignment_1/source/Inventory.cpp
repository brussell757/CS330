#include <utility>
#include <iomanip>
#include "Inventory.h"

// Allow the compiler to define the remaining 
// comparison operators
using namespace std::rel_ops;

/**
 * Call to Node Constructor
 */
Inventory::Node::Node()
    :data( Item(0, "Air"), 0 )
{
    this->next = nullptr;
}

/**
 * Call to Node Constructor with arguments
 */
Inventory::Node::Node( ItemStack s )
    :data(s)
{
    this->next = nullptr;
}

/**
 * Default constructor
 */
Inventory::Inventory(){
    this->first    = nullptr;
    this->last     = nullptr;
    this->slots    = 10;
    this->occupied = 0;
}

/**
 * Constructor with arguments
 */
Inventory::Inventory(int n){
	this->first    = nullptr;
	this->last     = nullptr;
	this->slots    = n;
	this->occupied = 0;
}

/**
 * Copy Constructor
 */
Inventory::Inventory(const Inventory &src){
	this->first    = nullptr; // Set the copy constructor's head to nullptr
	this->last     = nullptr; // Set the copy constructor's tail to nullptr
	this->slots    = src.slots;
	this->occupied = 0; // Set the copy constructor's occupied slots to 0

	
	// Traverses the source Inventory 
	for( Node *iterator = src.begin(); iterator != nullptr; iterator = iterator->next ) {

		this->addItems( iterator->data ); // Adds items to the copy constructor 

	}
}

/**
 * Destructor
 */
Inventory::~Inventory(){	
	disassemble();
}

/**
 * Disassemble the list (Called in the Destructor)
 */
void Inventory::disassemble(){

	Node *this_iterator = this->first; // Set to head node
    Node *to_delete = nullptr; // Node to delete

    // Iterate through list and delete each node
	while( this_iterator != nullptr ){
		to_delete = this_iterator;

		// Sets this_iterator to the next node
		this_iterator = this_iterator->next; 

		// Deletes this node
		delete to_delete;
		
		// Used to avoid dangling pointers 
		to_delete = nullptr;
	}

}

/**
 * Used to add items to the Inventory
 */
bool Inventory::addItems ( ItemStack stack ){

	//Setting new node here would cause memory leaks

	if(this->first == nullptr) {

		// Sets new_node equal to a new node containing the current ItemStack
    	Node *new_node = new Node(stack);

		this->first = new_node; // Sets the first node to the current ItemStack

		this->last = new_node; // Sets the last node to the current ItemStack

		this->occupied++; // Increments the number of occupied slots by one

		return true;

	} else {

		// Traverses the current Inventory
		for(Node *iterator = this->first; iterator != nullptr; iterator = iterator->next) {

			// Statement that merges ItemStacks with the same ID and updates the quantity of that ItemStack
			if(stack == iterator->data) {

				(iterator->data).ItemStack::addItems(stack.size());

				return true;

			}

		}

		// Statement that adds an ItemStack to the end of the list until all avaliable slots are taken
		if(this->occupied < slots) {

			// Sets new_node equal to a new node containing the current ItemStack
   			Node *new_node = new Node(stack);

			(this->last)->next = new_node; // Sets the node immediatley after the last node to the new ItemStack

			this->last = new_node; // Sets the last node to the new ItemStack

			occupied++; // Increments the number of occupied slots by one

			return true;

		} else if (occupied > slots) {
		// Statement that returns false and displays 'Discarded' if all avaliable slots are occupied

			return false;

		}

	}

} 

 /**
 * Used to display the output format 
 */
void Inventory::display( std::ostream &outs ) const{

	outs << std::left << std::setw(3) << "\n" << " -Used " << occupied << " of " << slots << " slots"; 

	for(Node *iterator = this->first; iterator != nullptr; iterator = iterator->next) {	

		outs<< std::left << std::setw(3) << "\n" << iterator->data;
	}
}

/**
 * Returns head of the list
 */
Inventory::Node* Inventory::begin() const{
	return this->first;
}

/**
 * Overloaded Assignment Operator
 */
Inventory &Inventory::operator=( const Inventory &rhs ){
    // Prevents self assignment
    if( this != &rhs ){
    	// Destroys the current Nodes
    	disassemble();

    	for( Node *iterator = rhs.begin(); iterator != nullptr; iterator = iterator->next ){
    		this->addItems( iterator->data );
    	}
    }

    return *this;
 }

