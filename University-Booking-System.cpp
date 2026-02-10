#include<iostream>
#include<string>
#include<iomanip>
using namespace std;

//----------Facility class-----------
class Facilities {
private:
	int id;
	string name;
	double hourlyRate;
public:
	Facilities(int i, string n, double r) {
		id = i;
		name = n;
		hourlyRate = r;
	}
	int getId() { return id; }
	string getName() { return name; }
	double getHourlyRate() { return hourlyRate; }
	void display() {
		cout << left << setw(10) << id << setw(20) << name << setw(15) << hourlyRate << endl;
	}
};

//----------Booking class-----------
class Booking {
private:
	int bookingId;
	int facilityId;
	int start;
	int duration;
	bool approved;
	int userid;
public:
	Booking(int bid, int fid, int st, int duar, int uid) {
		bookingId = bid;
		facilityId = fid;
		start = st;
		duration = duar;
		userid = uid;
		approved = false;
	}
	int getBookingId() { return bookingId; }
	int getFacilityId() { return facilityId; }
	int getStart() { return start; }
	int getDuration() { return duration; }
	int getUserId() { return userid; }
	bool isApproved() { return approved; }
	void setapprove(bool status) { approved = status; }
	void diplay() {
		cout << left << setw(12) << "BookingID" << setw(12) << "FacilityID" << setw(10) << "Start" << setw(10) << "Duration" << setw(10) << "Approved" << endl;
		cout << left << setw(12) << bookingId << setw(12) << facilityId << setw(10) << start << setw(10) << duration << setw(10) << approved << endl;
	}
	bool operator==(const Booking& b) {
		if (facilityId == b.facilityId && start < b.start + b.duration && b.start < start + duration) {
			return true;
		}
		return false;
	}
};

//----------User class-----------
class User {
private:
	int id;
	string name;
	string emil;
	string password;
public:
	User(int i, string n, string em, string p) {
		id = i;
		name = n;
		emil = em;
		password = p;
	}
	virtual ~User() {};
	bool login(string em, string p) {
		return (emil == em && password == p);
	}
	virtual string getRole() = 0;
	virtual string showMenu() = 0;
	int getid() { return id; }
};

//----------Derived User classes-----------
class Admin : public User {
public:
	Admin(int i, string n, string em, string p) : User(i, n, em, p) {}
	string getRole() override { return "Admin"; }
	string showMenu() override {
		cout << "\n==========Admin Menu:=========" << endl;
		cout << "1.Add Facility\n2.Edit Facility\n3.Remove Facility\n4.Approve Booking\n5.View Bookings\n6.Generate Report\n7.Logout\nChoice: ";
		return " ";
	}
};

class Faculty : public User {
public:
	Faculty(int i, string n, string em, string p) : User(i, n, em, p) {}
	string getRole() override { return "Faculty"; }
	string showMenu() override {
		cout << "\n===========Faculty Menu:===========\n1.View Facility\n2.View Bookings\n3.Request Booking\n4.Cancel Booking\n5.Logout\nChoice: ";
		return " ";
	}
};

class Student : public User {
public:
	Student(int i, string n, string em, string p) : User(i, n, em, p) {}
	string getRole() override { return "Student"; }
	string showMenu() override {
		cout << "\n===========Student Menu:============\n1.View Facility\n2.View Bookings\n3.Request Booking\n4.Cancel Booking\n5.Logout\nChoice: ";
		return " ";
	}
};

//----------Booking System class-----------
class BookingSystem {
private:
	Facilities** facilities;
	Booking** bookings;
	User** users;
	int facilityCount, bookingCount, userCount;
	int maxcount = 100;
public:
	BookingSystem() {
		facilities = new Facilities * [maxcount];
		bookings = new Booking * [maxcount];
		users = new User * [maxcount];
		facilityCount = bookingCount = userCount = 0;

		// Hardcoding User Data for Login
		users[userCount++] = new Admin(1, "Admin", "admin@gmail.com", "admin123");
		users[userCount++] = new Faculty(2, "Faculty", "daood@gmail.com", "daood123");
		users[userCount++] = new Student(4, "Student", "ali@gmail.com", "ali123");

		// Adding a Sample Facility
		facilities[facilityCount++] = new Facilities(101, "CS-Lab-1", 500.0);
	}

	~BookingSystem() {
		for (int i = 0; i < facilityCount; i++) delete facilities[i];
		for (int i = 0; i < bookingCount; i++) delete bookings[i];
		for (int i = 0; i < userCount; i++) delete users[i];
		delete[] facilities; delete[] bookings; delete[] users;
	}

