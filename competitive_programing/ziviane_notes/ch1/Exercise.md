1. **Dê a definição de:**
    1. Alogoritmo:
    2. Tipo de dado:
    3. Tipo abstrato de dado:
2. **O que significa dizer que uma função g(n) é O(f(n)):**
3. **O que significa dizer que um alogoritmo executa em tempo proporcional a n:**
4. **Explique a diferença entre O(1) e O(2):**
5. **Qual alogoritmo você prefere: Um que requer $n^5$ passos ou um que requer $2^n$ passos?:**
6. **Prove que $f(n) = \Sigma^{n}_{1}{i^2}$ é igual a $\frac{n^3}{3} + O(n^2)$:**
7. **Indique se as afirmativas a seguir são verdadeiras ou falsas e justifique sua resposta:**
    1. $2^{n+1} = O(2^n)$:
    2. $2^{2n} = O(2^n)$:
    3. $2^{\frac{n}{2}} =\Theta(n):$
    4. $f(n) = O(u(n)) \land g(n) = O(v(n)) \implies f(n) + g(n) = O(u(n) + v(n))$
    5. $f(n) = O(u(n)) \land g(n) = O(v(n)) \implies f(n) - g(n) = O(u(n) - v(n))$
8. **Sejam duas funções não negativas f(n) e g(n) diz-se que $f(n) = O(g(n))\land g(n) = O(f(n)) \implies f(n)=\Theta(g(n))$. Mostre que $max(f(n),g(n))=\Theta(f(n) + g(n))$**
9. Suponha um alogoritmo A e um algoritmo B com funções de complexidade de tempo $a(n) = n^2 - n + 549$ e $b(n) = 49n + 49$, respectivamente. Determine quais são os valores de n pertencentes a $\N$ para os quais A leva menos tempo para executar do que B
10. Implemente os três alogoritmos apresentados nos programas 1.3, 1.4 e 2.8, para obter o máximo e o mínimo de um conjunto contendo $n$ elementos. Execute os algoritmos para valores suficientemente grandes de $n$, gerando casos de teste para o melhor caso, o pior caso e o caso esperado. Meça o tempo de execução para cada algoritmo com relação aos três casos desta questão e comente os resultados.
11. (Carvalho, 1992) São dados $2n$ números distintos distribuidos em dois arranjos com $n$ A e B ordenados de maneira tal que: $A[1] > A[2] > A[3]>...>A[n]$ e $B[1] > B[2] > B[3] > ... > B[n]$ O problema é achar o $n$-ésimo maior número dentre estes $2n$ elementos:
    1. Obtenha um limite inferior para o número de comparações necessárias para resolver esse problema
    2. Apresente um alogoritmo cuja complexidade no pior caso seja igual o valor obtido em i., ou seja, um algoritmo ótimo
12. Seja um vetor A com $n$ elementos, i.e, A[1...n] (Loureiro, 2010). É possível determinar se existe um par de elementos distintos em tempo inferior a $\Omega(nlogn)$? Se sim, descreva o alogoritmo, caso contrário, justifique sua resposta.
13. É dada a uma matriz $n \times n$ A, na qual cada elemento é denominado A$_{i,j}$ e $1 \le i,j \le n$ (Carvalho, 1992). Sabemos que a matriz foi ordenada de modo a:
    1. $A_{i,j} < A_{i,k}, \forall_{i, j\space<\space k}$
    1. $A_{i,j} < A_{k,j}, \forall_{i, j\space<\space k}$

Apresente um alogoritmo que ache a localização de determinado elemento x em A e analise o comportamento no pior caso. (Dica: Existe um algoritmo que resolve este problema em O(n) comparações no pior caso.)

14. Apresente um alogoritmo para obter o maior e o segundo maior elemento de um conjunto. Apresente também uma análise do algoritmo. Você acha que o seu algoritmo é eficiente? Por quê? Procure comprovar suas respostas.
15. Considere o problema de inserir um novo elemento em um conjunto ordenado $A[1] > A[2] > A[3] > ... > A[n]$
    1. Apresente um limite inferior para essa classe de problemas: 
    2. Apresente uma prova informal para o limite inferior: 
    3. Apresente um alogoritmo para resolver o problema desta questão. O seu algoritmo é ótimo?:
16. Dada uma lista ordenada de $n$ elementos de valor inteiro, o problema de unificação de lista consiste em realizar seguidamente a operação de remover dois elementos de menor valor da lista e inserir um novo elemento com valor igual à soma dos dois primeiros. A cada operação a lista passa a ter um elemento a menos. A unificação termina quando restar somente um elemento na lista.
    1. Apresente um alogoritmo que realiza a unificação da lista em tempo O(n).
    2. É possível realizara a unificação da lista em tempo sublinear? Justifique sua resposta.
    3. Qual o limite inferior para o problema da unificação?
