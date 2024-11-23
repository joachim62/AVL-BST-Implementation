#include "../include/AVL.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>

struct Contact {
    std::string name;
    std::string phone;
    std::string email;
    std::string address;

    // Sort by name ( User in Contact )
    bool operator<(const Contact& other) const {
        return name < other.name;
    }

    bool operator>(const Contact& other) const {
        return name > other.name;
    }
};

class ContactManager {
private:
    ds::AVLTree<Contact> contacts;

public:
    void addContact(const std::string& name,
                   const std::string& phone,
                   const std::string& email,
                   const std::string& address) {
        contacts.insert(Contact{name, phone, email, address});
        std::cout << "Contact added: " << name << "\n";
    }

    void displayContacts() const {
        std::cout << "\nContact List (Alphabetically):\n";
        std::cout << "-----------------------------\n";
        std::cout << std::left
                  << std::setw(20) << "Name"
                  << std::setw(15) << "Phone"
                  << std::setw(25) << "Email"
                  << "Address\n";
        std::cout << std::string(75, '-') << "\n";

        contacts.inorder([](const Contact& contact) {
            std::cout << std::left
                      << std::setw(20) << contact.name
                      << std::setw(15) << contact.phone
                      << std::setw(25) << contact.email
                      << contact.address << "\n";
        });
    }

    bool searchContact(const std::string& name) const {
        Contact searchKey{name, "", "", ""};
        return contacts.contains(searchKey);
    }
};

int main() {
    ContactManager manager;

    // Adding sample contacts, with extra info
    manager.addContact("Diana", "176-820-2123", "Diana@email.com", "5 St Geogre");
    manager.addContact("Lumiere", "2689-4359", "Lumii@email.com", "2 Wonderful Street");
    manager.addContact("Alonzo", "60-125-30125", "Al0nZ0@email.com", "19B Inner Cast");
    manager.addContact("Chen", "+16-0308-2336", "Chen@email.com", "66 Santa Monica");
    manager.addContact("Gavi", "+5-369-0127", "Vivi@email.com", "03 Riad");

    // Display all contacts
    manager.displayContacts();

    // Search specific name
    std::string searchName = "Gavi";
    if (manager.searchContact(searchName)) {
        std::cout << "\nFound contact: " << searchName << "\n";
    } else {
        std::cout << "\nContact not found: " << searchName << "\n";
    }

    return 0;
}