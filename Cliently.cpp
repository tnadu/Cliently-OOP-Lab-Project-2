#include <iostream>
#include <string>

using namespace std;

string toLower(string str) {
    for (int i = 0; i < str.length(); i++)
        str[i] = tolower(str[i]);
    return str;
}

bool isNumber(string x) {
    for (int i = 0; i < x.length(); i++) {
        if (!isdigit(x[i])) return false;
    }
    return true;
}

class Person {
    int ID;
    string name, CNP;
    static int IDglobal;
protected:
    void setID() { this->ID = IDglobal++; };
public:
    Person() : ID(IDglobal++), name("None"), CNP("0000000000000") {};

    Person(const string &name, const string &CNP);

    Person(const Person &person) : ID(IDglobal++), name(person.name), CNP(person.CNP) {};

    virtual ~Person() {};

    static int getIDglobal() { return IDglobal; }

    Person &operator=(const Person &person);

    friend ostream &operator<<(ostream &out, const Person &person);

    friend istream &operator>>(istream &in, Person &person);

    void setName(const string &name);

    string getName() const;

    void setCNP(string CNP);

    string getCNP() const;
};

int Person::IDglobal = 1000;

Person::Person(const string &name, const string &CNP) {
    this->ID = IDglobal++;
    this->name = name;
    if (!isNumber(CNP) or CNP.length() != 13)
        do {
            cout << "Error: CNP must be numerical and must contain exactly 13 digits\n";
            cout << ">>> Enter a valid CNP: ";
            cin >> this->CNP;
        } while (!isNumber(this->CNP) or this->CNP.length() != 13);
    else this->CNP = CNP;
}

Person &Person::operator=(const Person &person) {
    ID = IDglobal++;
    name = person.name;
    CNP = person.CNP;
    return *this;
}

ostream &operator<<(ostream &out, const Person &person) {
    out << "Personal ID: " << person.ID << " - CNP: " << person.CNP << " - Name: ";
    out << person.name;
    return out;
}

istream &operator>>(istream &in, Person &person) {
    in >> person.name >> person.CNP;
    while (!isNumber(person.CNP) or person.CNP.length() != 13) {
        cout << "Error: CNP must be numerical and must contain exactly 13 digits\n";
        cout << ">>> Enter a valid CNP: ";
        in >> person.CNP;
    }
    return in;
}

void Person::setName(const string &name) {
    this->name = name;
}

string Person::getName() const {
    return name;
}

void Person::setCNP(string CNP) {
    if (!isNumber(CNP) or CNP.length() != 13)
        do {
            cout << "Error: CNP must be numerical and must contain exactly 13 digits\n";
            cout << ">>> Enter a valid CNP: ";
            cin >> this->CNP;
        } while (!isNumber(this->CNP) or this->CNP.length() != 13);
    else this->CNP = CNP;
}

string Person::getCNP() const {
    return CNP;
}




class Subscription {
    string name;
    float price;
    int period;
public:
    Subscription() : name("None"), price(0.0), period(0) {};

    Subscription(const string &name, float price, int period);

    Subscription(const Subscription &subscription) : name(subscription.name), price(subscription.price),
                                                     period(subscription.period) {};

    virtual ~Subscription() {};

    Subscription &operator=(const Subscription &subscription);

    friend ostream &operator<<(ostream &out, const Subscription &subscription);

    friend istream &operator>>(istream &in, Subscription &subscription);

    void setName(const string &name);

    string getName() const;

    void setPrice(float price);

    float getPrice() const;

    void setPeriod(int period);

    int getPeriod() const;

    virtual float getEarnings();
};

