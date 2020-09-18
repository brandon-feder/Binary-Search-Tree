#include <iostream>
#include <fstream>
#include <sstream>

#include "./MovieTree.cpp"

MovieTree initMovieTree( std::string file );
std::string getMovieTitle();

int main(int argc, char *argv[]) {

    // The BST with all the movies
    MovieTree movies = initMovieTree(std::string(argv[1]));

    bool quit = false; // Quit flag
    while(!quit) // Until quit flag is true
    {
        // Pring the menu
        std::cout  <<  "======Main Menu======" << std::endl;
        std::cout  <<  "1. Find a movie" << std::endl;
        std::cout  <<  "2. Rent a movie" << std::endl;
        std::cout  <<  "3. Print the inventory" << std::endl;
        std::cout  <<  "4. Delete a movie" << std::endl;
        std::cout  <<  "5. Count movies" << std::endl;
        std::cout << "6. Quit" << std::endl;

        int menuOption; // The menu option the user chooses

        // Get the users input
        std::cout << "Your option: ";
        std::cin >> menuOption;

        // Determine what the user wants to do
        switch( menuOption )
        {
            case 1: // Find a movie by title
                movies.findMovie( getMovieTitle() );
                break;

            case 2: // Rent a movie by title
                movies.rentMovie( getMovieTitle() );
                break;

            case 3: // Print the movie inventory
                movies.printMovieInventory();
                break;

            case 4: // Deletes a movie by title
                movies.deleteMovie( getMovieTitle() );
                break;

            case 5: // Counts the number of available movies
                movies.countMovies();
                break;

            case 6: // Quit
                quit = true;
                break;

            default:
              std::cout << "Invalid input." << std::endl;
        }
    }
}

MovieTree initMovieTree(std::string file)
{
    // The Tree with all the movies
    MovieTree movies = MovieTree();

    // File being read from
    std::ifstream input (file);

    if(!input) // If the file is not valid
    {
        // Report error then exit
        std::cout << "Invalid File" << std::endl;
        exit(1);
    } else // If file is valid
    {
        // Buffer the lin ewill be read into
        std::string line;
        while(std::getline(input, line)) // Read the line until eof
        {
            std::istringstream ss(line); // Create a stringstream containing the line read

            // Setup temporary variables
            std::string rank_str;
            std::string quantity_str;
            std::string year_str;

            std::string title;
            int rank;
            int quantity;
            int year;

            // Read each part of the line
            std::getline(ss, rank_str, ',');
            std::getline(ss, title, ',');
            std::getline(ss, year_str, ',');
            std::getline(ss, quantity_str, ',');

            // Convert numeric values to actuall integers
            rank = std::stoi( rank_str );
            quantity = std::stoi( quantity_str );
            year = std::stoi( year_str );

            // Create a MovieNode with the movie info
            movies.addMovieNode( rank, title, year, quantity);
        }
    }

    // Return the tree of movies
    return movies;
}

// Get the title of the movie from the user
std::string getMovieTitle()
{
    std::string title;
    std::cout << "Which Movie?: ";
    std::cin.ignore();
    std::getline(std::cin, title);
    return title;
}
