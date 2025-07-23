#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <map>
#include <cstring>
#include <limits>
#include <iomanip>

using namespace std;

struct Train {
    int train_no;
    string train_name;
    vector<string> stations;
    string departure;
    string arrival;
    int seats_available;
};

struct PassengerRail {
    string name;
    string seat_no;
};

struct Ticket {
    int pnr;
    vector<PassengerRail> passengers;
    int train_no;
    string train_name;
    string boarding_station;
    string destination_station;
    string coach_type;
    bool food_service;
    string food_choice;
    string payment_mode;
    double total_fare;
};

vector<Train> trains;
vector<Ticket> rail_tickets;

void Trains() {
    trains.push_back({12347, "SMVD Katra Express", {"New Delhi", "Ambala", "Ludhiana", "Jammu", "Udhampur", "Katra"}, "15:00", "23:00", 200});
    trains.push_back({12001, "Shatabdi Express", {"New Delhi", "Agra", "Gwalior", "Bhopal"}, "06:00", "14:00", 100});
    trains.push_back({12345, "Rajdhani Express", {"Mumbai", "Vadodara", "Jaipur", "Delhi"}, "16:00", "08:00", 150});
    trains.push_back({12346, "Jhelum Express", {"Pune", "Bhopal", "Delhi", "Jammu"}, "17:20", "04:30", 50});
    trains.push_back({12348, "Karnataka Express", {"Bangalore", "Nagpur", "Jhansi", "Delhi"}, "19:20", "07:10", 100});
    trains.push_back({12349, "Kerala Express", {"New Delhi", "Mathura","Bhopal", "Warangal", "Thiruvananthapuram"},"8:00","5:00", 150});
    trains.push_back({12367, "Madgaon Express", {"Mumbai", "Thane", "Panvel", "Madgaon"},"12:45", "22:42",150});
}