Subscription::Subscription(const string &name, float price, int period) {
    if (toLower(name) != "individual" and toLower(name) != "dual" and toLower(name) != "family")
        do {
            cout << "Error: Subscription Type can be 'Individual', 'Dual' or 'Family'\n";
            cout << ">>> Enter a valid subscription type: ";
            cin >> this->name;
        } while (toLower(this->name) != "individual" and toLower(this->name) != "dual" and toLower(this->name) != "family");
    else this->name = name;

    if (price < 0.0)
        do {
            cout << "Error: Subscription price must be a positive floating-point number\n";
            cout << ">>> Enter a valid subscription price: ";
            cin >> this->price;
        } while (this->price < 0.0);
    else this->price = price;

    if (period < 0)
        do {
            cout << "Error: Subscription period must be a positive integer\n";
            cout << ">>> Enter a valid subscription period: ";
            cin >> this->period;
        } while (this->period < 0);
    else this->period = period;
}

Subscription &Subscription::operator=(const Subscription &subscription) {
    name = subscription.name;
    price = subscription.price;
    period = subscription.period;
    return *this;
}

ostream &operator<<(ostream &out, const Subscription &subscription) {
    out << "Type: " << subscription.name << " - Price: " << subscription.price << "€ - Contract period: " << subscription.period << " months";
    return out;
}

istream &operator>>(istream &in, Subscription &subscription) {
    in >> subscription.name;
    while (toLower(subscription.name) != "individual" and toLower(subscription.name) != "dual" and toLower(subscription.name) != "family") {
        cout << "Error: Subscription Type can be 'Individual', 'Dual' or 'Family'\n";
        cout << ">>> Enter a valid subscription type: ";
        in >> subscription.name;
    }

    in >> subscription.price;
    while (subscription.price < 0.0) {
        cout << "Error: Subscription price must be a positive floating-point number\n";
        cout << ">>> Enter a valid subscription price: ";
        in >> subscription.price;
    }

    in >> subscription.period;
    while (subscription.period < 0) {
        cout << "Error: Subscription period must be a positive integer\n";
        cout << ">>> Enter a valid subscription period: ";
        in >> subscription.period;
    }

    return in;
}

void Subscription::setName(const string &name) {
    if (toLower(name) != "individual" and toLower(name) != "dual" and toLower(name) != "family")
        do {
            cout << "Error: Subscription Type can be 'Individual', 'Dual' or 'Family'\n";
            cout << ">>> Enter a valid subscription type: ";
            cin >> this->name;
        } while (toLower(this->name) != "individual" and toLower(this->name) != "dual" and toLower(this->name) != "family");
    else this->name = name;
}

string Subscription::getName() const {
    return name;
}

void Subscription::setPrice(float price) {
    if (price < 0.0)
        do {
            cout << "Error: Subscription price must be a positive floating-point number\n";
            cout << ">>> Enter a valid subscription price: ";
            cin >> this->price;
        } while (this->price < 0.0);
    else this->price = price;
}

float Subscription::getPrice() const {
    return price;
}

void Subscription::setPeriod(int period) {
    if (period < 0)
        do {
            cout << "Error: Subscription period must be a positive integer\n";
            cout << ">>> Enter a valid subscription period: ";
            cin >> this->period;
        } while (this->period < 0);
    else this->period = period;
}

int Subscription::getPeriod() const {
    return period;
}

float Subscription::getEarnings() {
    return price * (float)period;
}




class PremiumSubscription : public Subscription {
    int discount;
public:
    PremiumSubscription() : Subscription(), discount(0) {};

    PremiumSubscription(const string &name, float price, int period, int discount);

    PremiumSubscription(PremiumSubscription &premium);

    ~PremiumSubscription() {};

    PremiumSubscription &operator=(const PremiumSubscription &premium);

    friend ostream &operator<<(ostream &out, const PremiumSubscription &premium);

    friend istream &operator>>(istream &in, PremiumSubscription &premium);

    void setDiscount(int discount);

    int getDiscount() const;

    float getEarnings();
};

