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
let NERDTreeAutoCenterThreshold =  3 
let NERDTreeShowFiles =  1 
let NERDTreeMapOpenSplit = "i"
let NERDTreeCaseSensitiveSort =  0 
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
let NERDTreeMapUpdirKeepOpen = "U"
silent only
silent tabonly
cd ~\workspace\armstrong\Screen_Refresh
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
let s:shortmess_save = &shortmess
set shortmess=aoO
badd +43 Screen_Refresh.ino
badd +0 \Users\nwitt\workspace\armstrong\Clock\Clock.ino
badd +114 \Users\nwitt\Documents\Arduino\libraries\GFX_Library_for_Arduino\README.md
badd +20 \Users\nwitt\Documents\Arduino\libraries\GFX_Library_for_Arduino\src\canvas\Arduino_Canvas.h
badd +220 \Users\nwitt\Documents\Arduino\libraries\GFX_Library_for_Arduino\src\Arduino_GFX.h
badd +4 \Users\nwitt\Documents\Arduino\libraries\GFX_Library_for_Arduino\src\display\Arduino_GC9A01.cpp
badd +192 \Users\nwitt\Documents\Arduino\libraries\GFX_Library_for_Arduino\src\display\Arduino_GC9A01.h
badd +709 \Users\nwitt\Documents\Arduino\libraries\GFX_Library_for_Arduino\src\Arduino_TFT.cpp
badd +18 \Users\nwitt\Documents\Arduino\libraries\GFX_Library_for_Arduino\src\display\Arduino_GC9106.cpp
badd +61 \Users\nwitt\Documents\Arduino\libraries\GFX_Library_for_Arduino\src\databus\Arduino_AVRPAR8.cpp
badd +35 \Users\nwitt\Documents\Arduino\libraries\GFX_Library_for_Arduino\examples\Clock\Clock.ino
badd +27 \Users\nwitt\Documents\Arduino\libraries\GFX_Library_for_Arduino\src\databus\Arduino_HWSPI.cpp
badd +698 \Users\nwitt\Documents\Arduino\libraries\GFX_Library_for_Arduino\src\Arduino_GFX.cpp
badd +10 \Users\nwitt\Documents\Arduino\libraries\GFX_Library_for_Arduino\src\Arduino_DataBus.h
badd +0 \Users\nwitt\Documents\Arduino\libraries\GFX_Library_for_Arduino\examples\PDQgraphicstest\PDQgraphicstest.ino
badd +1 \Users\nwitt\Documents\Arduino\libraries\GFX_Library_for_Arduino\src\Arduino_G.h
badd +1 \Users\nwitt\Documents\Arduino\libraries\GFX_Library_for_Arduino\src\Arduino_G.cpp
argglobal
%argdel
set stal=2
tabnew +setlocal\ bufhidden=wipe
tabnew +setlocal\ bufhidden=wipe
tabnew +setlocal\ bufhidden=wipe
tabrewind
edit Screen_Refresh.ino
let s:save_splitbelow = &splitbelow
let s:save_splitright = &splitright
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
let &splitbelow = s:save_splitbelow
let &splitright = s:save_splitright
wincmd t
let s:save_winminheight = &winminheight
let s:save_winminwidth = &winminwidth
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe 'vert 1resize ' . ((&columns * 147 + 117) / 235)
exe 'vert 2resize ' . ((&columns * 87 + 117) / 235)
argglobal
balt \Users\nwitt\Documents\Arduino\libraries\GFX_Library_for_Arduino\src\Arduino_DataBus.h
setlocal fdm=indent
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=5
setlocal fml=1
setlocal fdn=20
setlocal fen
44
normal! zo
45
normal! zo
let s:l = 46 - ((14 * winheight(0) + 25) / 50)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 46
normal! 0127|
wincmd w
argglobal
if bufexists(fnamemodify("\Users\nwitt\Documents\Arduino\libraries\GFX_Library_for_Arduino\src\Arduino_GFX.cpp", ":p")) | buffer \Users\nwitt\Documents\Arduino\libraries\GFX_Library_for_Arduino\src\Arduino_GFX.cpp | else | edit \Users\nwitt\Documents\Arduino\libraries\GFX_Library_for_Arduino\src\Arduino_GFX.cpp | endif
balt Screen_Refresh.ino
setlocal fdm=indent
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=10
setlocal fml=1
setlocal fdn=20
setlocal fen
let s:l = 694 - ((31 * winheight(0) + 25) / 50)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 694
normal! 02|
wincmd w
exe 'vert 1resize ' . ((&columns * 147 + 117) / 235)
exe 'vert 2resize ' . ((&columns * 87 + 117) / 235)
tabnext
edit \Users\nwitt\Documents\Arduino\libraries\GFX_Library_for_Arduino\README.md
argglobal
balt \Users\nwitt\Documents\Arduino\libraries\GFX_Library_for_Arduino\src\Arduino_TFT.cpp
setlocal fdm=indent
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=1
setlocal fml=1
setlocal fdn=20
setlocal fen
let s:l = 145 - ((40 * winheight(0) + 25) / 50)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 145
normal! 0
tabnext
edit \Users\nwitt\Documents\Arduino\libraries\GFX_Library_for_Arduino\examples\PDQgraphicstest\PDQgraphicstest.ino
argglobal
setlocal fdm=indent
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=5
setlocal fml=1
setlocal fdn=20
setlocal fen
let s:l = 1069 - ((31 * winheight(0) + 25) / 50)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 1069
normal! 010|
tabnext
edit \Users\nwitt\workspace\armstrong\Clock\Clock.ino
argglobal
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
normal! 0
tabnext 4
set stal=1
if exists('s:wipebuf') && len(win_findbuf(s:wipebuf)) == 0
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20
let &shortmess = s:shortmess_save
let &winminheight = s:save_winminheight
let &winminwidth = s:save_winminwidth
let s:sx = expand("<sfile>:p:r")."x.vim"
if filereadable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &g:so = s:so_save | let &g:siso = s:siso_save
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
