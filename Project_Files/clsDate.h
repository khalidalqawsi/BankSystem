#pragma once
#pragma warning(disable : 4996)
#include <ctime>
#include <iostream>
#include "clsString.h"
using namespace std;

class clsDate
{
private:
    short _Year;
    short _Month;
    short _Day;

public:
    clsDate()
    {
        time_t t = time(0);
        tm *now = localtime(&t);
        _Year = now->tm_year + 1900;
        _Month = now->tm_mon + 1;
        _Day = now->tm_mday;
    }

    clsDate(string Date)
    {
        vector<string> vString = clsString::Split(Date, "/");
        _Day = stoi(vString[0]);
        _Month = stoi(vString[1]);
        _Year = stoi(vString[2]);
    }

    clsDate(short Day, short Month, short Year)
    {
        _Day = Day;
        _Month = Month;
        _Year = Year;
    }

    clsDate(short DayOrder, short Year)
    {
        clsDate Date = GetDateFromDayOrderInYear(DayOrder, Year);
        _Year = Date._Year;
        _Month = Date._Month;
        _Day = Date._Day;
    }

    void SetDay(short Day)
    {
        _Day = Day;
    }

    short GetDay()
    {
        return _Day;
    }

    void SetMonth(short Month)
    {
        _Month = Month;
    }
    short GetMonth()
    {
        return _Month;
    }

    void SetYear(short Year)
    {
        _Year = Year;
    }

    short GetYear()
    {
        return _Year;
    }

    
    static string GetSystemDateTimeString()
    {
        // system datetime string
        time_t t = time(0);
        tm *now = localtime(&t);

        short Day, Month, Year, Hour, Minute, Second;

        Year = now->tm_year + 1900;
        Month = now->tm_mon + 1;
        Day = now->tm_mday;
        Hour = now->tm_hour;
        Minute = now->tm_min;
        Second = now->tm_sec;

        return (to_string(Day) + "/" + to_string(Month) + "/" + to_string(Year) + " - " + to_string(Hour) + ":" + to_string(Minute) + ":" + to_string(Second));
    }


    void Print()
    {
        cout << DateToString() << endl;
    }