PremiumSubscription::PremiumSubscription(const string &name, float price, int period, int discount) : Subscription(name, price, period) {
    if (discount < 0 or discount > 100)
        do {
            cout << "Error: Subscription discount must be between 0 and 100\n";
            cout << ">>> Enter a valid subscription discount: ";
            cin >> this->discount;
        } while (this->discount < 0 or this->discount > 100);
    else this->discount = discount;
}

PremiumSubscription::PremiumSubscription(PremiumSubscription &premium) :
        Subscription(premium.getName(), premium.getPrice(), premium.getPeriod()) {
    discount = premium.discount;
}

PremiumSubscription &PremiumSubscription::operator=(const PremiumSubscription &premium) {
    this->setName(premium.getName());
    this->setPrice(premium.getPrice());
    this->setPeriod(premium.getPeriod());
    discount = premium.discount;
    return *this;
}

ostream &operator<<(ostream &out, const PremiumSubscription &premium) {
    out << dynamic_cast<const Subscription &>(premium) << " - Discount: " << premium.discount << "%";
    return out;
}

istream &operator>>(istream &in, PremiumSubscription &premium) {
    in >> dynamic_cast<Subscription &>(premium) >> premium.discount;
    while (premium.discount < 0 or premium.discount > 100) {
        cout << "Error: Subscription discount must be between 0 and 100\n";
        cout << ">>> Enter a valid subscription discount: ";
        in >> premium.discount;
    }
    return in;
}

void PremiumSubscription::setDiscount(int discount) {
    if (discount < 0 or discount > 100)
        do {
            cout << "Error: Subscription discount must be between 0 and 100\n";
            cout << ">>> Enter a valid subscription discount: ";
            cin >> this->discount;
        } while (this->discount < 0 or this->discount > 100);
    else this->discount = discount;
}

int PremiumSubscription::getDiscount() const {
    return discount;
}

float PremiumSubscription::getEarnings() {
    return this->getPrice() * (float)this->getPeriod() - (this->getPrice() * (float)this->getPeriod() * ((float)discount/100));
}




class Subscriber : public Person {
    string phoneNumber;
    Subscription *x;
public:
    Subscriber() : Person(), x(new Subscription), phoneNumber("0000000000") {};

    Subscriber(const string &name, const string &CNP, const string &phoneNumber, const string &subscriptionName, float price, int period,
               int discount = 0);

    Subscriber(const Subscriber &subscriber);

    ~Subscriber() {};

    Subscriber &operator=(Subscriber &subscriber);

    friend ostream &operator<<(ostream &out, const Subscriber &subscriber);

    friend istream &operator>>(istream &in, Subscriber &subscriber);

    void setPhoneNumber(const string &phoneNumber);

    string getPhoneNumber() { return phoneNumber; };

    Subscription *getSubscription() const { return x; };
};

Subscriber::Subscriber(const string &name, const string &CNP, const string &phoneNumber, const string &subscriptionName, float price, int period,
                       int discount) : Person(name, CNP) {
    if (discount == 0) {
        x = new Subscription(subscriptionName, price, period);
    } else x = new PremiumSubscription(subscriptionName, price, period, discount);

    if (!isNumber(phoneNumber) or phoneNumber.length() != 10)
        do {
            cout << "Error: Phone number must be numerical and must contain exactly 10 digits\n";
            cout << ">>> Enter a valid phone number: ";
            cin >> this->phoneNumber;
        } while (!isNumber(this->phoneNumber) or this->phoneNumber.length() != 10);
    else this->phoneNumber = phoneNumber;
}

Subscriber::Subscriber(const Subscriber &subscriber) : Person(subscriber.getName(), subscriber.getCNP()) {
    if (PremiumSubscription *construct = dynamic_cast<PremiumSubscription *>(subscriber.x)) {
        PremiumSubscription toBeInserted = *construct;
        this->x = &toBeInserted;
    } else {
        Subscription toBeInserted = *subscriber.x;
        this->x = &toBeInserted;
    }
    phoneNumber = subscriber.phoneNumber;
}

