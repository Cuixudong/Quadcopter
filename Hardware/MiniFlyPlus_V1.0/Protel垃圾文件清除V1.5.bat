::PROTEL垃圾文件删除器 
::正点原子制作
::论坛:www.openedv.com 

::版本 V1.5  20220324更新
::1, 新增删除.htm文件
::2, 新增删除.html文件

::版本 V1.4  20120914更新

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
::删除当前目录下的所有History文件夹
for /r /d %%b in (Project?Logs?for*) do rd "%%b" /s /q 
::删除当前目录下的所有带字符串Project Logs for的文件夹
for /r /d %%b in (Project?Outputs?for*) do rd "%%b" /s /q   
::删除当前目录下的所有带字符串Project Outputs for的文件夹
exit
