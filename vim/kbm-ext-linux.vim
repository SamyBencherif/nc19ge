" continuous auto-save, for quick preview in ncknge
"autocmd TextChanged,TextChangedI <buffer> silent write

" nothing linux specific, just considerations for system which are
" truly 8 color

set nonumber
set colorcolumn=0
set nowrap
set list
set ruler
set virtualedit=insert

highlight RED cterm=bold term=bold ctermbg=red
syntax match RED /1/

highlight GREEN cterm=bold term=bold ctermbg=green
syntax match GREEN /2/

highlight YELLOW cterm=bold term=bold ctermbg=yellow
syntax match YELLOW /3/

highlight BLUE cterm=bold term=bold ctermbg=blue
syntax match BLUE /4/

highlight MAGENTA cterm=bold term=bold ctermbg=magenta
syntax match MAGENTA /5/

highlight CYAN cterm=bold term=bold ctermbg=cyan
syntax match CYAN /6/

highlight WHITE cterm=bold term=bold ctermbg=white ctermfg=black
syntax match WHITE /7/

highlight BLACK cterm=bold term=bold ctermbg=black
syntax match BLACK /0/

" Preservation of self..
" TODO: need a solution that is more applicable to others
" map [ :prev<CR>:source ~/workspace/ncknge/vim/bmp-edit.vim<CR>
" map ] :next<CR>:source ~/workspace/ncknge/vim/bmp-edit.vim<CR>

