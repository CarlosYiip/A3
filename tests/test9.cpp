#include "Graph.h"

// use book class custom data type
// with < operator overloaded

// test printing and memory leak check

class Book {
public:
    Book(const std::string& name, const std::string& author,
         int isbn, double price);

    // getters

    // Defining member functions within the class definition should be
    // avoided as they reduce readability. Single line definitions are
    // (mostly) ok but for anything else use explicit inline defn.
    int getIsbn() const { return isbn_; }
    double getPrice() const;

    // Friend comparison operators
    friend bool operator<(const Book& a, const Book& b);
    friend bool operator>(const Book& a, const Book& b);
    friend bool operator==(const Book& a, const Book& b);
    friend bool operator!=(const Book& a, const Book& b);

    friend std::ostream& operator<<(std::ostream& out, const Book& b);
private:
  std::string name_;
  std::string author_;
  int isbn_;
  double price_;
};

Book::Book(const std::string& name, const std::string& author,
           int isbn, double price) :
    name_{name}, author_{author}, isbn_{isbn}, price_{price}
{ }

inline double Book::getPrice() const  { return price_; }


bool operator<(const Book& a, const Book& b)
{
    return a.isbn_ < b.isbn_;
}

bool operator>(const Book& a, const Book& b)
{
    return a.isbn_ > b.isbn_;
}

bool operator==(const Book& a, const Book& b)
{
    return a.isbn_ == b.isbn_;
}

bool operator!=(const Book& a, const Book& b)
{
    return a.isbn_ != b.isbn_;
}


// Note: the use of the C++11 raw string R"( .... )" syntax.
std::ostream& operator<<(std::ostream& out, const Book& b)
{
    return out << "Name: \"" << b.name_ << "\", "
               << R"xxx(Author: ")xxx" << b.author_ << R"(", )"
               << "ISBN: " << b.isbn_ << ", "
               << "Price: " << b.price_;
}

int main() {
	
	gdwg::Graph<Book,double> g;
	
	Book b1("LOTR","JRR",321,40);
	Book b2("The Hobbit","JRR",320,20);
	Book b3("Lion, Witch, Wardrobe","Lewis",200,15);
	Book b4("Alice in Wonderland","Carrol",100,10);
	Book b5("Harry Potter","Rolling",400,40);
	
	g.addNode(b1);
	g.addNode(b2);
	g.addEdge(b1,b2,1.0);
	g.addEdge(b2,b1,1.0);
	
	g.addNode(b3);
	g.addEdge(b3,b2,0.5);
	g.addNode(b4);
	g.addEdge(b3,b4,0.5);
	
	g.addNode(b5);
	g.addEdge(b5,b2,0.25);
	
	g.printNodes();
	
	g.printEdges(b3);
	
	// get an iterator
	auto it = g.begin();
	
	// delete a node
	g.deleteNode(b2);
	
	// print the graph and the edges
	g.printEdges(b3);
	g.printNodes();
	
}

