static unsigned char *memoryStart;
typedef int size_t;
int NULL;

void memReplace(char* mem, char oldChar, char newChar, size_t length) {
    for (size_t i = 0; i < length; i++) {
        if (mem[i] == oldChar) {
            mem[i] = newChar;
        }
    }
}
 void memfill(void *dest, size_t length, unsigned char value) {
    // Cast o ponteiro para unsigned char* para permitir o preenchimento byte a byte
    unsigned char *d = (unsigned char *)dest;

    // Preencha os bytes da memória com o valor especificado
    for (size_t i = 0; i < length; i++) {
        d[i] = value;
    }
}

void memcopy(void *dest, const void *src, size_t length) {
    // Cast os ponteiros para unsigned char* para permitir a cópia byte a byte
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;

    // Copie os bytes de src para dest
    for (size_t i = 0; i < length; i++) {
        d[i] = s[i];
    }
}
 char *malloc(int length) {
    // Verifica se há espaço suficiente na memória
    unsigned char *memoryEnd = memoryStart + length + sizeof(int) * 2+4;
    if (memoryEnd > (unsigned char *)0x700000) {
        // Não há espaço suficiente
        return (char*)NULL;
    }

    // Preenche o bloco de memória com zeros
    memfill(memoryStart, length + sizeof(int) * 2, 0);

    // Preenche o inteiro do cabeçalho
    *(char *)memoryStart = length;

    // Preenche o inteiro do rodapé
    *(char *)(memoryStart + length + sizeof(int)) = length;
    memoryEnd=(memoryStart + sizeof(int));
    memoryStart= memoryStart+ length + sizeof(int) * 2+8;
    // Retorna o endereço após os inteiros do cabeçalho
    return (char *)memoryEnd;
}

 // Função para contar o tamanho de uma string
size_t lens(const char* str) {
    size_t length = 0;
    while (*str) {
        length++;
        str++;
    }
    return length;
}

// Função para copiar uma string e adicionar seu comprimento ao valor
void strcpys(char* dest, const char* src) {
    while (*src) {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0'; // Null-terminator
}
unsigned char getKeys() {
    unsigned char value;
    
    // Usando uma instrução asm inline para ler a porta 0x60
    asm volatile ("inb %1, %0" : "=a"(value) : "Nd"(0x60));
    
    return value;
}

// Define a função que retorna uma string da memória baixa
char* getStringFromLowMemory() {
    // Ponteiro para a memória baixa (0x60000)
    unsigned char* memoryPointer = (unsigned char*)0x60000;

    // Retorna o ponteiro para a string na memória baixa
    return memoryPointer;
}

 int kernel_main()
        {
		unsigned char *datas;
		char *d;	   
		int n=0;	   
		int x=100;
		int y=100;
		unsigned char* addr;
		unsigned int memo=0x301000;
		unsigned int memos=0x301000;
		NULL=0;
		
		memoryStart = (unsigned char *)0x301000;

		datas=getStringFromLowMemory();
		for(n=0;n<64032;n++){
		    memoryStart[n]=datas[n];
		    //memoryStart++;
		    //datas++;
		}
		__asm__ __volatile__("call *%0\n\t"
		: 
		: "r" (memo));
		
		

		return 0;	  
        }
 

