#include <sys/types.h>
#include <sys/stat.h>

#include <fcntl.h>

#include <unistd.h>

#define TAM_NOME 30
#define TAM_ACC 50

void main () {


    char origin[TAM_NOME]; 
    int originCount, originOpen, originSize;

    char copy[TAM_NOME];
    int copyCount, copyOpen, copySize;

    char acc[TAM_ACC]; 
    int sizeRead;

    write(1, "Digite o nome do arquivo para ser copiado: ", 43);
    originCount = read(0, origin, TAM_NOME);
    origin[originCount - 1] = '\0';
    originOpen = open(origin, O_RDONLY);

    if (originOpen >= 0){

        write(1, "\nArquivo aceito!\n\n" , 20);
        write(1, "Digite o nome do arquivo que será a cópia: ", 45);
        copyCount = read(0, copy, TAM_NOME);
        copy[copyCount - 1] = '\0';
        copyOpen = open(copy, O_CREAT | O_EXCL | O_WRONLY, 0777);

        if (copyOpen >= 0){

            do {
                sizeRead = read(originOpen, acc, TAM_ACC);
                write(copyOpen, acc, sizeRead);
            } while (sizeRead > 0);

            originSize = lseek(originOpen, 0, SEEK_END);
            copySize = lseek(originOpen, 0, SEEK_END);

            if (originSize == copySize) 
                write(1, "\nArquivo copiado com sucesso!\n", 30);
            else 
                write(1, "\nErro ao copiar Arquivo!\n", 30);            

        } else {
            write(1, "\nAção inválida: o arquivo ja existe nesta pasta!\n", 30);
        }

    } else {
        write(0, "\nAção inválida: o arquivo não existe!\n", 44);
    }

    close(originOpen);
    close(copyOpen);

}
