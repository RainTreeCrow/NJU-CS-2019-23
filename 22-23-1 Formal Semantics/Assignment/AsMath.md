### 191220154 AsMath



1. False. Let $f = \lambda x \in \pmb N. x + 1$, $\emptyset \in \mathcal{P}(f) $ and $\{(0,1)\} \in \mathcal{P}(f)$. If  there exists $(A \subseteq \pmb N)$ and $(B \subseteq \pmb N)$ that satisfy $\mathcal{P}(f) \subseteq A \rightarrow B$, there  must be $\emptyset \in A \rightarrow B$ and $\{(0,1)\} \in A \rightarrow B$. Consider $A  \rightarrow B$  represent the set of all *total* functions from $A$ to $B$, $dom(A \rightarrow B) = A$, $A = \emptyset$ and $A = \{0\}$ cannot both be true, thus such $A$, $B$ do not exist. In fact, for any $f \neq \emptyset$, such $A$ and $B$ cannot be found.



2. False. Suppose for $f$ there is $f(0) = 42$, for $h$ there is $h(1) = 42$, and for $g$, there exists no such $y$ so that $g(y) = 42$, so for $f$ and $g$, $\forall x, y. (f(x) = 42) \and (g(y) = 42) \Longrightarrow (x = y)$, thus $f \bowtie g$, for $g$ and $h$, $\forall x, y. (g(x) = 42) \and (h(y) = 42) \Longrightarrow (x = y)$, thus $g \bowtie h$, but for $f$ and $h$, there exists $f(0) = 42$ and $h(1) = 42$, let $x = 0$ and $y = 1$, $x \neq y$, thus $f \bowtie h$ is not true.



3. False. Consider $H$ being the set of all functions from $S$ to $\pmb N$ where $S$ is a finite subset of $\pmb N$, let $h_1 = \{(0, 0)\}$ and $h_2 = \{(0, 1)\}$, so that $(h_1 \in H)$ and $(h_2 \in H)$,  however$(h_1 \cup h_2) = \{(0, 0), (0, 1)\}$ is not even a function, thus $(h_1 \cup h_2) \notin H$.



4. True. Consider any $h \in H$, for any $x$, $hclosed(h(x \leadsto 42))$ implies $closed(dom(h) \cup \{x\}, h(x \leadsto 42)$, that is to say, $\forall l, l'. (l \in dom(h) \cup \{x\}) \and (l' = h\{x \leadsto 42\}(l)) \Longrightarrow l' \in dom(h) \cup \{x\}$. If $hclosed(h)$ is not true, there exist $h_0$, $l_0$, $l_0'$ so that $l_0 \in dom(h_0)$, $l_0' = h_0(l_0)$ and $l_0' \notin dom(h_0)$. Suppose this $l_0' = 42$, that is to say, $42 \notin dom(h_0)$, let $l = x$ and $l' = h_0\{x \leadsto 42\}(x) = 42$,  $l' \in dom(h_0) \cup \{x\}$ is not true for any $x$ but only when $x = 42$. Suppose this $l_0' \neq 42$, let $l = l_0$ and $l' = h\{x \leadsto 42\}(x) = l_0'$, $l' \in dom(h) \cup \{x\}$ is only true when $x = l_0'$. Either ways such $h_0$, $l_0$, $l_0'$ do not exist, so $hclosed(h)$.
