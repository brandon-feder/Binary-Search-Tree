#include "MovieTree.hpp"

MovieTree::MovieTree() {}

MovieTree::~MovieTree()
{
    _treeDesctrucor(root);
}

// Gets a pointer to the node with the given title in the given subtree
MovieNode *MovieTree::search( MovieNode *node, std::string title )
{
    if( node == NULL ) // If the current node does not exists
    {
            return NULL; // Return NULL meaning no movie of that title is in the tree
    } else if( node->title.compare( title ) == 0 ) // If the title is equal to that of the current node
    {
        return node; // Return the current node
    } else if( node->title.compare( title ) > 0 ) // If the title is greater less than that of the current node
    {
        return search( node->leftChild, title ); // Run this function again on the left subtree
    } else // Otherwise
    {
        return search( node->rightChild, title ); // Run this function again on the right subtree
    }
}

void MovieTree::addMovieNode(int ranking, std::string title, int releaseYear, int quantity)
{
    MovieNode *newNode = new MovieNode(ranking, title, releaseYear, quantity);

    if( root == NULL )
    {
        root = newNode;
    } else
    {
        MovieNode *currentNode = root;

        while( true )
        {
            // *Note* no two movies have the same name so that case can be ignored

            bool isGreater = currentNode->title.compare( newNode->title ) > 0;

            if( isGreater ) // The current node is greater than the new node
            {
                if( currentNode->leftChild == NULL ) // If the left child does not exist
                {
                    newNode->parent = currentNode;
                    currentNode->leftChild = newNode; // Set the new node as the left child
                    break;
                } else { // If the left child hsa a child
                    currentNode = currentNode->leftChild; // set the currentNode to be the left child
                }
            } else // The current node is less than the new node
            {
                if( currentNode->rightChild == NULL ) // If the right child does not exist
                {
                    newNode->parent = currentNode;
                    currentNode->rightChild = newNode; // Set the new node as the right child
                    break;
                } else { // If the right child exists
                    currentNode = currentNode->rightChild;  // set the currentNode to be the right child
                }
            }
        }
    }
}

// Finds a movie by its title
void MovieTree::findMovie(std::string title)
{
    MovieNode *node = search( root, title ); // Get a pointer to the movie ( or NULL if it does not exist )

    if( node == NULL ) // If the mooie does not exist
    {
        std::cout << std::endl << "Error: Movie Not Found" << std::endl << std::endl;
    } else // If the movie does exist
    {
        // Print info about the movie
        std::cout << std::endl << "========= Info About Your Movie ==========" << std::endl;
        std::cout << "Title: " << title << std::endl;
        std::cout << "Rank: " << node->ranking << std::endl;
        std::cout << "Year: " << node->year << std::endl;
        std::cout << "Quantity: " << node->quantity << std::endl;
        std::cout << "==========================================" << std::endl << std::endl;
    }

}

// Rent a movie by title
void MovieTree::rentMovie( std::string title )
{

    MovieNode *node = search( root, title ); // Get a pointer to the movie ( or NULL if it does not exist )

    if( node == NULL ) // If the mooie does not exist
    {
        std::cout << std::endl << "Error: Movie Not Found" << std::endl << std::endl;
    } else if( node->quantity == 0 ) // If the movie is out of stock
    {
        std::cout << "Error: Movie out of stock" << std::endl;
    } else // If the movie does exist
    {
        node->quantity -= 1; // Reduce its quantity by once

        // Prin out info about it
        std::cout << std::endl << "========= Info About Your Movie ==========" << std::endl;
        std::cout << "Title: " << title << std::endl;
        std::cout << "Rank: " << node->ranking << std::endl;
        std::cout << "Year: " << node->year << std::endl;
        std::cout << "Quantity: " << node->quantity << std::endl;
        std::cout << "==========================================" << std::endl << std::endl;
    }
}

// Prints the inventory of movies
void MovieTree::printMovieInventory()
{
    std::cout << std::endl << "========= Info About The Inventory ==========" << std::endl;
    _printMovieInventory(root);
    std::cout << "==========================================" << std::endl << std::endl;
}

