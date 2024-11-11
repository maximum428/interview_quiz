// Adaptor

#include <iostream>

class Vehicle {
public:
  virtual ~Vehicle() {}
  virtual void start() = 0;
};

class GasVehicle: public Vehicle {
  std::string m_name;
public:
  GasVehicle(std::string name) : m_name(name) {}
  virtual ~GasVehicle() {}
  virtual void start() {
    std::cout << m_name << " is starting enginee!\n";
  }
};

class ElectricVehicle {
  std::string m_name;
public:
  ElectricVehicle(std::string name) : m_name(name) {}
  virtual ~ElectricVehicle() {}
  void startMotor() {
    std::cout << m_name << " is starting electric motor\n";
  }
};

class ElectricVehicleAdaptor : public Vehicle {
  ElectricVehicle *m_ElectircVehicle;
public:
  ElectricVehicleAdaptor(ElectricVehicle *ev) : m_ElectircVehicle(ev) {}
  virtual ~ElectricVehicleAdaptor() {}
  virtual void start() { m_ElectircVehicle->startMotor(); }
};

int main(int argc, char** argv) {
  Vehicle *gasVehicle = new GasVehicle("Mustang");
  gasVehicle->start();
  
  ElectricVehicle *electricVehicle = new ElectricVehicle("Tesla");
  Vehicle *electricVehicleAdaptor = new ElectricVehicleAdaptor(electricVehicle);
  electricVehicleAdaptor->start();
  
  delete gasVehicle;
  delete electricVehicleAdaptor;
  delete electricVehicle;
  
  return 0;
}
