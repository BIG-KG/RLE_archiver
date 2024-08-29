#include <stdio.h>

int decomress_reapits(FILE *compress, FILE *file){
    int num_of_repeat = 0;
    int repeating_el = 0;
    int right_type_compress = 0;

    right_type_compress = fscanf(compress, "%d$%c$", &num_of_repeat, &repeating_el);
    if(right_type_compress != 2){
        return 1;
    }

    for(int i = 0; i < num_of_repeat; i++){
        fputc(repeating_el, file);
    }
    return 0;
}

int stream_compress_to_file(FILE *compress, FILE *file){

    int streaming_el = -1;
    int error_decompress = 0;

    while((streaming_el =fgetc(compress)) != EOF){
        if(streaming_el == '$'){
            error_decompress = decomress_reapits(compress, file);
            if(error_decompress != 0){
                break;}
            continue;
        }
        fputc(streaming_el, file);
    }

    if(error_decompress != 0){
        return 1;
    }
    return 0;
}

int main(int argc, char **argv)
{	
	FILE * compessed = NULL;
	FILE * decompessed = NULL;
    if(argc == 1){
        compessed = fopen("out.txt", "r");
        decompessed = fopen("decompressed.txt", "w");
    }
    else if(argc == 2){
        compessed = fopen(argv[1], "r");
        decompessed = fopen(argv[2], "w");
    }

    else{
        compessed = fopen(argv[1], "r");
        decompessed = fopen("decompressed.txt", "w");
    }

    stream_compress_to_file(compessed, decompessed);

	fclose(compessed);
	fclose(decompessed);


}