17. Avalie as somas:
    1. $\Sigma^{n}_{i=1}{i}$
    2. $\Sigma^{n}_{i=1}{a^i}$
    3. $\Sigma^{n}_{i=1}{ia^i}$
    4. $\Sigma^{n}_{i=0}{\binom{n}{i}}$
    5. $\Sigma^{n}_{i=1}{\binom{n}{i}}$
    6. $\Sigma^{n}_{i=1}{i\binom{n}{i}}$
    7. $\Sigma^{n}_{i=1}{\frac{1}{i}}$
    8. $\Sigma^{n}_{i=1}{\log{i}}$
    9. $\Sigma^{n}_{i=1}{i2^{-i}}$
    10. $\Sigma^{n}_{i=1}{(\frac{1}{7})^i}$
    11. $\Sigma^{n}_{i=m}{a_i-a_{i-1}}$
18. Resolva as seguintes equações de recorrência:
    1. $\big\{^{T(n) = T(n - 1) + c}_{T(1)=0}$
    2. $\big\{^{T(n) = T(n-1)+2^n}_{T(0)=1}$
    3. $\big\{^{T(n) = cT(n - 1)}_{T(0) = k}$
    4. $\big\{^{T(n) = 3T(n/2) + n}_{T(1) = 1}$
    5. $\biggl\{^{T(n)=3T(n - 1) - 2T(n - 2)}_{T(1)=1}{T(0)=0}$
    6. $\big\{^{T(n)=\Sigma^{n-1}_{i=1}{2T(i) + 1}}_{T(1) = 1}$
    7. $\big\{^{T(n) = T(\sqrt n) + \log{n}}_{T(1)= 1}\big|$ Dica: Use mudança de variáveis 
    8. $\big\{^{T(n) = 2T(\lfloor n/2 \rfloor) + 2n\lg{n})}_{T(2) = 4}$

Prove usando indução matemática em $n$

19. Considere o algoritmo a seguir: Suponha que a operação crucial é o fato de inspecionar um elemento. O algoritmo inspeciona $n$ elementos de um conjunto e , de alguma forma, isso permite descartar 2/5 dos elementos e então fazer uma chamada recursiva sobre os $3n/5$ elementos restantes.

        procedure Pesquisa (n : integer);
        if n <= 1 
        then 'inspeciona elemento' e termine
        else beign
        para cada um dos n elementos 'inspecionar elemento';
        Pesquisa(3n/5);
        end;
        end;
    
    1. Escreva uma equação de recorrência que descreva esse comportamento.
    2. Converta essa equação para um somatório.
    3. Dê a fórmula fechada para esse somatório.

20. Considere o algoritmo a seguir:
    1. Escreva uma equação de recorrência que descreva esse comportamento.
    2. Converta essa equação para um somatório.
    3. Dê a fórmula fechada para esse somatório.

    
        procedure Sort2( var A: array[1...n] of integer; i, j: integer);  
        begin {-- n uma potencia de 3--}  
        if i < j  
        then begin  
        k := ((j - 1) + 1) / 3  
        Sort2(A, i, i + k - 1);  
        Sort2(A, i + k, i + 2k - 1);  
        Sort2(A, i + 2k, j);  
        Merge(A, i, i + k, i + 2k, j);  
        { Merge intercala A[i...(i + k - 1)], A[(i + k)..(i + 2k - 1)] e A[i + 2k..j] em A[i..j] a um custo de 5n/3 - 2  
        end;  
        end;

21. Obtenha o número máximo de regiões no plano determinado por n retas (Loureiro, 2010). Um plano sem nenhuma reta tem uma região, com uma reta tem duas regiões, com duas retas tem quatro regiões, e assim por diante.
    1. Obtenha a equação de recorrência para resolver o problema
    2. Resolva a equação de recorrência

22. Problema dos ovos (Baeza-Yates, 1997): Dado um edifício de $n$ andares e $k$ ovos especiais (ovo caipira), nós desejamos resolver o seguinte problema: qual é o andar mais alto do qual podemos arremessar um ovo sem que ele se quebre? Apresente o melhor algoritmo para cada um dos casos a seguir. Discuta se seu algoritmo é ótimo ou não em cada caso:
    1. Temos apenas um ovo
    2. Temos dois ovos
    3. Temos muitos ovos