Subscriber &Subscriber::operator=(Subscriber &subscriber) {
    this->setName(subscriber.getName());
    this->setCNP(subscriber.getCNP());
    this->setID();
    x = &*(subscriber.x);
    this->phoneNumber = subscriber.phoneNumber;
    return *this;
}

ostream &operator<<(ostream &out, const Subscriber &subscriber) {
    out << dynamic_cast<const Person &>(subscriber) << " - Phone Number: " << subscriber.phoneNumber;

    if (PremiumSubscription *subscription = dynamic_cast<PremiumSubscription *>(subscriber.getSubscription())) {
        out << "\n  Premium Subscription " << *subscription;
    } else out << "\n  Subscription " << *subscriber.x;

    return out;
}

istream &operator>>(istream &in, Subscriber &subscriber) {
    in >> dynamic_cast<Person &>(subscriber);

    in >> subscriber.phoneNumber;
    while (!isNumber(subscriber.phoneNumber) or subscriber.phoneNumber.length() != 10) {
        cout << "Error: Phone number must be numerical and must contain exactly 10 digits\n";
        cout << ">>> Enter a valid phone number: ";
        in >> subscriber.phoneNumber;
    }

    string command;
    in >> command;
    subscriber.x->setName(command);

    in >> command;
    subscriber.x->setPrice(stof(command));

    in >> command;
    subscriber.x->setPeriod(stoi(command));

    in >> command;

    if (PremiumSubscription *discount = dynamic_cast<PremiumSubscription *>(subscriber.x)) discount->setDiscount(stoi(command));
    else if (stoi(command) != 0) {
        Subscription *aux = subscriber.x;
        subscriber.x = new PremiumSubscription(aux->getName(), aux->getPrice(), aux->getPeriod(), stoi(command));
        delete aux;
    }

    return in;
}

void Subscriber::setPhoneNumber(const string &phoneNumber) {
    if (!isNumber(phoneNumber) or phoneNumber.length() != 10)
        do {
            cout << "Error: Phone number must be numerical and must contain exactly 10 digits\n";
            cout << ">>> Enter a valid phone number: ";
            cin >> this->phoneNumber;
        } while (!isNumber(this->phoneNumber) or this->phoneNumber.length() != 10);
    else this->phoneNumber = phoneNumber;
}




class Clients {
    int numberOfClients = 0;
    Subscriber subscribers[1000];
public:
    Clients() {};

    Clients(Subscriber subscribers[], int numberOfClients);

    Clients(Clients &clients);

    ~Clients() {};

    Clients &operator=(Clients &clients);

    friend ostream &operator<<(ostream &out, const Clients &clients);

    friend istream &operator>>(istream &in, Clients &clients);

    int getNumberOfClients() const { return numberOfClients; };

    int getNumberOfPremiumSubscribers();

    float getTotalEarnings();

    Subscriber *getSubscribers() { return subscribers; }

    void copyClient(Clients clients, int index);

    void clearClients();
};

Clients::Clients(Subscriber subscribers[], int numberOfClients) {
    this->numberOfClients = numberOfClients;
    while (numberOfClients < 0 or numberOfClients > 1000) {
        cout << "Error: Number of clients must be between 1 and 1000\n";
        cout << ">>> Enter a valid number of clients: ";
        cin >> this->numberOfClients;
    }

    for (int i = 0; i < numberOfClients; i++)
        this->subscribers[i] = subscribers[i];
}

Clients::Clients(Clients &clients) {
    numberOfClients = clients.numberOfClients;
    for (int i = 0; i < numberOfClients; i++)
        subscribers[i] = clients.subscribers[i];
}

Clients &Clients::operator=(Clients &clients) {
    numberOfClients = clients.numberOfClients;
    for (int i = 0; i < numberOfClients; i++)
        subscribers[i] = clients.subscribers[i];

    return *this;
}

