#include <sys/types.h>
#include <sys/stat.h>

#include <fcntl.h>

#include <unistd.h>

#define TAM_NOME 30
#define TAM_ACC 50

void main () {


    char origin[TAM_NOME]; ///Variável responsável por receber o nome do arquivo que será copiado
    int originCount; ///Variável responsável por receber a qtd de caracteres que a variável "origin" contém
    int originOpen; ///Variável responsável por receber o retorno do Open, que indica a situacao do mesmo
    int originSize;

    char copy[TAM_NOME]; ///Variavél responsável por receber o nome do arquivo que será a cópia
    int copyCount; ///Variavél responsável por receber a qtd de caracteres que a variável "copy" contém
    int copyOpen; ///Variável responsável por receber o retorno do Open, que indica a situacao do mesmo
    int copySize;

    char acc[TAM_ACC]; /// Acumulador, recebe os valores do arquivo será copiado.
    int sizeRead;


    ///Write System Call

    /// 1º parametro - "int fildes"
    ///	The file descriptor of where to write the output. You can either use a file descriptor
    /// obtained from the open system call, or you can use 0, 1, or 2, to refer to standard input, standard
    /// output, or standard error, respectively.

    /// 2º parametro - "const void *buf"
    /// A pointer to a buffer of at least nbytes bytes, which will be written to the file.

    /// 3º parametro - "size_t nbytes"
    /// The number of bytes to write. If smaller than the provided buffer, the output is truncated.

    /// Retorno - "return value"
    ///	Returns the number of bytes that were written. If value is negative, then the system call
    /// returned an error.

    write(1, "Digite o nome do arquivo para ser copiado: ", 43);
    originCount = read(0, origin, TAM_NOME);
    origin[originCount - 1] = '\0';
    originOpen = open(origin, O_RDONLY);

    ///| O_RDONLY - Apenas leitura no arquivo

    if (originOpen >= 0){
        write(1, "\nArquivo aceito!\n\n" , 20);
        write(1, "Digite o nome do arquivo que será a cópia: ", 45);
        copyCount = read(0, copy, TAM_NOME);
        copy[copyCount - 1] = '\0';
        copyOpen = open(copy, O_CREAT | O_EXCL | O_WRONLY, 0777);

        /// O_RDWRONLY --> O arquivo fica disponível tanto para Leitura como Escrita.

        /// O_CREATE --> Se o arquivo não existir, crie-o. Se a opção O_CREAT for usada,
        /// você deve incluir o terceiro parâmetro.

        /// O_EXCL --> Combinado com a opção O_CREAT, ele garante que o chamador deve criar o arquivo.
        /// Se o arquivo já existe, a chamada falhará.

        if (copyOpen >= 0){
            do {
                sizeRead = read(originOpen, acc, TAM_ACC);
                write(copyOpen, acc, sizeRead);
            } while (sizeRead > 0);
            originSize = lseek(originOpen, 0, SEEK_END);
            copySize = lseek(originOpen, 0, SEEK_END);
            if (originSize == copySize) {
                write(1, "\nArquivo copiado com sucesso!\n", 30);
            }
        } else {
            write(1, "\nErro ao copiar Arquivo!\n", 30);
        }
    } else {
        write(0, "\nAção inválida: o arquivo não existe!\n", 44);
    }
}