	User* login() {
		int role; string password, email, targetrole;
		cout << "===============================================================================\n                Welcome to University Facility Booking System\n===============================================================================\n1. Login Admin\n2. Login Faculty\n3. Login Student\n4. For Exit\nChoice: ";
		cin >> role;
		if (role == 1) targetrole = "Admin";
		else if (role == 2) targetrole = "Faculty";
		else if (role == 3) targetrole = "Student";
		else if (role == 4) exit(0);
		else return nullptr;

		cout << "Enter Email: "; cin >> email;
		cout << "Enter Password: "; cin >> password;

		for (int i = 0; i < userCount; i++) {
			if (users[i]->getRole() == targetrole && users[i]->login(email, password)) {
				cout << "\nLogin successful as " << targetrole << "!" << endl;
				return users[i];
			}
		}
		cout << "\nLogin failed! Invalid Credentials." << endl;
		return nullptr;
	}

	void viewfacilities() {
		cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(15) << "Hourly Rate" << endl;
		for (int i = 0; i < facilityCount; i++) facilities[i]->display();
	}

	void viewbooking() {
		if(bookingCount == 0) { cout << "No bookings yet." << endl; return; }
		cout << left << setw(12) << "BookingID" << setw(12) << "FacilityID" << setw(10) << "Start" << setw(10) << "Duration" << setw(10) << "Approved" << endl;
		for (int i = 0; i < bookingCount; i++)
			cout << left << setw(12) << bookings[i]->getBookingId() << setw(12) << bookings[i]->getFacilityId() << setw(10) << bookings[i]->getStart() << setw(10) << bookings[i]->getDuration() << setw(10) << bookings[i]->isApproved() << endl;
	}

	void requestBooking(int currentUserId) {
		int fid, start, duration;
		cout << "Enter Facility ID: "; cin >> fid;
		cout << "Enter Start Time: "; cin >> start;
		cout << "Enter Duration: "; cin >> duration;
		Booking* newBooking = new Booking(bookingCount + 1, fid, start, duration, currentUserId);
		bool conflict = false;
		for (int i = 0; i < bookingCount; i++) if (*bookings[i] == *newBooking) { conflict = true; break; }
		if (conflict) { cout << "Conflict detected!" << endl; delete newBooking; }
		else { bookings[bookingCount++] = newBooking; cout << "Request submitted." << endl; }
	}

	void cancelBooking(int currentUserId) {
		int bid; cout << "Enter Booking ID: "; cin >> bid;
		for (int i = 0; i < bookingCount; i++) {
			if (bookings[i]->getBookingId() == bid && bookings[i]->getUserId() == currentUserId && !bookings[i]->isApproved()) {
				delete bookings[i];
				for (int j = i; j < bookingCount - 1; j++) bookings[j] = bookings[j + 1];
				bookingCount--; cout << "Cancelled." << endl; return;
			}
		}
		cout << "Failed to cancel (Either not found or already approved)." << endl;
	}

	void Adminaction(int choice) {
		if (choice == 1) {
			int id; string name; double rate;
			cout << "Facility ID: "; cin >> id; cout << "Name: "; cin >> name; cout << "Rate: "; cin >> rate;
			facilities[facilityCount++] = new Facilities(id, name, rate);
		}
		else if (choice == 4) {
			for (int i = 0; i < bookingCount; i++) {
				if (!bookings[i]->isApproved()) {
					bookings[i]->diplay();
					char app; cout << "Approve? (y/n): "; cin >> app;
					if (app == 'y' || app == 'Y') bookings[i]->setapprove(true);
				}
			}
		}
		else if (choice == 5) viewbooking();
		else if (choice == 6) {
			double total = 0;
			for (int i = 0; i < bookingCount; i++) if (bookings[i]->isApproved()) total += 1000; // Sample calculation
			cout << "Generated Report: Total Approved Bookings = " << bookingCount << endl;
		}
	}

	void FacultyStudentAction(int choice, int currentUserId) {
		if (choice == 1) viewfacilities();
		else if (choice == 2) viewbooking();
		else if (choice == 3) requestBooking(currentUserId);
		else if (choice == 4) cancelBooking(currentUserId);
	}
};

int main() {
	BookingSystem s;
	User* currentUser = nullptr;
	while (true) {
		if (currentUser == nullptr) currentUser = s.login();
		else {
			currentUser->showMenu();
			int choice; cin >> choice;
			if (currentUser->getRole() == "Admin") {
				if (choice == 7) currentUser = nullptr;
				else s.Adminaction(choice);
			}
			else {
				if (choice == 5) currentUser = nullptr;
				else s.FacultyStudentAction(choice, currentUser->getid());
			}
		}
	}
}