string toLower(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

void viewTrain() {
    cout << "\nAvailable Trains:\n";
    cout << "-------------------------------------------------------------\n";
    for (auto &train : trains) {
        cout << "Train No: " << train.train_no << ", Name: " << train.train_name << ", Route: ";
        for (auto &station : train.stations) {
            cout << station;
            if (&station != &train.stations.back()) cout << " -> ";
        }
        cout << ", Departs: " << train.departure << ", Arrives: " << train.arrival;
        cout << ", Seats: " << train.seats_available << endl;
    }
    cout << "-------------------------------------------------------------\n";
}

void searchTrain() {
    string entry, destination;
    cout << "Enter Your Station: ";
    cin >> entry;
    cout << "Enter Destination Station: ";
    cin >> destination;
    bool found = false;

    for (auto &train : trains) {
        auto it_enter = find_if(train.stations.begin(), train.stations.end(),
            [&](const string& s){ return toLower(s) == toLower(entry); });
        auto it_dest = find_if(train.stations.begin(), train.stations.end(),
            [&](const string& s){ return toLower(s) == toLower(destination); });

        if (it_enter != train.stations.end() && it_dest != train.stations.end() && it_enter< it_dest) {
            cout << "Train No: " << train.train_no << " - " << train.train_name << endl;
            found = true;
        }
    }

    if (!found) cout << "No trains found between " << entry << " and " << destination << ".\n";
}

string selectFood() {
    int choice;
    cout << "\nSelect Food Option:\n";
    cout << "1. Veg Meal\n2. Non-Veg Meal\n3. Snacks + Drinks\nEnter choice (1-3): ";
    cin >> choice;
    switch(choice) {
        case 1: return "Veg Meal";
        case 2: return "Non-Veg Meal";
        case 3: return "Snacks + Drinks";
        default: return "No Food";
    }
}

string selectPaymentRail() {
    int choice;
    cout << "\nSelect Payment Mode:\n";
    cout << "1. UPI\n2. Credit Card\n3. Debit Card\n4. Cash\nEnter choice (1-4): ";
    cin >> choice;
    switch(choice) {
        case 1: return "UPI";
        case 2: return "Credit Card";
        case 3: return "Debit Card";
        case 4: return "Cash";
        default: return "Unknown";
    }
}

string selectCoach() {
    int choice;
    cout << "\nSelect Coach Type:\n";
    cout << "1. Sleeper Class (SL): (Rs500)\n2. AC 3 Tier (3A) (Rs1500)\n3. AC 2 Tier (2A) (Rs2500)\n4. AC 1 Tier (1A) (Rs3000)\n5. General (GN) (Rs100)\nEnter choice (1-5): ";
    cin >> choice;
    switch(choice) {
        case 1: return "Sleeper (SL)";
        case 2: return "AC 3 Tier (3A)";
        case 3: return "AC 2 Tier (2A)";
        case 4: return "AC 1 Tier (1A)";
        case 5: return "General (GN)";
        default: return "Sleeper (SL)";
    }
}

double coachFare(string coach) {
    if (coach == "Sleeper (SL)") return 500.0;
    if (coach == "AC 3 Tier (3A)") return 1500.0;
    if (coach == "AC 2 Tier (2A)") return 2500.0;
    if (coach == "AC 1 Tier (1A)") return 3000.0;
    if (coach == "General (GN)") return 100.0;
    return 0.0;
}

void bookRailTicket() {
    string name;
    int tno, num_passengers;
    cout << "Enter Train Number to book: ";
    cin >> tno;

    for (auto &train : trains) {
        if (train.train_no == tno) {
            if (train.seats_available > 0) {
                cout << "Available stations: \n";
                for (auto &station : train.stations) {
                    cout << station << "  ";
                }
                cout << "\n";

                string entry, destination;
                cin.ignore();  
                cout << "Enter Boarding Station: ";
                getline(cin, entry);
                cout << "Enter Destination Station: ";
                getline(cin, destination);

                auto it_entry = find_if(train.stations.begin(), train.stations.end(),
                    [&](const string& s){ return toLower(s) == toLower(entry); });

                auto it_destination = find_if(train.stations.begin(), train.stations.end(),
                    [&](const string& s){ return toLower(s) == toLower(destination); });

                if (it_entry == train.stations.end() || it_destination == train.stations.end() || it_entry >= it_destination) {
                    cout << "Invalid boarding or destination selection.\n";
                    return;
                }

                string coach = selectCoach();
                cout << "How many passengers you want to book for? ";
                cin >> num_passengers;

                if (num_passengers > train.seats_available) {
                    cout << "Only " << train.seats_available << " seats available.\n";
                    return;
                }

                vector<PassengerRail> passenger_list;
                for (int i = 1; i <= num_passengers; i++) {
                    cout << "Enter name of Passenger " << i << ": ";
                    cin >> name;
                    srand(time(0) + i);
                    int seat = rand() % 70 + 1;
                    passenger_list.push_back({name, coach.substr(coach.find("(") + 1, 2) + "-" + to_string(seat)});
                }

                char food_choice_char;
                bool food = false;
                string food_selected = "None";
                cout << "Do you want to add Food Service (Rs100 per passenger)? (y/n): ";
                cin >> food_choice_char;
                if (food_choice_char == 'y' || food_choice_char == 'Y') {
                    food = true;
                    food_selected = selectFood();
                }

                double base_fare = 150.0;
                double fare = base_fare + coachFare(coach);
                if (food) fare += 100.0;

                double total_fare = fare * num_passengers;
                if (total_fare > 2000.0) {
                    total_fare *= 0.9;
                }

                string payment = selectPaymentRail();

                srand(time(0));
                int pnr = rand() % 90000 + 10000;

                rail_tickets.push_back({pnr, passenger_list, tno, train.train_name, entry, destination, coach, food, food_selected, payment, total_fare});
                train.seats_available -= num_passengers;

                cout << "\n --------- RAILWAY TICKET RECEIPT ---------\n";
                cout << "PNR: " << pnr << endl;
                for (auto &passenger : passenger_list) {
                    cout << "Passenger: " << passenger.name << ", Seat No: " << passenger.seat_no << endl;
                }
                cout << "Train: " << train.train_name << " (" << train.train_no << ")\n";
                cout << "Journey: " << entry << " -> " << destination << endl;
                cout << "Coach: " << coach << endl;
                cout << "Food Service: " << (food ? ("Yes - " + food_selected) : "No") << endl;
                cout << "Payment Mode: " << payment << endl;
                cout << "Total Fare Paid: Rs" << total_fare << endl;
                cout << "Thank you for booking with us! Have a safe journey!\n";
                return;
            } else {
                cout << "Sorry, no seats available on this train.\n";
                return;
            }
        }
    }
    cout << "Invalid Train Number.\n";
}

void viewTickets() {
    if (rail_tickets.empty()) {
        cout << "\nNo railway tickets booked yet.\n";
        return;
    }

    int search_pnr;
    cout << "Enter your PNR number to view your ticket: ";
    cin >> search_pnr;

    bool found = false;

    for (auto &ticket : rail_tickets) {
        if (ticket.pnr == search_pnr) {
            cout << "\n---------- RAILWAY TICKET DETAILS ----------\n";
            cout << "PNR: " << ticket.pnr << endl;
            for (auto &p : ticket.passengers) {
                cout << "Passenger: " << p.name << ", Seat No: " << p.seat_no << endl;
            }
            cout << "Train: " << ticket.train_name << " (" << ticket.train_no << ")\n";
            cout << "Journey: " << ticket.boarding_station << " -> " << ticket.destination_station << endl;
            cout << "Coach: " << ticket.coach_type << endl;
            cout << "Food Service: " << (ticket.food_service ? ("Yes - " + ticket.food_choice) : "No") << endl;
            cout << "Payment Mode: " << ticket.payment_mode << endl;
            cout << "Total Fare Paid: Rs" << ticket.total_fare << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "No railway ticket found with PNR: " << search_pnr << endl;
    }
}

void cancelTicket() {
    int pnr_cancel;
    cout << "Enter PNR to cancel: ";
    cin >> pnr_cancel;

    for (int i = 0; i < rail_tickets.size(); i++) {
        if (rail_tickets[i].pnr == pnr_cancel) {
            int tno = rail_tickets[i].train_no;
            int booked_seats = rail_tickets[i].passengers.size();
            for (auto &train : trains) {
                if (train.train_no == tno) {
                    train.seats_available += booked_seats;
                    break;
                }
            }
            rail_tickets.erase(rail_tickets.begin() + i);
            cout << "Railway Ticket Cancelled Successfully.\n";
            return;
        }
    }
    cout << "Invalid PNR. Railway ticket not found.\n";
}

void railwayMenu() {
    Trains();
    int choice;
    do {
        cout << "\n========= Railway Reservation System =========\n";
        cout << "1. View All Trains\n";
        cout << "2. Search Train by Stations\n";
        cout << "3. Book Ticket\n";
        cout << "4. View Booked Tickets\n";
        cout << "5. Cancel Ticket\n";
        cout << "6. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: viewTrain(); break;
            case 2: searchTrain(); break;
            case 3: bookRailTicket(); break;
            case 4: viewTickets(); break;
            case 5: cancelTicket(); break;
            case 6: cout << "Returning to main menu...\n"; break;
            default: cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 6);
}

struct Destination {
    string name;
    double price;
};

struct FoodWater {
    string name;
    double price;
};

class Boat {
private:
    int id;
    string name;
    int capacity;
    int booked;

public:
    Boat(int id, string name, int capacity)
        : id(id), name(name), capacity(capacity), booked(0) {}

    int getId() const { return id; }
    string getName() const { return name; }
    int getCapacity() const { return capacity; }
    int getBooked() const { return booked; }

    bool reserveSeat() {
        if (booked < capacity) {
            booked++;
            return true;
        }
        return false;
    }

    void showDetails() const {
        cout << "Boat ID: " << id << ", Name: " << name
             << ", Capacity: " << capacity
             << ", Booked: " << booked << endl;
    }
};

class WaterReservation {
private:
    string passengerName;
    int boatId;
    Destination destination;
    FoodWater food;

public:
    WaterReservation(string name, int boatId, Destination dest, FoodWater food)
        : passengerName(name), boatId(boatId), destination(dest), food(food) {}

    void showReservation(const Boat &boat) const {
        cout << "Passenger: " << passengerName
             << ", Boat: " << boat.getName()
             << ", Destination: " << destination.name << " (Rs" << destination.price << ")"
             << ", Food: " << food.name << " (Rs" << food.price << ")"
             << ", Total: Rs" << (destination.price + food.price) << endl;
    }

    int getBoatId() const { return boatId; }
    string getPassengerName() const { return passengerName; }
};

class WaterReservationSystem {
private:
    vector<Boat> boats;
    vector<WaterReservation> reservations;

    vector<Destination> destinations = {
        {"Goa Beach", 4000.0},
        {"Andaman Islands", 6000.0},
        {"Alleppey Backwaters", 3500.0}};

    vector<FoodWater> foodOptions = {
        {"South Indian Thali", 300.0},
        {"Vegetarian Meal", 250.0},
        {"Seafood Special", 500.0}};

public:
    void initializeBoats() {
        boats.emplace_back(1, "Ganga Queen", 50);
        boats.emplace_back(2, "Bay Breeze", 30);
        boats.emplace_back(3, "Backwater Star", 40);
    }

    void showBoats() const {
        cout << "\nAvailable Boats:\n";
        for (const auto &boat : boats) {
            boat.showDetails();
        }
    }

    Boat *getBoatById(int id) {
        for (auto &boat : boats) {
            if (boat.getId() == id)
                return &boat;
        }
        return nullptr;
    }

    void makeReservation() {
        string name;
        int boatId;

        cout << "Enter your name: ";
        cin.ignore();
        getline(cin, name);

        showBoats();
        cout << "Enter Boat ID to reserve: ";
        while (!(cin >> boatId)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid Boat ID: ";
        }

        Boat *boat = getBoatById(boatId);
        if (!boat) {
            cout << "Invalid Boat ID.\n";
            return;
        }

        cout << "\nAvailable Destinations:\n";
        for (size_t i = 0; i < destinations.size(); ++i) {
            cout << i + 1 << ". " << destinations[i].name
                 << " (Rs" << destinations[i].price << ")\n";
        }

        int destChoice;
        cout << "Choose a destination (1-" << destinations.size() << "): ";
        cin >> destChoice;

        if (destChoice < 1 || destChoice > (int)destinations.size()) {
            cout << "Invalid destination choice.\n";
            return;
        }

        cout << "\nAvailable Food Options:\n";
        for (size_t i = 0; i < foodOptions.size(); ++i) {
            cout << i + 1 << ". " << foodOptions[i].name
                 << " (Rs" << foodOptions[i].price << ")\n";
        }

        int foodChoice;
        cout << "Choose a food option (1-" << foodOptions.size() << "): ";
        cin >> foodChoice;

        if (foodChoice < 1 || foodChoice > (int)foodOptions.size()) {
            cout << "Invalid food choice.\n";
            return;
        }

        if (boat->reserveSeat()) {
            reservations.emplace_back(name, boatId,
                                      destinations[destChoice - 1],
                                      foodOptions[foodChoice - 1]);

            double total = destinations[destChoice - 1].price + foodOptions[foodChoice - 1].price;

            cout << "\nReservation successful for " << name
                 << " on " << boat->getName() << "!\n"
                 << "Total Bill: Rs" << total << endl;
        }
        else {
            cout << "Sorry, the boat is fully booked.\n";
        }
    }

    void showReservations() const {
        cout << "\nWaterway Reservations:\n";
        for (const auto &r : reservations) {
            const Boat *boat = nullptr;
            for (const auto &b : boats) {
                if (b.getId() == r.getBoatId()) {
                    boat = &b;
                    break;
                }
            }
            if (boat)
                r.showReservation(*boat);
            else
                cout << "Boat ID " << r.getBoatId() << " not found.\n";
        }
    }
};

void waterwaysMenu() {
    WaterReservationSystem system;
    system.initializeBoats();
    int choice;
    do {
        cout << "\n--- Indian Waterways Reservation System ---\n";
        cout << "1. View Boats\n";
        cout << "2. Make Reservation\n";
        cout << "3. View Reservations\n";
        cout << "4. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            system.showBoats();
            break;
        case 2:
            system.makeReservation();
            break;
        case 3:
            system.showReservations();
            break;
        case 4:
            cout << "Returning to main menu...\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 4);
}

class Flight;

class UserAir {
public:
    virtual void showMenu() = 0;
    virtual ~UserAir() {}
};


struct CityInfo {
    string name;
    string currentTemp;
    vector<string> placesToVisit;
};


map<string, CityInfo> cityDatabase = {
    {"delhi", {"Delhi", "32°C", {"Red Fort", "India Gate", "Qutub Minar", "Lotus Temple", "Humayun's Tomb"}}},
    {"mumbai", {"Mumbai", "30°C", {"Gateway of India", "Marine Drive", "Elephanta Caves", "Juhu Beach", "Siddhivinayak Temple"}}},
    {"bangalore", {"Bangalore", "26°C", {"Lalbagh Botanical Garden", "Bangalore Palace", "Cubbon Park", "Vidhana Soudha", "ISKCON Temple"}}},
    {"chennai", {"Chennai", "38°C", {"Marina Beach", "Kapaleeshwarar Temple", "San Thome Basilica", "Guindy National Park", "Fort St. George"}}},
    {"hyderabad", {"Hyderabad", "29°C", {"Charminar", "Golconda Fort", "Ramoji Film City", "Hussain Sagar Lake", "Salar Jung Museum"}}},
    {"kolkata", {"Kolkata", "27°C", {"Victoria Memorial", "Howrah Bridge", "Dakshineswar Kali Temple", "Indian Museum", "Eden Gardens"}}},
    {"jaipur", {"Jaipur", "35°C", {"Hawa Mahal", "Amber Fort", "City Palace", "Jantar Mantar", "Nahargarh Fort"}}},
    {"goa", {"Goa", "29°C", {"Baga Beach", "Calangute Beach", "Fort Aguada", "Dudhsagar Falls", "Basilica of Bom Jesus"}}}
};

class PassengerAir : public UserAir {
private:
    string name;
    int age;
    string gender;
    int id;
    static int idCounter;
    static map<int, int> rewardPoints;

public:
    PassengerAir(string n, int a, string g) : name(n), age(a), gender(g) {
        id = ++idCounter;
        rewardPoints[id] = 0;
    }

    void bookFlight(Flight& flight, double price);
    void cancelFlight(Flight& flight);
    void showMenu() override;
    int getId() const { return id; }
    string getName() const { return name; }
    static void showRewardPoints(int pid);
};

int PassengerAir::idCounter = 0;
map<int, int> PassengerAir::rewardPoints;

void PassengerAir::showRewardPoints(int pid) {
    cout << "Reward Points for Passenger ID " << pid << ": " << rewardPoints[pid] << "\n";
}

class Flight {
private:
    string flightNo, source, destination;
    int capacity;
    double basePrice;
    vector<PassengerAir*> passengers;

public:
    Flight(string no, string src, string dest, int cap, double price) 
        : flightNo(no), source(src), destination(dest), capacity(cap), basePrice(price) {}

    bool addPassenger(PassengerAir* p) {
        if ((int)passengers.size() >= capacity) {
            cout << "Flight full!\n";
            return false;
        }
        passengers.push_back(p);
        return true;
    }

    void removePassenger(int pid) {
        bool found = false;
        vector<PassengerAir*> temp;
        for (auto* p : passengers) {
            if (p->getId() == pid) {
                found = true;
                continue;
            }
            temp.push_back(p);
        }
        passengers = temp;
        if (found) {
            cout << "Booking cancelled.\n";
        } else {
            cout << "Passenger not found.\n";
        }
    }

    void showDetails() {
        cout << "Flight: " << flightNo << " from " << source << " to " << destination 
             << " | Price: ₹" << fixed << setprecision(2) << basePrice
             << " | Seats: " << passengers.size() << "/" << capacity << "\n";
    }

    string getDestination() const { return destination; }
    string getFlightNo() const { return flightNo; }
    double getPrice() const { return basePrice; }
};

void PassengerAir::bookFlight(Flight& flight, double price) {
    if (flight.addPassenger(this)) {
        string destLower = flight.getDestination();
        transform(destLower.begin(), destLower.end(), destLower.begin(), ::tolower);
        
        if (cityDatabase.find(destLower) != cityDatabase.end()) {
            CityInfo info = cityDatabase[destLower];
            cout << "\n=== Destination Information ===\n";
            cout << "City: " << info.name << "\n";
            cout << "Current Temperature: " << info.currentTemp << "\n";
            cout << "Popular Places to Visit:\n";
            for (const auto& place : info.placesToVisit) {
                cout << "- " << place << "\n";
            }
            cout << "==============================\n";
        }

        cout << "\n=== Payment Options ===\n";
        cout << "Total Amount: Rs" << fixed << setprecision(2) << price << "\n";
        cout << "1. UPI\n2. Credit Card\n3. Debit Card\n4. Net Banking\n5. Cash\n";
        cout << "Select payment method (1-5): ";
        int paymentChoice;
        cin >> paymentChoice;
        
        string paymentMethod;
        switch(paymentChoice) {
            case 1: paymentMethod = "UPI"; break;
            case 2: paymentMethod = "Credit Card"; break;
            case 3: paymentMethod = "Debit Card"; break;
            case 4: paymentMethod = "Net Banking"; break;
            case 5: paymentMethod = "Cash"; break;
            default: paymentMethod = "Unknown";
        }
        
        cout << "\nProcessing payment via " << paymentMethod << "...\n";
        cout << "Payment of Rs" << price << " successful!\n";
        cout << "Booking confirmed for: " << name << "\n";
        
        rewardPoints[id] += 100;
    }
}

void PassengerAir::cancelFlight(Flight& flight) {
    flight.removePassenger(id);
    rewardPoints[id] -= 50;
}

void PassengerAir::showMenu() {
    cout << "Passenger Menu\n";
    cout << "1. Book Flight\n";
    cout << "2. Cancel Flight\n";
    cout << "3. Show Reward Points\n";
}

class AdminAir : public UserAir {
private:
    vector<Flight> flights;

public:
    void addFlight(string no, string src, string dest, int cap, double price) {
        string srcLower = src;
        string destLower = dest;
        transform(srcLower.begin(), srcLower.end(), srcLower.begin(), ::tolower);
        transform(destLower.begin(), destLower.end(), destLower.begin(), ::tolower);
        
        if (cityDatabase.find(destLower) == cityDatabase.end()) {
            cout << "Warning: Destination city '" << dest << "' not found in our database.\n";
            cout << "City information will not be available for this destination.\n";
        }
        
        flights.emplace_back(no, src, dest, cap, price);
        cout << "Flight added successfully!\n";
    }

    void removeFlight(string no) {
        vector<Flight> temp;
        bool removed = false;
        for (auto& f : flights) {
            if (f.getFlightNo() == no) {
                removed = true;
                continue;
            }
            temp.push_back(f);
        }
        flights = temp;
        if (removed) {
            cout << "Flight removed.\n";
        }
    }

    void showAllFlights() {
        for (int i = 0; i < (int)flights.size(); i++) {
            cout << "Index " << i << ": ";
            flights[i].showDetails();
        }
    }

    vector<Flight>& getFlights() { return flights; }

    void showMenu() override {
        cout << "Admin Menu\n";
        cout << "1. Add Flight\n";
        cout << "2. Remove Flight\n";
        cout << "3. Show All Flights\n";
        cout << "0. Exit Admin Panel\n";
    }
};

void airwaysMenu() {
    AdminAir admin;
    vector<PassengerAir> passengers;
    int choice;

    while (true) {
        cout << "\n--- Airways Reservation System ---\n";
        cout << "1. Admin Panel\n";
        cout << "2. Passenger Panel\n";
        cout << "3. Back to Main Menu\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int adminChoice;
            do {
                cout << "\n--- Admin Panel ---\n";
                admin.showMenu();
                cout << "Enter choice: ";
                cin >> adminChoice;
                if (adminChoice == 1) {
                    string no, src, dest;
                    int cap;
                    double price;
                    cout << "Enter flight no: ";
                    cin >> no;
                    cout << "Enter source: ";
                    cin >> src;
                    cout << "Enter destination: ";
                    cin >> dest;
                    cout << "Enter capacity: ";
                    cin >> cap;
                    cout << "Enter base price: ₹";
                    cin >> price;
                    admin.addFlight(no, src, dest, cap, price);
                } else if (adminChoice == 2) {
                    string no;
                    cout << "Enter flight number to remove: ";
                    cin >> no;
                    admin.removeFlight(no);
                } else if (adminChoice == 3) {
                    admin.showAllFlights();
                }
            } while (adminChoice != 0);
        } 
        else if (choice == 2) {
            int userChoice;
            vector<Flight>& flights = admin.getFlights();
            do {
                cout << "\n--- Passenger Panel ---\n";
                cout << "1. New Passenger Registration\n2. Book Flight\n3. Cancel Flight\n";
                cout << "4. Show Reward Points\n5. Show Flights\n6. Back\nEnter choice: ";
                cin >> userChoice;
                if (userChoice == 1) {
                    string name, gender;
                    int age;
                    cout << "Enter name: ";
                    cin.ignore();
                    getline(cin, name);
                    cout << "Enter age: ";
                    cin >> age;
                    cout << "Enter gender: ";
                    cin >> gender;
                    passengers.emplace_back(name, age, gender);
                    cout << "Registered with ID: " << passengers.back().getId() << "\n";
                } else if (userChoice == 2) {
                    int pid, flightIdx;
                    cout << "Enter your passenger ID: ";
                    cin >> pid;
                    bool found = false;
                    for (auto& p : passengers) {
                        if (p.getId() == pid) {
                            found = true;
                            admin.showAllFlights();
                            cout << "Enter flight index (starting from 0): ";
                            cin >> flightIdx;
                            if (flightIdx >= 0 && flightIdx < (int)flights.size()) {
                                p.bookFlight(flights[flightIdx], flights[flightIdx].getPrice());
                            } else {
                                cout << "Invalid flight index.\n";
                            }
                            break;
                        }
                    }
                    if (!found) cout << "Invalid ID\n";
                } else if (userChoice == 3) {
                    int pid, flightIdx;
                    cout << "Enter your passenger ID: ";
                    cin >> pid;
                    bool found = false;
                    for (auto& p : passengers) {
                        if (p.getId() == pid) {
                            found = true;
                            admin.showAllFlights();
                            cout << "Enter flight index (starting from 0): ";
                            cin >> flightIdx;
                            if (flightIdx >= 0 && flightIdx < (int)flights.size()) {
                                p.cancelFlight(flights[flightIdx]);
                            } else {
                                cout << "Invalid flight index.\n";
                            }
                            break;
                        }
                    }
                    if (!found) cout << "Invalid ID\n";
                } else if (userChoice == 4) {
                    int pid;
                    cout << "Enter your passenger ID: ";
                    cin >> pid;
                    PassengerAir::showRewardPoints(pid);
                } else if (userChoice == 5) {
                    admin.showAllFlights();
                }
            } while (userChoice != 6);
        }
        else if (choice == 3) {
            cout << "Returning to main menu...\n";
            break;
        }
        else {
            cout << "Invalid choice.\n";
        }
    }
}

class RoadBus {
    char busn[5], driver[10], arrival[5], depart[5], from[10], to[10], seat[8][4][10];
    char paymentStatus[8][4][10]; 
public:
    void install();
    void allotment();
    void empty();
    void show();
    void avail();
    void position(int i);
};

RoadBus bus[10];
static int p = 0;

void vline(char ch) {
    for (int i = 80; i > 0; i--)
        cout << ch;
}

void RoadBus::install() {
    cout << "Enter bus no: ";
    cin >> busn;
    cout << "\nEnter Driver's name: ";
    cin >> driver;
    cout << "\nArrival time: ";
    cin >> arrival;
    cout << "\nDeparture: ";
    cin >> depart;
    cout << "\nFrom: \t\t\t";
    cin >> from;
    cout << "\nTo: \t\t\t";
    cin >> to;
    empty();
}

void RoadBus::empty() {
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 4; j++) {
            strcpy(seat[i][j], "Empty");
        }
    }
}

