@echo off
setlocal
set _VERPATCH_=Dev_Test_2
echo "%_VERPATCH_%" > .\np3portableapp\_buildname.txt
Version -VerPatch "%_VERPATCH_%"
endlocal
