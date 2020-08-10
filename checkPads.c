#define PAD_ARRAY_LENGTH	1024
#define PAD_TAILING_DEFAULT	"(pad"

#define PAD_OPTION_ZERO		"-0"
#define PAD_OPTION_VERBOSE	"-v"
#define PAD_OPTION_HELP		"-h"

#include <stdio.h>
#include <string.h>

int main(int argc, char **argv){
	FILE *modFile;
	char *line;
	size_t len = 0;
	int idx;
	int countOk = 1;
	int initialPad = 1;
	int verbose = 0;

	int padNumbers[PAD_ARRAY_LENGTH];
	int parsedValue;
	int biggestPadNumber = 0;
	char strTailing[32];

	bzero(padNumbers, (sizeof(int) * PAD_ARRAY_LENGTH));

	if(argc < 2){
		printf("Wrong input. Usage:checkPads {file name} [-0|-v|-h]\n\t-0: Check for PAD zero\n\t-v: Verbose mode\n\t-h: show this menu\n");
		return 1;
	}

	if(argc > 2){
		for(idx = 2; idx < argc; idx++){
			if(strcmp(argv[idx], PAD_OPTION_ZERO) == 0){
				initialPad = 0;
			}else if(strcmp(argv[idx], PAD_OPTION_VERBOSE) == 0){
				verbose = 1;
			}else if(strcmp(argv[idx], PAD_OPTION_HELP) == 0){
				printf("Usage:checkPads {file name} [-0|-v|-h]\n\t-0: Check for PAD zero\n\t-v: Verbose mode\n\t-h: show this menu\n");
				return 0;
			}
		}
	}
	
	if(strcmp(argv[1], PAD_OPTION_HELP) == 0){
		printf("Usage:checkPads {file name} [-0|-v|-h]\n\t-0: Check for PAD zero\n\t-v: Verbose mode\n\t-h: show this menu\n");
		return 0;
	}

	modFile = fopen(argv[1], "r");
	if(modFile == NULL){
		printf("Could not open file '%s'. Exiting...\n", argv[1]);
		return 1;
	}

	while(getline(&line, &len, modFile) != -1){
		sscanf(line, "%s %d", strTailing, &parsedValue);

		if(strcmp(strTailing, PAD_TAILING_DEFAULT) == 0){
			// this is a PAD define in the module, account for it
			if((parsedValue < 0) || (parsedValue > 1024)){
				printf("Invalid PAD number '%d'\n", parsedValue);
			}else{
				if(parsedValue > biggestPadNumber)
					biggestPadNumber = parsedValue;
				
				if(verbose)
					printf("Found PAD number '%d'\n", parsedValue);

				padNumbers[parsedValue]++;
			}
		}
	}

	// check that all PADs are assigned and not repeated
	for(idx = initialPad; idx <= biggestPadNumber; idx++){
		if(padNumbers[idx] == 0){
			printf("PAD number '%d' is missing\n", idx);
			countOk = 0;
		}else if(padNumbers[idx] > 1){
			printf("Multiple PADs numbered '%d'\n", idx);
			countOk = 0;
		}
	}

	if(countOk)
		printf("Finished checking PADs on '%s', they are sequential and not repeating! Cool.\n", argv[1]);
	else
		printf("Repeated or missing PADs on '%s'\n", argv[1]);

	fclose(modFile);
	return 0;
}
