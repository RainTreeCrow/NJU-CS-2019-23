### 191220154 AsHL



1. $[\,y + 2*(x+1)-1=(x+1)^2\,]\;x:=x+1;\;[\,y+2*x-1=x^2\,]$	$_{AS}$

   $y=x^2 \;⇒\; y+2*x+1=x^2+2*x+1$

   $[\,y=x^2\,]\;x:=x+1;\;[\;y+2*x-1=x^2\;]$	$_{SP}$

   $[\,y+2*x-1=x^2\,]\;y := y + 2 ∗ x − 1;\;[\,y = x^2\,]$	$_{AS}$

   $[\,y=x^2\,]\;x:=x+1;\;y := y + 2 ∗ x − 1;\;[\;y=x^2\;]$	$_{SC}$

   The weakest assertion is  $y=x^2$.

   

   $[\,y=z\and (x+y)-y=w\,]\;x=x+y\;[\,y=z\and x-y=w\,]$	$_{AS}$

   $[\,x-(x-y)=z\and x-y=w\,]\; y := x − y;\; [\,x-y=z\and y=w\,]$	$_{AS}$

   $[\,x-y=z\and y=w\,] \;x := x − y;\; [\,x = z ∧ y = w\,]$	$_{AS}$

   The weakest assertion is  $y = z \and x = w$.

   

   $[\,i \and (b-(a+1)<x_0)\,] \;a:=a+1;\;[\,i\and(b-a<x_0)\,]$	$_{AS}$

   $i\and(a<b)\and(b-a=x_0) \;⇒\; i\and(b-a-1<x_0)$

   $[\,i\and(a<b)\and(b-a=x_0)\,] \;a:=a+1;\; [\,i\and(b-a<x_0)\,]$	$_{SP}$

   $[\,i\and(b-a<x_0)\,] \;y:=x+y;\; [\,i\and(b-a<x_0)\,]$	$_{AS}$

   $[\,i\and (a<b)\and (b-a=x_0)\,]\;a := a + 1;\;y := x + y;\;[\,i\and (b-a<x_0)\,]$	$_{SC}$

   $i \and (a<b)\;⇒\; b-a ≥ 0$

   $[\,i\,]\; \pmb{while}\; a < b \; \pmb{do}\; (a := a + 1;\; y := x + y;)\;[\,i\and\neg(a<b)\,]$	$_{WHT}$

   $i\and\neg(a<b) \;⇒\; y=x*b$

   Let the loop invariant $i$ be $y=x*a \and a≤b$ to satisfy the above derivation

   Also consider the case where while does not execute at all, then $y = x*b$

   The weakest assertion is  $(y=x*a \and a≤b) \or y=x*b$.

   

   $\pmb{while\;true\;do\;skip}$ changes nothing in the state, it also does not terminate,

   so it is impossible to find a non-negative metric that decreases on each iteration

   We simply put down  $\pmb{false}$  for the weakest assertion.

   

   $\left\{\, i\and \pmb{true}\,\right\}\;\pmb{skip}\;\left\{\,i\,\right\}$

   $i\and \pmb{false}\;⇒\;\pmb{false}$

   $\left\{\,i\,\right\}\;\pmb{while\;true\;do\;skip}\;\left\{\,i \and \neg\pmb{true}\,\right\}$

   We simply put down  $\pmb{true}$  for the weakest assertion.



