#include <iostream>
#include <string>


using namespace std;

string toLower (string str) {
    for (int i=0; i<str.length(); i++)
        str[i]=tolower(str[i]);
    return str;
}

bool isNumber (string x) {
    for (int i=0; i<x.length(); i++) {
        if (!isdigit(x[i])) return false;
    }
    return true;
}

class Person {
    static int IDglobal;
    int ID;
    string name, CNP;
    static int getIDglobal() { return IDglobal; };
public:
    Person() : ID(IDglobal++), name("None"), CNP("0000000000000") {};

    Person(const string &name, const string &CNP);

    Person(const Person &person) : ID(IDglobal++), name(person.name), CNP(person.CNP) {};

    virtual ~Person() {};

    Person &operator=(const Person &person);

    friend ostream &operator<<(ostream &out, const Person &person);

    friend istream &operator>>(istream &in, Person &person);

    void setName(const string &name);

    string getName() const;

    void setCNP(string CNP);

    string getCNP() const;

    void setID();
};

int Person::IDglobal = 0;

Person::Person(const string &name, const string &CNP) {
    if (!isNumber(CNP) or CNP.length()!=13) {
        cout<<"Error: CNP was set to '0000000000000', as it must be numerical and must contain exactly 13 digits\n";
        this->CNP="0000000000000";
    }
    else this->CNP=CNP;
    this->name=name;
    this->ID=IDglobal++;
}

Person &Person::operator=(const Person &person) {
    ID = person.ID;
    name = person.name;
    CNP = person.CNP;
    return *this;
}

ostream &operator<<(ostream &out, const Person &person) {
    out << "ID: " << person.ID << " - CNP: " << person.CNP << " - Name: "; out << person.name;
    return out;
}

istream &operator>>(istream &in, Person &person) {
    in>>person.name>>person.CNP;
    while(!isNumber(person.CNP) or person.CNP.length()!=13) {
        cout<<"Error: CNP must be numerical and must contain exactly 13 digits\n>>> ";
        in>>person.CNP;
    }
    return in;
}

void Person::setName(const string &name) {
    if (name == "") {
        this->name = "None";
        return;
    }
    this->name = name;
    return;
}

string Person::getName() const {
    return name;
}

void Person::setCNP(string CNP) {
    if (CNP.length() != 13) {
        cout << "Error: CNP must be numerical and must contain exactly 13 digits\n";
        return;
    }
    this->CNP = CNP;
}

string Person::getCNP() const {
    return CNP;
}

void Person::setID() {
    if(ID==0) ID=IDglobal++;
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

    friend ostream& operator<<(ostream& out, const Subscription& subscription);

    friend istream& operator>>(istream& in, Subscription& subscription);

    void setName (const string &name);

    string getName () const;

    void setPrice (float price);

    float getPrice () const;

    void setPeriod (int period);

    int getPeriod () const;
};

Subscription::Subscription(const string &name, float price, int period) {
    if (name!="Individual" and name!="Dual" and name!="Family") {
        cout<<"Error: Subscription Type was set to 'None', as it can only be one of the following: 'Individual', 'Dual' or 'Family'\n";
        this->name="None";
    }
    else this->name=name;

    if (price<0.0) {
        cout<<"Error: Subscription price was set to 0, as it must be a positive floating-point number\n";
        this->price=0;
    }
    else this->price=price;

    if (period<0) {
        cout<<"Error: Subscription period was set to 0, as it must be a positive integer\n";
        this->period=0;
    }
    else this->period=period;
}

Subscription& Subscription::operator=(const Subscription &subscription) {
    name=subscription.name;
    price=subscription.price;
    period=subscription.period;
    return *this;
}

ostream& operator<<(ostream& out, const Subscription& subscription) {
    out<<"Type: "<<subscription.name<<" - Price: "<<subscription.price<<"€ - Contract period: "<<subscription.period<<" months";
    return out;
}

