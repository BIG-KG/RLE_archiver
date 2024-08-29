#include <stdio.h>

void remove_reapit(FILE *infile, FILE *outfile, int *reapiting_char){
	int num_of_reapit = 2;                                                   // убать два
	char se = -1;
	while((se = fgetc(infile)) == *reapiting_char && se != EOF){
		num_of_reapit ++;
	}
	fprintf(outfile,"$%d$%c$",num_of_reapit, *reapiting_char);
	*reapiting_char = se;
}

int stream_file_to_comprs(FILE *inFile, FILE *outFile){
    int se = -2;
	int pe = fgetc(inFile);                                                             // поменять на норм значения
    while((se = fgetc(inFile)) != EOF){
		if(se == pe){
			remove_reapit(inFile, outFile, &pe);
			continue;
		}
		fprintf(outFile, "%c", pe);
		pe = se;
	}
	if(se != EOF){
	    fprintf(outFile, "%c", se);
	}
	return 0;
}


int main(int argc, char **argv)
{
    FILE *input = NULL;
    FILE *compressed = NULL;
    if(argc == 1){
        input = fopen("in.txt", "r");
        compressed = fopen("out.txt", "w");
    }
    else if(argc == 3){
        input = fopen(argv[1], "r");
        compressed = fopen(argv[2], "w");
    }
    else{
        input = fopen(argv[1], "r");
        compressed = fopen("out.txt", "w");
    }


	stream_file_to_comprs(input, compressed);

    fclose(input);
    fclose(compressed);

}
