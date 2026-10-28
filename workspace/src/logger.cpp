#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

int main(int argc, char **argv) {
    int fd;
    char buffer[1024];

    // borrar FIFO por si existiera previamente
    unlink("FIFO");

    /* crear el FIFO */
    if (mkfifo("FIFO", 0600)<0) {
        perror("No puede crearse el FIFO");
        return(1);
    }
    /* Abrir el FIFO */
    if ((fd=open("FIFO", O_RDONLY))<0) {
        perror("No puede abrirse el FIFO");
        return(1);
    }
    /* Leer de la FIFO */
    while (read(fd, buffer, sizeof(buffer)) > 0) {
	// X5: Imprimir el texto en la pantalla
	printf("%s\n", buffer);
    }
    close(fd);
    unlink("FIFO");
    return(0);
}
