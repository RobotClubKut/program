@REM "LED00.c"をコンパイルするためのバッチファイルです。
@REM 本バッチはGDLから使用されるものではありません。
@REM GDLを使用しないで単体でコンパイルする際に利用してください。
@SET PATH=C:\PROGRA~1\BestTech\GCCDEV~1\GCC\SH\bin;c:\PROGRA~1\BestTech\GCCDEV~1\GCC\SH\libexec\gcc\sh-elf\45-GNU~1.02;c:\PROGRA~1\BestTech\GCCDEV~1\GCC\SH\sh-elf\bin
sh-elf-gcc -I C:\PROGRA~1\BestTech\GCCDEV~1\TARGET\7125F -L C:\PROGRA~1\BestTech\GCCDEV~1\TARGET\7125F -m2 -nostartfiles -Wall -Wno-main -pipe -O0 -TC:\PROGRA~1\BestTech\GCCDEV~1\TARGET\7125F\shrom.x -Xlinker -Map -Xlinker "LED00.map" C:\PROGRA~1\BestTech\GCCDEV~1\TARGET\7125F\shrom.s "LED00.c" -ladd7125 -lm -o "LED00.exe" 
sh-elf-objcopy -O srec  "LED00.exe" "LED00.mot"
PAUSE