istream& operator>>(istream& in, Subscription& subscription) {
    in>>subscription.name;

    while(toLower(subscription.name)!="individual" and toLower(subscription.name)!="Dual" and toLower(subscription.name)!="Family") {
        cout<<"Error: Subscription Type can be 'Individual', 'Dual' or 'Family'\n>>> ";
        in>> subscription.name;
    }

    in>>subscription.price;
    
    while(subscription.price<0.0) {
        cout<<"Error: Subscription price must be a positive floating-point number\n>>> ";
        in>>subscription.price;
    }

    in>>subscription.period;
    
    while(subscription.period<0) {
        cout<<"Error: Subscription period must be a positive integer\n>>> ";
        in>>subscription.period;
    }
    
    return in;
}

void Subscription::setName (const string &name) {
    if (name!="Individual" and name!="Dual" and name!="Family") {
        cout<<"Error: Subscription Type was set to 'None', as it can only be one of the following: 'Individual', 'Dual' or 'Family'\n";
        this->name="None";
    }
    else this->name=name;
}

string Subscription::getName () const {
    return name;
}

void Subscription::setPrice (float price) {
    if (price<0.0) {
        cout<<"Error: Subscription price was set to 0, as it must be a positive floating-point number\n";
        this->price=0;
    }
    else this->price=price;
}

float Subscription::getPrice () const {
    return price;
}

void Subscription::setPeriod (int period) {
    if (period<0) {
        cout<<"Error: Subscription period was set to 0, as it must be a positive integer\n";
        this->period=0;
    }
    else this->period=period;
}

int Subscription::getPeriod () const {
    return period;
}


class PremiumSubscription: public Subscription {
    int discount;
public:
    PremiumSubscription(): Subscription(), discount(0) {};

    PremiumSubscription(const string &name, float price, int period, int discount);

    PremiumSubscription(const PremiumSubscription &premium);
    
    ~PremiumSubscription() {};
    
    PremiumSubscription& operator=(const PremiumSubscription &premium);
    
    friend ostream& operator<<(ostream& out, const PremiumSubscription &premium);
    
    friend istream& operator>>(istream& in, PremiumSubscription &premium);

    void setDiscount(int discount);

    int getDiscount() const;
};

PremiumSubscription::PremiumSubscription(const string &name, float price, int period, int discount): Subscription(name, price, period) {
    if (discount<0) {
        cout << "Error: Subscription discount was set to 0, as it must be between 0 and 1\n";
        this->discount=0;
        return;
    }
    else if (discount>1) {
        cout << "Error: Subscription discount was set to 1, as it must be between 0 and 1\n";
        this->discount=1;
        return;
    }
    this->discount=discount;
}

PremiumSubscription::PremiumSubscription(const PremiumSubscription &premium):
        Subscription(premium.getName(), premium.getPrice(), premium.getPeriod()) {
    discount=premium.discount;
}

PremiumSubscription& PremiumSubscription::operator=(const PremiumSubscription &premium) {
    this->setName(premium.getName());
    this->setPrice(premium.getPrice());
    this->setPeriod(premium.getPeriod());
    discount=premium.discount;
    return *this;
}

ostream& operator<<(ostream& out, const PremiumSubscription &premium) {
    out<< dynamic_cast<const Subscription&>(premium) << " - Discount: "<<premium.discount*100<<"%";
    return out;
}

istream& operator>>(istream& in, PremiumSubscription &premium) {
    in>> dynamic_cast<Subscription&>(premium) >> premium.discount;
    while (premium.discount<0 or premium.discount>1) {
        cout<<"Error: Subscription discount must be between 0 and 1\n";
        in>>premium.discount;
    }
    return in;
}

void PremiumSubscription::setDiscount (int discount) {
    if (discount<0 or discount>1) {
        cout<<"Error: Subscription discount must between 0 and 1\n";
        return;
    }
    this->discount=discount;
}

int PremiumSubscription::getDiscount() const {
    return discount;
}



class Subscriber : public Person {
    string phoneNumber;
    Subscription *x;
public:
    Subscriber() : Person(), x(new Subscription), phoneNumber("0000000000") {};

    Subscriber(const string &name, const string &CNP, const string &phoneNumber, const string &subscriptionName, float price, int period, int discount=0);

    Subscriber(const Subscriber &subscriber);

