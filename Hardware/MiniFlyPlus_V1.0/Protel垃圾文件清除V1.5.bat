::PROTEL�����ļ�ɾ���� 
::����ԭ������
::��̳:www.openedv.com 

::�汾 V1.5  20220324����
::1, ����ɾ��.htm�ļ�
::2, ����ɾ��.html�ļ�

::�汾 V1.4  20120914����

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
::ɾ����ǰĿ¼�µ�����History�ļ���
for /r /d %%b in (Project?Logs?for*) do rd "%%b" /s /q 
::ɾ����ǰĿ¼�µ����д��ַ���Project Logs for���ļ���
for /r /d %%b in (Project?Outputs?for*) do rd "%%b" /s /q   
::ɾ����ǰĿ¼�µ����д��ַ���Project Outputs for���ļ���
exit
