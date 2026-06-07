#pragma once
#pragma warning (disable: 4996)

#include <string>
#include "clsString.h"
#include <iostream>
#include <ctime>

using namespace std;

class clsDate
{
private:

	short _Day = 1;
	short _Month = 1;
	short _Year = 1900;

public:

	clsDate()
	{
		clsDate Date = GetSystemDate();
		_Day = Date.Day;
		_Month = Date.Month;
		_Year = Date.Year;
	}

	clsDate(string sDate)
	{
		vector <string> vDate;
		vDate = clsString::Split(sDate, "/");

		_Day = stoi(vDate[0]);
		_Month = stoi(vDate[1]);
		_Year = stoi(vDate[2]);
	}

	clsDate(short Day, short Month, short Year)
	{
		_Day = Day;
		_Month = Month;
		_Year = Year;
	}

	clsDate(short DateOrderInYear, short Year)
	{
		clsDate Date1 = GetDateFromDayOrderInYear(DateOrderInYear, Year);
		_Day = Date1.Day;
		_Month = Date1.Month;
		_Year = Date1.Year;
	}

	void SetDay(short Day) 
	{
		_Day = Day;
	}

	short GetDay() 
	{
		return _Day;
	}

	__declspec(property(get = GetDay, put = SetDay)) short Day;

	void SetMonth(short Month) 
	{
		_Month = Month;
	}

	short GetMonth() 
	{
		return _Month;
	}

	__declspec(property(get = GetMonth, put = SetMonth)) short Month;

	void SetYear(short Year) 
	{
		_Year = Year;
	}

	short GetYear() 
	{
		return _Year;
	}

	__declspec(property(get = GetYear, put = SetYear)) short Year;

	void Print()
	{
		cout << DateToString() << endl;
	}

	static clsDate GetSystemDate()
	{
		time_t t = time(0);
		tm* now = localtime(&t);

		short Day, Month, Year;

		Year = now->tm_year + 1900;
		Month = now->tm_mon + 1;
		Day = now->tm_mday;

		return clsDate(Day, Month, Year);
	}

	static string GetSystemTime()
	{
		time_t t = time(0);
		tm* now = localtime(&t);

		short Seconds, Minutes, Hours;

		Hours = now->tm_hour;
		Minutes = now->tm_min;
		Seconds = now->tm_sec;

		string SystemTime = "";
		SystemTime += to_string(Hours) + ":";
		SystemTime += to_string(Minutes) + ":";
		SystemTime += to_string(Seconds);

		return SystemTime;
	}

	static bool IsValidDate(clsDate Date)
	{
		return (Date.Month < 1 || Date.Month > 12) ? false : (Date.Day > NumberOfDaysInMonth(Date.Month, Date.Year) || Date.Day <= 0) ? false :
			(Date.Year <= 0) ? false : true;
	}

	bool IsValid()
	{
		return IsValidDate(*this);
	}

	static string DateToString(clsDate Date)
	{
		return  to_string(Date.Day) + "/" + to_string(Date.Month) + "/" + to_string(Date.Year);
	}

	string DateToString()
	{
		return  DateToString(*this);
	}

