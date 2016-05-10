set nu si mouse=a sw=4 ts=4 sts=4
set mp=g++\ -O2\ -Wall\ --std=c++11\ -Wno-unused-result\ %:r.cpp\ -o\ %:r
nmap <F2> :vs %:r.in <CR>
nmap <F8> :!time ./%:r < %:r.in <CR>
nmap <F9> :w <CR> :make<CR>
