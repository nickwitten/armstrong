let SessionLoad = 1
if &cp | set nocp | endif
let s:so_save = &g:so | let s:siso_save = &g:siso | setg so=0 siso=0 | setl so=-1 siso=-1
let v:this_session=expand("<sfile>:p")
let NERDTreeMapPreviewSplit = "gi"
let NERDTreeMapCloseChildren = "X"
let NERDTreeShowHidden =  0 
let NERDTreeMapCloseDir = "x"
let NERDTreeSortHiddenFirst =  1 
let NERDTreeMinimalUI =  0 
let NERDTreeShowLineNumbers =  0 
let NERDTreeRespectWildIgnore =  0 
let NERDTreeAutoDeleteBuffer =  0 
let NERDTreeBookmarksFile = "C:\\Users\\nwitt/.NERDTreeBookmarks"
let NERDTreeMapToggleHidden = "I"
let NERDTreeWinSize =  31 
let NERDTreeMenuUp = "k"
let NERDTreeSortDirs =  1 
let NERDTreeBookmarksSort =  1 
let NERDTreeUseTCD =  0 
let NERDTreeMapPreview = "go"
let NERDTreeCascadeSingleChildDir =  1 
let NERDTreeNotificationThreshold =  100 
let NERDTreeMapActivateNode = "o"
let NERDTreeQuitOnOpen =  0 
let NERDTreeMapCustomOpen = "<CR>"
let NERDTreeWinPos = "left"
let NERDTreeDirArrowExpandable = "+"
let NERDTreeMapMenu = "m"
let NERDTreeStatusline = "%{exists('b:NERDTree')?b:NERDTree.root.path.str():''}"
let NERDTreeMapOpenInTabSilent = "T"
let NERDTreeMapHelp = "?"
let NERDTreeMapJumpParent = "p"
let NERDTreeMapToggleFilters = "f"
let NERDTreeMapJumpPrevSibling = "<C-k>"
let NERDTreeNodeDelimiter = ""
let NERDTreeShowBookmarks =  1 
let NERDTreeRemoveDirCmd = "rmdir /s /q "
let NERDTreeMapOpenInTab = "t"
let NERDTreeCopyFileCmd = "copy /y "
let NERDTreeChDirMode =  0 
let RunCMD = "wsl make; cp BUILD\\mbed.bin D:\\;"
let NERDTreeAutoCenterThreshold =  3 
let NERDTreeShowFiles =  1 
let NERDTreeMapOpenSplit = "i"
let NERDTreeHijackNetrw =  1 
let NERDTreeMapRefresh = "r"
let NERDTreeHighlightCursorline =  1 
let NERDTreeMouseMode =  1 
let NERDTreeMapCWD = "CD"
let NERDTreeNaturalSort =  0 
let NERDTreeMenuDown = "j"
let NERDTreeMapPreviewVSplit = "gs"
let NERDTreeMapUpdir = "u"
let NERDTreeMapJumpRoot = "P"
let NERDTreeGlyphReadOnly = "RO"
let NERDTreeMapChdir = "cd"
let NERDTreeCreatePrefix = "silent"
let NERDTreeMapToggleZoom = "A"
let NERDTreeMarkBookmarks =  1 
let NERDTreeMinimalMenu =  0 
let NERDTreeMapRefreshRoot = "R"
let NERDTreeAutoCenter =  1 
let NERDTreeCascadeOpenSingleChildDir =  1 
let NERDTreeMapOpenVSplit = "s"
let NERDTreeMapJumpLastChild = "J"
let NERDTreeMapDeleteBookmark = "D"
let NERDTreeMapJumpNextSibling = "<C-j>"
let NERDTreeMapQuit = "q"
let NERDTreeMapChangeRoot = "C"
let NERDTreeMapToggleFiles = "F"
let NERDTreeMapOpenExpl = "e"
let NERDTreeMapJumpFirstChild = "K"
let NERDTreeDirArrowCollapsible = "~"
let NERDTreeCopyDirCmd = "xcopy /s /e /i /y /q "
let NERDTreeMapOpenRecursively = "O"
let NERDTreeMapToggleBookmarks = "B"
let SerialArgs = "COM3 9600"
let NERDTreeMapUpdirKeepOpen = "U"
let NERDTreeCaseSensitiveSort =  0 
silent only
silent tabonly
cd ~\workspace\mbed
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
set shortmess=aoO
argglobal
%argdel
set stal=2
tabnew
tabrewind
edit source\robot.h
argglobal
balt source\rtos_blink.h
setlocal fdm=indent
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=3
setlocal fml=1
setlocal fdn=20
setlocal fen
let s:l = 14 - ((13 * winheight(0) + 25) / 50)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 14
normal! 022|
tabnext
edit main.cpp
argglobal
balt source\serial_lcd.h
setlocal fdm=indent
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
let s:l = 1 - ((0 * winheight(0) + 25) / 50)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 1
normal! 025|
tabnext 2
set stal=1
badd +1 source\rtos_blink.h
badd +0 main.cpp
badd +17 source\serial_lcd.h
badd +50 .\mbed\Serial.h
badd +1 examples\serial_loopback.h
badd +60 Makefile
badd +8 examples\lcd.h
badd +1 source\serial_loopback.h
badd +8 examples\lcd_template.cpp
badd +5 examples\rtos_template.cpp
badd +5 examples\sd_template.cpp
badd +7 examples\wave_template.cpp
badd +5 examples\wave_player.h
badd +217 .\4DGL-uLCD-SE\uLCD_4DGL.h
badd +114 .\mbed\SerialBase.h
badd +1 ~\config\.vimrc
badd +1 ~\_vimrc
badd +1 ~\config\profile.ps1
badd +67 ~\config\setup.ps1
badd +22 ~\config\setup.sh
badd +46 mbed\Stream.h
badd +0 source\robot.h
if exists('s:wipebuf') && len(win_findbuf(s:wipebuf)) == 0
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20 shortmess=filnxtToOS
let s:sx = expand("<sfile>:p:r")."x.vim"
if filereadable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &g:so = s:so_save | let &g:siso = s:siso_save
nohlsearch
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
