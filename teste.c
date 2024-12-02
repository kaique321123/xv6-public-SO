#include "types.h"
#include "user.h"
#include "stat.h"

int main(void) {
    int count;

    count = getreadcount();  // Chama a syscall
    printf(1, "Total de chamadas a read(): %d\n", count);

    exit();  // Finaliza o programa
}