    ~Subscriber() {};

    Subscriber& operator=(Subscriber &subscriber);

    friend ostream& operator<<(ostream &out, const Subscriber &subscriber);

    friend istream& operator>>(istream &in, Subscriber &subscriber);

    void setPhoneNumber (const string &phoneNumber);

    string getPhoneNumber () {return phoneNumber;};

    float getSubscriptionPrice();

    int getSubscriptionPeriod();

    Subscription* getSubscriptionPointer();
};

Subscriber::Subscriber(const string &name, const string &CNP, const string &phoneNumber, const string &subscriptionName, float price, int period, int discount):
Person(name, CNP)  {
    if (discount<0) {
        cout<<"Error: Discount was set to 0, as it must be between 0 and 1\n";
        x=new PremiumSubscription(subscriptionName, price, period, 0);
    }
    else if (discount>1) {
        cout<<"Error: Discount was set to 1, as it must be between 0 and 1\n";
        x=new PremiumSubscription(subscriptionName, price, period, 1);
    }
    else if (discount==0) {
        x=new Subscription(subscriptionName, price, period);
    }
    else x=new PremiumSubscription(subscriptionName, price, period, discount);

    if (!isNumber(phoneNumber) or phoneNumber.length()!=10) {
        cout<<"Error: Phone number was set to default, as it must be numerical and must contain exactly 10 digits\n";
        this->phoneNumber="0000000000";
    }
    else this->phoneNumber=phoneNumber;

}

Subscriber::Subscriber(const Subscriber &subscriber): Person(subscriber.getName(), subscriber.getCNP()) {
    if (PremiumSubscription *construct=dynamic_cast<PremiumSubscription*>(subscriber.x)) {
        PremiumSubscription toBeInserted = *construct;
        x=&toBeInserted;
    }
    else {
        Subscription toBeInserted= *subscriber.x;
        x=&toBeInserted;
    }
    phoneNumber=subscriber.phoneNumber;
}

Subscriber& Subscriber::operator=( Subscriber &subscriber) {
    this->setName(subscriber.getName());
    this->setCNP(subscriber.getCNP());
    this->setID();
    if (PremiumSubscription *construct=dynamic_cast<PremiumSubscription*>(subscriber.x)) {
        PremiumSubscription toBeInserted = *construct;
        x=&toBeInserted;
    }
    else {
        Subscription toBeInserted= *subscriber.x;
        x=&toBeInserted;
    }
    this->phoneNumber=subscriber.phoneNumber;
    return *this;
}

ostream& operator<<(ostream &out, const Subscriber &subscriber) {
    out<<"  Subscriber "<<dynamic_cast<const Person&>(subscriber)<<" - Phone Number (mobile): "<<subscriber.phoneNumber;

    if (PremiumSubscription* subscription=dynamic_cast<PremiumSubscription*>(subscriber.x)) {
        out<<"\n  Premium Subscription "<<*subscription;
    }
    else out<<"\n  Subscription "<<*subscriber.x;

    return out;
}

istream& operator>>(istream& in, Subscriber &subscriber) {
    in>>dynamic_cast<Person&>(subscriber);
    string command[4];
    in>> command[0];

    in>>command[1];
    while(stof(command[1])<0.0) {
        cout<<"Error: Subscription price must be a positive floating-point number\n>>> ";
        in>>command[1];
    }

    in>>command[2];
    while(stoi(command[2])<0) {
        cout<<"Error: Subscription period must be a positive integer\n>>> ";
        in>>command[2];
    }

    in>>command[3];

    if (stoi(command[3])==0) {
        subscriber.x->setName(command[0]);
        subscriber.x->setPrice(stof(command[1]));
        subscriber.x->setPeriod(stoi(command[2]));
    }
    else if (stoi(command[3])<0){
        delete subscriber.x;
        subscriber.x=new PremiumSubscription(command[0], stof(command[1]), stoi(command[2]), 0);
    }
    else {
        delete subscriber.x;
        subscriber.x=new PremiumSubscription(command[0], stof(command[1]), stoi(command[2]), stoi(command[3]));
    }

    in>>subscriber.phoneNumber;
    while(!isNumber(subscriber.phoneNumber) or subscriber.phoneNumber.length()!=10) {
        cout<<"Error: Subscriber phone number must be numerical and must contain exactly 10 digits\n";
        in>>subscriber.phoneNumber;
    }

    return in;
}

