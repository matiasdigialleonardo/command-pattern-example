#include <iostream>
#include <vector>
#include <memory>

using namespace std;

// The Command interface
class Command {
public:
    virtual void execute() = 0;
    virtual string getDescription() = 0;
};

// Concrete commands
class OpenCommand : public Command {
public:
    void execute() override {
        cout << "This option would open a file" << endl;
    }

    string getDescription() override {
        return "Open a file";
    }
};

class SaveCommand : public Command {
public:
    void execute() override {
        cout << "This option would save a file" << endl;
    }

    string getDescription() override {
        return "Save a file";
    }
};

class ExitCommand : public Command {
public:
    void execute() override {
        cout << "This option would exit the program" << endl;
    }

    string getDescription() override {
        return "Exit the program";
    }
};

// Create a type alias for shared_ptr so creating one doesnt hurt to read
using SharedCommand = std::shared_ptr<Command>;

// Client
int main() {
    // Create a menu of commands using smart pointers
    vector<SharedCommand> menu;
    menu.push_back(make_shared<OpenCommand>());
    menu.push_back(make_shared<SaveCommand>());
    menu.push_back(make_shared<ExitCommand>());

    // Show the list of options by going through each command and getting their descriptions
    for (int i = 0; i < menu.size(); i++) {
        cout << (i + 1) << ". " << menu[i]->getDescription() << endl;
    }

    while (true) {
        // Simulate a menu selection while the choice is between range of the possible choices
        int choice;
        do {
            cout << "Enter your choice (1-" << menu.size() << "): ";
            cin >> choice;
        } while (choice < 1 || choice > menu.size());

        // Substract one for the index since we are showing the options starting from 0
        choice -= 1;
        menu[choice]->execute();

        if (menu[choice] == menu.back()) {
            /*
            Exit the loop if the "Exit" option is chosen
            The "Exit" option must be at the end of the vector
            since we are getting its last element for this
            */
            break;
        }
    }

    // Clean up
    menu.clear();

    return 0;
}