void MovieTree::_printMovieInventory(MovieNode *node)
{
    if( node != NULL ) // If the node exists
    {
        // Run this function on the left
        _printMovieInventory( node->leftChild );

        // Print info about the movie
        std::cout << node->title << ": " << node->quantity << std::endl;

        // Run this function on the right
        _printMovieInventory(node ->rightChild);

    }
}

void MovieTree::countMovies()
{
    std::cout << std::endl << "========= Movie Count ==========" << std::endl;
    std::cout << "There are " << _countMovies( root ) << " movies" << std::endl;
    std::cout << "==========================================" << std::endl << std::endl;
}

int MovieTree::_countMovies( MovieNode *node )
{
    if(node != NULL) // If the movie exists
    {
        // Return 1 + count of the right subtree + count of the left subtree
        return 1 + _countMovies( node->rightChild ) + _countMovies( node->leftChild );
    } else {
        return 0;
    }
}

void MovieTree::deleteMovie(std::string title)
{
    // ====== Step One: Get the current node ( and its parent ) ======
    MovieNode *node = search( root, title );


    // Test whether the node was found
    if(node == NULL)
    {
        std::cout << "Error: Node to delete does not exist" << std::endl;
    } else
    {
        MovieNode *parent = node->parent;

        // ===================================================
        // ====== Case 1 - The node to delete is a leaf ======
        // ===================================================

        if( node->rightChild == NULL && node->leftChild == NULL )
        {
            if( node == root ) // Special Case - Node is root
            {
                delete root; // Delete the node from memory
                root = NULL; // Set the root to NULL
            } else // If the node to delete is not the root
            {
                if( parent->rightChild == node ) // If the node is its parents right child
                {
                    delete node; // Delete the node
                    parent->rightChild = NULL; // Set the parents right child to be NULL
                } else // If the node is its parents left child
                {
                    delete node; // Delete the node
                    parent->leftChild = NULL; // Set the left child to be NULL
                }
            }
        }

        // ===================================================
        // == Case 2 - The node to delete has two children ===
        // ===================================================
        else if(  node->rightChild != NULL && node->leftChild != NULL )
        {
            // Special Case - The right node is the successor
            if( node->rightChild->leftChild == NULL )
            {
                if( parent->rightChild == node ) // If the parents right child is the node
                {
                    parent->rightChild = node->rightChild; // Set the parents right child to be the nodes right child
                } else
                {
                    parent->leftChild = node->rightChild; // Set the parents right child to be the nodes left child
                }
                node->rightChild->parent = parent; // Set the nodes rightChild's parent to be the nodes parent
                node->rightChild->leftChild = node->leftChild;

                delete node; // Delete the node
            }

            // If the node's successor is its right then leftmost child
            else
            {
                MovieNode *successor = node->rightChild->leftChild;

                while( successor->leftChild != NULL )
                {
                    successor = successor->leftChild;
                }

                successor->parent = ( root == node ) ? NULL : parent;
                parent->rightChild = successor;
                successor->parent->leftChild = successor->rightChild;
                successor->rightChild->parent = successor->parent;
            }
        }

        // ===================================================
        //  Case 3 - The node to delete has a left child only
        // ===================================================
        else if( node->leftChild != NULL && node->rightChild == NULL )
        {
            if( root == node )
            {
                root = root->leftChild;
            } else
            {
                if( parent->leftChild  == node)
                {
                    parent->leftChild = node->leftChild;
                } else
                {
                    parent->rightChild = node->leftChild;
                }
            }

            delete node;
        }

        // ===================================================
        //  Case 4 - The node to delete has a right child only
        // ===================================================

        else
        {
            if( root == node )
            {
                root = root->rightChild;
            } else
            {
                if( parent->leftChild  == node)
                {
                    parent->leftChild = node->rightChild;
                } else
                {
                    parent->rightChild = node->rightChild;
                }
            }

            delete node;
        }
    }
}

void MovieTree::_treeDesctrucor(MovieNode *node)
{
    if( node != NULL ) // If the current pointer points to a movie
    {
        _treeDesctrucor( node->leftChild ); // Delete its left subtree

        MovieNode *right = node->rightChild; // Stores a pointer to the right subtree
        delete node; // Delete the current node

        _treeDesctrucor(right); // Delete the right subtree
    }
}
