//******************************//
//				//
//	travel.c		//
//	Matt Rundle		//
//	cse20211.01		//
//				//
//******************************//

#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Create struct for flight	
struct f{
	int flight_num;
	char orig_port[4]; // original airport
	char dest_port[4];  // destination airport
	int depart_time_min,depart_time_hour; // departing time, minutes and hours
	int arrive_time_min,arrive_time_hour; // arriving time, minutes and hours
	int cost;
};

void import_flights(struct f *flight)
{
	// Open file flights.txt
	FILE *fp=fopen("flights.txt","r");
	char orig_port[4],dest_port[4];
	int depart_time_min,depart_time_hour,arrive_time_min,arrive_time_hour,cost;
	char buf[100];
	int i=0;
	int j;
	// Scan in the flight information
	while((fgets(buf,sizeof(buf),fp))!=NULL){
		sscanf(buf,"%s %s %d:%d %d:%d $%d",orig_port,dest_port,&depart_time_hour,&depart_time_min,&arrive_time_hour,&arrive_time_min,&cost);
		// Copy this information to a flight struct
		strcpy(flight[i].orig_port,orig_port);
		strcpy(flight[i].dest_port,dest_port);
		flight[i].depart_time_hour=depart_time_hour;
		flight[i].depart_time_min=depart_time_min;
		flight[i].arrive_time_hour=arrive_time_hour;
		flight[i].arrive_time_min=arrive_time_min;
		flight[i].cost=cost;
		// increment i to move to the next line
		i++;
	}
	fclose(fp);
}

// Print a flight to the screen
void print_flight(struct f *flight,int i)
{
printf("\n  %02d           %s         %s           %02d:%02d             %02d:%02d        $%d",	i,
												flight[i].orig_port,flight[i].dest_port,
				   								flight[i].depart_time_hour,flight[i].depart_time_min,
				   								flight[i].arrive_time_hour,flight[i].arrive_time_min,
				   								flight[i].cost);
}

// Prints header to the screen
void print_header()
{
	printf("\n");
	printf("         __________  ___ _    __________   ___   _____________   ________      \n");
	printf("        /_  __/ __ |/   | |  / / ____/ /  /   | / ____/ ____/ | / /_  __/      \n");
	printf("         / / / /_/ / /| | | / / __/ / /  / /| |/ / __/ __/ /  |/ / / /         \n");
	printf("        / / / _, _/ ___ | |/ / /___/ /__/ ___ / /_/ / /___/ /|  / / /          \n");
	printf("       /_/ /_/ |_/_/  |_|___/_____/______/  |_|____/_____/_/ |_/ /_/           \n");
	printf("                               by Matthew Rundle                              \n");
}

// Print out available flights to the screen
void print_options(struct f *flight, char orig_port[4],int hour,int min)
{
	int i;
	printf("\n");
	printf("******************************[ AVAILABLE FLIGHTS ]*******************************\n");
	printf("              Port of     Port of\n");
	printf("Flight #      Departure    Arrival      Departure        Arrival        Cost\n");
	printf("--------------------------------------------------------------------------------");
	for(i=0;i<100;i++){
		if (strcmp(flight[i].orig_port,orig_port) == 0){
			if(((flight[i].depart_time_hour*60) + (flight[i].depart_time_min)) >= ((hour*60)+min)){
					print_flight(flight,i);
			}
		}
	}
}
		
// Print out the airports available for flights to the user (static)
// Then collect input from the user 
int initial_input(struct f *flight,char *orig_port)
{
	printf("\033[2J\033[H");
	print_header();
	printf("\n");
	printf("******************************[ AVAILABLE AIRPORTS ]******************************\n\n");
	printf("South Bend Airport       (SBN)		O'hare Int'l Airport               (ORD)\n");
	printf("Detroit Metro Airport    (DTW)		Minneapolis-St. Paul Int'l Airport (MSP)\n");
	printf("Reagan National Airport  (DCA)		Massport-Logan Airport             (BOS)\n");
	printf("Miami Int'l Airport      (MIA)		Atlanta Int'l Airport              (ATL)\n");
	printf("Denver Int'l Airport     (DEN) 		Indianapolis Int'l Airport         (IND)\n\n");
	printf("**********************************************************************************\n");
	printf("\nWelcome to TravelAgent. Let's build your itinerary.");
	printf("\nWhat airport are you starting at? Please enter the 3 letter code here: ");            
	int n=0;
	int out=0;
	while(out==0){
		n=scanf("\n%s",orig_port);
		if((n==1) && ((strlen(orig_port))==3)){ out=1; break;}
		printf("Unable to recognize that 3 letter airport code.\nPlease try again: ");
	} 
	// Change to upper
	int i;
	for(i=0;i<(strlen(orig_port));i++){ 
		orig_port[i]=toupper(orig_port[i]);
	}
	return 700;	
}

