mkdir ~/.vim/bundle/ncknge-kbm
mkdir ~/.vim/bundle/ncknge-kbm/ftplugin
cp kbm-ext.vim ~/.vim/bundle/ncknge-kbm/ftplugin

mkdir ~/.vim/bundle/ncknge-kbm/ftdetect
echo "autocmd BufNewFile,BufRead *.kbm setf kbm" > ~/.vim/bundle/ncknge-kbm/ftdetect/ncknge-kbm
