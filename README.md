# PP7

## Goal 

In this exercise you will:

* **Understand** each stage of the C compilation pipeline (preprocessing, compilation to assembly, assembling, and linking).
* **Inspect** intermediate outputs to see how your C code transforms at each step.
* **Use** text‑processing tools (`grep`, `sed`, `awk`) with regular expressions to search and replace patterns in code.
* **Automate** search/replace interactively and non‑interactively in **Vim**.
* **Modularize** C code by defining functions across separate files and **link** them together manually.

**Important:** Start a stopwatch when you begin and work uninterruptedly for **90 minutes**. When time is up, stop immediately and record exactly where you paused.

---

## Workflow

1. **Fork** this repository on GitHub.
2. **Clone** your fork to your local machine.
3. Create a directory at the repository root named `solutions/`:

   ```bash
   mkdir solutions
   ```
4. For each task below, add the required files under `solutions/` (for example, `solutions/sample.c`, `solutions/sample.i`, etc.).
5. **Commit** your changes locally, then **push** them to GitHub.
6. **Submit** your repository link for review.

---

## Prerequisites

* A C compiler toolchain (e.g. `gcc`).
* Familiarity with command‑line tools: `grep`, `sed`, `awk`, and `vim`.
* Man‑pages for reference:

  ```bash
  man gcc   # for compiler options
  man grep  # for searching
  man sed   # for stream editing
  man awk   # for pattern scanning
  man vim   # for interactive editing
  ```

---

## Tasks

### Task 1: C Compilation Stages

**Objective:** Break down the process of transforming C source into an executable and inspect each intermediate file.

1. In `solutions/`, create a C source file named `sample.c` containing a simple `main()`:

   ```c
   #include <stdio.h>

   int main(void) {
       printf("Hello, PP7!\n");
       return 0;
   }
   ```
2. **Preprocess** only (run the preprocessor, `-E`) and save the output:

   ```bash
   gcc -E sample.c -o solutions/sample.i
   ```

   * Open `solutions/sample.i` in an editor and note how `#include <stdio.h>` expands and macros are handled.
3. **Compile to assembly** (`-S`):

   ```bash
   gcc -S solutions/sample.i -o solutions/sample.s
   ```

   * Examine `solutions/sample.s` to see the generated assembly instructions for `printf` and `return`.
4. **Assemble** (`-c`):

   ```bash
   gcc -c solutions/sample.s -o solutions/sample.o
   ```

   * Verify that `solutions/sample.o` is an object file (e.g., with `file sample.o`).
5. **Link** to produce an executable:

   ```bash
   gcc solutions/sample.o -o solutions/sample
   ```

   * Run `./solutions/sample` and confirm it prints `Hello, PP7!`.
6. **Explain** in comments or a short README how each stage transforms the code.

```
Hier erkläre ich, wie die Kompilierung von `sample.c` funktioniert, wie es in der Aufgabe steht.

1. Vorverarbeitung
- Befehl: `gcc -E solutions/sample.c -o solutions/sample.i`
- Was passiert: Der Befehl nimmt `sample.c` und macht daraus `sample.i`. Das `#include <stdio.h>` wird durch den ganzen Inhalt von `stdio.h` ersetzt. Das ist ne lange Datei mit vielen Definitionen für Sachen wie `printf`. Kommentare verschwinden, und wenn es Makros gibt, werden die aufgelöst.

2. Kompilierung zu Assembler
- Befehl: `gcc -S solutions/sample.i -o solutions/sample.s`
- Was passiert: Aus `sample.i` wird Assemblercode (`sample.s`). Das ist so ne Art Maschinensprache mit Befehlen wie `call printf` (für den `printf`-Aufruf) und `mov $0, %eax` (für `return 0`). Das hängt von meinem Computer ab (x86_64).

3. Assemblieren
- Befehl: `gcc -c solutions/sample.s -o solutions/sample.o`
- Was passiert: Der Assembler macht aus `sample.s` eine Objektdatei `sample.o`. Das ist Maschinencode, aber noch nicht ausführbar. Mit `file solutions/sample.o` hab ich gecheckt, dass es ein ELF-Objektfile ist.

