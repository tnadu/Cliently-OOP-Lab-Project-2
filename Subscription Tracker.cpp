#include <iostream>

using namespace std;

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
protected:
    static int getIDglobal() { return IDglobal; };
public:
    Person() : ID(IDglobal++), name("None"), CNP("0000000000000") {};

    Person(string name, string CNP);

    Person(const Person &person) : ID(IDglobal++), name(person.name), CNP(person.CNP) {};

    ~Person();

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
        return;
    }
    this->name=name;
    this->CNP=CNP;
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
    in >> person.name >> person.CNP;
    while(!isNumber(person.CNP)) {
        cout<<"Error: CNP must be numerical\n";
        in>>person.CNP;
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

    ~Subscription();

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
        cout<<"Error: Subscription name can be 'Individual', 'Dual' or 'Family'\n";
        return;
    }
    this->name=name;

    if (price<0) {
        cout<<"Error: Subscription price must be a positive floating-point number\n";
        return;
    }
    this->price=price;

    if (period<0) {
        cout<<"Error: Subscription period must be a positive integer\n";
        return;
    }
    this->period=period;
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
    in>>subscription.name;

    while(subscription.name!="Individual" and subscription.name!="Dual" and subscription.name!="Family") {
        cout<<"Error: Subscription name can be 'Individual', 'Dual' or 'Family'\n>>> ";
        in>>subscription.name;
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
        cout<<"Error: Subscription name can be 'Individual', 'Dual' or 'Family'\n";
        return;
    }
    this->name=name;
}

string Subscription::getName () const {
    return name;
}

void Subscription::setPrice (float price) {
    if (price<0) {
        cout<<"Error: Subscription price must be a positive floating-point number\n";
        return;
    }
    this->price=price;
}

float Subscription::getPrice () const {
    return price;
}

void Subscription::setPeriod (int period) {
    if (period<0) {
        cout<<"Error: Subscription period must be a positive integer\n";
        return;
    }
    this->period=period;
}

int Subscription::getPeriod () const {
    return period;
}


class PremiumSubscription: public Subscription {
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

PremiumSubscription::PremiumSubscription(string name, float price, int period, int discount) {
    if (discount<0) {
        cout<<"Error: Subscription discount must be a positive integer\n";
        return;
    }
    Subscription(name, price, period);
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
    string phoneNumber;
    Subscription x;
public:
    Subscriber() : Person(), x(), phoneNumber("0000000000") {};

    Subscriber(string name, string CNP, string phoneNumber, string subscriptionName, float price, int period);

    Subscriber(const Subscriber &subscriber);

    ~Subscriber();

    Subscriber& operator=(Subscriber &subscriber);
};

Subscriber::Subscriber(string name, string CNP, string phoneNumber, string subscriptionName, float price, int period) {
    if (!isNumber(phoneNumber)) {
        cout<<"Error: Phone number must be numerical\n";
        return;
    }
    Person(name, CNP);
    Subscription(subscriptionName, price, period);
    this->phoneNumber=phoneNumber;
}

Subscriber::Subscriber(const Subscriber &subscriber): Person(subscriber.getName(), subscriber.getCNP()),
                                                      x(subscriber.x.getName(), subscriber.x.getPrice(), subscriber.x.getPeriod()) {
    phoneNumber=subscriber.phoneNumber;
}

Subscriber& Subscriber::operator=( Subscriber &subscriber) {
    this->setName(subscriber.getName());
    this->setCNP(subscriber.getCNP());
    this->setID();
    x.setName(subscriber.x.getName());
}

int main() {
    return 0;
}