    static bool IsLeapYear(short Year)
    {
        return (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
    }

    bool IsLeapYear()
    {
        return IsLeapYear(_Year);
    }

    static short NumberOfDaysInAYear(short Year)
    {
        return IsLeapYear(Year) ? 366 : 365; // Fixed: leap year has 366 days
    }

    short NumberOfDaysInAYear()
    {
        return NumberOfDaysInAYear(_Year);
    }

    static short NumberOfHoursInAYear(short Year)
    {
        return NumberOfDaysInAYear(Year) * 24;
    }

    short NumberOfHoursInAYear()
    {
        return NumberOfHoursInAYear(_Year);
    }

    static int NumberOfMinutesInAYear(short Year)
    {
        return NumberOfHoursInAYear(Year) * 60;
    }

    int NumberOfMinutesInAYear()
    {
        return NumberOfMinutesInAYear(_Year);
    }

    static int NumberOfSecondsInAYear(short Year)
    {
        return NumberOfMinutesInAYear(Year) * 60;
    }

    int NumberOfSecondsInAYear()
    {
        return NumberOfSecondsInAYear(_Year); // Fixed: was calling itself
    }

    static short NumbOfDaysInMonth(short Year, short Month)
    {
        if (12 < Month || Month < 1)
        {
            return 0;
        }
        short DaysOfMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        return (Month == 2) ? (IsLeapYear(Year) ? 29 : 28) : (DaysOfMonth[Month - 1]);
    }

    short NumbOfDaysInMonth()
    {
        return NumbOfDaysInMonth(_Year, _Month);
    }

    static short NumberOfHoursInAMonth(short Month, short Year)
    {
        return NumbOfDaysInMonth(Year, Month) * 24; // Fixed: was calling itself
    }

    short NumberOfHoursInAMonth()
    {
        return NumberOfHoursInAMonth(_Month, _Year);
    }

    static int NumberOfMinutesInAMonth(short Month, short Year)
    {
        return NumberOfHoursInAMonth(Month, Year) * 60;
    }

    int NumberOfMinutesInAMonth()
    {
        return NumberOfMinutesInAMonth(_Month, _Year);
    }

    static int NumberOfSecondsInAMonth(short Month, short Year)
    {
        return NumberOfMinutesInAMonth(Month, Year) * 60;
    }

    int NumberOfSecondsInAMonth()
    {
        return NumberOfSecondsInAMonth(_Month, _Year);
    }

    static bool IsLastDayInMonth(clsDate Date)
    {
        return (Date._Day == NumbOfDaysInMonth(Date._Year, Date._Month));
    }

    bool IsLastDayInMonth()
    {
        return IsLastDayInMonth(*this);
    }

    static bool IsLastMonthInYear(clsDate Date)
    {
        return (Date._Month == 12);
    }

    static clsDate GetDateFromDayOrderInYear(short DateOrderInYear, short Year)
    {
        clsDate Date;
        short RemainingDays = DateOrderInYear;
        short MonthDays = 0;
        Date._Year = Year;
        Date._Month = 1;
        while (true)
        {
            MonthDays = NumbOfDaysInMonth(Year, Date._Month);
            if (RemainingDays > MonthDays)
            {
                RemainingDays -= MonthDays;
                Date._Month++;
            }
            else
            {
                Date._Day = RemainingDays;
                break;
            }
        }
        return Date;
    }

    static clsDate GetSystemDate()
    {
        clsDate Date;
        time_t t = time(0);
        tm *now = localtime(&t);
        Date._Year = now->tm_year + 1900;
        Date._Month = now->tm_mon + 1;
        Date._Day = now->tm_mday;
        return Date;
    }

    static string DateToString(clsDate Date)
    {
        return to_string(Date._Day) + "/" + to_string(Date._Month) + "/" + to_string(Date._Year);
    }

    string DateToString()
    {
        return DateToString(*this);
    }

    static short DayOfWeekOrder(short Day, short Month, short Year)
    {
        short a, y, m;
        a = (14 - Month) / 12;
        y = Year - a;
        m = Month + (12 * a) - 2;
        // Gregorian:
        // 0:sun, 1:Mon, 2:Tue...etc
        return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
    }

    short DayOfWeekOrder()
    {
        return DayOfWeekOrder(_Day, _Month, _Year);
    }

    static string DayShortName(short DayOfWeekOrder)
    {
        string arrDayNames[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
        return arrDayNames[DayOfWeekOrder];
    }

    static string DayShortName(short Day, short Month, short Year)
    {
        string arrDayNames[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
        return arrDayNames[DayOfWeekOrder(Day, Month, Year)];
    }

    string DayShortName()
    {
        string arrDayNames[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
        return arrDayNames[DayOfWeekOrder(_Day, _Month, _Year)];
    }

    static string MonthShortName(short MonthNumber)
    {
        string Months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
        return Months[MonthNumber - 1];
    }

    string MonthShortName()
    {
        return MonthShortName(_Month);
    }

    static bool IsValid(clsDate Date)
    {
        if (Date._Month < 1 || Date._Month > 12)
            return false;

        if (Date._Day < 1 || Date._Day > 31)
            return false;

        short DaysInMonth = NumbOfDaysInMonth(Date._Year, Date._Month);
        return Date._Day <= DaysInMonth;
    }

    bool IsValid()
    {
        return IsValid(*this);
    }

    static void PrintMonthCalendar(short Month, short Year)
    {
        int NumberofDays = NumbOfDaysInMonth(Year, Month);

        int Current = DayOfWeekOrder(1, Month, Year);

        // Print the current month name
        printf("\n  _______________%s_______________\n\n", MonthShortName(Month).c_str());
        // Print the columns
        printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n"); // Print appropriate spaces
        int i;
        for (i = 0; i < Current; i++)
            printf("     ");

        for (int j = 1; j <= NumberofDays; j++)
        {
            printf("%5d", j);
            if (++i == 7)
            {
                i = 0;
                printf("\n");
            }
        }
        printf("\n  _________________________________\n");
    }

    void PrintMonthCalendar()
    {
        PrintMonthCalendar(_Month, _Year);
    }

    static void PrintYearCalendar(short Year)
    {
        cout << "\n_____________________________________________________________\n\n";
        cout << "\t\t\t Calendar - " << Year << endl;
        for (short i = 1; i < 13; i++)
        {
            PrintMonthCalendar(i, Year);
        }
    }

    void PrintYearCalendar()
    {
        printf("\n  _________________________________\n\n");
        printf("           Calendar - %d\n", _Year);
        printf("  _________________________________\n");

        for (int i = 1; i <= 12; i++)
        {
            PrintMonthCalendar(i, _Year);
        }

        return;
    }

    static short DaysFromTheBeginingOfTheYear(short Day, short Month, short Year)
    {
        short TotalDays = 0;

        for (int i = 1; i <= Month - 1; i++)
        {
            TotalDays += NumbOfDaysInMonth(Year, i);
        }

        TotalDays += Day;

        return TotalDays;
    }

    short DaysFromTheBeginingOfTheYear()
    {
        short TotalDays = 0;

        for (int i = 1; i <= _Month - 1; i++)
        {
            TotalDays += NumbOfDaysInMonth(_Year, i);
        }

        TotalDays += _Day;

        return TotalDays;
    }

    void AddDays(short Days)
    {
        short RemainingDays = Days + DaysFromTheBeginingOfTheYear(_Day, _Month, _Year);
        short MonthDays = 0;

        _Month = 1;

        while (true)
        {
            MonthDays = NumbOfDaysInMonth(_Year, _Month);

            if (RemainingDays > MonthDays)
            {
                RemainingDays -= MonthDays;
                _Month++;

                if (_Month > 12)
                {
                    _Month = 1;
                    _Year++;
                }
            }
            else
            {
                _Day = RemainingDays;
                break;
            }
        }
    }

    static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2)
    {
        if (Date1._Year < Date2._Year)
            return true;
        if (Date1._Year == Date2._Year && Date1._Month < Date2._Month)
            return true;
        if (Date1._Year == Date2._Year && Date1._Month == Date2._Month && Date1._Day < Date2._Day)
            return true;
        return false;
    }

    bool IsDate1BeforeDate2(clsDate Date)
    {
        return IsDate1BeforeDate2(*this, Date);
    }

    static bool IsDate1EqualDate2(clsDate Date1, clsDate Date2)
    {
        return (Date1._Year == Date2._Year) ? ((Date1._Month == Date2._Month) ? ((Date1._Day == Date2._Day) ? true : false) : false) : false;
    }

    bool IsDateEqualDate2(clsDate Date2)
    {
        return IsDate1EqualDate2(*this, Date2);
    }

    static clsDate IncreaseDateByOneDay(clsDate Date)
    {
        if (IsLastDayInMonth(Date))
        {
            if (IsLastMonthInYear(Date))
            {
                Date._Year++;
                Date._Month = 1;
                Date._Day = 1;
            }
            else
            {
                Date._Month++;
                Date._Day = 1;
            }
        }
        else
        {
            Date._Day++;
        }
        return Date;
    }

    void IncreaseDateByOneDay()
    {
        *this = IncreaseDateByOneDay(*this);
    }

    static short GetDifferenceInDays(clsDate Date, clsDate SystemDate, bool IncludeEndDay = false)
    {
        short Days = 0;
        while (IsDate1BeforeDate2(Date, SystemDate))
        {
            Days++;
            Date = IncreaseDateByOneDay(Date);
        }
        return IncludeEndDay ? Days + 1 : Days;
    }

    int GetDifferenceInDays(clsDate Date2, bool IncludeEndDay = false)
    {
        return GetDifferenceInDays(*this, Date2, IncludeEndDay);
    }

    static short CalculateMyAgeInDays(clsDate DateOfBirth)
    {
        return GetDifferenceInDays(DateOfBirth, clsDate::GetSystemDate(), true);
    }

    static clsDate IncreaseDateByOneWeek(clsDate &Date)
    {
        for (int i = 1; i <= 7; i++)
        {
            Date = IncreaseDateByOneDay(Date);
        }
        return Date;
    }

    void IncreaseDateByOneWeek()
    {
        *this = IncreaseDateByOneWeek(*this); // Fixed: assign result back
    }

    static clsDate IncreaseDateByXWeeks(short Weeks, clsDate &Date)
    {
        for (short i = 1; i <= Weeks; i++)
        {
            Date = IncreaseDateByOneWeek(Date);
        }
        return Date;
    }

    void IncreaseDateByXWeeks(short Weeks)
    {
        *this = IncreaseDateByXWeeks(Weeks, *this); // Fixed: assign result back
    }

    static clsDate IncreaseDateByOneMonth(clsDate &Date)
    {
        if (Date._Month == 12)
        {
            Date._Year++;
            Date._Month = 1;
        }
        else
        {
            Date._Month++;
        }

        // last check day in date should not exceed max days in the current month
        // example if date is 31/1/2022 increasing one month should not be 31/2/2022, it should
        // be 28/2/2022
        short NumberOfDaysInCurrentMonth = NumbOfDaysInMonth(Date._Year, Date._Month);
        if (Date._Day > NumberOfDaysInCurrentMonth)
        {
            Date._Day = NumberOfDaysInCurrentMonth;
        }
        return Date;
    }

    void IncreaseDateByOneMonth()
    {
        *this = IncreaseDateByOneMonth(*this);
    }

    static clsDate IncreaseDateByXMonths(short Months, clsDate &Date)
    {
        for (short i = 1; i <= Months; i++)
        {
            Date = IncreaseDateByOneMonth(Date);
        }
        return Date;
    }

    void IncreaseDateByXMonths(short Months)
    {
        *this = IncreaseDateByXMonths(Months, *this); // Fixed: assign result back
    }

    static clsDate IncreaseDateByOneYear(clsDate &Date)
    {
        Date._Year++;
        return Date;
    }

    void IncreaseDateByOneYear()
    {
        *this = IncreaseDateByOneYear(*this); // Fixed: assign result back
    }

    static clsDate IncreaseDateByXYears(short Years, clsDate &Date)
    {
        Date._Year += Years;
        return Date;
    }

    void IncreaseDateByXYears(short Years)
    {
        *this = IncreaseDateByXYears(Years, *this); // Fixed: missing *this parameter
    }

    static clsDate IncreaseDateByOneDecade(clsDate &Date)
    {
        // Period of 10 years
        Date._Year += 10;
        return Date;
    }

    void IncreaseDateByOneDecade()
    {
        *this = IncreaseDateByOneDecade(*this); // Fixed: assign result back
    }

    static clsDate IncreaseDateByXDecades(short Decade, clsDate &Date)
    {
        Date._Year += Decade * 10;
        return Date;
    }

    void IncreaseDateByXDecades(short Decade)
    {
        *this = IncreaseDateByXDecades(Decade, *this); // Fixed: assign result back
    }

    static clsDate IncreaseDateByOneCentury(clsDate &Date)
    {
        // Period of 100 years
        Date._Year += 100;
        return Date;
    }

    void IncreaseDateByOneCentury()
    {
        *this = IncreaseDateByOneCentury(*this); // Fixed: assign result back
    }

    static clsDate IncreaseDateByOneMillennium(clsDate &Date)
    {
        // Period of 1000 years
        Date._Year += 1000;
        return Date;
    }

    void IncreaseDateByOneMillennium()
    {
        *this = IncreaseDateByOneMillennium(*this); // Fixed: missing return and assignment
    }

    static clsDate DecreaseDateByOneDay(clsDate Date)
    {
        if (Date._Day == 1)
        {
            if (Date._Month == 1)
            {
                Date._Month = 12;
                Date._Day = 31;
                Date._Year--;
            }
            else
            {
                Date._Month--;
                Date._Day = NumbOfDaysInMonth(Date._Year, Date._Month); // Fixed: was using wrong function
            }
        }
        else
        {
            Date._Day--;
        }

        return Date;
    }

    void DecreaseDateByOneDay()
    {
        *this = DecreaseDateByOneDay(*this); // Fixed: assign result back
    }

    static clsDate DecreaseDateByOneWeek(clsDate &Date)
    {
        for (int i = 1; i <= 7; i++)
        {
            Date = DecreaseDateByOneDay(Date);
        }
        return Date;
    }

    void DecreaseDateByOneWeek()
    {
        *this = DecreaseDateByOneWeek(*this); // Fixed: assign result back
    }

    static clsDate DecreaseDateByXWeeks(short Weeks, clsDate &Date)
    {
        for (short i = 1; i <= Weeks; i++)
        {
            Date = DecreaseDateByOneWeek(Date);
        }
        return Date;
    }

    void DecreaseDateByXWeeks(short Weeks)
    {
        *this = DecreaseDateByXWeeks(Weeks, *this); // Fixed: assign result back
    }

    static clsDate DecreaseDateByOneMonth(clsDate &Date)
    {
        if (Date._Month == 1)
        {
            Date._Month = 12;
            Date._Year--;
        }
        else
            Date._Month--;

        // last check day in date should not exceed max days in the current month
        // example if date is 31/3/2022 decreasing one month should not be 31/2/2022, it should
        // be 28/2/2022
        short NumberOfDaysInCurrentMonth = NumbOfDaysInMonth(Date._Year, Date._Month);
        if (Date._Day > NumberOfDaysInCurrentMonth)
        {
            Date._Day = NumberOfDaysInCurrentMonth;
        }

        return Date;
    }

    void DecreaseDateByOneMonth()
    {
        *this = DecreaseDateByOneMonth(*this); // Fixed: assign result back
    }

    static clsDate DecreaseDateByXDays(short Days, clsDate &Date)
    {
        for (short i = 1; i <= Days; i++)
        {
            Date = DecreaseDateByOneDay(Date);
        }
        return Date;
    }

    void DecreaseDateByXDays(short Days)
    {
        *this = DecreaseDateByXDays(Days, *this); // Fixed: assign result back
    }

    static clsDate DecreaseDateByXMonths(short Months, clsDate &Date)
    {
        for (short i = 1; i <= Months; i++)
        {
            Date = DecreaseDateByOneMonth(Date);
        }
        return Date;
    }

    void DecreaseDateByXMonths(short Months)
    {
        *this = DecreaseDateByXMonths(Months, *this); // Fixed: assign result back
    }

    static clsDate DecreaseDateByOneYear(clsDate &Date)
    {
        Date._Year--;
        return Date;
    }

    void DecreaseDateByOneYear()
    {
        *this = DecreaseDateByOneYear(*this); // Fixed: assign result back
    }

    static clsDate DecreaseDateByXYears(short Years, clsDate &Date)
    {
        Date._Year -= Years;
        return Date;
    }

    void DecreaseDateByXYears(short Years)
    {
        *this = DecreaseDateByXYears(Years, *this); // Fixed: assign result back
    }

    static clsDate DecreaseDateByOneDecade(clsDate &Date)
    {
        // Period of 10 years
        Date._Year -= 10;
        return Date;
    }

    void DecreaseDateByOneDecade()
    {
        *this = DecreaseDateByOneDecade(*this); // Fixed: assign result back
    }

    static clsDate DecreaseDateByXDecades(short Decades, clsDate &Date)
    {
        Date._Year -= Decades * 10;
        return Date;
    }

    void DecreaseDateByXDecades(short Decades)
    {
        *this = DecreaseDateByXDecades(Decades, *this); // Fixed: assign result back
    }

    static clsDate DecreaseDateByOneCentury(clsDate &Date)
    {
        // Period of 100 years
        Date._Year -= 100;
        return Date;
    }

    void DecreaseDateByOneCentury()
    {
        *this = DecreaseDateByOneCentury(*this); // Fixed: assign result back
    }

    static clsDate DecreaseDateByOneMillennium(clsDate &Date)
    {
        // Period of 1000 years
        Date._Year -= 1000;
        return Date;
    }

    void DecreaseDateByOneMillennium()
    {
        *this = DecreaseDateByOneMillennium(*this); // Fixed: assign result back
    }

    static short IsEndOfWeek(clsDate Date)
    {
        return DayOfWeekOrder(Date._Day, Date._Month, Date._Year) == 6;
    }

    short IsEndOfWeek()
    {
        return IsEndOfWeek(*this);
    }

    static bool IsWeekEnd(clsDate Date)
    {
        // Weekends are Fri and Sat
        short DayIndex = DayOfWeekOrder(Date._Day, Date._Month, Date._Year);
        return (DayIndex == 5 || DayIndex == 6);
    }

    bool IsWeekEnd()
    {
        return IsWeekEnd(*this);
    }

    static bool IsBusinessDay(clsDate Date)
    {
        // Weekends are Sun,Mon,Tue,Wed and Thur

        /*
         short DayIndex = DayOfWeekOrder(Date._Day, Date._Month, Date._Year);
         return  (DayIndex >= 5 && DayIndex <= 4);
        */

        // shorter method is to invert the IsWeekEnd: this will save updating code.
        return !IsWeekEnd(Date);
    }

    bool IsBusinessDay()
    {
        return IsBusinessDay(*this);
    }

    static short DaysUntilTheEndOfWeek(clsDate Date)
    {
        return 6 - DayOfWeekOrder(Date._Day, Date._Month, Date._Year);
    }

    short DaysUntilTheEndOfWeek()
    {
        return DaysUntilTheEndOfWeek(*this);
    }

    static short DaysUntilTheEndOfMonth(clsDate Date1)
    {
        clsDate EndOfMontDate;
        EndOfMontDate._Day = NumbOfDaysInMonth(Date1._Year, Date1._Month);
        EndOfMontDate._Month = Date1._Month;
        EndOfMontDate._Year = Date1._Year;

        return GetDifferenceInDays(Date1, EndOfMontDate, true);
    }

    short DaysUntilTheEndOfMonth()
    {
        return DaysUntilTheEndOfMonth(*this);
    }

    static short DaysUntilTheEndOfYear(clsDate Date1)
    {
        clsDate EndOfYearDate;
        EndOfYearDate._Day = 31;
        EndOfYearDate._Month = 12;
        EndOfYearDate._Year = Date1._Year;

        return GetDifferenceInDays(Date1, EndOfYearDate, true);
    }

    short DaysUntilTheEndOfYear()
    {
        return DaysUntilTheEndOfYear(*this);
    }

    // i added this method to calculate business days between 2 days
    static short CalculateBusinessDays(clsDate DateFrom, clsDate DateTo)
    {
        short Days = 0;
        while (IsDate1BeforeDate2(DateFrom, DateTo))
        {
            if (IsBusinessDay(DateFrom))
                Days++;

            DateFrom = IncreaseDateByOneDay(DateFrom);
        }

        return Days;
    }

    static short CalculateVacationDays(clsDate DateFrom, clsDate DateTo)
    {
        /*short Days = 0;
        while (IsDate1BeforeDate2(DateFrom, DateTo))
        {
            if (IsBusinessDay(DateFrom))
                Days++;

            DateFrom = AddOneDay(DateFrom);
        }*/

        return CalculateBusinessDays(DateFrom, DateTo);
    }
    // above method is eough , no need to have method for the object

    static clsDate CalculateVacationReturnDate(clsDate DateFrom, short VacationDays)
    {
        short WeekEndCounter = 0;

        for (short i = 1; i <= VacationDays; i++)
        {
            if (IsWeekEnd(DateFrom))
                WeekEndCounter++;

            DateFrom = IncreaseDateByOneDay(DateFrom);
        }
        // to add weekends
        for (short i = 1; i <= WeekEndCounter; i++)
            DateFrom = IncreaseDateByOneDay(DateFrom);

        return DateFrom;
    }
    static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2)
    {
        return (!IsDate1BeforeDate2(Date1, Date2) && !IsDate1EqualDate2(Date1, Date2));
    }

    bool IsDateAfterDate2(clsDate Date2)
    {
        return IsDate1AfterDate2(*this, Date2);
    }

    enum enDateCompare
    {
        Before = -1,
        Equal = 0,
        After = 1
    };

    static enDateCompare CompareDates(clsDate Date1, clsDate Date2)
    {
        if (IsDate1BeforeDate2(Date1, Date2))
            return enDateCompare::Before;

        if (IsDate1EqualDate2(Date1, Date2))
            return enDateCompare::Equal;

        /* if (IsDate1AfterDate2(Date1,Date2))
             return enDateCompare::After;*/

        // this is faster
        return enDateCompare::After;
    }

    enDateCompare CompareDates(clsDate Date2)
    {
        return CompareDates(*this, Date2);
    }

    static void SwapDates(clsDate &Date1, clsDate &Date2)
    {

        clsDate TempDate;
        TempDate = Date1;
        Date1 = Date2;
        Date2 = TempDate;
    }
};