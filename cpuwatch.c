#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void alarm_handler(int signum) {
	alarm(1); 
}

int main() { 
	signal(SIGALRM, alarm_handler); 
	alarm(1); 
	
	char cpu[5]; 
	long nice, userp, userc, userd, systemp, systemc, systemd, idlep, idlec, idled, percentage;
	
	while(1) {
		pause(); 
		
		userp = userc; 
		systemp = systemc; 
		idlep = idlec; 
		
		char line[999];
		FILE *file = fopen("/proc/stat", "r"); 
		fgets(line, 999, file); 
		fclose(file); 
		sscanf(line, "%s %ld %ld %ld %ld", cpu, &userc, &nice, &systemc, &idlec); 
		
		userd = userc - userp;
		systemd = systemc - systemp; 
		idled = idlec - idlep;
		percentage = 100 * (userd + systemd) / (userd + systemd + idled); 
		
		printf("User\tSystem\tIdle\tUsage\n"); 
		printf("%ld\t%ld\t%ld\t%ld%%\n\n", userd, systemd, idled, percentage); 
	}
}
