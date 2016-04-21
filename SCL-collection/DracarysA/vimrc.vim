\begin{lstlisting}
set nu ai ci si mouse=a ts=4 sts=4 sw=4

nmap<C-A> ggVG
vmap<C-C> "+y

nmap<F3> : vs %<.in <CR>
nmap<F4> : !gedit % <CR>
nmap<F5> : !./%< <CR>
nmap<F8> : !./%< < %<.in <CR>
nmap<F9> : make %< <CR>

"nmap<F9> :!export CXXFLAGS=-Wall && make %< <CR>
"autocmd BufNewFile *.cpp 0r ~/temp.cpp
"set hlsearch incseach

"syntax on
"filetype plugin indent on
\end{lstlisting}