void Subscriber::setPhoneNumber (const string &phoneNumber) {
    if (!isNumber(phoneNumber) or phoneNumber.length()!=10) {
        cout<<"Error: Subscriber phone number was set to default, as it must be numerical and must contain exactly 10 digits\n";
        this->phoneNumber="0000000000";
    }
    else this->phoneNumber=phoneNumber;
}

float Subscriber::getSubscriptionPrice () {
    return x->getPrice();
}

int Subscriber::getSubscriptionPeriod () {
    return x->getPeriod();
}

Subscription* Subscriber::getSubscriptionPointer() {
    return x;
}



class Clients {
    int numberOfClients=0;
    Subscriber *subscribers;
public:
    Clients();

    Clients(Subscriber subscribers[], int numberOfClients);

    Clients(const Clients &clients);

    ~Clients();

    Clients& operator=(const Clients &clients);

    friend ostream& operator<<(ostream &out, const Clients &clients);

    friend istream& operator>>(istream &in, Clients &clients);

    int getNumberOfClients () const {return numberOfClients;};

    int getNumberOfPremiumSubscribers ();

    float getValueOfSubscriptions ();
};

Clients::Clients() {
    subscribers=new Subscriber[200];
}

Clients::Clients(Subscriber subscribers[], int numberOfClients) {
    delete[]this->subscribers;
    this->numberOfClients=numberOfClients;
    for (int i=0; i<numberOfClients; i++) {
        Subscriber aux=subscribers[i];
        this->subscribers[i]=aux;
    }
}

Clients::Clients(const Clients &clients) {
    delete[]subscribers;
    numberOfClients=clients.numberOfClients;
    for (int i=0; i<numberOfClients; i++) {
        Subscriber aux=clients.subscribers[i];
        subscribers[i]=aux;
    }
}

Clients::~Clients() {
    delete[]subscribers;
}

Clients& Clients::operator=(const Clients& clients) {
    delete[]subscribers;
    numberOfClients=clients.numberOfClients;
    for (int i=0; i<numberOfClients; i++) {
        Subscriber aux=clients.subscribers[i];
        subscribers[i]=aux;
    }
    return *this;
}

ostream& operator<<(ostream &out, const Clients &clients) {
    out<<"All stored clients:\n";
    for(int i=0; i<clients.numberOfClients; i++) out<<clients.subscribers[i]<<"\n\n";
    return out;
}

istream& operator>>(istream &in, Clients &clients) {
    cout<<">>> Enter the number of clients you wish to input: ";
    in>>clients.numberOfClients;
    while(clients.numberOfClients<=0) {
        cout<<"Error: Number of clients must be a positive integer\n";
        cout<<">>> Enter the number of clients you wish to input: ";
        in>>clients.numberOfClients;
    }

    cout<<"Enter a list of clients in the following format, using SPACE as a delimiter:\n";
    cout<<"Warning: A discount is only available for premium subscriptions. Type '0' in the discount field for a basic subscription\n";
    cout<<"ClientName    CNP    SubscriptionName    SubscriptionPrice   ContractPeriod   SubscriptionDiscount   PhoneNumber\n\n";

    for (int i=0; i<clients.numberOfClients; i++) {
        cout<<">>> Enter a client:\n";
        in>>clients.subscribers[i];
    }

    return in;
}

int Clients::getNumberOfPremiumSubscribers () {
    int premiumSubscribers=0;
    for (int i=0; i<this->numberOfClients; i++) {
        if (dynamic_cast<PremiumSubscription*>((this->subscribers+i)->getSubscriptionPointer())) premiumSubscribers++;
    }
    return premiumSubscribers;
}

float Clients::getValueOfSubscriptions () {
    float value=0;
    for (int i=0; i<this->numberOfClients; i++)
        value+=this->subscribers[i].getSubscriptionPrice()*(float)subscribers[i].getSubscriptionPeriod();
    return value;
}

