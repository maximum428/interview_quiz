/* 設計一個「火車購票系統」

1. Define requirements:
   - Check train schedule
   - Check seats
   - Buy tickets
   - Cancel tickets
   - Calculate fee
   - Support different passenger type
      - Adult, Student, Senior
   - Support differnt seat type
      - Business, frist class, second class
2. Goal
  - Exppandible
  - maintainable
  - avoid high copuling
  - Flexible for future requests (ex. add seat type, charging, promotion/discount)

3. OOB
  1. Train
  2. Seat
  3. Trip
  4. Ticket
  5. Passenger
  6. Order
  7. BookingSystem

4. Design patterns
  - Strategy pattern: Tickets
  - Factory Pattern: create tickets
  - Observer Pattern:  SMS, Email, logging
  - Singleton ??
  - State Pattern: Created, Paid, Cancelled, Refunded
*/


#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <stdexcept>

using namespace std;

enum class SeatType {
  Business,
  FirstClass,
  SecondClass
};

enum class PassengerType {
  Adult,
  Student,
  Senior
};

class Passenger {
private:
  string m_name;
  PassengerType m_type;
public:
  Passenger(const string& name, PassengerType type) : m_name(name), m_type(type) {}
  string getName() const { return m_name; }
  PassengerType getType() const { return m_type; }
};

class Seat {
private:
  int m_seatId;
  SeatType m_type;
  bool m_booked;
public:
  Seat(int id, SeatType type) : m_seatId(id), m_type(type), m_booked(false) {}
  int getSeatId() const { return m_seatId; }
  SeatType getSeatType() const { return m_type; }
  bool isBooked() const { return m_booked; }
  void book() {
    if (m_booked) {
      throw runtime_error("Seat already booked");
    }
    m_booked = true;
  }
  void cancel() {
    m_booked = false;
  }
};

class Train {
private:
  string m_trainNo;
  vector<shared_ptr<Seat>> m_seats;
public:
  Train(const string& no) : m_trainNo(no) {}
  void addSeat(shared_ptr<Seat> seat) {
    m_seats.push_back(seat);
  }
  const vector<shared_ptr<Seat>>& getSeats() const {
    return m_seats;
  }
  string getTrainNo() const { return m_trainNo; }
};

class Trip {
private:
  string tripId;
  string fromStation;
  string toStation;
  string date;
  shared_ptr<Train> train;
public:
  Trip(const string& id, const string& from, const string& to, const string& date, shared_ptr<Train> train) : tripId(id), fromStation(from), toStation(to), date(date), train(train) {}
  string getTripId() const { return tripId; }
  string getFrom() const { return fromStation; }
  string getTo() const { return toStation; }
  string getDate() const { return date; }
  shared_ptr<Train> getTrain() const { return train; }
};

class PricingStrategy {
public:
  virtual ~PricingStrategy() = default;
  virtual double calculatePrice(double basePrice) const = 0;
};

class FullFareStrategy : public PricingStrategy {
public:
  double calculatePrice(double basePrice) const override {
    return basePrice;
  }
};

class StudentFareStrategy : public PricingStrategy {
public:
  double calculatePrice(double basePrice) const override {
    return basePrice * 0.8;
  }
};

class SeniorFareStrategy : public PricingStrategy {
public:
  double calculatePrice(double basePrice) const override {
    return basePrice * 0.5;
  }
};

class PricingStrategyFactory {
public:
  static unique_ptr<PricingStrategy> create(PassengerType type) {
    switch (type) {
      case PassengerType::Adult:
        return make_unique<FullFareStrategy>();
      case PassengerType::Student:
        return make_unique<StudentFareStrategy>();
      case PassengerType::Senior:
        return make_unique<SeniorFareStrategy>();
      default:
        throw runtime_error("Unknown passenger type");
    }
  }
};

class Ticket {
private:
  Passenger passenger;
  shared_ptr<Trip> trip;
  shared_ptr<Seat> seat;
  double price;
public:
  Ticket(const Passenger& passenger, shared_ptr<Trip> trip, shared_ptr<Seat> seat, double price) : 
         passenger(passenger), trip(trip), seat(seat), price(price) {}
  void print() const {
    cout << "=== Ticket Info ===\n";
    cout << "Passenger: " << passenger.getName() << endl;
    cout << "Trip ID: " << trip->getTripId() << endl;
    cout << "Train No: " << trip->getTrain()->getTrainNo() << endl;
    cout << "From: " << trip->getFrom() << endl;
    cout << "To: " << trip->getTo() << endl;
    cout << "Date: " << trip->getDate() << endl;
    cout << "Seat ID: " << seat->getSeatId() << endl;
    cout << "Price: " << price << endl;
  }
  shared_ptr<Seat> getSeat() const {
    return seat;
  }
};

class TicketFactory {
public:
  static shared_ptr<Ticket> creatTicket(const Passenger& passenger, shared_ptr<Trip> trip, 
                                        shared_ptr<Seat> seat, double basePrice) {
    auto strategy = PricingStrategyFactory::create(passenger.getType());
    double finalPrice = strategy->calculatePrice(basePrice);
    return make_shared<Ticket>(passenger, trip, seat, finalPrice);
  }
};

class BookingSystem {
  vector<shared_ptr<Trip>> trips;
  vector<shared_ptr<Ticket>> tickets;
public:
  void addTrip(shared_ptr<Trip> trip) {
    trips.push_back(trip);
  }
  vector<shared_ptr<Trip>> searchTrips(const string& from, const string& to) const {
    vector<shared_ptr<Trip>> res;
    for (const auto& trip : trips) {
      if (trip->getFrom() == from && trip->getTo() == to) {
        res.push_back(trip);
      }
    }
    return res;
  }
  shared_ptr<Ticket> bookTicket(const Passenger& passenger, shared_ptr<Trip> trip, SeatType desiredSeatType, double basePrice) {
    for (auto& seat : trip->getTrain()->getSeats()) {
      if (!seat->isBooked() && seat->getSeatType() == desiredSeatType) {
        seat->book();
        auto ticket = TicketFactory::creatTicket(passenger, trip, seat, basePrice);
        tickets.push_back(ticket);
        return ticket;
      }
    }
    throw runtime_error("No available seat");
  }
  void cancelTicket(shared_ptr<Ticket> ticket) {
    ticket->getSeat()->cancel();
  }
};

int main(int argc, char** argv) {
  auto train = make_shared<Train>("G123");
  train->addSeat(make_shared<Seat>(1, SeatType::Business));
  train->addSeat(make_shared<Seat>(2, SeatType::FirstClass));
  train->addSeat(make_shared<Seat>(3, SeatType::SecondClass));
  train->addSeat(make_shared<Seat>(4, SeatType::SecondClass));

  auto trip = make_shared<Trip>("T001", "Taipei", "Kaohsiung", "2026-04-10", train);

  BookingSystem system;
  system.addTrip(trip);
  Passenger passenger("Alex", PassengerType::Student);

  try {
    auto ticket = system.bookTicket(passenger, trip, SeatType::SecondClass, 1000.0);
    ticket->print();

    cout << "\nCancel ticket...\n";
    system.cancelTicket(ticket);
  } catch (const exception& e) {
    cout << "Error: " << e.what() << endl;
  }
  return 0;
}