2. The loop invariant is  $(x=y\and x≤100)\or x=0$.

   Actually  $x=y\and x≤100$  is the “real"  $i$, however  $x=0$  does not satisfy it.

   $\left\{\,x+1≤100\,\right\}\;x:=x+1;\;\left\{\,x≤100\,\right\}$	$_{AS}$

   $((x=y\and x≤100)\or x=0)\and x < 100 \;⇒\; x+1≤100$

   $\left\{\,((x=y\and x≤100)\or x=0)\and x < 100\,\right\} \;x:=x+1;\; \left\{\,x≤100\,\right\}$	$_{SP}$

   $\left\{\,x=x\and x≤100\,\right\}\;y=x;\;\left\{\,x=y\and x≤100\,\right\}$	$_{AS}$

   $x≤100\;⇒\;x=x\and x≤100$

   $\left\{x≤100\,\right\}\;y=x;\;\left\{\,x=y\and x≤100\,\right\}$	$_{SP}$

   $x=y\and x≤100 \;⇒\;(x=y\and x≤100)\or x=0$

   $\left\{x≤100\,\right\}\;y=x;\;\left\{\,(x=y\and x≤100)\or x=0\,\right\}$	$_{WC}$

   $\left\{\,((x=y\and x≤100)\or x=0)\and x < 100\,\right\} \;x:=x+1;\;y:=x;$

   ​		$\left\{\,(x=y\and x≤100)\or x=0\,\right\}$	$_{SC}$

   $\left\{\,(x=y\and x≤100)\or x=0\,\right\} \;\pmb{while}\;x<100 \;\pmb{do}\;(x:=x+1;\;y:=x;)$

   ​		$\left\{\,((x=y\and x≤100)\or x=0)\and \neg (x<100)\,\right\}$	$_{WHT}$

   $x=0 \;⇒\; (x=y\and x≤100)\or x=0$

   $\left\{\, x=0\,\right\} \;\pmb{while}\;x<100 \;\pmb{do}\;(x:=x+1;\;y:=x;)$

   ​		$\left\{\,((x=y\and x≤100)\or x=0)\and \neg (x<100)\,\right\}$	$_{SP}$

   $((x=y\and x≤100)\or x=0)\and \neg (x<100) \;⇒\; x=100\and y=100$

   $\left\{\, x=0\,\right\} \;\pmb{while}\;x<100 \;\pmb{do}\;(x:=x+1;\;y:=x;)\;\left\{\,x=100\and y=100\,\right\}$	$_{WC}$



3. (a) i. $\left\{\,\pmb{true}\,\right\}\;x:=x+1;\;\left\{\,x=x+1\,\right\}$

   ​		the precondition of the triple "$\pmb{true}$" always holds,

   ​		the program as a single assignment command always terminates,

   ​		however the postcondition "$x=x+1$" makes no sense logically.

   ​		If we try to apply the assignment rule to this triple we may get:

   ​		$\left\{\,x+1=x+1+1\,\right\}\;x:=x+1;\;\left\{\,x=x+1\,\right\}$

   ​		but there is no such thing as  $\pmb{true} \;⇒\; x+1=x+2$.

   

   ​     ii. The condition that supports  $\left\{\,\pmb{true}\,\right\}\;x:=e;\;\left\{\,x=e\,\right\}$  is  $e[e/x] = e$,

   ​		that is to say, either  $x$  does not occur in  $e$  at all, or  $e=x$.

   ​		We then have  $\left\{\,e=e\,\right\}\;x:=e;\;\left\{\,x=e\,\right\}$	$_{AS}$

   ​		$\pmb{true} \;⇒\; e=e$

   ​		$\left\{\,\pmb{true}\,\right\}\;x:=e;\;\left\{\,x=e\,\right\}$	$_{SP}$

   

   (b) $[\,\pmb{true}\,] \;\pmb{while\;true\;do\;skip}\; [\,\pmb{true}\,]$

   ​	The triple cannot be proved simply because the program does not terminate.



4. The partial correctness Hoare logic rule for $\pmb{repeat}\;c\;\pmb{until}\;b$ is

   #### $\left\{p\right\}\,c\,\left\{i\right\}\;\;\left\{i\and\neg b\right\}\,c\,\left\{i\right\} \over \;\left\{p\right\}\,\pmb{repeat}\;c\;\pmb{until}\;b\,\left\{i\and b\right\}\;$

