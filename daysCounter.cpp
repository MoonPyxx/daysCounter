#include <iostream>
#include <chrono>
#include <ctime>
#include <sstream>

// namespaces
using namespace std;
using namespace std::chrono;

// function declarations
tm getInputDate();
duration<long, ratio<3600>> calculateTimeDifference(const tm& input_date);
string formatDate(const tm& input_date);

int main() {
    tm input_date = getInputDate();

    auto difference_in_hours = calculateTimeDifference(input_date);

    int days = difference_in_hours.count() / 24;

    string message = (system_clock::from_time_t(mktime(&input_date)) > system_clock::now()) 
                     ? "Days until " : "Days from ";

    cout << message << formatDate(input_date) << ": " << days << " days" << endl;

    return 0;
}

tm getInputDate() {
    int year, month, day;
    cout << "Enter a date (DD MM YYYY): ";
    cin >> day >> month >> year;

    tm input_date = {};
    input_date.tm_year = year - 1900;
    input_date.tm_mon = month - 1;
    input_date.tm_mday = day;

    return input_date;
}

duration<long, ratio<3600>> calculateTimeDifference(const tm& input_date) {
 
    tm date_copy = input_date; 

    auto entered_time = system_clock::from_time_t(mktime(&date_copy));
    auto current_time = system_clock::now();

    return (entered_time > current_time) 
           ? duration_cast<hours>(entered_time - current_time)
           : duration_cast<hours>(current_time - entered_time);
}


string formatDate(const tm& input_date) {
    stringstream date_stream;
    date_stream << put_time(&input_date, "%d-%m-%Y");
    return date_stream.str();
}