ostream &operator<<(ostream &out, const Clients &clients) {
    for (int i = 0; i < clients.numberOfClients; i++) {
        out << "Client " << i + 1 << ": " << clients.subscribers[i];
        if (i != clients.numberOfClients - 1) cout << "\n";
    }
    return out;
}

istream &operator>>(istream &in, Clients &clients) {
    cout << ">>> Enter the number of clients you wish to input: ";
    in >> clients.numberOfClients;
    while (clients.numberOfClients <= 0 or clients.numberOfClients > 1000) {
        cout << "Error: Number of clients must be between 1 and 1000\n";
        cout << ">>> Enter a valid number of clients: ";
        in >> clients.numberOfClients;
    }

    cout << "Warning: A discount is only available for premium subscriptions.";
    cout << "\nType '0' in the discount field for a basic subscription";
    cout << "\nOnce a basic subscription has been converted to a premium one, it cannot be reverted\n";
    for (int i = 0; i < clients.numberOfClients; i++) {
        cout << "\n>>> Input a client in the following format, using ENTER as a delimiter:\n";
        cout << "ClientName    CNP    PhoneNumber    SubscriptionType    SubscriptionPrice    ContractPeriod    SubscriptionDiscount\n";
        in >> clients.subscribers[i];
    }

    return in;
}

int Clients::getNumberOfPremiumSubscribers() {
    int premiumSubscribers = 0;
    for (int i = 0; i < this->numberOfClients; i++) {
        if (dynamic_cast<PremiumSubscription *>((this->subscribers + i)->getSubscription())) premiumSubscribers++;
    }
    return premiumSubscribers;
}

float Clients::getTotalEarnings() {
    float value = 0;
    for (int i = 0; i < numberOfClients; i++)
        value += (subscribers+i)->getSubscription()->getEarnings();
    return value;
}

void Clients::copyClient(Clients clients, int index) {
    if (numberOfClients == 1000) {
        cout << "Error: Client array already full\n";
        return;
    }
    subscribers[numberOfClients++] = clients.subscribers[index];
}

void Clients::clearClients() {
    numberOfClients = 0;
}




