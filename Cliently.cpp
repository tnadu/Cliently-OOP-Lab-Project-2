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

    void setID(int ID);

    int getID() {return ID;};
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
        cout<<"Error: CNP must be numerical and must contain exactly 13 digits\n";
        cout<<">>> Enter a valid CNP: ";
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

void Person::setID(int ID) {
    this->ID=ID;
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
        cout<<"Error: Subscription Type can be 'Individual', 'Dual' or 'Family'\n";
        cout<<">>> Enter a valid subscription type: ";
        in>> subscription.name;
    }

    in>>subscription.price;
    
    while(subscription.price<0.0) {
        cout<<"Error: Subscription price must be a positive floating-point number\n";
        cout<<">>> Enter a valid subscription price: ";
        in>>subscription.price;
    }

    in>>subscription.period;
    
    while(subscription.period<0) {
        cout<<"Error: Subscription period must be a positive integer\n";
        cout<<">>> Enter a valid subscription period: ";
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
        cout << "Error: Subscription discount was set to 0, as it must be between 0 and 100\n";
        this->discount=0;
        return;
    }
    else if (discount>100) {
        cout << "Error: Subscription discount was set to 100, as it must be between 0 and 100\n";
        this->discount=100;
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
    out<< dynamic_cast<const Subscription&>(premium) << " - Discount: "<<premium.discount<<"%";
    return out;
}

istream& operator>>(istream& in, PremiumSubscription &premium) {
    in>> dynamic_cast<Subscription&>(premium) >> premium.discount;
    while (premium.discount<0 or premium.discount>100) {
        cout<<"Error: Subscription discount must be between 0 and 100\n";
        cout<<">>> Enter a valid subscription discount: ";
        in>>premium.discount;
    }
    return in;
}

void PremiumSubscription::setDiscount (int discount) {
    if (discount<0 or discount>100) {
        cout<<"Error: Subscription discount must between 0 and 100\n";
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

    Subscription* getSubscription() {return x;};
};

Subscriber::Subscriber(const string &name, const string &CNP, const string &phoneNumber, const string &subscriptionName, float price, int period, int discount):
Person(name, CNP)  {
    if (discount==0) {
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
        cout<<"Error: Subscription price must be a positive floating-point number\n";
        cout<<">>> Enter a valid subscription price: ";
        in>>command[1];
    }

    in>>command[2];
    while(stoi(command[2])<0) {
        cout<<"Error: Subscription period must be a positive integer\n";
        cout<<">>> Enter a valid subscription period: ";
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
        cout<<"Error: Phone number must be numerical and must contain exactly 10 digits\n";
        cout<<">>> Enter a valid phone number: ";
        in>>subscriber.phoneNumber;
    }

    return in;
}

void Subscriber::setPhoneNumber (const string &phoneNumber) {
    if (!isNumber(phoneNumber) or phoneNumber.length()!=10) {
        cout<<"Error: Phone number was set to default, as it must be numerical and must contain exactly 10 digits\n";
        this->phoneNumber="0000000000";
    }
    else this->phoneNumber=phoneNumber;
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

    Subscriber* getSubscribers () {return subscribers;}

    int getNumberOfPremiumSubscribers ();

    float getTotalEarnings ();

    void deleteClients();
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
        cout<<">>> Enter a valid number of clients: ";
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
        if (dynamic_cast<PremiumSubscription*>((this->subscribers+i)->getSubscription())) premiumSubscribers++;
    }
    return premiumSubscribers;
}

float Clients::getTotalEarnings () {
    float value=0;
    for (int i=0; i<this->numberOfClients; i++)
        if (PremiumSubscription *premium=dynamic_cast<PremiumSubscription*>(this->subscribers+i)) {
            value += this->subscribers[i].getSubscription()->getPrice() * (float) subscribers[i].getSubscription()->getPeriod();
            value -= value * ((float)premium->getDiscount()/100);
        }
        else value+=this->subscribers[i].getSubscription()->getPrice()*(float)subscribers[i].getSubscription()->getPeriod();
    return value;
}

void Clients::deleteClients () {
    numberOfClients=0;
    delete[]subscribers;
    subscribers=new Subscriber[200];
}