// Checks to make sure that the user entered valid input
// Returns true (1) if every element of the input is a digit
int flight_check(char *option,struct f *flight,int *itinerary)
{
	int i;
	// Make sure input is not over 2 digits long
	if(strlen(option)>2) return 0;
	// Make sure input contains all digits
	for(i=0;i<strlen(option);i++){
		if(isdigit(option[i])==0) return 0;
	}
	int flight_num=atoi(option,flight,itinerary);
	// Make sure flight does not leave before the previous one arrives
	if( ((((flight[flight_num].depart_time_hour)*60)+(flight[flight_num].depart_time_min))<(((flight[itinerary[itinerary[0]]].arrive_time_hour)*60)+(flight[itinerary[itinerary[0]]].arrive_time_min))) && itinerary[0]!=0){
		return 0;
	}
	// Make sure flight leaves from same place that the previous flight arrives at
	if((strcmp(flight[flight_num].orig_port,flight[itinerary[itinerary[0]]].dest_port)!=0) && itinerary[0]!=0){
		return 0;
	}
	// Make sure flight
	return 1;
}

// After the initial input, this function prompts the user for input.
// It collects the input and handles it appropriately, returning a number that will determine a message sent to the user.
int usr_pick(struct f *flight,char *orig_port,int *itinerary,int *hour,int *min)
{
	// Address the user and axe him fo sum input
	printf("\n\n-To add a flight, enter the Flight # from the list above.\n");
	printf("-To cancel the previous flight, or pick a new starting destination if no flights are selected, press 'cancel'.\n");
	printf("-If your itinerary is complete, enter 'end'.\n\n");
	printf("Please enter your command here: ");
	char option[100];
	int flight_num;
	scanf("%s",option);
	// Handle the string scanned in from the user
	if(strcmp(option,"cancel")==0 && itinerary[0]!=0){
		flight_num=itinerary[itinerary[0]];
		int canceled_flight=flight_num;
		itinerary[0]--;
		flight_num=itinerary[itinerary[0]];
		strcpy(orig_port,flight[flight_num].dest_port);
		*hour=flight[flight_num].arrive_time_hour;
		*min=flight[flight_num].arrive_time_min;
		if(itinerary[0]==0){
			*hour=0;
			*min=0;
			strcpy(orig_port,flight[itinerary[0]+1].orig_port);
		}
		return canceled_flight;
	}
	if(strcmp(option,"cancel")==0 && itinerary[0]==0){
		return 900;
	}
	if(strcmp(option,"end")==0){
		return 500;
	}
	// If the user types in a correct flight no, convert to int 
	// And handle the data
	if(flight_check(option,flight,itinerary)==1){
		flight_num=atoi(option,flight,itinerary);	
		int added_flight=flight_num;
		strcpy(orig_port,flight[flight_num].dest_port);
		*hour=flight[flight_num].arrive_time_hour;
		*min=flight[flight_num].arrive_time_min;
		itinerary[++itinerary[0]]=flight_num;
		return (100+added_flight);
	}
	return 600;
}

// Prints itinerary to screen
void print_itinerary(struct f *flight,int *itinerary)
{
	int i;
	printf("\n\n");
	printf("*******************************[ YOUR ITINERARY ]*********************************\n");
	printf("              Port of     Port of\n");
	printf("Flight #      Departure     Arrival      Departure        Arrival        Cost\n");
	printf("--------------------------------------------------------------------------------");
	for(i=1;i<=itinerary[0];i++){
		print_flight(flight,itinerary[i]);
	}
	printf("\n");
}

// Handles actions/errors based on number passed in; prints a response to the user.
void handle_errors(int choice,char *orig_port)
{
	if(choice>=0 && choice <100){
		printf("\n\n[ ACTION COMPLETE ]: Flight %02d has been removed from your itinerary.",choice);
		return;
	}
	if(choice>=100 && choice<200){
		printf("\n\n[ ACTION COMPLETE ]: Flight %02d has been added to your itinerary.",choice-100);
		return;
	}
	if(choice==600){
		printf("\n\n[ ERROR ]: Cannot process your response. Please check available flights and re-enter your choice.");
		return;
	}
	if(choice==700){
		printf("\n\n[ ACTION COMPLETE ]: You entered: %s. Available flights listed above.",orig_port);
		return;
	}
}

