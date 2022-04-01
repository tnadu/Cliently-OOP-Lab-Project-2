#include <iostream>
#include <string>

using namespace std;

bool isNumber (string x) {
    for (int i=0; i<x.length(); i++) {
        if (!isdigit(x[i])) return false;
    }
    return true;
}

class Person {
protected:
    static int IDglobal;
    int ID;
    string name, CNP;
    static int getIDglobal() { return IDglobal; };
public:
    Person() : ID(IDglobal++), name("None"), CNP("0000000000000") {};

    Person(string name, string CNP);

    Person(const Person &person) : ID(IDglobal++), name(person.name), CNP(person.CNP) {};

    virtual ~Person();

    Person &operator=(const Person &person);

    friend ostream &operator<<(ostream &out, const Person &person);

    friend istream &operator>>(istream &in, Person &person);

    void setName(string name);

    string getName() const;

    void setCNP(string CNP);

    string getCNP() const;

    void setID();

    int  getID() const;
};

int Person::IDglobal = 0;

Person::Person(string name, string CNP) {
    if (!isNumber(CNP)) {
        cout<<"Error: CNP must be numerical\n";
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
    out << "ID: " << person.ID << " - CNP: " << person.CNP << " - Name: " << person.name;
    return out;
}

istream &operator>>(istream &in, Person &person) {
    getline(in, person.name, '\t');
    getline(in, person.CNP, '\t');
    while(!isNumber(person.CNP)) {
        cout<<"Error: CNP must be numerical\n";
        getline(in, person.CNP);
    }
    return in;
}

void Person::setName(string name) {
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
        cout << "Invalid";
        return;
    }
    this->CNP = CNP;
}

string Person::getCNP() const {
    return CNP;
}

void Person::setID() {
    ID=IDglobal++;
}

int Person::getID() const {
    return ID;
}



class Subscription {
protected:
    string name;
    float price;
    int period;
public:
    Subscription() : name("None"), price(0), period(0) {};

    Subscription(string name, float price, int period);

    Subscription(const Subscription &subscription) : name(subscription.name), price(subscription.price),
                                                     period(subscription.period) {};

    virtual ~Subscription();

    Subscription &operator=(const Subscription &subscription);

    friend ostream& operator<<(ostream& out, const Subscription& subscription);

    friend istream& operator>>(istream& in, Subscription& subscription);

    void setName (string name);

    string getName () const;

    void setPrice (float price);

    float getPrice () const;

    void setPeriod (int period);

    int getPeriod () const;
};

