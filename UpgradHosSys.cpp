#include <iostream>
#include <fstream>
#include <cstdlib>
#include <conio.h>
#include <ctime>
#include <iomanip>
#include <vector>
using namespace std;

// Base class: Person
class Person {
protected:
    string name;
    int age;
    string gender;
    string contact;

public:
    Person(string n = "", int a = 0, string g = "", string c = "") : name(n), age(a), gender(g), contact(c) {}

    // Display basic info (polymorphism)
    virtual void displayInfo() const {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Gender: " << gender << endl;
        cout << "Contact: " << contact << endl;
    }

    virtual ~Person() {}
};

// Patient class (inherits from Person)
class Patient : public Person {
private:
    int pidc=0;
    string patientID;
    string bloodGroup;
    string pastDiseases;
    string roomType;
    vector<string> symptoms;
    vector<string> diagnosis;
    vector<string> medicines;

public:
    Patient(string n, int a, string g, string c, string bg, string pd)
        : Person(n, a, g, c), bloodGroup(bg), pastDiseases(pd) {
        patientID = generatePatientID();
    }

    // Generate unique patient ID
    string generatePatientID() {
       
        int id = ++pidc;
        return "P" + to_string(id);
    }

    // Record symptoms, diagnosis, and medicines
    void addDiagnosis(string sym, string diag, string med) {
        symptoms.push_back(sym);
        diagnosis.push_back(diag);
        medicines.push_back(med);
    }

    void setRoom(string room) {
        roomType = room;
    }

    void displayInfo() const override {
        Person::displayInfo();
        cout << "Patient ID: " << patientID << endl;
        cout << "Blood Group: " << bloodGroup << endl;
        cout << "Past Diseases: " << pastDiseases << endl;
        cout << "Room Type: " << roomType << endl;
        cout << "Diagnosis Info:\n";
        for (size_t i = 0; i < symptoms.size(); ++i) {
            cout << "Symptom: " << symptoms[i] << ", Diagnosis: " << diagnosis[i] << ", Medicine: " << medicines[i] << endl;
        }
    }

    string getPatientID() const {
        return patientID;
    }
};

// Doctor class (inherits from Person)
class Doctor : public Person {
private:
    int dIDCounter=0;
    string specialty;
    string doctorID;

public:
    Doctor(string n, int a, string g, string c, string s) : Person(n, a, g, c), specialty(s) {
        doctorID = generateDoctorID();
    }

    // Generate unique doctor ID
    string generateDoctorID() {        
        int id = ++dIDCounter;
        return "D" + to_string(id);
    }

    void displayInfo() const override {
        Person::displayInfo();
        cout << "Doctor ID: " << doctorID << endl;
        cout << "Specialty: " << specialty << endl;
    }

    string getDoctorID() const {
        return doctorID;
    }
};

// Appointment class
class Appointment {
private:
    string patientID;
    string doctorID;
    string appointmentDate;
    string appointmentTime;

public:
    Appointment(string pid, string did, string date, string time)
        : patientID(pid), doctorID(did), appointmentDate(date), appointmentTime(time) {}

    void displayAppointment() const {
        cout << "Appointment Details:\n";
        cout << "Patient ID: " << patientID << endl;
        cout << "Doctor ID: " << doctorID << endl;
        cout << "Date: " << appointmentDate << endl;
        cout << "Time: " << appointmentTime << endl;
    }

    string getDoctorID() const{
        return doctorID;
    }

    string getPatientID() const{
        return patientID;
    }
    string getAppointmentDate() const {
        return appointmentDate;
    }
    string getAppointmentTime()const{
        return appointmentTime;
    }
};

// Hospital Management System class
class HospitalManagement {
private:
    vector<Patient> patients;
    vector<Doctor> doctors;
    vector<Appointment> appointments;

    bool isValidPatientID(const string& patientID, const vector<Patient>& patients) {
    for (const auto& patient : patients) {
        if (patient.getPatientID() == patientID) {
            return true;  // Patient ID exists
        }
    }
    return false;  // Patient ID not found
    }

bool isValidDoctorID(const string& doctorID, const vector<Doctor>& doctors) {
    // Assuming you have a list/vector of valid doctor IDs
    for (const auto& id : doctors) {
        if (id.getDoctorID() == doctorID) {
            return true;  // Doctor ID exists
        }
    }
    return false;  // Doctor ID not found
    }

bool isValidDate(const string& date) {
    // Simple check for date format dd/mm/yyyy
    if (date.length() != 10 || date[2] != '/' || date[5] != '/') {
        return false;
    }

    int day = stoi(date.substr(0, 2));
    int month = stoi(date.substr(3, 2));
    int year = stoi(date.substr(6, 4));

    if (day < 1 || day > 31 || month < 1 || month > 12 || year < 2024) {
        return false;
    }
    // Optionally add more checks for valid days per month and leap years
    return true;
}

bool isValidTime(const string& time) {
    // Simple check for time format hh:mm
    if (time.length() != 5 || time[2] != ':') {
        return false;
    }

    int hours = stoi(time.substr(0, 2));
    int minutes = stoi(time.substr(3, 2));

    if (hours < 0 || hours > 23 || minutes < 0 || minutes > 59) {
        return false;
    }
    return true;
}

bool isDoctorAvailable(const string& doctorID, const string& date, const string& time, const vector<Appointment>& appointments) {
    for (const auto& appointment : appointments) {
        if (appointment.getDoctorID() == doctorID && appointment.getAppointmentDate() == date && 
            appointment.getAppointmentTime() == time) {
            return false;  // Doctor is busy at the given time
        }
    }
    return true;  // Doctor is available
}


public:
    void addPatient() {
        string name, gender, contact, bloodGroup, pastDiseases;
        int age;
        cout << "Enter Patient Details:\n";
        cout << "Name: "; cin >> name;
        cout << "Age: "; cin >> age;
        cout << "Gender: "; cin >> gender;
        cout << "Contact: "; cin >> contact;
        cout << "Blood Group: "; cin >> bloodGroup;
        cout << "Past Diseases: "; cin >> pastDiseases;

        Patient newPatient(name, age, gender, contact, bloodGroup, pastDiseases);
        patients.push_back(newPatient);
        cout << "Patient Added Successfully. Patient ID: " << newPatient.getPatientID() << endl;
    }