// Prints the itinerary to an external file, itinerary.txt
void export_itinerary(struct f *flight,int *itinerary)
{
	// Open the file for writing
	FILE *fp=fopen("itinerary.txt","w");
	fprintf(fp,"##################################################################################\n");
	fprintf(fp,"##        __________  ___ _    __________   ___   _____________   ________      ##\n");
	fprintf(fp,"##       /_  __/ __ |/   | |  / / ____/ /  /   | / ____/ ____/ | / /_  __/      ##\n");
	fprintf(fp,"##        / / / /_/ / /| | | / / __/ / /  / /| |/ / __/ __/ /  |/ / / /         ##\n");
	fprintf(fp,"##       / / / _, _/ ___ | |/ / /___/ /__/ ___ / /_/ / /___/ /|  / / /          ##\n");
	fprintf(fp,"##      /_/ /_/ |_/_/  |_|___/_____/______/  |_|____/_____/_/ |_/ /_/           ##\n");
	fprintf(fp,"##                               by Matthew Rundle                              ##\n");
	fprintf(fp,"##################################################################################\n");
	fprintf(fp,"##                                                                              ##\n");
	fprintf(fp,"##------------------------------[ YOUR ITINERARY ]------------------------------##\n");
	fprintf(fp,"##    Flight   Port of     Port of                                              ##\n");
	fprintf(fp,"##    Number   Departure     Arrival      Departure        Arrival        Cost  ##\n");
	fprintf(fp,"##------------------------------------------------------------------------------##\n");
	int i;
	int total_cost=0;
	for(i=1;i<=itinerary[0];i++){
	fprintf(fp,"##                                                                              ##\n");
	fprintf(fp,"##      %02d        %s        %s          %02d:%02d            %02d:%02d       $%d     ##\n",	itinerary[i],
												flight[itinerary[i]].orig_port,flight[itinerary[i]].dest_port,
				   								flight[itinerary[i]].depart_time_hour,flight[itinerary[i]].depart_time_min,
				   								flight[itinerary[i]].arrive_time_hour,flight[itinerary[i]].arrive_time_min,
				   								flight[itinerary[i]].cost);
	fprintf(fp,"##                                                                              ##\n");
	total_cost+=flight[itinerary[i]].cost;
	}
	fprintf(fp,"##                                                                              ##\n");
	fprintf(fp,"##------------------------------------------------------------------------------##\n");
	fprintf(fp,"##                                                                              ##\n");
	fprintf(fp,"##                                                 Total cost of trip: $%4d    ##\n",total_cost);
	fprintf(fp,"##                                                                              ##\n");
	fprintf(fp,"##                                                                              ##\n");
	fprintf(fp,"##                                                                              ##\n");
	fprintf(fp,"##           Thank you for choosing TravelAgent! Enjoy your trip.               ##\n");
	fprintf(fp,"##                                                                              ##\n");
	fprintf(fp,"##################################################################################\n");
	// Close the file
	fclose(fp);
}








int main(){
// Create array of flights and import flight list
struct f flight[100];
import_flights(flight);

// Create 'itinerary' array 
// In this array, [0] will keep track of total number of flights
int itinerary[10];  

//Collect initial input
char orig_port[100];
int hour=0;
int min=0;
int choice;
choice=initial_input(flight,orig_port);


//Run the program
while(choice!=500){
	//Clear screen and print header
	printf("\033[2J\033[H");
	print_header();

	//Print itinerary to the screen
	print_itinerary(flight,itinerary);

	//Print available flight options
	print_options(flight,orig_port,hour,min);

	//Give feedback to the user about errors or what was done
	handle_errors(choice,orig_port);

	//Collect and process input from the user. If itinerary is zero, collect initial input again
	choice=usr_pick(flight,orig_port,itinerary,&hour,&min);
	if(choice==900){ // 900 is an arbitrary code number
		choice=initial_input(flight,orig_port);
		hour=0;
		min=0;
	}
		
}

// Once the user has filled the itinerary, print it to itinerary.txt
export_itinerary(flight,itinerary);
printf("\n");
printf("          ###########################################################\n");
printf("          #                                                         #\n");
printf("          #   Your itinerary has been printed to 'itinerary.txt'.   #\n");
printf("          #            Thanks for using TravelAgent!                #\n");
printf("          #                                                         #\n");
printf("          ###########################################################\n");
printf("\n");
return 0;
}
