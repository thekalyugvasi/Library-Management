#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

// Define Book class
class Book {
private:
    string title;
    string author;
    string isbn;
    string genre;
    bool available;

public:
    // Constructor
    Book(string title, string author, string isbn, string genre) :
        title(title), author(author), isbn(isbn), genre(genre), available(true) {}

    // Getter methods
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getISBN() const { return isbn; }
    string getGenre() const { return genre; }
    bool isAvailable() const { return available; }

    // Setter method for availability
    void setAvailability(bool availability) { available = availability; }

    // Print book details
    void printDetails() const {
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "ISBN: " << isbn << endl;
        cout << "Genre: " << genre << endl;
        cout << "Availability: " << (available ? "Available" : "Not Available") << endl;
    }
};

// Define Patron class
class Patron {
private:
    string name;
    string contactInfo;

public:
    // Constructor
    Patron(string name, string contactInfo) : name(name), contactInfo(contactInfo) {}

    // Getter methods
    string getName() const { return name; }
    string getContactInfo() const { return contactInfo; }
};

// Define Library class
class Library {
private:
    vector<Book> books;
    vector<Patron> patrons;

public:
    // Add book to library
    void addBook(const Book& book) {
        books.push_back(book);
    }

    // Remove book from library
    void removeBook(const string& isbn) {
        for (auto it = books.begin(); it != books.end(); ++it) {
            if (it->getISBN() == isbn) {
                books.erase(it);
                cout << "Book with ISBN " << isbn << " removed from the library." << endl;
                return;
            }
        }
        cout << "Book with ISBN " << isbn << " not found in the library." << endl;
    }

    // Add patron to library
    void addPatron(const Patron& patron) {
        patrons.push_back(patron);
    }

    // Remove patron from library
    void removePatron(const string& name) {
        for (auto it = patrons.begin(); it != patrons.end(); ++it) {
            if (it->getName() == name) {
                patrons.erase(it);
                cout << "Patron " << name << " removed from the library." << endl;
                return;
            }
        }
        cout << "Patron " << name << " not found in the library." << endl;
    }

    // Search for a book by title
    void searchBook(const string& title) const {
        bool found = false;
        for (const auto& book : books) {
            if (book.getTitle() == title) {
                book.printDetails();
                found = true;
            }
        }
        if (!found)
            cout << "Book with title \"" << title << "\" not found in the library." << endl;
    }

    // Save library data to file
    void saveLibraryData(const string& filename) const {
        ofstream outFile(filename);
        if (!outFile) {
            cerr << "Error: Unable to open file for writing." << endl;
            return;
        }

        // Write books data
        for (const auto& book : books) {
            outFile << book.getTitle() << "," << book.getAuthor() << ","
                    << book.getISBN() << "," << book.getGenre() << ","
                    << (book.isAvailable() ? "Available" : "Not Available") << endl;
        }

        // Write patrons data
        for (const auto& patron : patrons) {
            outFile << patron.getName() << "," << patron.getContactInfo() << endl;
        }

        outFile.close();
        cout << "Library data saved successfully to " << filename << endl;
    }
};

int main() {
    Library library;

    // Sample data
    Book book1("The Great Gatsby", "F. Scott Fitzgerald", "9780743273565", "Fiction");
    Book book2("To Kill a Mockingbird", "Harper Lee", "9780061120084", "Fiction");
    Patron patron1("John Doe", "john@example.com");
    Patron patron2("Jane Smith", "jane@example.com");

    // Add books to library
    library.addBook(book1);
    library.addBook(book2);

    // Add patrons to library
    library.addPatron(patron1);
    library.addPatron(patron2);

    // Search for a book
    cout << "Searching for a book by title..." << endl;
    library.searchBook("To Kill a Mockingbird");
    
    // Remove a book
    cout << "\nRemoving a book from the library..." << endl;
    library.removeBook("9780743273565");

    // Remove a patron
    cout << "\nRemoving a patron from the library..." << endl;
    library.removePatron("John Doe");

    // Save library data to file
    library.saveLibraryData("library_data.txt");

    return 0;
}