void RoadBus::show() {
    int n;
    char number[5];
    cout << "Enter bus no: ";
    cin >> number;

    for(n = 0; n < 10; n++) {
        if(strcmp(bus[n].busn, number) == 0)
            break;
    }

    if(n >= 10) {
        cout << "Enter correct bus no: ";
        return;
    }

    vline('*');
    cout << "Bus no: \t" << bus[n].busn
         << "\nDriver: \t" << bus[n].driver
         << "\t\tArrival time: \t" << bus[n].arrival
         << "\tDeparture time: " << bus[n].depart
         << "\nFrom: \t\t" << bus[n].from
         << "\t\tTo: \t\t" << bus[n].to << "\n";
    vline('*');
    
    bus[0].position(n); 

    int a = 1;
    int empty_seats = 0;

    for (int i = 0; i < 8; i++) {
        for(int j = 0; j < 4; j++) {
            a++;
            if(strcmp(bus[n].seat[i][j], "Empty") != 0) {
                cout << "\nThe seat no " << (a - 1) << " is reserved for " << bus[n].seat[i][j] << ".";
            } else {
                empty_seats++;
            }
        }
    }
}

void RoadBus::position(int l) {
    int s = 0;
    int empty_seats = 0;

    for (int i = 0; i < 8; i++) {
        cout << "\n";
        for (int j = 0; j < 4; j++) {
            s++;
            cout.width(5);
            cout.fill(' ');
            cout << s << ".";

            cout.width(10);
            cout.fill(' ');
            cout << bus[l].seat[i][j];

            if(strcmp(bus[l].seat[i][j], "Empty") == 0) {
                empty_seats++;
            }
        }
    }

    if (empty_seats > 0) {
        cout << "\n\nThere are " << empty_seats << " seats empty in Bus No: " << bus[l].busn << ".";
    }
}


