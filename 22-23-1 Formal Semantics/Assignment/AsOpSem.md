### 191220154 AsOpSem



1. Let $c_1$ be $x := \pmb 0$, $c_2$ be $\pmb {while \; true \; do} \; x := x + \pmb 1$, for any $σ$ there is 

   ​	$(c_1; c_2, σ) = (x := \pmb 0; \pmb {while \; true \; do} \; x := x + \pmb 1, σ)$

   $\rightarrow \, (\pmb {skip}; \pmb {while \; true \; do} \; x := x + \pmb 1, σ\left\{ x \rightsquigarrow 0\right\})$

   $\rightarrow \, (\pmb {while \; true \; do} \; x := x + \pmb 1, σ\left\{ x \rightsquigarrow 0\right\})$

   $\rightarrow \, (\pmb {if \; true \; then} \; (x := x + \pmb 1; \pmb {while \; true \; do} \; x := x + \pmb 1) \; \pmb {else} \; \pmb {skip}, σ\left\{ x \rightsquigarrow 0\right\})$

   $\rightarrow \, (x := x + \pmb 1; \pmb {while \; true \; do} \; x := x + \pmb 1, σ\left\{ x \rightsquigarrow 0\right\})$

   $\rightarrow^* \, (\pmb {skip}; \pmb {while \; true \; do} \; x := x + \pmb 1, σ\left\{ x \rightsquigarrow 1\right\})$

   $\rightarrow \, (\pmb {while \; true \; do} \; x := x + \pmb 1, σ\left\{ x \rightsquigarrow 1\right\})$

   There exists $σ' = σ\left\{ x \rightsquigarrow 1\right\}$ so that $(c_1; c_2, σ) \, \rightarrow^* \, (c_2, σ')$. However,

   ​	$(c_1, σ) = (x := \pmb 0, σ) \, \rightarrow \, (\pmb {skip}, σ\left\{ x \rightsquigarrow 0\right\})$

   $(\pmb {skip}, σ\left\{ x \rightsquigarrow 0\right\}) \, \nrightarrow^* \, (\pmb {skip}, σ\left\{ x \rightsquigarrow 1\right\})$, thus $(c_1, σ) \, \nrightarrow^* \, (\pmb {skip}, σ')$



2.  (a)  the small-step operational semantics rule for ++x

   ### 	$σ(x) \, = \, ⌊\pmb n⌋ \;\;\;\; ⌊\pmb n'⌋ \, = \, ⌊\pmb n⌋ \, + \, 1 \over (+ + x, \, σ) \, \rightarrow \, (\pmb n', \, σ\left\{ x \, \rightsquigarrow \, ⌊\pmb n⌋ \, + \, 1\right\})$

   

   (b) the full execution path for the program

   ​	$(\pmb {while} \; x < \pmb 7 \; \pmb {do} \; x := (x++) + (++x), \left\{ x \rightsquigarrow 6\right\})$

   $\rightarrow \, (\pmb {if} \; x < \pmb 7 \; \pmb {do} \; (x := (x++) + (++x);$

   ​		$\pmb {while} \; x < \pmb 7 \; \pmb {do} \; x := (x++) + (++x)) \; \pmb {else \; skip}, \left\{ x \rightsquigarrow 6\right\})$

   $\rightarrow \, (\pmb {if} \; \pmb 6 < \pmb 7 \; \pmb {do} \; (x := (x++) + (++x);$

   ​		$\pmb {while} \; x < \pmb 7 \; \pmb {do} \; x := (x++) + (++x)) \; \pmb {else \; skip}, \left\{ x \rightsquigarrow 6\right\})$

   $\rightarrow \, (\pmb {if \; true} \; \pmb {do} \; (x := (x++) + (++x);$

   ​		$\pmb {while} \; x < \pmb 7 \; \pmb {do} \; x := (x++) + (++x)) \; \pmb {else \; skip}, \left\{ x \rightsquigarrow 6\right\})$

   $\rightarrow \, (x := (x++) + (++x); \pmb {while} \; x < \pmb 7 \; \pmb {do} \; x := (x++) + (++x), \left\{ x \rightsquigarrow 6\right\})$

   $\rightarrow \, (x := \pmb 6 + (++x); \pmb {while} \; x < \pmb 7 \; \pmb {do} \; x := (x++) + (++x), \left\{ x \rightsquigarrow 7\right\})$

   $\rightarrow \, (x := \pmb 6 + \pmb 8; \pmb {while} \; x < \pmb 7 \; \pmb {do} \; x := (x++) + (++x), \left\{ x \rightsquigarrow 8\right\})$

   $\rightarrow \, (x := \pmb {14}; \pmb {while} \; x < \pmb 7 \; \pmb {do} \; x := (x++) + (++x), \left\{ x \rightsquigarrow 8\right\})$

   $\rightarrow \, (\pmb {skip};\pmb{while} \; x < \pmb 7 \; \pmb {do} \; x := (x++) + (++x), \left\{ x \rightsquigarrow 14\right\})$

   $\rightarrow \, (\pmb {while} \; x < \pmb 7 \; \pmb {do} \; x := (x++) + (++x), \left\{ x \rightsquigarrow 14\right\})$

   $\rightarrow \, (\pmb {if} \; x < \pmb 7 \; \pmb {do} \; (x := (x++) + (++x);$

   ​		$\pmb {while} \; x < \pmb 7 \; \pmb {do} \; x := (x++) + (++x)) \; \pmb {else \; skip}, \left\{ x \rightsquigarrow 14\right\})$

   $\rightarrow \, (\pmb {if} \; \pmb {14} < \pmb 7 \; \pmb {do} \; (x := (x++) + (++x);$

   ​		$\pmb {while} \; x < \pmb 7 \; \pmb {do} \; x := (x++) + (++x)) \; \pmb {else \; skip}, \left\{ x \rightsquigarrow 14\right\})$

   $\rightarrow \, (\pmb {if} \; \pmb {false \; do} \; (x := (x++) + (++x);$

   ​		$\pmb {while} \; x < \pmb 7 \; \pmb {do} \; x := (x++) + (++x)) \; \pmb {else \; skip}, \left\{ x \rightsquigarrow 14\right\})$

   $\rightarrow \, (\pmb {skip}, \left\{ x \rightsquigarrow 14\right\})$



3. (a) small-step operational semantics rules for the new expression

   ### 	$(c, σ) \, \rightarrow \, (c', σ') \over (\pmb {do} \; c \; \pmb {return} \; e, σ) \, \rightarrow \, (\pmb {do} \; c' \; \pmb {return} \; e, σ')$

   ### 	$\over (\pmb {do \; skip \; return} \; e, σ) → (e, σ)$

   

   (b) For each of the following properties, does it hold?

   ​		i. $∀e_1, e_2. \, (e_1 + e_2) ≺ (e_1 + e_2 + \pmb1)$

   ​			Yes.

   ​		ii. $∀e_1, e_2. \, (e_1 + e_2) ≺ (e_2 + e_1 + \pmb1)$

   ​			No. let $e_1$ be $x$, $e_2$ be $\pmb {do} \; x := x - \pmb2 \; \pmb {return} \; y$

   ​			for any given $σ$, let $\pmb{n_1'} = σ(x)$, $\pmb {n_2'} = σ(y)$, $⌊\pmb {n_3'}⌋ \, = \, ⌊\pmb {n_1'}⌋ \, - \, 2$

   ​				$(e_1 + e_2, σ)$

   ​			$\rightarrow \, (\pmb{n_1'} + e_2, σ)$

   ​			$\rightarrow \, (\pmb{n_1'} + \pmb{n_2'}, σ\left\{ x \rightsquigarrow n_3'\right\})$

   ​				$(e_2 + e_1 + \pmb1, σ)$

   ​			$\rightarrow \, (\pmb{n_2'} + e_1 + \pmb1, σ\left\{ x \rightsquigarrow n_3'\right\})$

   ​			$\rightarrow \, (\pmb{n_2'} + \pmb{n_3'} + \pmb1, σ\left\{ x \rightsquigarrow n_3'\right\})$

   ​			so we have $(e_1 + e_2, σ) \, \rightarrow^* \, (\pmb{n1},σ_1)$, $(e_2 + e_1 + 1, σ) \, \rightarrow^* \, (\pmb{n2},σ_2)$

   ​			where $⌊\pmb {n_1}⌋ = ⌊\pmb {n_1'}⌋ + ⌊\pmb {n_2'}⌋$, $⌊\pmb {n_2}⌋ = ⌊\pmb {n_2'}⌋ + ⌊\pmb {n_3'}⌋ + 1 = \, ⌊\pmb {n_1'}⌋ + ⌊\pmb {n_2'}⌋ - 1$

   ​			$⌊\pmb {n_1}⌋ > ⌊\pmb {n_2}⌋$, thus $(e_1 + e_2) ≺ (e_2 + e_1 + \pmb1)$ does not stand

   ​		iii. $∀e. \, ¬(e ≺ e)$

   ​			No. let $e$ be $\pmb {do} \; (\pmb {while \; true \; do \; skip}) \; \pmb {return \; 0}$

   ​			there exists no $\pmb {n_1}$, $σ_1$ or $\pmb {n_2}$, $σ_2$ so that $(e, σ) \, \rightarrow^* \, (\pmb{n_1}, σ_1)$, $(e, σ) \, \rightarrow^* \, (\pmb{n_2}, σ_2)$

   ​			as the program loops forever, thus we can say $(e ≺ e)$

   ​		iv. $∀e_1, e_2, e_3. \, (e_1 ≺ e_2) ∧ (e_2 ≺ e_3) ⇒ (e_1 ≺ e_3)$

   ​			No. let $e_1$ be $\pmb1$, $e2$ be $\pmb {do} \; (\pmb {while \; true \; do \; skip}) \; \pmb {return \; 0}$, $e3$ be $\pmb0$

   ​			there exists no $\pmb {n_2}$, $σ_2$ so that $(e_2, σ) \, \rightarrow^* \, (\pmb{n_2}, σ_2)$

   ​			thus we can say $(e_1 ≺ e_2)$ and $(e_2 ≺ e_3)$

   ​			however, because $(e_1, σ) \, \rightarrow^* \, (\pmb{1}, σ)$ and $(e_3, σ) \, \rightarrow^* \, (\pmb{0}, σ)$
   
   ​			we have $⌊\pmb 1⌋ > ⌊\pmb 0⌋$, thus $(e_1 ≺ e_3)$ does not stand
