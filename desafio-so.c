#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>

#include <stdlib.h>

#define TAM_NOME 30
#define TAM_ACC 50

typedef struct {
  char name[TAM_NOME];
  int sizeOperation;
  int fileOpening;
} File;

int main () {

    File source;
    File destiny;

    char buffer[TAM_ACC];

    write(1, "Digite o nome do arquivo para ser copiado: ", 43);
    source.sizeOperation = read(0, source.name, TAM_NOME);
    source.name[source.sizeOperation - 1] = '\0';
    source.fileOpening = open(source.name, O_RDONLY);

    if (source.fileOpening >= 0){

        write(1, "\nArquivo aceito!\n\n" , 20);
        write(1, "Digite o nome do arquivo que será a cópia: ", 45);
        destiny.sizeOperation = read(0, destiny.name, TAM_NOME);
        destiny.name[destiny.sizeOperation - 1] = '\0';
        destiny.fileOpening = open(destiny.name, O_CREAT | O_EXCL | O_WRONLY, 0777);

        if (destiny.fileOpening >= 0){

            do {
                source.sizeOperation = read(source.fileOpening, buffer, TAM_ACC);
                destiny.sizeOperation = write(destiny.fileOpening, buffer, source.sizeOperation);

                // Forma simples de verificar a integridade dos dados
                if (source.sizeOperation != destiny.sizeOperation) {
                    write(1, "\nErro ao copiar Arquivo!\n", 30);
                    exit(1);
                }

            } while (source.sizeOperation > 0);

            write(1, "\nArquivo copiado com sucesso!\n", 30);
            close(source.fileOpening);
            close(destiny.fileOpening);

        } else {
            write(1, "\nAção inválida: o arquivo ja existe nesta pasta!\n\n", 30);
            close(source.fileOpening);
        }

    } else {
        write(0, "\nAção inválida: o arquivo não existe!\n", 44);
    }

    return 0;
}
