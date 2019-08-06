autocmd TextChanged,TextChangedI <buffer> silent write
set nonumber

highlight RED cterm=bold term=bold ctermbg=red ctermfg=red
syntax match RED /1/

highlight GREEN cterm=bold term=bold ctermbg=green ctermfg=green
syntax match GREEN /2/

highlight YELLOW cterm=bold term=bold ctermbg=yellow ctermfg=yellow
syntax match YELLOW /3/

highlight BLUE cterm=bold term=bold ctermbg=blue ctermfg=blue
syntax match BLUE /4/

highlight MAGENTA cterm=bold term=bold ctermbg=magenta ctermfg=magenta
syntax match MAGENTA /5/

highlight CYAN cterm=bold term=bold ctermbg=cyan ctermfg=cyan
syntax match CYAN /6/

highlight WHITE cterm=bold term=bold ctermbg=white ctermfg=white
syntax match WHITE /7/

" Preservation of self..
map [ :prev<CR>:source scripts/bmp-edit.vim<CR>
map ] :next<CR>:source scripts/bmp-edit.vim<CR>

set colorcolumn=0