void RoadBus::avail() {
    for(int n = 0; n < 10; n++) {
        if(strlen(bus[n].busn)) {
            vline('*');
            cout << "Bus no: \t" << bus[n].busn << "\nDriver: \t" << bus[n].driver
            << "\t\tArrival time: \t" << bus[n].arrival << "\tDeparture Time: \t"
            << bus[n].depart << "\nFrom: \t\t" << bus[n].from << "\t\tTo: \t\t\t"
            << bus[n].to << "\n";
            vline('*');
            vline('_');
        }
    }
}
void RoadBus::allotment() {
    int seatNum;
    char number[5];
top:
    cout << "Bus no: ";
    cin >> number;
    int n;
    for(n = 0; n <= p; n++) {
        if(strcmp(bus[n].busn, number) == 0)
            break;
    }
    if(n > p) {
        cout << "Enter correct bus no.\n";
        goto top;
    }

    cout << "\nSeat Number: ";
    cin >> seatNum;

    if(seatNum < 1 || seatNum > 32) {
        cout << "\nThere are only 32 seats available in this bus.\n";
        return;
    }

    int row = (seatNum - 1) / 4;
    int col = (seatNum - 1) % 4;

    if (strcmp(bus[n].seat[row][col], "Empty") == 0) {
        cout << "Enter passenger's name: ";
        cin >> bus[n].seat[row][col];
        cout << "Enter payment method (e.g., Cash, Card, UPI): ";
        cin >> bus[n].paymentStatus[row][col];

        cout << "\n Seat reserved and payment done successfully!\n";
        cout << "\n========= Booking Receipt =========\n";
        cout << "Bus No      : " << bus[n].busn << endl;
        cout << "Passenger   : " << bus[n].seat[row][col] << endl;
        cout << "Seat No     : " << seatNum << endl;
        cout << "From        : " << bus[n].from << endl;
        cout << "To          : " << bus[n].to << endl;
        cout<<"amount        : Rs1500"<<endl;
        cout << "Payment     : Paid by " << bus[n].paymentStatus[row][col] << endl;
        cout << "===================================\n";

    } else {
        cout << "The seat no. is already reserved.\n";
    }
}

