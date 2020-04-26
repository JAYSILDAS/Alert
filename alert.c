#include "alert.h"
//#include "dress.h"

struct Date { int dd, mm, yy; };
char *active_list[MAX_NO_REC];
char *holiday_list[MAX_NO_REC];
int cmpstring(const void *p1, const void *p2);
int month_days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
//char day_name[7][10]= {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
char day_name[7][4]= {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

int main () 
{
	time_t t; 
	struct tm* tm_info; 
	int days_diff, i, j, k;
	char buff[MAX_WIDTH], flag;
	struct Date input_date, curr_date;	
	char day[3], month[3], year[5];


	time(&t); 
	tm_info = localtime(&t);
	i = 0, j = 0, k=0;

	curr_date.dd = tm_info->tm_mday;
	curr_date.mm = tm_info->tm_mon + 1;
	curr_date.yy = tm_info->tm_year + 1900;

	for (i=0; acivity_table[i]; i++) 
	{
		sscanf (acivity_table[i],"%[^'|']|%d|%d|%d|%c", buff, &input_date.dd, &input_date.mm, &input_date.yy, &flag); 
		//printf ("printing int:[%s][%d][%d][%d][%c]\n", buff, input_date.dd, input_date.mm, input_date.yy,flag);

		if (flag == 'D')                /*Disable record will skip*/
		{
			continue;
		}
		if (flag == 'A' || flag == 'H')  /* Only for active and holiday record*/
		{
			sscanf (acivity_table[i],"%[^'|']|%[^'|']|%[^'|']|%[^'|']|%c", buff, day, month, year, &flag); 
			//printf ("printing char:[%s][%s][%s][%s][%c]\n", buff, day, month, year,flag);

			days_diff = days_between_dates (curr_date, input_date);

			if ((flag == 'A') && (days_diff <= DISPLAY_DAYS)) 
			{
				active_list[j] = (char *)malloc(MAX_WIDTH);
				sprintf (active_list[j],"%-30s|%2s-%2s-%4s|%4d", buff, day, month, year, days_diff); 
				//printf ("[%s]\n", active_list[j]);
				j++;
			}
			if ((flag == 'H') && (days_diff > 0))
			{
				holiday_list[k] = (char *)malloc(MAX_WIDTH);
				//sprintf (holiday_list[k],"%-30s|%2s-%2s-%4s|%4d", buff, day, month, year, days_diff); 
				buff[28]= '\0';
				sprintf (holiday_list[k],"%-35s|%-3s|%2s-%2s-%4s|%4d", buff, day_name[dayofweek(day, month, year)], day, month, year, days_diff); 
				//printf ("[%s]\n", holiday_list[k]);
				k++;
			}
		}
	}
	qsort (active_list,  j--, sizeof(char *), cmpstring);
	qsort (holiday_list, k--, sizeof(char *), cmpstring);

	printf (ANSI_COLOR_YELLOW);
	printf ("\n");
	printf ("--------------------------------------------------------------\n");
	printf ("                        -- REMINDER --                        \n");
	printf ("--------------------------------------------------------------\n");
	printf (" SL                   ITEMS                  DUE DATE  NO.DAYS\n");
	printf ("--------------------------------------------------------------\n");
	display (active_list, j);

	printf ("--------------------------------------------------------------\n");
	printf ("                        -- HOLIDAYS --                        \n");
	printf ("--------------------------------------------------------------\n");
	printf (ANSI_COLOR_YELLOW);
	display (holiday_list, k);

	printf ("--------------------------------------------------------------\n");
	printf ("Generated on:Dt %d-%d-%d.\n", tm_info->tm_mday, tm_info->tm_mon + 1, tm_info->tm_year + 1900);
	printf (ANSI_COLOR_RESET);	
}

display (char *list[], int total_row)
{
	int row_no = 0;
	while (total_row >= 0)
	{
		printf ("|%2d| %s |\n", ++row_no, list[total_row]);
		free(list[total_row]);
		total_row--;
	}
}

int cmpstring(const void *p1, const void *p2)
{
	int num1, num2;
	int day, month, year;
	char buff[MAX_WIDTH];

	sscanf (* (char * const *) p1,"%[^'|']|%d-%d-%d|%d", buff, &day, &month, &year, &num1); 
	sscanf (* (char * const *) p2,"%[^'|']|%d-%d-%d|%d", buff, &day, &month, &year, &num2); 
	//printf ("printing :[%s][%d][%d][%d]\n", buff, day, month, year);
	//printf (".....[%d] [%d]\n", num1, num2);
	if (num1 <  num2)
		return 1;
	else 
		return -1;
}

int countLeapYears(struct Date d)
{
	int years = d.yy;

	// Check if the current year needs to be considered
	// for the count of leap years or not
	if (d.mm <= 2)
		years--;

	// An year is a leap year if it is a multiple of 4,
	// multiple of 400 and not a multiple of 100.
	return years / 4 - years / 100 + years / 400;
}

int days_between_dates(struct Date dt1, struct Date dt2)
{
	int i;
	// COUNT TOTAL NUMBER OF DAYS BEFORE FIRST DATE 'dt1'

	// initialize count using years and day
	long int n1 = dt1.yy*365 + dt1.dd;

	// Add days for months in given date
	for (i=0; i<dt1.mm - 1; i++)
		n1 += month_days[i];

	// Since every leap year is of 366 days,
	// Add a day for every leap year
	n1 += countLeapYears(dt1);

	// SIMILARLY, COUNT TOTAL NUMBER OF DAYS BEFORE 'dt2'

	long int n2 = dt2.yy * 365 + dt2.dd;
	for (i=0; i<dt2.mm - 1; i++)
		n2 += month_days[i];
	n2 += countLeapYears(dt2);

	// return difference between two counts
	return (n2 - n1);
}
int dayofweek(char *dd, char *mm, char *yy)
{
	int d = atoi(dd);
	int m = atoi(mm);
	int y = atoi(yy);
	static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
	y -= m < 3;
	return ( y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
}