    void addDoctor() {
        string name, gender, contact, specialty;
        int age;
        cout << "Enter Doctor Details:\n";
        cout << "Name: "; cin >> name;
        cout << "Age: "; cin >> age;
        cout << "Gender: "; cin >> gender;
        cout << "Contact: "; cin >> contact;
        cout << "Specialty: "; cin >> specialty;

        Doctor newDoctor(name, age, gender, contact, specialty);
        doctors.push_back(newDoctor);
        cout << "Doctor Added Successfully. Doctor ID: " << newDoctor.generateDoctorID() << endl;
    }

   
   void scheduleAppointment() {
    string patientID, doctorID, date, time;

    cout << "Enter Appointment Details:\n";
    cout << "Patient ID: "; cin >> patientID;
    if (!isValidPatientID(patientID, patients)) {
        cout << "Invalid Patient ID.\n";
        return;
    }

    cout << "Doctor ID: "; cin >> doctorID;
    if (!isValidDoctorID(doctorID, doctors)) {
        cout << "Invalid Doctor ID.\n";
        return;
    }

    cout << "Appointment Date (dd/mm/yyyy): "; cin >> date;
    if (!isValidDate(date)) {
        cout << "Invalid Date format.\n";
        return;
    }

    cout << "Appointment Time (hh:mm): "; cin >> time;
    if (!isValidTime(time)) {
        cout << "Invalid Time format.\n";
        return;
    }

    if (!isDoctorAvailable(doctorID, date, time, appointments)) {
        cout << "Doctor is not available at this time.\n";
        return;
    }

    // All checks passed, schedule the appointment
    Appointment newAppointment(patientID, doctorID, date, time);
    appointments.push_back(newAppointment);
    cout << "Appointment Scheduled Successfully.\n";
}


    void showPatients() const {
        for (const auto& patient : patients) {
            patient.displayInfo();
            cout << endl;
        }
    }

    void showDoctors() const {
        for (const auto& doctor : doctors) {
            doctor.displayInfo();
            cout << endl;
        }
    }

    void showAppointments() const {
        for (const auto& appointment : appointments) {
            appointment.displayAppointment();
            cout << endl;
        }
    }
};

// Main function
int main() {
cout<<"\n\t\t\t\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
cout<<"\t\t\t\t\t@@ ________________________________________________________________________ @@\n";
cout<<"\t\t\t\t\t@@|                                           		                  |@@\n";
cout<<"\t\t\t\t\t@@|                                           		                  |@@\n";
cout<<"\t\t\t\t\t@@|                                           		                  |@@\n";
cout<<"\t\t\t\t\t@@|                                           		                  |@@\n";
cout<<"\t\t\t\t\t@@|                                           		                  |@@\n";
cout<<"\t\t\t\t\t@@|                                           		                  |@@\n";
cout<<"\t\t\t\t\t@@|                                  WELCOME TO                           |@@\n";
cout<<"\t\t\t\t\t@@|                                                                       |@@\n";
cout<<"\t\t\t\t\t@@|                           HOSPITAL MANAGEMENT SYSTEM                  |@@\n";
cout<<"\t\t\t\t\t@@|                                                                       |@@\n";
cout<<"\t\t\t\t\t@@|                                                                       |@@\n";
cout<<"\t\t\t\t\t@@|                                                                       |@@\n";
cout<<"\t\t\t\t\t@@|                                                                       |@@\n";
cout<<"\t\t\t\t\t@@|                                                                       |@@\n";
cout<<"\t\t\t\t\t@@|                                                                       |@@\n";
cout<<"\t\t\t\t\t@@|_______________________________________________________________________|@@\n";
cout<<"\t\t\t\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\n\n\n\t\t\t\t\t";

    HospitalManagement hms;
    int choice;

    do {
        cout << "\nHospital Management System\n";
        cout << "1. Add New Patient\n";
        cout << "2. Add New Doctor\n";
        cout << "3. Schedule Appointment\n";
        cout << "4. Show All Patients\n";
        cout << "5. Show All Doctors\n";
        cout << "6. Show All Appointments\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            hms.addPatient();
            break;
        case 2:
            hms.addDoctor();
            break;
        case 3:
            hms.scheduleAppointment();
            break;
        case 4:
            hms.showPatients();
            break;
        case 5:
            hms.showDoctors();
            break;
        case 6:
            hms.showAppointments();
            break;
        case 7:
            cout << "Exiting the system...\n";
            system("cls");
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 7);

    return 0;
}