int main() {
    Clients clients;
    Subscriber favourite;
    int n, command = -3, option1 = -3, option2 = -3, option3;
    float option4;
    string auxiliary;

    //  clients reading and welcome message
    cout << "Welcome to Cliently v1.0 !\n..........LOADING...........\n\n";
    cin >> clients;

    //  copying of VIP clients into array 'VIPclients'
    cout << "\nVIP client list is unmodifiable\n";
    cout << ">>> Enter the number of VIP clients: ";

    cin >> n;
    while (n <= 0 or n > clients.getNumberOfClients()) {
        cout << "Error: Number of VIP clients must be between 1 and total number of clients\n";
        cout << ">>> Enter the number of VIP clients: ";
        cin >> n;
    }
    Clients VIPclients(clients.getSubscribers(), clients.getNumberOfClients());
    VIPclients.clearClients();

    int VIPindex = 0;
    while (VIPindex < n) {
        cout << ">>> Enter the ID of a VIP client: ";
        cin >> option1;

        while (option1 <= 0 or option1 > clients.getNumberOfClients()) {
            cout << "Error: client IDs must be positive and cannot exceed maximum ID number\n";
            cout << ">>> Enter the ID of a VIP client: ";
            cin >> option1;
        }
        option1--;

        VIPclients.copyClient(clients, option1);
        VIPindex++;
    }

    //  copying of favourite client into 'favourite'
    cout << "\nFavourite client is unmodifiable\n";
    cout << ">>> Enter the ID of your favourite client: ";
    cin >> option1;

    while (option1 <= 0 or option1 > clients.getNumberOfClients()) {
        cout << "Error: client ID must be positive and cannot exceed maximum ID number\n";
        cout << ">>> Enter the ID of your favourite client: ";
        cin >> option1;
    }

    if (PremiumSubscription *favouriteSubscription = dynamic_cast<PremiumSubscription *>(clients.getSubscribers()[option1 - 1].getSubscription())) {
        Subscriber *x = &clients.getSubscribers()[option1 - 1];
        Subscriber y(x->getName(), x->getCNP(), x->getPhoneNumber(), favouriteSubscription->getName(),
                     favouriteSubscription->getPrice(), favouriteSubscription->getPeriod(), favouriteSubscription->getDiscount());
        favourite = y;
    } else {
        Subscriber *x = &clients.getSubscribers()[option1 - 1];
        Subscriber y(x->getName(), x->getCNP(), x->getPhoneNumber(), x->getSubscription()->getName(),
                     x->getSubscription()->getPrice(), x->getSubscription()->getPeriod());
        favourite = y;
    }

    // program functions and instructions listing
    cout << "\nCliently employs the following functions:\n";
    cout << "1) modify client data\n";
    cout << "2) print the number of premium clients\n";
    cout << "3) print the total earnings\n";
    cout << "4) print client data by ID\n";
    cout << "5) print favourite client\n";
    cout << "6) print VIP client(s)\n";
    cout << "7) print all stored clients\n\n";
    cout << "Instruction manual:\n";
    cout << "- function-menus can only be accessed by giving their ID number as input\n";
    cout << "- to abort current function-menu, type '-1'\n";
    cout << "- to quit the program, type '-2'\n";
    cout << "- clients can only be identified by their order number in the list\n";

    while (command != -2) {
        // request and verify input is valid (1-7 for menu options, -1 to abort, -2 to quit)
        cout << "\n>>> Enter a valid function-menu or command ID: ";
        cin >> command;
        switch (command) {
            case 1:         // modify client menu
                cout << "Modify menu options:\n";
                cout << "1) Name\n";
                cout << "2) CNP\n";
                cout << "3) Phone Number\n";
                cout << "4) Subscription Type\n";
                cout << "5) Subscription Price\n";
                cout << "6) Contract Period\n";
                cout << "7) Subscription Discount\n";
                cout << "Warning: Subscription Discount is only applicable to premium subscriptions\n";
                cout << "Choosing '7)' will change basic subscriptions to premium\n";
                cout << "Once a basic subscription has been converted to a premium one, it cannot be reverted\n\n";
                cout << ">>> Enter a valid option or command ID: ";
                cin >> option1;

                while (option1 < -2 or option1 > 7 or option1 == 0) {
                    cout << "Error: out of range modify-menu option (1-7) and command (-1,-2) IDs\n";
                    cout << ">>> Enter a valid option or command ID: ";
                    cin >> option1;
                }

                if (option1 == -1) {        // abort
                    cout << "Aborting\n";
                    break;
                } else if (option1 == -2) {       // quit
                    command = -2;
                    break;
                } else {
                    cout << ">>> Enter the ID of the client to be modified: ";
                    cin >> option2;

                    while (option2 < -2 or option2 > clients.getNumberOfClients() or option2 == 0) {
                        cout << "Error: client IDs must be positive and cannot exceed maximum ID number\n";
                        cout << ">>> Enter the ID of the client to be modified: ";
                        cin >> option2;
                    }

                    if (option2 == -1) {       // abort
                        cout << "Aborting\n";
                        break;
                    } else if (option2 == -2) {       // quit
                        command = -2;
                        break;
                    } else {                    // both function-menu option and book ID have been received and verified
                        option2--;
                        switch (option1) {
                            case 1:         // modify client name
                                cout << ">>> Enter a new name for \"" << clients.getSubscribers()[option2].getName() << "\": ";
                                cin >> auxiliary;
                                clients.getSubscribers()[option2].setName(auxiliary);
                                cout << "Client name has been modified\n";
                                break;

                            case 2:         // modify client CNP
                                cout << ">>> Enter a new CNP for \"" << clients.getSubscribers()[option2].getName() << "\": ";
                                cin >> auxiliary;
                                clients.getSubscribers()[option2].setCNP(auxiliary);
                                cout << "CNP has been modified\n";
                                break;

                            case 3:         // modify client phone number
                                cout << ">>> Enter a new phone number for \"" << clients.getSubscribers()[option2].getName() << "\": ";
                                cin >> auxiliary;
                                clients.getSubscribers()[option2].setPhoneNumber(auxiliary);
                                cout << "Phone number has been modified\n";
                                break;

                            case 4:         //  modify subscription type
                                cout << ">>> Enter a new subscription type for \"" << clients.getSubscribers()[option2].getName() << "\": ";
                                cin >> auxiliary;
                                clients.getSubscribers()[option2].getSubscription()->setName(auxiliary);
                                cout << "Subscription Type has been modified\n";
                                break;

                            case 5:         // modify subscription price
                                cout << ">>> Enter a new subscription price for \"" << clients.getSubscribers()[option2].getName() << "\": ";
                                cin >> option4;
                                clients.getSubscribers()[option2].getSubscription()->setPrice(option4);
                                cout << "Subscription price has been modified\n";
                                break;

                            case 6:         // modify contract period
                                cout << ">>> Enter a new contract period for \"" << clients.getSubscribers()[option2].getName() << "\": ";
                                cin >> option3;
                                clients.getSubscribers()[option2].getSubscription()->setPeriod(option3);
                                cout << "Contract period has been modified\n";
                                break;

                            case 7:         // modify subscription discount
                                cout << "Enter a new subscription discount for \"" << clients.getSubscribers()[option2].getName() << "\": ";
                                cin >> option3;
                                if (PremiumSubscription *subscription = dynamic_cast<PremiumSubscription *>(clients.getSubscribers()[option2].getSubscription()))
                                    subscription->setDiscount(option3);
                                else {
                                    Subscription *pointer = clients.getSubscribers()[option2].getSubscription();
                                    Subscription aux(pointer->getName(), pointer->getPrice(), pointer->getPeriod());
                                    delete pointer;
                                    pointer = new PremiumSubscription(aux.getName(), aux.getPrice(), aux.getPeriod(), option3);
                                }

                                cout << "Subscription discount has been modified\n";
                                break;
                        }
                    }
                }
                break;

            case 2:
                cout << "The total number of premium clients: " << clients.getNumberOfPremiumSubscribers() << '\n';
                break;

            case 3:
                cout << "Total earnings: " << clients.getTotalEarnings() << "€\n";
                break;

            case 4:         //  print client data by ID menu
                cout << ">>> Enter the ID of the client whose data will be printed: ";

                cin >> option1;
                while (option1 < -2 or option1 > clients.getNumberOfClients() or option1 == 0) {
                    cout << "Error: client IDs must be positive and cannot exceed maximum ID number\n";
                    cout << ">>> Enter the ID of the client whose data will be printed: ";
                    cin >> option1;
                }

                if (option1 == -1) {       // abort
                    cout << "Aborting\n";
                    break;
                } else if (option1 == -2) {       // quit
                    command = -2;
                    break;
                } else cout << "Client " << option1 << ": " << clients.getSubscribers()[option1 - 1] << '\n';

                break;

            case 5:     //  print favourite client data
                cout << "Your favourite client: " << favourite << '\n';
                break;

            case 6:     //  print VIP client(s) data
                if (VIPindex == 1) cout << "Stored VIP client: " << VIPclients.getSubscribers()[0] << '\n';
                else cout << "All stored VIP clients:\n" << VIPclients << '\n';
                break;

            case 7:         // print all stored clients
                cout << "All stored clients:\n" << clients << '\n';
                break;

            case -1:         // abort
                cout << "Error: abort command can only be used inside function-menus\n";
                break;
            case -2:         // quit
                break;
            default:
                cout << "Error: out of range function-menu (1-5) and command (-1,-2) IDs\n";
                break;
        }
    }

    cout << "Last client ID: " << Person::getIDglobal();
    return 0;
}