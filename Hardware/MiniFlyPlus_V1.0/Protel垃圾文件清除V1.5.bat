::PROTEL垃圾文件删除器 

del *.SchDocPreview /s
del *.PcbDocPreview /s 
del *.pcbPreview /s 
del *.PrjPCBStructure /s 
del *.drc /s
del *.LOG /s 
del *.OutJob /s 
del *.htm /s
del *.html /s
for /r /d %%b in (History) do rd "%%b" /s /q 
for /r /d %%b in (Project?Logs?for*) do rd "%%b" /s /q 
for /r /d %%b in (Project?Outputs?for*) do rd "%%b" /s /q 
exit
