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



# Task 2: Regex Suche und Ersetzung

## 1. Grep
   - **Befehl**: `grep -En "printf\s*\(" solutions/debug_sample.c`
   - **Was passiert**: Mit diesem Befehl habe ich alle Stellen gesucht, an denen printf aufgerufen wird. Das `\s*\(` erlaubt beliebige Leerzeichen vor der öffnenden Klammer. Die Option `-n` zeigt die Zeilennummern an, `-E` erlaubt erweiterte reguläre Ausdrücke. Ergebnis: printf stand in Zeile 4.

## 2. Sed
   - **Befehl**: `sed -E -i.bak 's/printf\s*/debug_printf/g' solutions/debug_sample.c`
   - **Was passiert**: Dieser Befehl ersetzt printf durch debug_printf direkt in der Datei. Mit `-i.bak` wird automatisch eine Sicherungskopie (.bak) angelegt. Das `s/.../.../g` ersetzt alle Vorkommen in jeder Zeile, und `\s*` berücksichtigt auch Leerzeichen. Hat problemlos funktioniert.

## 3. Awk
   - **Befehl**: `awk '/debug_printf/ { print NR, $0 }' solutions/debug_sample.c`
   - **Was passiert**: Mit awk habe ich gezielt nach Zeilen mit debug_printf gesucht. NR steht für die Zeilennummer, $0 für den gesamten Zeileninhalt. Auch hier kam wieder Zeile 4 raus, diesmal mit dem geänderten Funktionsnamen.

## 4. Vim (interaktiv)
   - **Befehl**: `vim solutions/debug_sample.c`, dann `:%s/printf/debug_printf/g`
   - **Was passiert**: Ich habe die Datei in Vim geöffnet und per Suche (`/printf`) geschaut, ob noch etwas zu ersetzen ist (war aber schon erledigt). Dann mit `:%s` die Ersetzung ausprobiert – im Prinzip wie sed, aber visuell. Gespeichert mit `:wq`.

## 5. Vim (per Kommandozeile)
   - **Befehl**: `vim -c ":%s/printf/debug_printf/g" -c ":wq" solutions/debug_sample.c`
   - **Was passiert**: Gleiche Ersetzung wie oben, aber ohne Vim wirklich zu öffnen. Die Befehle werden automatisch ausgeführt. Da vorher schon alles ersetzt war, gab's hier nichts Neues.

## **Fazit: Wann verwende ich was?**
- Grep ist super zum schnellen Durchsuchen von Dateien – besonders nützlich, wenn ich wissen will, ob etwas überhaupt vorkommt.
- Sed eignet sich gut für automatische Ersetzungen, vor allem wenn viele Dateien betroffen sind. Das Backup-Feature ist hilfreich.
- Awk verwende ich, wenn ich gezielt bestimmte Zeilen mit Zusatzinfos (z. B. Zeilennummern) rausfiltern will.
- Vim interaktiv ist sinnvoll, wenn ich genau sehen möchte, was geändert wird – braucht aber mehr Zeit.
- Vim über CLI ist praktisch für schnelle Ersetzungen, ohne die Oberfläche zu benutzen – gut, wenn ich genau weiß, was ich tue.