int main() {
    Clients clients, *favouriteClients;
    int n, command = -3, option1 = -3, option2 = -3, option3;
    float option4;
    string auxiliary;

//    subscribers reading and welcome message
    cout << "Welcome to Cliently v1.0 !\n..........LOADING...........\n\n";
    cin>>clients;

    //  copying of favourite book in object 'favourite'
    cout << "\nFavourite book is unmodifiable\n";
    cout << ">>> Enter the ID of your favourite book: ";
    cin >> option1;
    while (option1 > n or option1 <= 0) {
        cout << "Error: book IDs must be positive, non-null and cannot exceed total book number\n";
        cout << ">>> Enter the ID of your favourite book: ";
        cin >> option1;
    }
    option1--;
    carte favourite(books[option1]);

    // program functions and instructions listing
    cout << "\nCliently employs the following functions:\n";
    cout << "1) modify client data\n";
    cout << "2) new client entry\n";
    cout<<"3) print the number of premium clients\n";
    cout<<"4) print the total earnings\n";
    cout << "5) print client data by ID\n";
    cout << "6) print VIP client(s)\n";
    cout << "7) print all stored clients\n\n";
    cout << "Instruction manual:\n";
    cout << "- function-menus can only be accessed by giving their ID number as input\n";
    cout << "- to abort current function-menu, type \"-1\"\n";
    cout << "- to quit the program, type \"-2\"\n";
    cout << "- clients can only be identified by their global ID (their order number in the list)\n";

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
                cout << "\t\tChoosing '7)' will change basic subscriptions to premium\n";
                cout << ">>> Enter a valid option or command ID: ";
                cin >> option1;

                while (option1 < -2 or option1 > 6) {
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

                    while (option2 < -2 or option2 > clients.getNumberOfClients() - 1 or option2 == 0) {
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
                                cout << ">>> Enter a new name for \"" <<  << "\": ";
                                cin>>auxiliary;
                                // MODIFY CLIENT NAME

                                cout << "Client name has been modified\n";
                                break;

                            case 2:         // modify client CNP
                                cout << ">>> Enter a new CNP for \"" <<  << "\": ";
                                cin>>auxiliary;
                                // MODIFY CLIENT CNP

                                cout << "CNP has been modified\n";
                                break;

                            case 3:         // modify client phone number
                                cout << ">>> Enter a new phone number for \"" <<  << "\": ";
                                cin>>auxiliary;
                                // MODIFY CLIENT PHONE NUMBER

                                cout << "Phone number has been modified\n";
                                break;

                            case 4:         //  modify subscription type
                                cout << ">>> Enter a new subscription type for \"" <<  << "\": ";
                                cin>>auxiliary;
                                // MODIFY SUBSCRIPTION TYPE

//                                cin >> option3;
//                                while (option3 < 0) {
//                                    cout << "Error: Number of pages must be a positive number\n";
//                                    cout << ">>> Enter a new number of pages for \"" << books[option2].getDenumire() << "\": ";
//                                    cin >> option3;
//                                }
//                                books[option2].setPagini(option3);
                                cout << "Subscription Type has been modified\n";
                                break;

                            case 5:         // modify subscription price
                                cout << ">>> Enter a new subscription price for \"" << << "\": ";
                                cin >> option4;
                                while (option4 < 0.0) {
                                    cout<<"Error: Subscription price must be a positive floating-point number\n ";
                                    cout << ">>> Enter a new subscription price for \"" << << "\": ";
                                    cin>>option4;
                                }
                                clients.subscribers[option2].setPret(option4);
                                cout << "Subscription price has been modified\n";
                                break;

                            case 6:         // modify contract period
                                cout << ">>> Enter a new contract period for \"" <<  << "\": ";
                                cin >> option3;
                                while (option3 < 0) {
                                    cout<<"Error: Subscription period must be a positive integer\n";
                                    cout << ">>> Enter a new contract period for \"" <<  << "\": ";
                                    cin >> option3;
                                }
                                // MODIFY CONTRACT PERIOD

                                cout << "Contract period has been modified\n";
                                break;

                            case 7:
                                cout<<"Enter a new subscription discount for \"" << << "\": ";
                                cin >> option3;
                                while (option3 < 0) {
                                    cout<<"Error: Subscription discount must be between 0 and 100\n";
                                    cout << ">>> Enter a new contract period for \"" <<  << "\": ";
                                    cin >> option3;
                                }
                                // MODIFY CONTRACT PERIOD

                                cout<< "Subscription discount has been modified\n";
                                break;
                        }
                    }
                }
                break;


            case 2:         // new-client-entry menu
                cout << "New client entry options:\n";
                cout << "1) default client entry\n";
                cout << "2) input new client entry\n";
                cout << ">>> Enter a valid option or command ID: ";

                cin >> option1;
                while (option1 > 2 or option1 < -2) {
                    cout << "Error: out of range new-client-entry-menu option (1-2) and command (-1,-2) IDs\n";
                    cout << ">>> Enter a valid option or command ID: ";
                    cin >> option1;
                }

                switch (option1) {
                    case -1: {              // abort
                        cout << "Aborting\n";
                        break;
                    }
                    case -2: {              // quit
                        command = -2;
                        break;
                    }
                    case 1: {
                        //  NEW DEFAULT CLIENT
//                        n++;
                        cout << "New client entry was initialized with the default values\n";
                        break;
                    }
                    case 2: {
                        //  NEW INPUT CLIENT
//                        n++;
                        cout << "New client entry was initialized successfully\n";
                        break;
                    }
                }
                break;


            case 4:         //  print book by ID menu
                cout << "Print book info options:\n";
                cout << "1) Book title\n";
                cout << "2) Main author\n";
                cout << "3) Second author\n";
                cout << "4) Number of pages\n";
                cout << "5) Price\n";
                cout << "6) Goodreads rating\n";
                cout << ">>> Enter a valid option or command ID: ";

                cin >> option1;
                while (option1 > 6 or option1 < -2) {
                    cout << "Error: out of range print-menu option (1-6) and command (-1,-2) IDs\n";
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
                    cout << ">>> Enter the ID of the book to be printed: ";

                    cin >> option2;
                    while (option2 < -2 or option2 > n or option2 == 0) {
                        cout << "Error: book IDs must be positive, non-null and cannot exceed total book number\n";
                        cout << ">>> Enter the ID of the book to be printed: ";
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
                            case 1:         // print book title
                                cout << "The title of book " << option2 + 1 << " is: \'" << books[option2].getDenumire() << "\'\n";
                                break;

                            case 2:         // print main author
                                cout << "The main author of book \'" << books[option2].getDenumire() << "\' is: "
                                     << books[option2].getAutorPrincipal() << '\n';
                                break;

                            case 3:         // print second author
                                cout << "The second author of book \'" << books[option2].getDenumire() << "\' is: "
                                     << books[option2].getAutorSecundar() << '\n';
                                break;

                            case 4:         //  print number of pages
                                cout << "\'" << books[option2].getDenumire() << "\' has " << books[option2].getPagini() << " pages\n";
                                break;

                            case 5:         // print price
                                cout << "\'" << books[option2].getDenumire() << "\' costs " << books[option2].getPret() << "€\n";
                                break;

                            case 6:         // print rating
                                cout << "\'" << books[option2].getDenumire() << "\' is rated at " << books[option2].getRating() << "/5.0 stars\n";
                                break;
                        }
                    }
                }
                break;


            case 5:     //  favourite book
                cout << "Your favourite book:\n" << favourite << '\n';
                break;
            case 6:         // print all stored books
                cout << "All stored books will be printed to the screen:\n";
                for (int i = 0; i < n; i++) cout << books[i] << '\n';  // printing to the screen
                break;

            case -1:         // abort
                cout << "Error: abort command can only be used inside function-menus\n";
                break;
            case -2:         // quit
                break;
            default:
                cout << "Error: out of range function-menu (1-6) and command (-1,-2) IDs\n";
                break;
        }
    }

    return 0;
}