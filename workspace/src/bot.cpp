#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "DatosMemCompartida.h"
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc,char* argv[])
{
	int i;
	DatosMemCompartida* dat;
	char *direccion;
	int fd;
	
	fd=open("DatosMemCompartida", O_RDWR);
	if (fd == -1)
	{
		perror("Error al abrir el archivo"); 
		return 1;
	}
        direccion = (char*)mmap(NULL, sizeof(DatosMemCompartida), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (direccion == MAP_FAILED)
	{
		perror("Error en la proyeccion mmap"); 
		return 1;
	}
	close(fd);
	dat=(DatosMemCompartida*)direccion;

	while(1)
	{
		usleep(25000);
	if (dat->esfera.centro.y > (dat->raqueta1.y1 + dat->raqueta1.y2 + 1)/2)
            dat->accion = 1;
        else if (dat->esfera.centro.y < (dat->raqueta1.y1 + dat->raqueta1.y2 - 1)/2)
            dat->accion = -1;
            
        if (dat->res == 0) break;
	}
	munmap(dat, sizeof(DatosMemCompartida));
	return 0;
}
