@echo --------------------------------------------------------
@echo Copyright (c) 2013,WebJet Business Division,CYOU
@echo All rights reserved.
@echo Name       auot make apk
@echo Date       2013/5/27       
@echo Author     xuhengjin
@echo --------------------------------------------------------
@echo please make sure this file run at android project dir
@echo step1:==========================upate android project

call ./make_apk_updateProject.bat

@echo step2:=========================== make apk
ant -buildfile ./build.xml debug
pause