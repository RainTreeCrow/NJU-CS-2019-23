### 191220154 AsLambda



1. $(λf. λx. f (f \, x))(λb. λx. λy. b \, y \, x) (λz. λw. z)$

   

   (a) the normal order reduction sequence

   $(λf. λx. f (f \, x))(λb. λx. λy. b \, y \, x) (λz. λw. z)$

   $\rightarrow \, (\lambda x.(λb. λx. λy. b \, y \, x)((λb. λx. λy. b \, y \, x) \, x))) (λz. λw. z)$

   $\rightarrow \, (λb. λx. λy. b \, y \, x)((λb. λx. λy. b \, y \, x) (λz. λw. z))$

   $\rightarrow \, λx. λy. ((λb. λx. λy. b \, y \, x) (λz. λw. z)) \, y \, x$	*

   $\rightarrow \, λx. λy. (λx. λy. (λz. λw. z) \, y \, x) \, y \, x$

   $\rightarrow \, λx. λy. (λu. (λz. λw. z) \, u \, y) \, x$

   $\rightarrow \, λx. λy. ((λz. λw. z) \, x \, y)$

   $\rightarrow \, λx. λy. ((λw. x) \, y)$

   $\rightarrow \, λx. λy. x$

   

   (b) the first canonical form is reached at mark *

   $\rightarrow \, λx. λy. ((λb. λx. λy. b \, y \, x) (λz. λw. z)) \, y \, x$

   

   (c) the eager evaluation sequence

   $(λf. λx. f (f \, x))(λb. λx. λy. b \, y \, x) (λz. λw. z)$

   ​		$(λf. λx. f (f \, x))(λb. λx. λy. b \, y \, x)$

   ​				$λf. λx. f (f \, x) \, \Rightarrow_E \, λf. λx. f (f \, x)$

   ​				$λb. λx. λy. b \, y \, x \, \Rightarrow_E \, λb. λx. λy. b \, y \, x$

   ​				$\lambda x.(λb. λx. λy. b \, y \, x)((λb. λx. λy. b \, y \, x) \, x))$

   ​				$\Rightarrow_E \, \lambda x.(λb. λx. λy. b \, y \, x)((λb. λx. λy. b \, y \, x) \, x))$

   ​		$\Rightarrow_E \, \lambda x.(λb. λx. λy. b \, y \, x)((λb. λx. λy. b \, y \, x) \, x))$

   ​		$λz. λw. z \, \Rightarrow_E \, λz. λw. z$

   ​		$(λb. λx. λy. b \, y \, x)((λb. λx. λy. b \, y \, x) \, (λz. λw. z))$

   ​				$λb. λx. λy. b \, y \, x \, \Rightarrow_E \, λb. λx. λy. b \, y \, x$

   ​				$(λb. λx. λy. b \, y \, x) \, (λz. λw. z)$

   ​						$λb. λx. λy. b \, y \, x \, \Rightarrow_E \, λb. λx. λy. b \, y \, x$

   ​						$λz. λw. z \, \Rightarrow_E \, λz. λw. z$

   ​						$λx. λy. (λz. λw. z) \, y \, x \, \Rightarrow_E \, λx. λy. (λz. λw. z) \, y \, x$

   ​				$\Rightarrow_E \, λx. λy. (λz. λw. z) \, y \, x$

   ​				$λx. λy. (λx. λy. (λz. λw. z) \, y \, x) \, y \, x$

   ​				$\Rightarrow_E \, λx. λy. (λx. λy. (λz. λw. z) \, y \, x) \, y \, x$

   ​		$\Rightarrow_E \, λx. λy. (λx. λy. (λz. λw. z) \, y \, x) \, y \, x$

   ​	$\Rightarrow_E \, λx. λy. (λx. λy. (λz. λw. z) \, y \, x) \, y \, x$

   

   $(λf. f \, f) (λf. λx. f \, (f \, x))$

   

   (a) the normal order reduction sequence

   $(λf. f \, f) (λf. λx. f \, (f \, x))$

   $\rightarrow \, (λf. λx. f \, (f \, x)) (λf. λx. f \, (f \, x))$

   $\rightarrow \, λy. (λf. λx. f \, (f \, x)) ((λf. λx. f \, (f \, x)) \, y)$	*

   $\rightarrow \, λy. λz. ((λf. λx. f \, (f \, x)) \, y) (((λf. λx. f \, (f \, x)) \, y) \, z)$

   $\rightarrow \, λy. λz. (λx. y \, (y \, x)) (((λf. λx. f \, (f \, x)) \, y) \, z)$

   $\rightarrow \, λy. λz. y \, (y \, (((λf. λx. f \, (f \, x)) \, y) \, z))$

   $\rightarrow \, λy. λz. y \, (y \, ((λx. y \, (y \, x)) \, z))$

   $\rightarrow \, λy. λz. y \, (y \, (y \, (y \, z)))$

   

   (b) the first canonical form is reached at mark *

   $\rightarrow \, λy. (λf. λx. f \, (f \, x)) ((λf. λx. f \, (f \, x)) \, y)$

   

   (c) the eager evaluation sequence

   $(λf. f \, f) (λf. λx. f \, (f \, x))$

   ​		$λf. f \, f \, \Rightarrow_E \, λf. f \, f$

   ​		$λf. λx. f \, (f \, x) \, \Rightarrow_E \, λf. λx. f \, (f \, x)$

   ​		$(λf. λx. f \, (f \, x)) (λf. λx. f \, (f \, x))$

   ​				$λf. λx. f \, (f \, x) \, \Rightarrow_E \, λf. λx. f \, (f \, x)$

   ​				$λf. λx. f \, (f \, x) \, \Rightarrow_E \, λf. λx. f \, (f \, x)$

   ​		$λy. (λf. λx. f \, (f \, x)) ((λf. λx. f \, (f \, x)) \, y)$

   ​		$\Rightarrow \, λy. (λf. λx. f \, (f \, x)) ((λf. λx. f \, (f \, x)) \, y)$

   $\Rightarrow \, λy. (λf. λx. f \, (f \, x)) ((λf. λx. f \, (f \, x)) \, y)$



