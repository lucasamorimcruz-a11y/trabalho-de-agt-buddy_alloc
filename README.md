Buddy Memory Allocator

Este projeto implementa um alocador de memória baseado no algoritmo Buddy System. O objetivo é fornecer uma estrutura simples para gerenciar alocação e liberação de blocos de memória utilizando divisão e fusão de blocos em potências de dois.

O alocador utiliza:

Uma área de memória contínua obtida via mmap.

Uma lista de blocos livres organizada por níveis.

Cada nível representa blocos de tamanho 2^(MIN_SIZE + nível).

Blocos são divididos quando necessário e fundidos quando possível.
