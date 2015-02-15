#ifndef INVENTORY_H_INCLUDED
#define INVENTORY_H_INCLUDED

#include <iostream>

#include "ItemStack.h"

/**
 * An Inventory is composed of n slots. Each slot may store only
 * one type of item--specified by *slots*. 
 * <p>
 * Once all slots are filled, no additional Item types may be
 * stored. Individual slots may contain any number of the same 
 * Item.
 */
class Inventory{
    private:
        /**
         * Each Node represents one Inventory slot--i.e., space
         */
        struct Node{
            ItemStack data; ///< One ItemStack
            Node *next;     ///< Next ItemStack Node

            /**
             * Create an empty *Air* Node
             */
            Node();
            
            /**
             * Create a Node that contains an ItemStack, *s*
             */
            Node( ItemStack s );
        };

        Node *first;  ///< First inventory slot
        Node *last;   ///< Last inventory slot

        int slots;    ///< Capacity
        int occupied; ///< Number of occupied slots

        /**
         * Disassembles the list for Deconstructor
         */
        void disassemble();

    public:
        /**
         * Default to 10 slots
         */
        Inventory();

        /**
         * Create an inventory with n slots
         *
         * @pre n > 0
         */
        Inventory( int n );

        /**
         * Copy an already existing Inventory
         */
        Inventory( const Inventory &src );

        /**
         * Destruct an Inventory
         */
        ~Inventory();
        
        /**
         * Add one or more items to the inventory list
         *
         * @return true if *stack* was added and false otherwise
         */
        bool addItems( ItemStack stack );

        /**
         * Print a Summary of the Inventory and all Items contained within
         */
        void display( std::ostream &outs ) const;
        
        /**
         *
         */
        Inventory::Node* begin() const;

        /**
         *
         */
        Inventory::Node* end() const;

        /**
         * Overloaded assignment operator for Inventory
         */
        Inventory& operator=( const Inventory &rhs );
};

/**
 * Print the Inventory through use of the display member function
 */
inline std::ostream& operator<<( std::ostream &outs, const Inventory &prt ){
    prt.display( outs );
    return outs;
}

#endif