	static bool IsLeapYear(short Year)
	{
		return (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
	}

	bool IsLeapYear()
	{
		return IsLeapYear(_Year);
	}

	static short NumberOfDaysInYear(short Year)
	{
		return  IsLeapYear(Year) ? 366 : 365;
	}

	short NumberOfDaysInYear()
	{
		return  NumberOfDaysInYear(_Year);
	}

	static short NumberOfHoursInYear(short Year)
	{
		return  NumberOfDaysInYear(Year) * 24;
	}

	short NumberOfHoursInYear()
	{
		return  NumberOfHoursInYear(_Year);
	}

	static int NumberOfMinutesInYear(short Year)
	{
		return  NumberOfHoursInYear(Year) * 60;
	}

	int NumberOfMinutesInYear()
	{
		return  NumberOfMinutesInYear(_Year);
	}

	static int NumberOfSecondsInYear(short Year)
	{
		return  NumberOfMinutesInYear(Year) * 60;
	}

	int NumberOfSecondsInYear()
	{
		return  NumberOfSecondsInYear(_Year);
	}

	static short NumberOfDaysInMonth(short Month, short Year)
	{
		if (Month < 1 || Month>12)
			return  0;

		int days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

		return (Month == 2) ? (IsLeapYear(Year) ? 29 : 28) : days[Month - 1];
	}

	short NumberOfDaysInMonth()
	{
		return NumberOfDaysInMonth(_Month, _Year);
	}

	static short NumberOfHoursInMonth(short Month, short Year)
	{
		return  NumberOfDaysInMonth(Month, Year) * 24;
	}

	short NumberOfHoursInMonth()
	{
		return  NumberOfDaysInMonth(_Month, _Year) * 24;
	}

	static int NumberOfMinutesInMonth(short Month, short Year)
	{
		return  NumberOfHoursInMonth(Month, Year) * 60;
	}

	int NumberOfMinutesInMonth()
	{
		return  NumberOfHoursInMonth(_Month, _Year) * 60;
	}

	static int NumberOfSecondsInMonth(short Month, short Year)
	{
		return  NumberOfMinutesInMonth(Month, Year) * 60;
	}

	int NumberOfSecondsInMonth()
	{
		return  NumberOfMinutesInMonth(_Month, _Year) * 60;
	}

	static short DayOfWeekOrder(short Day, short Month, short Year)
	{
		short a, y, m;
		a = (14 - Month) / 12;
		y = Year - a;
		m = Month + (12 * a) - 2;
		return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
	}

	short DayOfWeekOrder()
	{
		return DayOfWeekOrder(_Day, _Month, _Year);
	}

	static string DayShortName(short DayOfWeekOrder)
	{
		string arrDayNames[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };
		return arrDayNames[DayOfWeekOrder];
	}

	static string DayShortName(short Day, short Month, short Year)
	{
		string arrDayNames[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };
		return arrDayNames[DayOfWeekOrder(Day, Month, Year)];
	}

	string DayShortName()
	{
		string arrDayNames[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };
		return arrDayNames[DayOfWeekOrder(_Day, _Month, _Year)];
	}

	static string MonthShortName(short MonthNumber)
	{
		string Months[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
		return (Months[MonthNumber - 1]);
	}

	string MonthShortName()
	{
		return MonthShortName(_Month);
	}

	static void PrintMonthCalendar(short Month, short Year)
	{
		int NumberOfDays;
		int current = DayOfWeekOrder(1, Month, Year);

		NumberOfDays = NumberOfDaysInMonth(Month, Year);

		printf("\n  _______________%s_______________\n\n", MonthShortName(Month).c_str());
		printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

		int i;

		for (i = 0; i < current; i++)
			printf("     ");

		for (int j = 1; j <= NumberOfDays; j++)
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

	static void PrintYearCalendar(int Year)
	{
		printf("\n  _________________________________\n\n");
		printf("           Calendar - %d\n", Year);
		printf("  _________________________________\n");

		for (int i = 1; i <= 12; i++)
		{
			PrintMonthCalendar(i, Year);
		}

		return;
	}

	void PrintYearCalendar()
	{
		PrintYearCalendar(_Year);
	}

	static short DaysFromBeginingOfTheYear(short Day, short Month, short Year)
	{
		short TotalDays = 0;

		for (int i = 1; i <= Month - 1; i++)
		{
			TotalDays += NumberOfDaysInMonth(i, Year);
		}

		TotalDays += Day;

		return TotalDays;
	}

	short DaysFromBeginingOfTheYear()
	{
		/*short TotalDays = 0;

		for (int i = 1; i <= _Month - 1; i++)
		{
			TotalDays += NumberOfDaysInMonth(i, _Year);
		}

		TotalDays += _Day;

		return TotalDays;*/
		
		return DaysFromBeginingOfTheYear(_Day, _Month, _Year);
		
	}

	static clsDate GetDateFromDayOrderInYear(short DateOrderInYear, short Year)
	{
		clsDate Date;
		short RemainingDays = DateOrderInYear;
		short MonthDays = 0;

		Date.Year = Year;
		Date.Month = 1;

		while (true)
		{
			MonthDays = NumberOfDaysInMonth(Date.Month, Year);

			if (RemainingDays > MonthDays)
			{
				RemainingDays -= MonthDays;
				Date.Month++;
			}
			else
			{
				Date.Day = RemainingDays;
				break;
			}

		}

		return Date;
	}

	void AddDays(short Days)
	{
		short RemainingDays = Days + DaysFromBeginingOfTheYear(_Day, _Month, _Year);
		short MonthDays = 0;

		_Month = 1;

		while (true)
		{
			MonthDays = NumberOfDaysInMonth(_Month, _Year);

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
		return  (Date1.Year < Date2.Year) ? true : ((Date1.Year == Date2.Year) ? (Date1.Month < Date2.Month ? true : (Date1.Month == Date2.Month ? Date1.Day < Date2.Day : false)) : false);
	}

	bool IsDateBeforeDate2(clsDate Date2)
	{
		return  IsDate1BeforeDate2(*this, Date2);
	}

	static bool IsDate1EqualDate2(clsDate Date1, clsDate Date2)
	{
		return  (Date1.Year == Date2.Year) ? ((Date1.Month == Date2.Month) ? ((Date1.Day == Date2.Day) ? true : false) : false) : false;
	}

	bool IsDateEqualDate2(clsDate Date2)
	{
		return  IsDate1EqualDate2(*this, Date2);
	}

	static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2)
	{
		return (!IsDate1EqualDate2(Date1, Date2) && !IsDate1BeforeDate2(Date1, Date2));
	}

	bool IsDateAfterDate2(clsDate Date2)
	{
		return IsDate1BeforeDate2(*this, Date2);
	}

	enum enDatesComparison { Before = -1, Equal = 0, After = 1 };

	static enDatesComparison CompareDates(clsDate Date1, clsDate Date2)
	{
		return (IsDate1BeforeDate2(Date1, Date2) ? Before : IsDate1EqualDate2(Date1, Date2) ? Equal : After);
	}

	enDatesComparison CompareDates(clsDate Date2)
	{
		return CompareDates(*this, Date2);
	}

	static bool IsLastDayInMonth(clsDate Date)
	{
		return (Date.Day == NumberOfDaysInMonth(Date.Month, Date.Year));
	}

	bool IsLastDayInMonth()
	{
		return IsLastDayInMonth(*this);
	}

	static bool IsLastMonthInYear(short Month)
	{
		return (Month == 12);
	}

	static clsDate AddOneDay(clsDate Date)
	{
		if (IsLastDayInMonth(Date))
		{
			if (IsLastMonthInYear(Date.Month))
			{
				Date.Month = 1;
				Date.Day = 1;
				Date.Year++;
			}
			else
			{
				Date.Day = 1;
				Date.Month++;
			}
		}
		else
		{
			Date.Day++;
		}

		return Date;
	}

	void AddOneDay()
	{
		*this = AddOneDay(*this);
	}

	static void  SwapDates(clsDate& Date1, clsDate& Date2)
	{
		clsDate TempDate;
		TempDate = Date1;
		Date1 = Date2;
		Date2 = TempDate;
	}

	static int GetDifferenceInDays(clsDate Date1, clsDate Date2, bool IncludeEndDay = false)
	{
		int Days = 0;
		short SawpFlagValue = 1;

		if (!IsDate1BeforeDate2(Date1, Date2))
		{
			SwapDates(Date1, Date2);
			SawpFlagValue = -1;
		}

		while (IsDate1BeforeDate2(Date1, Date2))
		{
			Days++;
			Date1 = AddOneDay(Date1);
		}

		return IncludeEndDay ? ++Days * SawpFlagValue : Days * SawpFlagValue;
	}

	int GetDifferenceInDays(clsDate Date2, bool IncludeEndDay = false)
	{
		return GetDifferenceInDays(*this, Date2, IncludeEndDay);
	}

	static short CalculateMyAgeInDays(clsDate DateOfBirth)
	{
		return GetDifferenceInDays(DateOfBirth, clsDate::GetSystemDate(), true);
	}

	static clsDate IncreaseDateByOneWeek(clsDate& Date)
	{
		for (int i = 1; i <= 7; i++)
		{
			Date = AddOneDay(Date);
		}

		return Date;
	}

	void IncreaseDateByOneWeek()
	{
		*this = IncreaseDateByOneWeek(*this);
	}

	static clsDate IncreaseDateByXWeeks(short Weeks, clsDate& Date)
	{
		for (short i = 1; i <= Weeks; i++)
		{
			Date = IncreaseDateByOneWeek(Date);
		}
		return Date;
	}

	void IncreaseDateByXWeeks(short Weeks)
	{
		*this = IncreaseDateByXWeeks(Weeks, *this);
	}

	static clsDate IncreaseDateByOneMonth(clsDate& Date)
	{
		if (IsLastMonthInYear(Date.Month))
		{
			Date.Year++;
			Date.Month = 1;
			return Date;
		}

		Date.Month++;
		int NumberOfDaysInCurrentMonth = NumberOfDaysInMonth(Date.Month, Date.Year);
		if (Date.Day > NumberOfDaysInCurrentMonth)
		{
			Date.Day = NumberOfDaysInCurrentMonth;
		}
		return Date;
	}

	void IncreaseDateByOneMonth()
	{
		*this = IncreaseDateByOneMonth(*this);
	}

	static clsDate IncreaseDateByXDays(short Days, clsDate& Date)
	{
		for (short i = 1; i <= Days; i++)
		{
			Date = AddOneDay(Date);
		}

		return Date;
	}

	void IncreaseDateByXDays(short Days)
	{
		*this = IncreaseDateByXDays(Days, *this);
	}

	static clsDate IncreaseDateByXMonths(short Months, clsDate& Date)
	{
		for (short i = 1; i <= Months; i++)
		{
			Date = IncreaseDateByOneMonth(Date);
		}

		return Date;
	}

	void IncreaseDateByXMonths(short Months)
	{
		*this = IncreaseDateByXMonths(Months, *this);
	}

	static clsDate IncreaseDateByOneYear(clsDate& Date)
	{
		Date.Day = (Date.Day == NumberOfDaysInMonth(2, Date.Year)) ?
			NumberOfDaysInMonth(2, Date.Year + 1) : Date.Day;

		Date.Year++;
		return Date;
	}

	void IncreaseDateByOneYear()
	{
		*this = IncreaseDateByOneYear(*this);
	}

	static clsDate IncreaseDateByXYears(short Years, clsDate& Date)
	{
		Date.Day = (Date.Day == NumberOfDaysInMonth(2, Date.Year) && IsLeapYear(Date.Year)) ?
			NumberOfDaysInMonth(2, Date.Year + Years) : Date.Day;

		return Date;
	}

	void IncreaseDateByXYears(short Years)
	{
		*this = IncreaseDateByXYears(Years, *this);
	}

	static clsDate IncreaseDateByOneDecade(clsDate& Date)
	{
		return IncreaseDateByXYears(10, Date);
	}

	void IncreaseDateByOneDecade()
	{
		*this = IncreaseDateByOneDecade(*this);
	}

	static clsDate IncreaseDateByXDecades(short Decades, clsDate& Date)
	{
		return IncreaseDateByXYears(10 * Decades, Date);
	}

	void IncreaseDateByXDecades(short Decades)
	{
		*this = IncreaseDateByXDecades(Decades, *this);
	}

	static clsDate IncreaseDateByOneCentury(clsDate& Date)
	{
		return IncreaseDateByXDecades(10, Date);
	}

	void IncreaseDateByOneCentury()
	{
		*this = IncreaseDateByOneCentury(*this);
	}

	static clsDate IncreaseDateByOneMillennium(clsDate& Date)
	{
		for (short i = 0; i < 10; i++)
		{
			Date = IncreaseDateByOneCentury(Date);
		}
		return Date;
	}

	void IncreaseDateByOneMillennium()
	{
		*this = IncreaseDateByOneMillennium(*this);
	}

	static clsDate DecreaseDateByOneDay(clsDate Date)
	{
		if (Date.Day == 1)
		{
			if (Date.Month == 1)
			{
				Date.Month = 12;
				Date.Day = 31;
				Date.Year--;
			}
			else
			{
				Date.Month--;
				Date.Day = NumberOfDaysInMonth(Date.Month, Date.Year);
			}
		}
		else
		{
			Date.Day--;
		}

		return Date;
	}

	void DecreaseDateByOneDay()
	{
		*this = DecreaseDateByOneDay(*this);
	}

	static clsDate DecreaseDateByOneWeek(clsDate& Date)
	{
		for (int i = 1; i <= 7; i++)
		{
			Date = DecreaseDateByOneDay(Date);
		}

		return Date;
	}

	void DecreaseDateByOneWeek()
	{
		*this = DecreaseDateByOneWeek(*this);
	}

	static clsDate DecreaseDateByXWeeks(short Weeks, clsDate& Date)
	{
		for (short i = 1; i <= Weeks; i++)
		{
			Date = DecreaseDateByOneWeek(Date);
		}

		return Date;
	}

	void DecreaseDateByXWeeks(short Weeks)
	{
		*this = DecreaseDateByXWeeks(Weeks, *this);
	}

	static clsDate DecreaseDateByOneMonth(clsDate& Date)
	{
		if (Date.Month == 1)
		{
			Date.Month = 12;
			Date.Year--;
		}
		else
			Date.Month--;

		short NumberOfDaysInCurrentMonth = NumberOfDaysInMonth(Date.Month, Date.Year);

		if (Date.Day > NumberOfDaysInCurrentMonth)
		{
			Date.Day = NumberOfDaysInCurrentMonth;
		}

		return Date;
	}

	void DecreaseDateByOneMonth()
	{
		*this = DecreaseDateByOneMonth(*this);
	}

	static clsDate DecreaseDateByXDays(short Days, clsDate& Date)
	{
		for (short i = 1; i <= Days; i++)
		{
			Date = DecreaseDateByOneDay(Date);
		}

		return Date;
	}

	void DecreaseDateByXDays(short Days)
	{
		*this = DecreaseDateByXDays(Days, *this);
	}

	static clsDate DecreaseDateByXMonths(short Months, clsDate& Date)
	{
		for (short i = 1; i <= Months; i++)
		{
			Date = DecreaseDateByOneMonth(Date);
		}

		return Date;
	}

	void DecreaseDateByXMonths(short Months)
	{
		*this = DecreaseDateByXMonths(Months, *this);
	}

	static clsDate DecreaseDateByOneYear(clsDate& Date)
	{
		Date.Year--;
		return Date;
	}

	void DecreaseDateByOneYear()
	{
		*this = DecreaseDateByOneYear(*this);
	}

	static clsDate DecreaseDateByXYears(short Years, clsDate& Date)
	{
		Date.Year -= Years;
		return Date;
	}

	void DecreaseDateByXYears(short Years)
	{
		*this = DecreaseDateByXYears(Years, *this);
	}

	static clsDate DecreaseDateByOneDecade(clsDate& Date)
	{
		Date.Year -= 10;
		return Date;
	}

	void DecreaseDateByOneDecade()
	{
		*this = DecreaseDateByOneDecade(*this);
	}

	static clsDate DecreaseDateByXDecades(short Decades, clsDate& Date)
	{
		Date.Year -= Decades * 10;
		return Date;
	}

	void DecreaseDateByXDecades(short Decades)
	{
		*this = DecreaseDateByXDecades(Decades, *this);
	}

	static clsDate DecreaseDateByOneCentury(clsDate& Date)
	{
		Date.Year -= 100;
		return Date;
	}

	void DecreaseDateByOneCentury()
	{
		*this = DecreaseDateByOneCentury(*this);
	}

	static clsDate DecreaseDateByOneMillennium(clsDate& Date)
	{
		Date.Year -= 1000;
		return Date;
	}

	void DecreaseDateByOneMillennium()
	{
		*this = DecreaseDateByOneMillennium(*this);
	}

	static short IsEndOfWeek(clsDate Date)
	{
		return  DayOfWeekOrder(Date.Day, Date.Month, Date.Year) == 6;
	}

	short IsEndOfWeek()
	{
		return IsEndOfWeek(*this);
	}

	static bool IsWeekEnd(clsDate Date)
	{
		short DayIndex = DayOfWeekOrder(Date.Day, Date.Month, Date.Year);
		return  (DayIndex == 5 || DayIndex == 6);
	}

	bool IsWeekEnd()
	{
		return  IsWeekEnd(*this);
	}

	static bool IsBusinessDay(clsDate Date)
	{
		return !IsWeekEnd(Date);
	}

	bool IsBusinessDay()
	{
		return  IsBusinessDay(*this);
	}

	static short DaysUntilTheEndOfWeek(clsDate Date)
	{
		return 6 - DayOfWeekOrder(Date.Day, Date.Month, Date.Year);
	}

	short DaysUntilTheEndOfWeek()
	{
		return  DaysUntilTheEndOfWeek(*this);
	}

	static short DaysUntilTheEndOfMonth(clsDate Date1)
	{
		clsDate EndOfMontDate;
		EndOfMontDate.Day = NumberOfDaysInMonth(Date1.Month, Date1.Year);
		EndOfMontDate.Month = Date1.Month;
		EndOfMontDate.Year = Date1.Year;

		return GetDifferenceInDays(Date1, EndOfMontDate, true);
	}

	short DaysUntilTheEndOfMonth()
	{
		return DaysUntilTheEndOfMonth(*this);
	}

	static short DaysUntilTheEndOfYear(clsDate Date1)
	{
		clsDate EndOfYearDate;
		EndOfYearDate.Day = 31;
		EndOfYearDate.Month = 12;
		EndOfYearDate.Year = Date1.Year;

		return GetDifferenceInDays(Date1, EndOfYearDate, true);
	}

	short DaysUntilTheEndOfYear()
	{
		return  DaysUntilTheEndOfYear(*this);
	}

	static short CalculateBusinessDays(clsDate DateFrom, clsDate DateTo)
	{
		short Days = 0;

		while (IsDate1BeforeDate2(DateFrom, DateTo))
		{
			if (IsBusinessDay(DateFrom))
				Days++;

			DateFrom = AddOneDay(DateFrom);
		}

		return Days;
	}

	static short CalculateVacationDays(clsDate DateFrom, clsDate DateTo)
	{
		return CalculateBusinessDays(DateFrom, DateTo);
	}

	static clsDate CalculateVacationReturnDate(clsDate DateFrom, short VacationDays)
	{
		short WeekEndCounter = 0;

		for (short i = 1; i <= VacationDays; i++)
		{
			if (IsWeekEnd(DateFrom))
				WeekEndCounter++;

			DateFrom = AddOneDay(DateFrom);
		}

		for (short i = 1; i <= WeekEndCounter; i++)
			DateFrom = AddOneDay(DateFrom);

		return DateFrom;
	}

	static short ReadYear()
	{
		short Year = 0;

		cout << "Enter the year: ";
		cin >> Year;

		return Year;
	}

	static short ReadMonth()
	{
		short Month = 0;

		cout << "Enter month: ";
		cin >> Month;

		return Month;
	}

	static short ReadDay()
	{
		short Day = 0;

		cout << "Enter day: ";
		cin >> Day;

		return Day;
	}

	static clsDate ReadDate()
	{
		clsDate Date;

		Date.Day = ReadDay();
		Date.Month = ReadMonth();
		Date.Year = ReadYear();

		return Date;
	}

	static bool isLastDayInMonth(clsDate Date)
	{
		return (Date.Day == NumberOfDaysInMonth(Date.Year, Date.Month));
	}

	bool isLastDayInMonth()
	{
		return isLastDayInMonth(*this);
	}

	static bool isLastMonthInYear(short Month)
	{
		return (Month == 12);
	}

	bool isLastMonthInYear()
	{
		return isLastMonthInYear(_Month);
	}

	static int DifferenceBetweenTwoDates(clsDate Date1, clsDate Date2, bool IncludeEndDay = false)
	{
		int Days = 0;
		short SwapFlagValue = 1;

		if (!IsDate1BeforeDate2(Date1, Date2))
		{
			SwapDates(Date1, Date2);
			SwapFlagValue = -1;
		}

		while (IsDate1BeforeDate2(Date1, Date2))
		{
			Days++;
			Date1 = AddOneDay(Date1);
		}

		return (IncludeEndDay ? ++Days * SwapFlagValue : Days * SwapFlagValue);
	}

	int DifferenceBetweenTwoDates(clsDate Date, bool IncludeEndDay = false)
	{
		return DifferenceBetweenTwoDates(*this, Date, IncludeEndDay);
	}

	static string GetDateTimeString()
	{
		string DateTime = DateToString(GetSystemDate()) + " - " + GetSystemTime();
		return DateTime;
	}
};