void roadwaysMenu() {
    int w;
    while(1) {
        cout << "\n\n\n\n\n";
        cout << "\t\t\t1.Install\n\t\t\t"
        << "2.Reservation\n\t\t\t"
        << "3.Show\n\t\t\t"
        << "4.Buses Available. \n\t\t\t"
        << "5.Back to Main Menu";
        cout << "\n\t\t\tEnter your choice:-> ";
        cin >> w;
        switch(w) {
            case 1:  bus[p].install();
                p++;
                break;
            case 2:  bus[p].allotment();
                break;
            case 3:  bus[0].show();
                break;
            case 4:  bus[0].avail();
                break;
            case 5:  return;
        }
    }
}

int main() {
    int mainChoice;
    do {
        cout << "\n---------- Multi-Transport Booking System ---------\n";
        cout << "1. Railway Reservation\n";
        cout << "2. Waterways Reservation\n";
        cout << "3. Airways Reservation\n";
        cout << "4. Roadways Reservation\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> mainChoice;

        switch (mainChoice) {
            case 1: railwayMenu(); break;
            case 2: waterwaysMenu(); break;
            case 3: airwaysMenu(); break;
            case 4: roadwaysMenu(); break;
            case 5: cout << "Thank You For Booking Through Us!!!!. Have A Safe Trip!!!!!\n"; break;
            default: cout << "Invalid choice! Please try again.\n";
        }
    } while (mainChoice != 5);

    return 0;
}