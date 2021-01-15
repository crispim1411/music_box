Music Box
**********

Passe uma música de uma partitura para o Arduino. 

Estrutura
==========
A música é armazenada numa lista de notas, onde cada nota é composta da frequência e duração.

Notação
========
As notas musicais estão representadas em letras e os acidentes musicais de sustenido acompanhados da letra S

* Ex: D# -> DS

Quanto à duração das notas, estão representadas tendo a semibreve como figura de tempo, conforme a relação abaixo:

- semibreve : WHOLE
- mínima : HALF
- semínima : QUARTER
- colcheia : EIGHTH
- semicolcheia : SIXTEENTH

O tempo de cada intervalo é calculado informando a medida de BPM de uma semínima no código.
Geralmente esta informação consta no canto esquerdo superior da partitura.



