@REM "MTU00.c"をコンパイルするためのバッチファイルです。
@REM 本バッチはGDLから使用されるものではありません。
@REM GDLを使用しないで単体でコンパイルする際に利用してください。
@SET PATH=C:\PROGRA~1\BestTech\GCCDEV~1\GCC\SH\bin;c:\PROGRA~1\BestTech\GCCDEV~1\GCC\SH\libexec\gcc\sh-elf\45-GNU~1.02;c:\PROGRA~1\BestTech\GCCDEV~1\GCC\SH\sh-elf\bin
sh-elf-gcc -I C:\PROGRA~1\BestTech\GCCDEV~1\TARGET\7125F -L C:\PROGRA~1\BestTech\GCCDEV~1\TARGET\7125F -m2 -nostartfiles -Wall -Wno-main -pipe -O0 -TC:\PROGRA~1\BestTech\GCCDEV~1\TARGET\7125F\shrom.x -Xlinker -Map -Xlinker "MTU00.map" C:\PROGRA~1\BestTech\GCCDEV~1\TARGET\7125F\shrom.s "MTU00.c" -ladd7125 -lm -o "MTU00.exe" 
sh-elf-objcopy -O srec  "MTU00.exe" "MTU00.mot"
PAUSE