Subscription::Subscription(string name, float price, int period) {
    if (name!="Individual" and name!="Dual" and name!="Family") {
        cout<<"Error: Subscription name was set to 'None', as it can only be one of the following: 'Individual', 'Dual' or 'Family'\n";
        this->name="None";
    }
    else this->name=name;

    if (price<0) {
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
    out<<"Name: "<<subscription.name<<" - Price: "<<subscription.price<<" - Contract period: "<<subscription.period;
    return out;
}

istream& operator>>(istream& in, Subscription& subscription) {
    getline(in, subscription.name, '\t');

    while(subscription.name!="Individual" and subscription.name!="Dual" and subscription.name!="Family") {
        cout<<"Error: Subscription name can be 'Individual', 'Dual' or 'Family'\n>>> ";
        getline(in, subscription.name);
    }

    in>>subscription.price;
    
    while(subscription.price<0) {
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

void Subscription::setName (string name) {
    if (name!="Individual" and name!="Dual" and name!="Family") {
        cout<<"Error: Subscription name was set to 'None', as it can only be one of the following: 'Individual', 'Dual' or 'Family'\n";
        this->name="None";
    }
    else this->name=name;
}

string Subscription::getName () const {
    return name;
}

void Subscription::setPrice (float price) {
    if (price<0) {
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
protected:
    int discount;
public:
    PremiumSubscription(): Subscription(), discount(0) {};

    PremiumSubscription(string name, float price, int period, int discount);

    PremiumSubscription(const PremiumSubscription &premium);
    
    ~PremiumSubscription();
    
    PremiumSubscription& operator=(const PremiumSubscription &premium);
    
    friend ostream& operator<<(ostream& out, const PremiumSubscription &premium);
    
    friend istream& operator>>(istream& in, PremiumSubscription &premium);

    void setDiscount(int discount);

    int getDiscount() const;
};

PremiumSubscription::PremiumSubscription(string name, float price, int period, int discount): Subscription(name, price, period) {
    if (discount<0) {
        cout << "Error: Subscription discount was set to 0, as it must be a positive integer\n";
        this->discount=0;
        return;
    }
    this->discount=discount;
}

PremiumSubscription::PremiumSubscription(const PremiumSubscription &premium) {
    this->setName(premium.name);
    this->setPrice(premium.price);
    this->setPeriod(premium.period);
    discount=premium.discount;
}

PremiumSubscription& PremiumSubscription::operator=(const PremiumSubscription &premium) {
    name=premium.name;
    price=premium.price;
    period=premium.period;
    discount=premium.discount;
    return *this;
}

ostream& operator<<(ostream& out, const PremiumSubscription &premium) {
    out<< dynamic_cast<const Subscription&>(premium) << " - Discount: "<<premium.discount;
    return out;
}

istream& operator>>(istream& in, PremiumSubscription &premium) {
    in>> dynamic_cast<Subscription&>(premium) >> premium.discount;
    while (premium.discount<0) {
        cout<<"Error: Subscription discount must be a positive integer\n";
        in>>premium.discount;
    }
    return in;
}

void PremiumSubscription::setDiscount (int discount) {
    if (discount<0) {
        cout<<"Error: Subscription discount must be a positive integer\n";
        return;
    }
    this->discount=discount;
}

int PremiumSubscription::getDiscount() const {
    return discount;
}



class Subscriber : public Person {
protected:
    string phoneNumber;
    Subscription *x;
public:
    Subscriber() : Person(), x(new Subscription), phoneNumber("0000000000") {};

    Subscriber(string name, string CNP, string phoneNumber, string subscriptionName, float price, int period, int discount=0);

    Subscriber(const Subscriber &subscriber);

    ~Subscriber();

    Subscriber& operator=(Subscriber &subscriber);

    friend ostream& operator<<(ostream &out, const Subscriber &subscriber);

    friend istream& operator>>(istream &in, Subscriber &subscriber);

    void setPhoneNumber (string phoneNumber);

    string getPhoneNumber ();
};

Subscriber::Subscriber(string name, string CNP, string phoneNumber, string subscriptionName, float price, int period, int discount):
Person(name, CNP)  {
    if (discount<0) {
        cout<<"Error: Discount was set to 0, as it must be a positive integer\n";
        x=new PremiumSubscription(subscriptionName, price, period, 0);
    }
    else if (discount==0) {
        x=new Subscription(subscriptionName, price, period);
    }
    else x=new PremiumSubscription(subscriptionName, price, period, discount);

    if (!isNumber(phoneNumber)) {
        cout<<"Error: Phone number was set to default, as it must be numerical\n";
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
    this->name=subscriber.name;
    this->CNP=subscriber.CNP;
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

void Subscriber::setPhoneNumber (string phoneNumber) {
    if (!isNumber(phoneNumber)) {
        cout<<"Error: Subscriber phone number was set to default, as it must be numerical\n";
        this->phoneNumber="0000000000";
    }
    else this->phoneNumber=phoneNumber;
}

ostream& operator<<(ostream &out, const Subscriber &subscriber) {
    out<<"Subscriber:: "<<dynamic_cast<const Person&>(subscriber)<<" - Phone Number: "<<subscriber.phoneNumber;
    out<<"\nSubscription:: "<<subscriber.x;
    return out;
}

istream& operator>>(istream& in, Subscriber &subscriber) {
    in>>dynamic_cast<Person&>(subscriber);
    string command[4];
    getline(in, command[0], '\t');
    getline(in, command[1], '\t');
    in>>command[2];
    while(stof(command[2])<0) {
        cout<<"Error: Subscription price must be a positive floating-point number\n>>> ";
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
    while(!isNumber(subscriber.phoneNumber)) {
        cout<<"Error: Subscriber phone number must be numerical\n";
        in>>subscriber.phoneNumber;
    }

    return in;
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

    int getNumberOfClients () {return numberOfClients;};
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
    for(int i=0; i<clients.numberOfClients; i++) out<<clients.subscribers[i]<<'\n';
    return out;
}

istream& operator>>(istream &in, Clients &clients) {
    
}

int main() {

    return 0;
}