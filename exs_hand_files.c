#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

int main (int argc, char **argv) {
   bin_handler_apb();
   bin_handler_r();
   return 0;
}

int bin_handler_r() {
    FILE *bf;
    char *fname = "inteiros.bin";
    struct stat info;
    stat(fname, &info);
    printf("FILE SIZE BYTES: %d\n", info.st_size/4);

    int r_int[info.st_size/4];
    int result;
    if((bf = fopen(fname, "rb")) == NULL) {
        printf("Error\n");
        return 1;
    }

    result = fread(&r_int[0], sizeof(int), 100, bf);

    for(int i=0; i < result; i++)
        printf("%d\n", r_int[i]);

    fclose(bf);

    return 0;
}
//sem tratar erros em fwrite e fread
//le somente o ultimo inteiro adicionado pelo append
int bin_handler_apb() {
    FILE *bf;
    char *fname = "inteiros.bin";
    int wr = 101;

    if((bf = fopen(fname, "a+b")) == NULL) {
        printf("Error\n");
        return 1;
    }

    fwrite(&wr, sizeof(int), 1, bf);
    
    fseek(bf, -1*sizeof(int), SEEK_END);
    int r_wr;
    fread(&r_wr, sizeof(int), 1, bf);
    printf("READ INT APPEND ADD:%d\n", r_wr);
    fclose(bf);
    return 0;
}

int ex1_stringf() {
	FILE *f;
	char string[256];

	if((f = fopen("teste.txt",	"a+")) == NULL) {
		printf("Erro ao abrir arquivo\n");
		return 1;
	}

	do {
	fgets(string, 256, stdin);
	fputs(string, f);
	} while(string[0] != '\n');

	rewind(f);

	while (fgets(string, 256, f) != NULL)		
		fputs(string, stdout);

	fclose(f);
	return 0;
}