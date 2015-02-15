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
	this->first    = new Node(*src.first);
	this->last     = new Node(*src.last);
	this->slots    = src.slots;
	this->occupied = src.occupied;

	for( Node *iterator = src.begin(); iterator != src.end(); iterator = iterator->next ) {
		this->addItems( iterator->data );
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
	
	Node* new_node = nullptr;

	// Implements a new Inventory, if no ItemStacks exist
	if(this->first == nullptr) {

		// Sets new_node equal to a new node containing the current ItemStack
		new_node = new Node(stack);

		// Sets the first node in the Inventory to the new Node
		this->first = new_node;

		// Sets the last node in the Inventory to the new Node
		this->last = new_node;

		// Sets the new_node back to a nullptr;
		new_node = nullptr;

		// Increments the occupied slots by one
		occupied++;

		return true;

	} else if(this->first != nullptr) {
	// Adds a new item to the Inventory if the Inventory is not empty

		// Sets the iterator to the last node in the Inventory
		Node *iterator = this->last;

		// Runs until all avaliable slots in an Inventory are full
		while(occupied < slots) {

			// Sets new_node equal to a new node containing the current ItemStack
			new_node = new Node(stack);

			// Sets the last node in the Inventory to the new_node
			iterator = new_node;

			// Points the last node in the Inventory to a nullptr
			iterator = iterator->next;

			// Sets the new_node back to a nullptr
			new_node = nullptr;

			// Increments the occupied slots by one
			occupied++;

			return true;

		}
	}
} 

/**
 * Used to display the output format 
 */
void Inventory::display( std::ostream &outs ) const{

	  outs << std::left << std::setw(3) << " -Used " << occupied << " of " << slots << " slots"; 
	 
	  for( Node *item = this->first; item != nullptr; item = item->next ) {
	  		outs<< std::left << std::setw(3) << "\n" << item->data;
	  }
}

/**
 * Returns head of the list
 */
Inventory::Node* Inventory::begin() const{
	return this->first;
}

/**
 * Returns tail(nullptr) of the list
 */
Inventory::Node* Inventory::end() const{
	return nullptr;
}

/**
 * Overloaded Assignment Operator
 */
 Inventory &Inventory::operator=( const Inventory &rhs ){
    // Prevents self assignment
    if( this != &rhs ){
    	// Destroys the current Nodes
    	disassemble();

    	for( Node *iterator = rhs.begin(); iterator != rhs.end(); iterator = iterator->next ){
    		this->addItems( iterator->data );
    	}
    }

    return *this;
 }

