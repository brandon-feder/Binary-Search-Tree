#ifndef MOVIETREE_HPP
#define MOVIETREE_HPP

#include <string>

struct MovieNode
{
    int ranking;
    std::string title;
    int year;
    int quantity;
    MovieNode *parent = NULL; // I added this for convinience
    MovieNode *leftChild;
    MovieNode *rightChild;
    MovieNode(){};
    MovieNode(int in_ranking, std::string in_title, int in_year, int in_quantity)
    {
        ranking = in_ranking;
        title = in_title;
        year = in_year;
        quantity = in_quantity;
        parent = leftChild = rightChild = nullptr;
    }
};

class MovieTree
{
    public:
        MovieTree();
        ~MovieTree();
        void printMovieInventory();
        void addMovieNode(int ranking, std::string title, int releaseYear, int quantity);
        void findMovie(std::string title);
        void rentMovie(std::string title);
        void deleteMovie(std::string title);
        void countMovies();
        MovieNode *root = NULL; // I added this " =  NULL" to make my life just a little easier

    private:
        MovieNode *search(MovieNode *node, std::string title);
        void _printMovieInventory(MovieNode *node); //It makes more sence to use recursion to print the tree then an iteratieve loop
        int _countMovies(MovieNode *node); //It makes more sence to use recursion to count the tree then an iteratieve loop
        void _treeDesctrucor( MovieNode *node );
};
#endif // MOVIETREE_HPP