2. (a) 3 new typing rules, one for each new form of term

   ### ${} \over { Γ \, ⊢ \, None \, : \, option \, τ }$		${Γ \, ⊢ \, M \, : \, τ} \over {Γ \, ⊢ \, Some \, M \, : \, option \, τ }$		${Γ \, ⊢ \, M \, : \, option \, τ} \over {Γ \, ⊢ \, get \, M \, : \, τ}$

   

   (b) consider preservation and progress theorem for each case

   ​		i. remove the ($GET-M$) rule

   ​				Preservation yes, progress no.

   ​				For example, for $Γ ⊢ y : τ $ ,  $Γ ⊢ get \, ((\lambda x:τ.Some \, x)y) : τ$

   ​				however, without $GET-M$, lambda reduction inside $get()$ is not allowed.

   ​		ii. remove both the ($SOME$) rule and the ($GET-M$) rule

   ​				Preservation yes, progress no.

   ​				Counterexample same as (i).

   ​		iii. add the rule ($GET-V$)

   ​				Preservation yes, progress yes.

   ​		iv. change the ($GET-SOME$) rule to ($GET-SOME'$)

   ​				Preservation yes, progress yes.

   ​		v. change the ($GET-SOME$) rule to ($GET-SOME''$)

   ​				Preservation no, progress yes.

   ​				For example, for $Γ ⊢ x : τ$, $Γ ⊢ get \, (Some \, x) : τ$

   ​				however, $Some \, (get \, x)$ will not have the same type $τ$.

   ​		vi. change the above ($GET-NONE$) rule to ($GET-NONE'$)

   ​				Preservation no, progress yes.

   ​				For example, suppose $None$ has a type $σ$ (whatever that is)

   ​				cosider $get \, (None) \, \rightarrow \, None$, $get \, (None)$ should have exactly the same type

   ​				however, for $get \, (None) : σ $, $None$ should have $option \, σ$

   ​				there is no way $σ$ and $option \, σ$ could be the same type.
