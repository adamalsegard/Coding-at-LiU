#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "dsexceptions.h"
#include <algorithm>
#include <memory>
#include <iomanip>

using namespace std;

// BinarySearchTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class BinarySearchTree
{
public:
    BinarySearchTree( ) : root { nullptr }
    {
    }

    /**
     * Copy constructor
     */
    BinarySearchTree( const BinarySearchTree & rhs ) : root { nullptr }
    {
        root = clone( rhs.root , weak_ptr<BinaryNode>());
    }

    /**
     * Move constructor
     */
    BinarySearchTree( BinarySearchTree && rhs ) : root { rhs.root }
    {
        rhs.root = nullptr;
    }

    /**
     * Destructor for the tree
     */
    ~BinarySearchTree( )
    {
        makeEmpty( );
    }

    /**
     * Copy assignment
     */
    BinarySearchTree & operator=( const BinarySearchTree & rhs )
    {
        BinarySearchTree copy = rhs;
        std::swap( *this, copy );
        return *this;
    }

    /**
     * Move assignment
     */
    BinarySearchTree & operator=( BinarySearchTree && rhs )
    {
        std::swap( root, rhs.root );
        return *this;
    }


    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException { };
        return findMin( root )->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMax( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException { };
        return findMax( root )->element;
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const
    {
        return root == nullptr;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree( ostream & out = cout ) const
    {
        if( isEmpty( ) )
            out << "Empty tree" << endl;
        else
            printTree( root, out, 0 );
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( const Comparable & x )
    {
        insert( x, root , nullptr);
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( Comparable && x )
    {
        insert( std::move( x ), root , nullptr);
    }

    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove( const Comparable & x )
    {
        remove( x, root );
    }

    //Test function
    Comparable get_parent(const Comparable &x)
    {
        return get_parent(x, root);
    }

    void find_pred_succ(const Comparable &x, Comparable &a, Comparable &b)
    {
        if (isEmpty())
        {
            return;
        }

        auto base = root;

        while (base)
        {
            if (base->element == x)
            {
                auto rightSmallest = findMin(base->right);
                auto leftLargest = findMax(base->left);

                if (rightSmallest) b = rightSmallest->element;
                if (leftLargest) a = leftLargest->element;

                return;
            }

            else if (x < base->element)
            {
                b = base->element;
                base = base->left;
            }

            else
            {
                a = base->element;
                base = base->right;
            }
        }
    }

private:
    struct BinaryNode
    {
        Comparable element;
        shared_ptr<BinaryNode> left;
        shared_ptr<BinaryNode> right;
        weak_ptr<BinaryNode> parent;

        BinaryNode( const Comparable & theElement, shared_ptr<BinaryNode> lt, shared_ptr<BinaryNode> rt, weak_ptr<BinaryNode> _parent )
            : element { theElement }, left { lt }, right { rt }, parent {_parent} { }

        BinaryNode( Comparable && theElement, shared_ptr<BinaryNode> lt, shared_ptr<BinaryNode> rt, weak_ptr<BinaryNode> _parent )
            : element { std::move( theElement ) }, left { lt }, right { rt }, parent {_parent} { }
    };

    shared_ptr<BinaryNode> root;



    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( const Comparable & x, shared_ptr<BinaryNode> &t, const shared_ptr<BinaryNode> & parent )
    {
        if( !t )
            t = make_shared<BinaryNode>( x, nullptr, nullptr, parent );
        else if( x < t->element )
            insert( x, t->left, t );
        else if( t->element < x )
            insert( x, t->right, t );
        else
        {
            ;  // Duplicate; do nothing
        }
    }

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( Comparable && x, shared_ptr<BinaryNode> &t, shared_ptr<BinaryNode> /*&*/parent )
    {
        if(!t)
            t = make_shared<BinaryNode>( std::move(x), nullptr, nullptr, parent );
        else if( x < t->element )
            insert( std::move( x ), t->left, t );
        else if( t->element < x )
            insert( std::move( x ), t->right, t );
        else
        {
            ;  // Duplicate; do nothing
        }
    }

    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove( const Comparable & x, shared_ptr<BinaryNode> &t)
    {
        if( !t )
            return;   // Item not found; do nothing
        if( x < t->element )
            remove( x, t->left);
        else if( t->element < x )
            remove( x, t->right);
        else if(t->left && t->right) // Two children
        {
            t->element = findMin( t->right )->element;
            remove( t->element, t->right);
        }
        else
        {
            shared_ptr<BinaryNode> oldNode = t; // oldNode gets deleted when it goes out of scope
            t = (t->left) ? t->left : t->right;
            if (!t) return;
            t->parent = oldNode->parent;//.lock();
        }
    }

    Comparable get_parent(const Comparable &x, shared_ptr<BinaryNode> &t)
    {
        if (!t)
            return Comparable();
        if (x < t->element)
            return get_parent(x, t->left);
        else if (t->element < x)
            return get_parent(x, t->right);
        else
        {
            auto parent = t->parent.lock();

            if (parent)
                return parent->element;
            else
                return Comparable();
        }
    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    shared_ptr<BinaryNode> findMin( shared_ptr<BinaryNode> t ) const
    {
        if( !t )
            return nullptr;
        if( !t->left )
            return t;
        return findMin( t->left );
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    shared_ptr<BinaryNode> findMax( shared_ptr<BinaryNode> t ) const
    {
        if( t )
            while( t->right )
                t = t->right;
        return t;
    }

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty( shared_ptr<BinaryNode> &t )
    {
        if(t)
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
        }

        t = nullptr;
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     * In-order traversal is used
     */
    void printTree( shared_ptr<BinaryNode> t, ostream & out, unsigned currentDepth ) const
    {
        if(t)
        {
            out << setw(2 * currentDepth + 2) << t->element << endl;
            printTree( t->left, out , currentDepth + 1);
            printTree( t->right, out, currentDepth + 1);
        }
    }

    /**
     * Internal method to clone subtree.
     */
    shared_ptr<BinaryNode> clone( const shared_ptr<BinaryNode> t,   const weak_ptr<BinaryNode> & par) const
    {
        if( !t )
            return nullptr;
        else
        {
            shared_ptr<BinaryNode> temp = make_shared<BinaryNode>( t->element, nullptr, nullptr, par);
            temp->left = clone(t->left, temp);
            temp->right = clone(t->right, temp);

            return temp;
        }
           // return make_shared<BinaryNode>( t->element, clone(t->left, ???), clone(t->right)), nullptr );
    }

public:
    class BiIterator
    {
        friend class BinarySearchTree;

    public:


        Comparable operator*()
        {
            return current->element;
        }

        Comparable* operator->() const
        {
            //return current.get();
            return &current->element;
        }

        bool operator==( const BiIterator &x) const
        {
            return(current == x.current);
        }

        bool operator!=(const BiIterator &x) const
        {
            return (current != x.current);
        }

        // auto newIterator = ++iterator;
        BiIterator& operator++()
        {
            if (current && current->right)
            {
                // going down to the right
                //   C        C = current
                //    \       N = next
                //     X
                //    / \
                //   N   X

                current = current->right;
                //   X        C = current
                //    \       N = next
                //     C
                //    / \
                //   N   X

                while (current->left)
                {
                    current = current->left;
                    //   X        C = current
                    //    \       N = next
                    //     X
                    //    / \
                    //   C   X
                }
            }

            else
            {
                shared_ptr<BinaryNode> last = current;

                //   C        L = last
                //  / \       C = current
                // L   O
                while (current && current->left != last)
                {
                    // going up!
                    last = current;
                    current = current->parent.lock();
                }
            }

            return *this;
        }

        // auto oldIterator = iterator++;
        BiIterator operator++(int)
        {
            BiIterator old(this->current);

            ++(*this);

            return old;
        }

        // auto newIterator = --iterator;
        BiIterator& operator--()
        {
            if (current && current->left)
            {
                current = current->left;

                while (current->right)
                {
                    current = current->right;
                }
            }

            else
            {
                shared_ptr<BinaryNode> last = current;

                while (current && current->right != last)
                {
                    // going up!
                    last = current;
                    current = current->parent.lock();
                }
            }

            return *this;
        }

        // auto oldIterator = iterator--;
        BiIterator operator--(int)
        {
            BiIterator old(this->current);

            --(*this);

            return old;
        }



    private:
        BiIterator()
            : current(nullptr) {}

        BiIterator(shared_ptr<BinaryNode> base)
            : current(base) {}

        shared_ptr<BinaryNode> current;
    };


    BiIterator end()
    {
        return BiIterator();
    }

    BiIterator begin()
    {
        if (isEmpty())
        {
            return end();
        }

        return BiIterator(findMin(root));
    }

    /**
     * Returns true if x is found in the tree.
     */
    BiIterator contains( const Comparable & x ) const
    {
        return contains( x, root );
    }

private:
    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the subtree.
     */
    BiIterator contains( const Comparable & x, shared_ptr<BinaryNode> t ) const
    {
        if( !t )
            return BiIterator();
        else if( x < t->element )
            return contains( x, t->left );
        else if( t->element < x )
            return contains( x, t->right );
        else
            return BiIterator(t);    // Match
    }
    /****** NONRECURSIVE VERSION*************************
        bool contains( const Comparable & x, shared_ptr<BinaryNode> t ) const
        {
            while( t != nullptr )
                if( x < t->element )
                    t = t->left;
                else if( t->element < x )
                    t = t->right;
                else
                    return true;    // Match

            return false;   // No match
        }
    *****************************************************/

};

#endif
