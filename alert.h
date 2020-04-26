#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_WIDTH       80      
#define DISPLAY_DAYS    45
#define MAX_NO_REC      200
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"



char *acivity_table[] = {
/*Just Once*/
"Q1: PAN Address Change                 |01|01|2020|A",
"Q2: Soni & Dudu Passport               |01|04|2020|A",

/*Weekly Activity*/
"M: CV update                           |01|07|2020|A",

/*M: Finance*/

/*M: Activity*/
"M: Car Wash                            |01|04|2020|A",
"M: Spun Filter Wash                    |01|04|2020|A",
"M: Bed Exchange                        |01|05|2020|A",
"M: House Roof Clean                    |01|04|2020|A",
"M: Weight Measurement                  |01|05|2020|A",

/*Quarter Activity*/

"Q1: Spun Filter Change:1               |01|01|2020|D",
"Q2: Spun Filter Change:2               |01|04|2020|A",
"Q3: Spun Filter Change:3               |01|07|2020|A",
"Q4: Spun Filter Change:4               |01|10|2020|A",

"Q1: Office Jacket Wash:1               |01|01|2020|D",
"Q2: Office Jacket Wash:2               |01|04|2020|A",
"Q3: Office Jacket Wash:3               |01|07|2020|A",
"Q4: Office Jacket Wash:4               |01|10|2020|A",

"Q1: Office Bottle Wash:1               |01|01|2020|D",
"Q2: Office Bottle Wash:2               |01|04|2020|A",
"Q3: Office Bottle Wash:3               |01|07|2020|A",
"Q4: Office Bottle Wash:4               |01|10|2020|A",

"Q1: Clock Time Sync:1                  |01|01|2020|A",
"Q2: Clock Time Sync:2                  |01|04|2020|A",
"Q3: Clock Time Sync:3                  |01|07|2020|A",
"Q4: Clock Time Sync:4                  |01|10|2020|A",

"Q1: Mob Photo to Laptop Backup:1       |01|01|2020|D",
"Q2: Mob Photo to Laptop Backup:2       |01|04|2020|A",
"Q3: Mob Photo to Laptop Backup:3       |01|07|2020|A",
"Q4: Mob Photo to Laptop Backup:4       |01|10|2020|A",

"Q1: Table Cloth Wash:1                 |01|01|2020|D",
"Q2: Table Cloth Wash:2                 |01|04|2020|A",
"Q3: Table Cloth Wash:3                 |01|07|2020|A",
"Q4: Table Cloth Wash:4                 |01|10|2020|A",

/*Half yearly Activity*/
"Q2: PW Change: 1                       |01|04|2020|A",
"Q4: PW Change: 2                       |01|10|2020|A",
"Q2: Comb Clean: 1                      |01|04|2020|A",
"Q4: Comb Clean: 2                      |01|10|2020|A",
"Q2: TV Table and Book Shelf: 1         |01|04|2020|A",
"Q4: TV Table and Book Shelf: 2         |01|10|2020|A",
"Q2: Freeze & Washing Machine: 1        |01|04|2020|A",
"Q4: Freeze & Washing Machine: 2        |01|10|2020|A",
"Q2: Car Full Body Wash: 1              |01|04|2020|A",
"Q4: Car Full Body Wash: 2              |01|10|2020|A",
"Q2: Soni Thread: 1                     |01|04|2020|A",
"Q4: Soni Thread: 2                     |01|10|2020|A",
"Q2: Laptop Tab Desktop Clean: 1        |01|04|2020|A",
"Q4: Laptop Tab Desktop Clean: 2        |01|10|2020|A",
"Q2: Naphthalene balls: 1               |01|04|2020|A",
"Q4: Naphthalene balls: 2               |01|10|2020|A",
"Q2: Photo Clean: 1                     |01|04|2020|A",
"Q4: Photo Clean: 2                     |01|10|2020|A",
"Q2: Office Bag Wash: 1                 |01|04|2020|A",
"Q4: Office Bag Wash: 2                 |01|10|2020|A",
"Q1: Lingeris Purchase: 1               |01|01|2020|D",
"Q3: Lingeris Purchase: 2               |01|07|2020|A",
"Q1: Socks Purchase: 1                  |01|01|2020|D",
"Q3: Socks Purchase: 2                  |01|07|2020|A",

/*House Clean*/
"Q2: Drawing Room: 1                    |01|04|2020|A",
"Q2: Kitchen Room: 1                    |01|04|2020|A",
"Q2: Dudu Bed Room: 1                   |01|04|2020|A",
"Q2: My Bath Room: 1                    |01|04|2020|A",
"Q2: Common Bath Room: 1                |01|04|2020|A",
"Q2: My Bed Room: 1                     |01|04|2020|A",
"Q2: Blanket Wash: 1                    |01|04|2020|A",
"Q2: Curtain Wash: 1                    |01|04|2020|A",
"Q2: Mosquito Net Wash: 1               |01|04|2020|A",

/*Yearly activity*/ 
"Q1: Running Shoe Change                |01|01|2020|A",
"Q1: Office Shoe Change                 |01|01|2020|A",
"Q1: Boot Polish Brush change           |01|01|2020|D",
"Q1: Tool servicing                     |01|01|2020|A",
"Q1: Electric Unit Update               |01|01|2020|A",
"Q1: Hard & Soft broom change           |01|01|2020|A",
"Q1: Paper Sell (Feb-Apr)               |01|02|2020|A",
"Q2: House rent update in HRMS          |01|04|2020|A",
"Q1: Slipper Change                     |01|01|2020|D",
"Q1: Water Filter paper change          |01|01|2020|D",
"Q2: Mcafee Antivirus                   |01|04|2020|A",
"Q1: Magzine Subscription               |01|01|2020|D",
"Q2: Cushion Cover Wash:                |01|04|2020|A",
"Q1: NSLD Renew                         |01|01|2020|A",
"Q1: Acid clean of Bath Rooms:          |01|01|2020|D",

/*House Tax*/
"Q2: HOUSE TAX                           |01|04|2020|A",

/*Income Tax*/
"Q3: INCOME TAX RETURN FILE             |15|07|2020|A",
"Q4: IT Proof Collection: School        |15|11|2020|A",
"Q4: IT Proof Collection: Rent          |15|11|2020|A",
"Q4: IT Proof Collection: Bank          |15|11|2020|A",

/*DPS SCHOOL*/
"Q2: DPS Bus Fee:                       |01|04|2020|A",
"Q2: DPS Tuition Fee: 1                 |01|06|2020|A",
"Q3: DPS Tuition Fee: 2                 |15|11|2020|A",

/*DATA*/
"Q1: Laptop Data to HD Backup:1         |01|01|2020|D",
"Q3: Laptop Data to HD Backup:2         |01|07|2020|A",
"Q1: Config files to Laptop Backup:1    |15|01|2020|D",
"Q3: Config files to Laptop Backup:2    |15|06|2020|A",
"Q1: All Contacts to Laptop Backup:1    |01|01|2020|D",
"Q3: All Contacts to Laptop Backup:2    |01|07|2020|A",

/*Bank Card Details*/
"SBI Soni Debit card expire             |01|07|2021|A",
"ICICI my Debit card expire             |01|01|2022|A",
"SBM   my Debit card expire             |30|01|2022|A",
"ICICI my Credit card expire            |01|09|2022|A",

/*Bank FD Details*/
"Q2: Bank Intrest Statement             |01|04|2020|A",
"Q2: Form 16G submission                |01|04|2020|A",

/*HEALTH*/
"Q1: Medicine Replacement               |01|01|2021|A",
"Q1: Health Check-up: 1                 |01|01|2020|D",
"Q3: Health Check-up: 2                 |01|07|2020|A",
"Q1: Renew of Health insurance at off   |01|01|2020|A",
"Q1: Dudu vaccination on 10 year:       |01|01|2021|A",

/*CAR*/
"Q1: CAR INSURANCE RENEW                |01|01|2020|D",
"Q2: Car Full Service                   |01|04|2020|A",
"5Y: Car Fitness Check                  |01|01|2023|A",
"5Y: Car Driving Licence                |01|01|2023|A",
"5Y: Car Battery Chnage (01/01/2019)    |01|01|2021|A",
"Q1: CAR EMISSION TEST: 1               |24|03|2020|D",
"Q3: CAR EMISSION TEST: 2               |15|09|2020|A",
"Q2: Car Polishing: 1                   |01|04|2020|A",
"Q3: Car Polishing: 2                   |01|10|2020|A",
"Q2: Car Seat cover wash: 1             |01|04|2020|A",
"Q4: Car Seat cover wash: 2             |01|10|2020|A",

/*Traveling*/
"Q3: SBC-BBS TRAIN TICKET BOOK       	|01|08|2020|A",
"Q3: BBS-SBC TRAIN TICKET BOOK          |01|09|2020|A",
"Q3: AIR TICKET                         |15|07|2020|A",

/*Two Year*/
"Y2: Car Cover Change                   |01|01|2021|A",
"Y2: Umbrella Change                    |01|01|2021|A",
"Y2: Office Bag Change                  |01|01|2021|A",
"Y2: Pressure Cooker Rim Change         |01|01|2021|A",
"Y2: Toilet Brush Change                |01|01|2021|A",
"Y2: Dudu Cycle Tyre Change             |01|01|2021|A",
"Y2: Emergency Light Bar Change         |01|01|2021|A",

/*Three Year*/
"Y2: Bus Pass Identity Card             |01|01|2022|A",
"Y2: Gas Stove Servicing                |01|01|2022|A",
"Y2: Gas Pipe Change                    |01|01|2022|A",
"Y2: Pressure Cooker Rim Change         |01|01|2022|A",
"Y2: Web Brush Change                   |01|01|2020|A",
"Y2: Mop Cloth Change                   |01|01|2022|A",

/*Birthday and Anniversary*/
"B: Jayesh Birthday                     |12|02|2020|D",
"B: Soni Birthday                       |23|03|2020|A",
"B: My Birthday                         |06|10|2020|A",
"Marriage Anniversary                   |13|12|2020|A",
"Bapa Death Anniversary                 |04|02|2021|D",
"Maa Death Anniversary                  |08|01|2021|A",
"Bapa Death Anniversary(Tithi)          |12|02|2020|D",
"Maa Death Anniversary (Tithi)          |08|01|2020|D",

/*Holidays*/
"H: Ugadhi                              |25|03|2020|H",
"H: Good Friday                         |10|04|2020|H",
"H: May Day	                       	    |01|05|2020|H",
"H: Ramzan                       	    |25|05|2020|H",
"H: JanamaShatami                       |11|08|2020|H",
"H: Gandhi Jayanthi                     |02|10|2020|H",
"H: Dussehra                            |26|10|2020|H",
"H: Deepavali                           |16|11|2020|H",
"H: Christmas Day                       |25|12|2020|H",
NULL
};