4. Linken
- Befehl: `gcc solutions/sample.o -o solutions/sample`
- Was passiert: Der Linker nimmt `sample.o` und verbindet es mit Bibliotheken (z. B. für `printf`). Daraus wird die ausführbare Datei `sample`. Wenn ich `./solutions/sample` ausführe, kommt „Hello, PP7!“ raus, also hat’s geklappt.
```

---

### Task 2: Regex Search & Replace in Code

**Objective:** Use `grep`, `sed`, and `awk` to locate and modify code patterns, then perform the same edits in **Vim** both interactively and via the CLI.

1. Copy `solutions/sample.c` to `solutions/debug_sample.c`:

   ```bash
   cp solutions/sample.c solutions/debug_sample.c
   ```
2. **Search** for all calls to `printf` using `grep` with a regex pattern and save the results:

   ```bash
   grep -En "printf\s*\(" solutions/debug_sample.c
   ```
3. **Replace** each `printf` with `debug_printf` in the file using `sed` (in‑place):

   ```bash
   sed -E -i.bak 's/printf\s*/debug_printf/g' solutions/debug_sample.c
   ```
4. **Extract** lines containing `debug_printf` using `awk`:

   ```bash
   awk '/debug_printf/ { print NR, $0 }' solutions/debug_sample.c
   ```
5. **Vim Interactive**: open `solutions/debug_sample.c` in Vim:

   ```bash
   vim solutions/debug_sample.c
   ```

   * Use search (`/printf`) and substitute (`:%s/printf/debug_printf/g`) commands interactively.
   * Save and quit.
6. **Vim CLI**: perform the same substitute without opening the full UI:

   ```bash
   vim -c ":%s/printf/debug_printf/g" -c ":wq" solutions/debug_sample.c
   ```
7. **Explain** each tool’s approach to regex-based search and replace, and when you might prefer one over the others.

```
1. Grep
   - Befehl: `grep -En "printf\s*\(" solutions/debug_sample.c`
   - Was passiert: Mit diesem Befehl habe ich alle Stellen gesucht, an denen printf aufgerufen wird. Das `\s*\(` erlaubt beliebige Leerzeichen vor der öffnenden Klammer. Die Option `-n` zeigt die Zeilennummern an, `-E` erlaubt erweiterte reguläre Ausdrücke. Ergebnis: printf stand in Zeile 4.

2. Sed
   - Befehl: `sed -E -i.bak 's/printf\s*/debug_printf/g' solutions/debug_sample.c`
   - Was passiert: Dieser Befehl ersetzt printf durch debug_printf direkt in der Datei. Mit `-i.bak` wird automatisch eine Sicherungskopie (.bak) angelegt. Das `s/.../.../g` ersetzt alle Vorkommen in jeder Zeile, und `\s*` berücksichtigt auch Leerzeichen. Hat problemlos funktioniert.

3. Awk
   - Befehl: `awk '/debug_printf/ { print NR, $0 }' solutions/debug_sample.c`
   - Was passiert: Mit awk habe ich gezielt nach Zeilen mit debug_printf gesucht. NR steht für die Zeilennummer, $0 für den gesamten Zeileninhalt. Auch hier kam wieder Zeile 4 raus, diesmal mit dem geänderten Funktionsnamen.

4. Vim (interaktiv)
   - Befehl: `vim solutions/debug_sample.c`, dann `:%s/printf/debug_printf/g`
   - Was passiert: Ich habe die Datei in Vim geöffnet und per Suche (`/printf`) geschaut, ob noch etwas zu ersetzen ist (war aber schon erledigt). Dann mit `:%s` die Ersetzung ausprobiert – im Prinzip wie sed, aber visuell. Gespeichert mit `:wq`.

5. Vim (per Kommandozeile)
   - Befehl: `vim -c ":%s/printf/debug_printf/g" -c ":wq" solutions/debug_sample.c`
   - Was passiert: Gleiche Ersetzung wie oben, aber ohne Vim wirklich zu öffnen. Die Befehle werden automatisch ausgeführt. Da vorher schon alles ersetzt war, gab's hier nichts Neues.

