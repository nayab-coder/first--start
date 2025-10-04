#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Passenger {
public:
    string name;
    int age;
    string seat_class;
    bool is_reserved;

    Passenger(string n = "", int a = 0, string cls = "", bool reserved = false)
        : name(n), age(a), seat_class(cls), is_reserved(reserved) {}
};

// Abstract Train class for abstraction
class Train {
protected:
    string train_name;
    int total_seats;
    int current_reservations;
    int current_waitlist;
    vector<Passenger> passengers;
    vector<Passenger> waitlist;

public:
    Train(string name, int seats)
        : train_name(name), total_seats(seats), current_reservations(0), current_waitlist(0) {}

    virtual void reserveSeat(string name, int age, string seat_class) = 0;
    virtual void deleteReservation(string name) = 0;
    virtual void displayReservations() = 0;
    virtual void displayAllReservedSeats() = 0;
    virtual void displayWaitlist() = 0;
    virtual void checkAvailableSeats() = 0;
    virtual void updateReservation(string name, string new_seat_class) = 0;
    virtual string getTrainName() = 0;
};

// Concrete class for Train implementing all functionalities
class ConcreteTrain : public Train {
public:
    ConcreteTrain(string name, int seats) : Train(name, seats) {}

    string getTrainName() override {
        return train_name;
    }

    void reserveSeat(string name, int age, string seat_class) override {
        if (current_reservations < total_seats) {
            passengers.push_back(Passenger(name, age, seat_class, true));
            current_reservations++;
            cout << "Reservation Successful!" << endl;
        } else {
            if (current_waitlist < 10) {
                waitlist.push_back(Passenger(name, age, seat_class, false));
                current_waitlist++;
                cout << "No seats available. Added to waitlist." << endl;
            } else {
                cout << "No more room in the waitlist. Reservation cannot be made." << endl;
            }
        }
    }

    void deleteReservation(string name) override {
        bool found = false;
        for (int i = 0; i < passengers.size(); i++) {
            if (passengers[i].name == name && passengers[i].is_reserved) {
                found = true;
                passengers.erase(passengers.begin() + i);
                current_reservations--;
                cout << "Reservation for " << name << " has been canceled." << endl;
                if (!waitlist.empty()) {
                    Passenger moved = waitlist.front();
                    moved.is_reserved = true;
                    passengers.push_back(moved);
                    waitlist.erase(waitlist.begin());
                    current_waitlist--;
                    current_reservations++;
                    cout << "Waitlisted passenger " << moved.name << " has been moved to reserved." << endl;
                }
                break;
            }
        }
        if (!found) {
            cout << "No reservation found for " << name << "." << endl;
        }
    }

    void displayReservations() override {
        if (passengers.empty()) {
            cout << "No reservations found." << endl;
            return;
        }
        for (Passenger p : passengers) {
            cout << "Name: " << p.name << ", Age: " << p.age
                 << ", Class: " << p.seat_class
                 << ", Reserved: " << (p.is_reserved ? "Yes" : "No") << endl;
        }
    }

    void displayAllReservedSeats() override {
        cout << "Reserved Seats for " << train_name << ":\n";
        bool reserved = false;
        for (int i = 0; i < passengers.size(); i++) {
            if (passengers[i].is_reserved) {
                cout << "Seat " << i + 1 << ": " << passengers[i].name << ", " << passengers[i].seat_class << endl;
                reserved = true;
            }
        }
        if (!reserved) {
            cout << "No reserved seats available.\n";
        }
    }

    void displayWaitlist() override {
        if (waitlist.empty()) {
            cout << "No passengers in the waitlist.\n";
            return;
        }
        cout << "Waitlist for " << train_name << ":\n";
        for (int i = 0; i < waitlist.size(); i++) {
            cout << "Waitlist " << i + 1 << ": " << waitlist[i].name << ", " << waitlist[i].seat_class << endl;
        }
    }

    void checkAvailableSeats() override {
        cout << "Available seats in " << train_name << ": " << total_seats - current_reservations << endl;
    }

    void updateReservation(string name, string new_seat_class) override {
        for (Passenger &p : passengers) {
            if (p.name == name) {
                p.seat_class = new_seat_class;
                cout << "Reservation for " << name << " updated to " << new_seat_class << " class." << endl;
                return;
            }
        }
        cout << "No reservation found for " << name << "." << endl;
    }
};

int main() {
    Train* train1 = new ConcreteTrain("Express 101", 5);
    Train* train2 = new ConcreteTrain("Superfast 202", 5);
    int choice;
    string name, seat_class, new_seat_class;
    int age;

    do {
        cout << "\nRailway Reservation System" << endl;
        cout << "1. Reserve Seat in Express 101" << endl;
        cout << "2. Reserve Seat in Superfast 202" << endl;
        cout << "3. View Reservations for Express 101" << endl;
        cout << "4. View Reservations for Superfast 202" << endl;
        cout << "5. Delete Reservation in Express 101" << endl;
        cout << "6. Delete Reservation in Superfast 202" << endl;
        cout << "7. View Reserved Seats in Express 101" << endl;
        cout << "8. View Reserved Seats in Superfast 202" << endl;
        cout << "9. View Waitlist in Express 101" << endl;
        cout << "10. View Waitlist in Superfast 202" << endl;
        cout << "11. Check Available Seats for Express 101" << endl;
        cout << "12. Check Available Seats for Superfast 202" << endl;
        cout << "13. Update Reservation in Express 101" << endl;
        cout << "14. Update Reservation in Superfast 202" << endl;
        cout << "15. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter name: "; cin >> name;
                cout << "Enter age: "; cin >> age;
                cout << "Enter seat class (AC / Sleeper): "; cin >> seat_class;
                train1->reserveSeat(name, age, seat_class);
                break;
            case 2:
                cout << "Enter name: "; cin >> name;
                cout << "Enter age: "; cin >> age;
                cout << "Enter seat class (AC / Sleeper): "; cin >> seat_class;
                train2->reserveSeat(name, age, seat_class);
                break;
            case 3:
                cout << "\nReservations for " << train1->getTrainName() << ":" << endl;
                train1->displayReservations();
                break;
            case 4:
                cout << "\nReservations for " << train2->getTrainName() << ":" << endl;
                train2->displayReservations();
                break;
            case 5:
                cout << "Enter name to delete reservation: "; cin >> name;
                train1->deleteReservation(name);
                break;
            case 6:
                cout << "Enter name to delete reservation: "; cin >> name;
                train2->deleteReservation(name);
                break;
            case 7:
                train1->displayAllReservedSeats();
                break;
            case 8:
                train2->displayAllReservedSeats();
                break;
            case 9:
                train1->displayWaitlist();
                break;
            case 10:
                train2->displayWaitlist();
                break;
            case 11:
                train1->checkAvailableSeats();
                break;
            case 12:
                train2->checkAvailableSeats();
                break;
            case 13:
                cout << "Enter name to update reservation: "; cin >> name;
                cout << "Enter new seat class (AC / Sleeper): "; cin >> new_seat_class;
                train1->updateReservation(name, new_seat_class);
                break;
            case 14:
                cout << "Enter name to update reservation: "; cin >> name;
                cout << "Enter new seat class (AC / Sleeper): "; cin >> new_seat_class;
                train2->updateReservation(name, new_seat_class);
                break;
            case 15:
                cout << "Exiting system." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }

    } while (choice != 15);

    delete train1;
    delete train2;
    return 0;
}
