#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//gcc [srcfiles.c] -o destfile

//struct para armazenar todos os argumentos
typedef struct args {
    char *compiler;      //gcc
    int output_argn;     //-o
    char *destfile;      //destifile
}args;

//Procura o "-o", que sempre será o terceiro argumento ou superior
int search_output(int argnum, int argc, char *argv[]){
    if(argnum >= argc) return 0;
    if(strcmp("-o", argv[argnum]) == 0) return argnum;
    search_output(argnum+1, argc, argv);
}

//Seta o nome do arquivo de saida(binario)
void handle_destfile(args *args, char *argv[]) {
    if(!args->output_argn) return;
    args->destfile = argv[args->output_argn+1];
    return;
}

//Seta as variaveis da struct args
void set_args(args *args, int argc, char *argv[]){
    args->compiler = "gcc";
    args->output_argn = search_output(2, argc, argv);
    handle_destfile(args, argv);
}

//Conta a quantidade de caracteres necessarios para alocar na string
int count_command_characters(int argc, char *argv[]) {
    int length = argc;
    for(int i = 1; i < argc; i++) {
        length += (int)strlen(argv[i]);
    }
    return length;
}

//Monta o comando de compilação
char *mount_command(args *args, int argc, char *argv[]) {
    char *command = malloc(count_command_characters(argc, argv));
    
    strcat(command, args->compiler);
    strcat(command, " ");

    for(int i = 1; i < argc; i++) {
        strcat(command, argv[i]);
        strcat(command, " ");
    }
    return command;
}

int main(int argc, char *argv[]){
    if (argc < 2){
        printf("Argumentos insuficientes\n");
        return 0;
    }

    args *args = malloc(sizeof(args));
    set_args(args, argc, argv);
    
    char *comp_command = mount_command(args, argc, argv);
    
    char *run_command;
    if(args->output_argn) {
        run_command = malloc(strlen(args->destfile + 3));
        strcat(run_command, "./");
        strcat(run_command, args->destfile);
    }

    printf("Compiling...\n");
    int comp_result = system(comp_command);

    if(!comp_result) {
		printf("Running..\n");
        if(!args->output_argn) {
            system("./a.out");
        } else {
            system(run_command);
        }
    }

    if(args->output_argn){
        free(run_command);
    }
    free(args);
    free(comp_command);

    return 0;
}
