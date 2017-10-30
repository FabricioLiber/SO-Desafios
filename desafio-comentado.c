/// Bibliotecas para compatibilidade em algumas distribuições UNIX
#include <sys/types.h>
#include <sys/stat.h>

///Biblioteca para utilização da System Call open()
#include <fcntl.h>

///Biblioteca para utilização da System Calls lseek(), close(), read() e write()
#include <unistd.h>

///Variáveis com valor Constante para facilitar a manutenção do código
#define TAM_NOME 30
#define TAM_ACC 50

/// System Calls - Definição

/// São um conjunto especial de funções disponíveis em várias linguagens de programação. Eles são usados ??por programas
/// para se comunicar diretamente com um sistema operacional. O sistema operacional se comunica de volta ao programa do
/// usuário através do valor de retorno da função;

void main () {


    char origin[TAM_NOME]; /// Recebe o nome do arquivo que será copiado;
    int originCount; /// Recebe a qtd de caracteres que a variável "origin" contém;
    int originOpen; /// Recebe o retorno do Open, que indica a situacao do mesmo;
    int originSize; /// Recebe o retorno do Lseek, que indica a quantidade de bytes do arquivo;

    char copy[TAM_NOME]; /// Recebe o nome do arquivo que será a cópia;
    int copyCount; /// Recebe a qtd de caracteres que a variável "copy" contém;
    int copyOpen; /// Recebe o retorno do Open, que indica a situacao do mesmo;
    int copySize; /// Recebe o retorno do Lseek, que indica a quantidade de bytes do arquivo;

    char acc[TAM_ACC]; /// Acumulador, recebe os valores do arquivo será copiado;
    int sizeRead; /// Recebe o Retorno do Read da variável "acc";


    ///Write System Call

    /// 1º parametro - "int fildes":
    ///	O descritor de arquivo de onde escrever a saída. Você pode usar uma descritor de arquivo obtido da
    /// system call Open, ou você pode usar 0, 1 ou 2, para se referir a entrada padrão, saída
    /// padrão ou erro padrão, respectivamente.

    /// 2º parametro - "const void *buf":
    /// Um ponteiro para um buffer de pelo menos bytes nbytes, que será gravado no arquivo.

    /// 3º parametro - "size_t nbytes":
    /// O número de bytes a escrever. Se menor do que o buffer fornecido, a saída é truncada.

    /// Retorno - "return value":
    ///	Retorna o número de bytes que foram escritos. Se o valor for negativo, a system call
    /// retorna um erro.

    /// Read System Call

    /// 1º parametro - "int fildes":
    /// O descritor de arquivo de onde ler a entrada. Você pode usar um descritor de arquivo obtido da
    /// chamada do sistema aberto , ou você pode usar 0, 1 ou 2, para se referir a entrada padrão, saída
    /// padrão ou erro padrão, respectivamente.

    /// 2º parametro - "const void * buf":
    /// Uma matriz de caracteres onde o conteúdo lido será armazenado.

    /// 3º parametro - "size_t nbytes":
    /// O número de bytes a serem lidos antes de truncar os dados. Se os dados a serem lidos forem menores do
    /// que nbytes, todos os dados serão salvos no buffer.

    /// Retorno - "return value":
    /// Retorna o número de bytes que foram lidos. Se o valor for negativo, a chamada do sistema retornou um erro.

    /// Open System Call

    /// 1º parametro - "caminho const char *":
    /// O caminho relativo ou absoluto para o arquivo que deve ser aberto.

    /// 2º parametro - "int oflags":
    /// Uma lista de valores separados por bits ou separadas que determinam o método em que o arquivo deve ser aberto
    /// (seja ele somente leitura, leitura / gravação, seja devolvido quando aberto, etc.).

    /// 3º parametro - "modo mode_t":
    /// Uma lista de valores separados por bit ou separada que determina as permissões do arquivo se ele for criado.

    /// Retorno - "return value":
    /// Retorna o descritor de arquivo para o novo arquivo. O descritor de arquivo retornado é sempre o inteiro mais
    /// pequeno maior que zero que ainda está disponível. Se um valor negativo for retornado, houve um erro ao abrir o arquivo.

    /// Lseek System Call

    /// É uma system call que é usada para alterar a localização do ponteiro de leitura / gravação de um descritor de arquivo.

    /// 1º parametro - "int fildes":
    /// O descritor de arquivo do ponteiro que será movido.

    /// 2º parametro - "off_t offset":
    /// O deslocamento do ponteiro (medido em bytes).

    /// 3º parametro - "int whence":
    /// O método em que o deslocamento deve ser interpretado (relativo, absoluto, etc.).

    /// Retorno - "return value":
    /// Retorna o deslocamento do ponteiro (em bytes) desde o início do arquivo. Se o valor de retorno for -1, então houve um erro ao mover o ponteiro.

    write(1, "Digite o nome do arquivo para ser copiado: ", 43);
    originCount = read(0, origin, TAM_NOME);
    origin[originCount - 1] = '\0';
    originOpen = open(origin, O_RDONLY);

    ///| O_RDONLY --> (READ ONLY) O arquivo fica disponível apenas para leitura.

    if (originOpen >= 0){
        write(1, "\nArquivo aceito!\n\n" , 20);
        write(1, "Digite o nome do arquivo que será a cópia: ", 45);
        copyCount = read(0, copy, TAM_NOME);
        copy[copyCount - 1] = '\0';
        copyOpen = open(copy, O_CREAT | O_EXCL | O_WRONLY, 0777);

        /// O_WRONLY --> (WRITE ONLY) O arquivo fica disponível apenas para escrita.

        /// O_CREATE --> Se o arquivo não existir, crie-o. Se a opção O_CREAT for usada,
        /// você deve incluir o terceiro parâmetro.

        /// O_EXCL --> Combinado com a opção O_CREAT, ele garante que o chamador deve criar o arquivo.
        /// Se o arquivo já existe, a chamada falhará.

        /// 0777 --> Permissão total para manipulação do arquivo, se caso for criado a partir do programa.

        if (copyOpen >= 0){
            do {
                sizeRead = read(originOpen, acc, TAM_ACC);
                write(copyOpen, acc, sizeRead);
            } while (sizeRead > 0);
            originSize = lseek(originOpen, SEEK_SET, SEEK_END);
            copySize = lseek(copyOpen, SEEK_SET, SEEK_END);
            if (originSize == copySize)
                write(1, "\nArquivo copiado com sucesso!\n", 30);
            else
                write(1, "\nErro ao copiar Arquivo!\n", 30);

            close(originOpen);
            close(copyOpen);

    } else {
        write(0, "\nAção inválida: o arquivo não existe!\n", 44);
    }
}