int main() {
    Clients clients, VIPclients;
    int n, command = -3, option1 = -3, option2 = -3, option3;
    float option4;
    string auxiliary;

    //  clients reading and welcome message
    cout << "Welcome to Cliently v1.0 !\n..........LOADING...........\n\n";
    cin>>clients;

    //  copying of VIP clients in pointer array 'VIPclients'
    cout << "\nVIP client list is unmodifiable\n";
    cout << ">>> Enter the number of VIP clients: ";

    cin >> n;
    while (n<=0 or n>clients.getNumberOfClients()) {
        cout << "Error: Number of VIP clients must be between 1 and total number of clients\n";
        cout << ">>> Enter the number of VIP clients: ";
        cin >> n;
    }
    VIPclients=Clients(clients);
    VIPclients.deleteClients();


    for (int i=0; i<n; i++) {
        cout << ">>> Enter the ID of a VIP client: ";
        cin >> option1;

        while (option1<0 or option1>=clients.getNumberOfClients()) {
            cout << "Error: client IDs must be positive and cannot exceed maximum ID number\n";
            cout << ">>> Enter the ID of a VIP client: ";
            cin >> option1;
        }

        (VIPclients.getSubscribers())[i]=clients.getSubscribers()[option1];
        (VIPclients.getSubscribers())[i].setID(clients.getSubscribers()[option1].getID());
    }

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
                                cout << ">>> Enter a new name for \"" << clients.getSubscribers()[option2].getName() << "\": ";
                                cin>>auxiliary;
                                clients.getSubscribers()[option2].setName(auxiliary);
                                cout << "Client name has been modified\n";
                                break;

                            case 2:         // modify client CNP
                                cout << ">>> Enter a new CNP for \"" << clients.getSubscribers()[option2].getName() << "\": ";

                                cin>>auxiliary;
                                while(!isNumber(auxiliary) or auxiliary.length()!=13) {
                                    cout<<"Error: CNP must be numerical and must contain exactly 13 digits\n";
                                    cout<<">>> Enter a valid CNP: ";
                                    cin>>auxiliary;
                                }
                                clients.getSubscribers()[option2].setCNP(auxiliary);

                                cout << "CNP has been modified\n";
                                break;

                            case 3:         // modify client phone number
                                cout << ">>> Enter a new phone number for \"" << clients.getSubscribers()[option2].getName() << "\": ";

                                cin>>auxiliary;
                                while(!isNumber(auxiliary) or auxiliary.length()!=10) {
                                    cout<<"Error: Phone number must be numerical and must contain exactly 10 digits\n";
                                    cout<<">>> Enter a valid phone number: ";
                                    cin>>auxiliary;
                                }
                                clients.getSubscribers()[option2].setPhoneNumber(auxiliary);

                                cout << "Phone number has been modified\n";
                                break;

                            case 4:         //  modify subscription type
                                cout << ">>> Enter a new subscription type for \"" << clients.getSubscribers()[option2].getName() << "\": ";

                                cin>>auxiliary;
                                while(toLower(auxiliary)!="individual" and toLower(auxiliary)!="Dual" and toLower(auxiliary)!="Family") {
                                    cout<<"Error: Subscription Type can be 'Individual', 'Dual' or 'Family'\n";
                                    cout<<">>> Enter a valid subscription type: ";
                                    cin>> auxiliary;
                                }
                                clients.getSubscribers()[option2].setName(auxiliary);

                                cout << "Subscription Type has been modified\n";
                                break;

                            case 5:         // modify subscription price
                                cout << ">>> Enter a new subscription price for \"" << clients.getSubscribers()[option2].getName() << "\": ";

                                cin >> option4;
                                while (option4 < 0.0) {
                                    cout<<"Error: Subscription price must be a positive floating-point number\n ";
                                    cout << ">>> Enter a new subscription price for \"" << clients.getSubscribers()[option2].getName() << "\": ";
                                    cin>>option4;
                                }
                                clients.getSubscribers()[option2].getSubscription()->setPrice(option4);

                                cout << "Subscription price has been modified\n";
                                break;

                            case 6:         // modify contract period
                                cout << ">>> Enter a new contract period for \"" << clients.getSubscribers()[option2].getName() << "\": ";

                                cin >> option3;
                                while (option3 < 0) {
                                    cout<<"Error: Subscription period must be a positive integer\n";
                                    cout << ">>> Enter a new contract period for \"" << clients.getSubscribers()[option2].getName() << "\": ";
                                    cin >> option3;
                                }
                                clients.getSubscribers()[option2].getSubscription()->setPeriod(option3);

                                cout << "Contract period has been modified\n";
                                break;

                            case 7:         // modify subscription discount
                                cout<<"Enter a new subscription discount for \"" << clients.getSubscribers()[option2].getName() << "\": ";

                                cin >> option3;
                                while (option3 < 0) {
                                    cout<<"Error: Subscription discount must be between 0 and 100\n";
                                    cout << ">>> Enter a new contract period for \"" << clients.getSubscribers()[option2].getName() << "\": ";
                                    cin >> option3;
                                }
                                clients.getSubscribers()[option2].getSubscription()->setDiscount();

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

                
            case 3:
                cout<<"The total number of premium clients: "<<clients.getNumberOfPremiumSubscribers()<<'\n';
                break;
                
            case 4:
                cout<<"Total earnings: "<<clients.getTotalEarnings()<<"€\n";
                break;

            case 5:         //  print client data by ID menu
                cout << ">>> Enter the ID of the client whose data will be printed: ";

                cin >> option1;
                while (option1 < -2 or option1 > clients.getNumberOfClients()-1 or option1 == 0) {
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
                } else cout<<clients.getSubscribers()[option1];

                break;


            case 6:     //  print VIP client(s) data
                // TO BE IMPLEMENTED WITH AN ARRAY OF POINTERS OF TYPE SUBSCRIBER

                break;

            case 7:         // print all stored clients
                cout << clients;
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