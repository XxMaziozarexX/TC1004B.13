// Todo este programa solo funciona en Linux  // En windows lo que cambia son las funciones
#include <unistd.h>
#include <stdio.h>

int main(){
    int fd[2];  // Arreglo de 2 elementos // entrada fd[1] y salida fd[0]
    pipe(fd);  // Crea tuberia y la guarda en la variable fd
    int pid = fork(); // fork para tener 2 procesos

    if(pid == 0){ // Proceso hijo ejecuta wc
        close(STDIN_FILENO);
        dup(fd[0]); // Funcion dup hace la conexion de la tuberia
        close(fd[1]);
        execlp("wc","wc","-l",NULL);

    }else{  // Proceso padre ejecuta ls
        close(STDOUT_FILENO);
        dup(fd[1]);   
        close(fd[0]);
        execlp("ls","ls",NULL);
    }
    return 0;
}