Fazit: Wann verwende ich was?
- Grep ist super zum schnellen Durchsuchen von Dateien – besonders nützlich, wenn ich wissen will, ob etwas überhaupt vorkommt.
- Sed eignet sich gut für automatische Ersetzungen, vor allem wenn viele Dateien betroffen sind. Das Backup-Feature ist hilfreich.
- Awk verwende ich, wenn ich gezielt bestimmte Zeilen mit Zusatzinfos (z. B. Zeilennummern) rausfiltern will.
- Vim interaktiv ist sinnvoll, wenn ich genau sehen möchte, was geändert wird – braucht aber mehr Zeit.
- Vim über CLI ist praktisch für schnelle Ersetzungen, ohne die Oberfläche zu benutzen – gut, wenn ich genau weiß, was ich tue.
```
---

### Task 3: Modular Linking with `extern`

**Objective:** Create a separate addition function in `add.c`, declare it `extern` in `main.c`, and compile/link manually to form an executable.

1. In `solutions/`, create `add.c`:

   ```c
   // add.c
   int add(int a, int b) {
       return a + b;
   }
   ```
2. Create `main.c` that uses `add`:

   ```c
   // main.c
   #include <stdio.h>
   extern int add(int, int);

   int main(void) {
       int sum = add(5, 7);
       printf("5 + 7 = %d\n", sum);
       return 0;
   }
   ```
3. **Compile** each source separately:

   ```bash
   gcc -c solutions/add.c -o solutions/add.o
   gcc -c solutions/main.c -o solutions/main.o
   ```
4. **Link** the object files manually:

   ```bash
   gcc solutions/add.o solutions/main.o -o solutions/add_example
   ```
5. Run `./solutions/add_example` to verify it prints `5 + 7 = 12`.
6. **Document** the workflow in comments or a short file, emphasizing:

   * The role of `extern` declarations.
   * Why separating compilation can speed up builds.
   * How manual linking differs from letting `gcc` handle all steps in one command.

```
Hier erkläre ich, wie ich Task 3 gemacht hab, mit einer `add`-Funktion in `add.c`, die in `main.c` aufgerufen wird, und wie ich die Dateien separat kompiliert und manuell gelinkt hab.

## Workflow

1. Erstelle `add.c`:
   - Hab `add.c` gemacht mit der Funktion `int add(int a, int b)`, die einfach `a + b` zurückgibt.

2. Erstelle `main.c`:
   - In `main.c` hab ich `extern int add(int, int);` deklariert, um die `add`-Funktion zu nutzen. Dann hab ich `add(5, 7)` aufgerufen und das Ergebnis mit `printf` ausgegeben.

3. Kompiliere separat:
   - Mit `gcc -c solutions/add.c -o solutions/add.o` hab ich `add.c` zu einer Objektdatei kompiliert.
   - Mit `gcc -c solutions/main.c -o solutions/main.o` hab ich `main.c` kompiliert.

4. Linke manuell:
   - Mit `gcc solutions/add.o solutions/main.o -o solutions/add_example` hab ich die Objektdateien zu einem ausführbaren Programm `add_example` gelinkt.

5. Führe aus:
   - Mit `./solutions/add_example` hab ich das Programm gestartet, und es hat `5 + 7 = 12` ausgegeben.

## Erklärungen

- Rolle von `extern`-Deklarationen:
  Die `extern`-Deklaration in `main.c` sagt dem Compiler, dass die Funktion `add` woanders definiert ist (in `add.c`). Ohne `extern` würde der Compiler meckern, weil er die Funktion nicht findet. Beim Linken wird dann die echte Funktion aus `add.o` eingebunden.

- Warum separate Kompilierung Builds beschleunigt:
  Wenn ich `add.c` und `main.c` separat kompiliere, muss ich nur die Datei neu kompilieren, die sich geändert hat. Zum Beispiel, wenn ich nur `main.c` ändere, kompiliere ich nur `main.c` zu `main.o` und linke dann mit dem alten `add.o`. Das spart Zeit bei großen Projekten mit vielen Dateien.

- Manuelles Linken vs. gcc in einem Schritt:
  Normalerweise macht `gcc main.c add.c -o add_example` alles auf einmal: kompilieren und linken. Beim manuellen Linken kompiliere ich erst zu Objektdateien (`add.o`, `main.o`) und linke sie dann selbst. Das gibt mehr Kontrolle, z. B. kann ich einzelne Objektdateien wiederverwenden oder mit anderen Programmen linken. Aber es ist mehr Aufwand, weil ich mehrere Befehle eingeben muss.
```


---

**Remember:** Stop working after **90 minutes** and record where you stopped.
