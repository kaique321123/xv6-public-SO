# Implementação do EP - Syscall `getreadcount`

### **Diário de Implementação**

Este documento detalha as etapas realizadas para implementar a syscall `getreadcount` no kernel e na interface de usuário do sistema operacional xv6. A implementação envolveu a modificação de vários arquivos no kernel e no lado do usuário, detalhados a seguir.

---

### **Modificações no Kernel**

1. **Arquivos estudados:**
   - `syscall.c`: Contém a tabela que mapeia números para funções de sistema (prefixadas por `sys_`, retornam `int` e não possuem argumentos).
   - `sysproc.c`: Implementa syscalls relacionadas ao gerenciamento de processos e memória.
   - `sysfile.c`: Lida com syscalls associadas ao sistema de arquivos.

2. **Etapas principais:**
   - Adicionei uma entrada para `SYS_getreadcount` na tabela de syscalls (`syscall.c`).
   - Declarei a função `sys_getreadcount()` como `extern` em `syscall.c` e defini seu número no header correspondente:
     ```c
     #define SYS_getreadcount 22
     ```
   - Implementei a função no arquivo `sysfile.c`:
     ```c
     int sys_getreadcount(void) {
         extern int read_count;
         return read_count;
     }
     ```
   - Adicionei a variável global `read_count` para contar as chamadas `read()`.
   - Configurei o ambiente para rodar no QEMU e ajustei erros de compilação.

---

### **Modificações no Usuário**

1. **Arquivos modificados:**
   - `user.h`: Adicionei o protótipo da syscall:
     ```c
     int getreadcount(void);
     ```
   - `usys.S`: Ativei o interrupt da syscall `getreadcount`.
   - `test_1.c`: Criei um programa para testar a nova syscall:
     ```c
     #include "types.h"
     #include "user.h"
     #include "stat.h"

     int main(void) {
         int count = getreadcount(); // Chama a syscall
         printf(1, "Total de chamadas a read(): %d\n", count);
         exit();
     }
     ```

2. **Testes:**
   - Após ajustes iniciais, o contador exibiu corretamente o número de chamadas a `read()`.
   - Executei dois testes: 
     - **Teste 1**: Validou o funcionamento básico.
     - **Teste 2**: Confirmou a consistência do contador.

---

### **Decisões e Aprendizados**

1. **Locks**:  
   - Decidi não implementar locks para o contador, pois a concorrência é rara e o SO já gerencia as colisões.
   - Tentei implementar locks por curiosidade, mas encontrei dificuldades. Por simplicidade e segurança, optei por não incluí-los na solução final.

2. **Considerações:**  
   - Analisar implementações semelhantes foi essencial para entender o padrão.
   - A troca de ideias com colegas e o enunciado claro do EP ajudaram a guiar o processo.

---

### **Conclusão**

A syscall `getreadcount` foi implementada com sucesso e testada em diferentes cenários. A funcionalidade está integrada ao kernel e ao usuário, permitindo contar chamadas a `read()`. A implementação foi validada tanto no meu PC quanto na máquina virtual.

---
