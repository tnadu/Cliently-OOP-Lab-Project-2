#include <iostream>

using namespace std;

class Person {
    static int IDglobal;
    int ID;
    string name, CNP;
protected:
    static int getIDglobal() { return IDglobal; };
public:
    Person() : ID(IDglobal++), name("Default"), CNP("0000000000000") {};

    Person(string name, string CNP) : ID(IDglobal++), name(name), CNP(CNP) {};

    Person(const Person &person) : ID(IDglobal++), name(person.name), CNP(person.CNP) {};

    ~Person();

    Person &operator=(const Person &person);

    friend ostream &operator<<(ostream &out, const Person &person);

    friend istream &operator>>(istream &in, Person &person);

    void setName(string name);

    string getName();

    void setCNP(string CNP);

    string getCNP();
};

int Person::IDglobal = 0;


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
    return in;
}

void Person::setName(string name) {
    if (name == "") {
        this->name = "Default";
        return;
    }
    this->name = name;
    return;
}

string Person::getName() {
    return name;
}

void Person::setCNP(string CNP) {
    if (CNP.length() != 13) {
        cout << "Invalid";
        return;
    }
    this->CNP = CNP;
}

string Person::getCNP() {
    return CNP;
}


class Subscription {
    string subscriptionName;
    float price;
    int period;
public:
    Subscription() : subscriptionName("Default"), price(0), period(0) {};

    Subscription(string subscriptionName, float price, int period) : subscriptionName(subscriptionName), price(price), period(period) {};

    Subscription(const Subscription &subscription) : subscriptionName(subscription.subscriptionName), price(subscription.price),
                                                     period(subscription.period) {};

    ~Subscription();

    Subscription &operator=(const Subscription &subscription);

    friend ostream& operator<<(ostream& out, const Subscription& subscription);

    friend istream& operator>>(istream& in, Subscription& subscription);
};

Subscription& Subscription::operator=(const Subscription &subscription) {
    subscriptionName=subscription.subscriptionName;
    price=subscription.price;
    period=subscription.period;
    return *this;
}

ostream& operator<<(ostream& out, const Subscription& subscription) {
    out<<"Name: "<<subscription.subscriptionName<<" - Price: "<<subscription.price<<" - Contract period: "<<subscription.period;
    return out;
}

istream& operator>>(istream& in, Subscription& subscription) {
    in>>subscription.subscriptionName;

    while()
}


class Subscriber : public Person {
    string phoneNumber;
    Subscription x;
public:
    Subscriber() : Person(), x(), phoneNumber("0000000000") {};

    Subscriber(string name, string CNP, string phoneNumber) : Person(name, CNP), phoneNumber(phoneNumber) {};
};

int main() {
    return 0;
}