# Task 1: C Kompilierung

Hier erkläre ich, wie die Kompilierung von `sample.c` funktioniert, wie es in der Aufgabe steht.

## 1. Vorverarbeitung
- **Befehl**: `gcc -E solutions/sample.c -o solutions/sample.i`
- **Was passiert**: Der Befehl nimmt `sample.c` und macht daraus `sample.i`. Das `#include <stdio.h>` wird durch den ganzen Inhalt von `stdio.h` ersetzt. Das ist ne lange Datei mit vielen Definitionen für Sachen wie `printf`. Kommentare verschwinden, und wenn es Makros gibt, werden die aufgelöst.

## 2. Kompilierung zu Assembler
- **Befehl**: `gcc -S solutions/sample.i -o solutions/sample.s`
- **Was passiert**: Aus `sample.i` wird Assemblercode (`sample.s`). Das ist so ne Art Maschinensprache mit Befehlen wie `call printf` (für den `printf`-Aufruf) und `mov $0, %eax` (für `return 0`). Das hängt von meinem Computer ab (x86_64).

## 3. Assemblieren
- **Befehl**: `gcc -c solutions/sample.s -o solutions/sample.o`
- **Was passiert**: Der Assembler macht aus `sample.s` eine Objektdatei `sample.o`. Das ist Maschinencode, aber noch nicht ausführbar. Mit `file solutions/sample.o` hab ich gecheckt, dass es ein ELF-Objektfile ist.

## 4. Linken
- **Befehl**: `gcc solutions/sample.o -o solutions/sample`
- **Was passiert**: Der Linker nimmt `sample.o` und verbindet es mit Bibliotheken (z. B. für `printf`). Daraus wird die ausführbare Datei `sample`. Wenn ich `./solutions/sample` ausführe, kommt „Hello, PP7!“ raus, also hat’s geklappt.
