# E_PULSE

```{index} single: E_PULSE
```

**Wichtiger Hinweis: Dieser Baustein benötigt nur ein Ereignis (Event) und keine zyklischen Aufrufe. Er besitzt keinen Ausgang ET und zeigt die verstrichene Zeit nicht an.**

![image](https://github.com/user-attachments/assets/f5119723-ac8b-477f-afe1-795808faa1e2)

* * * * * * * * * *

![E_PULSE](E_PULSE.svg)


Folgender Text wurde erzeugt von <https://chat.deepseek.com/> am 05.02.2025 und noch nicht korrekturgelesen (HF)

### Der Baustein E_PULSE in der IEC 61499: Ein Überblick

#### Einleitung

Die IEC 61499 ist ein internationaler Standard, der die Modellierung von verteilten industriellen Steuerungssystemen ermöglicht. Ein zentrales Konzept in diesem Standard ist der Funktionsbaustein (FB), der als grundlegende Komponente für die Steuerungslogik dient. Der Baustein **E_PULSE** (Event-driven Pulse) ist ein Beispiel für einen solchen Funktionsbaustein, der in der IEC 61499 verwendet wird, um einen Impuls mit einer bestimmten Dauer zu erzeugen. Dieser Aufsatz beschreibt die Struktur, das Verhalten und die Anwendung des E_PULSE-Bausteins anhand des bereitgestellten Quelltextes. Ein besonderer Aspekt, der hervorgehoben werden soll, ist, dass dieser Baustein **auch dann funktioniert, wenn er nicht zyklisch aufgerufen wird**, da er intern auf dem **E_DELAY**-Baustein aus der IEC 61499 basiert.

#### Struktur des E_PULSE-Bausteins

Der E_PULSE-Baustein ist ein **Composite Function Block (CFB)**, der gemäß der IEC 61499 spezifiziert ist. Ein CFB besteht aus einer Schnittstelle (Interface) und einem internen Netzwerk von Funktionsbausteinen, die zusammenarbeiten, um das gewünschte Verhalten zu realisieren.

##### Schnittstelle (Interface)

Die Schnittstelle des E_PULSE-Bausteins besteht aus:

- **Eingangsereignisse (Event Inputs)**:
  - **REQ (Request)**: Dieses Ereignis löst die Ausführung des Bausteins aus. Es ist mit der Eingangsvariablen **PT** (Pulse Time) verknüpft.
  - **R (Reset)**: Dieses Ereignis setzt den Timer zurück.

- **Ausgangsereignis (Event Output)**:
  - **CNF (Confirmation)**: Dieses Ereignis wird ausgelöst, wenn die Ausführung des Bausteins abgeschlossen ist. Es ist mit der Ausgangsvariablen **Q** verknüpft.

- **Eingangsvariable (Input Variable)**:
  - **PT (Pulse Time)**: Dies ist eine Zeitvariable (TIME), die die Dauer des Impulses definiert.

- **Ausgangsvariable (Output Variable)**:
  - **Q (Output)**: Dies ist eine boolesche Variable, die den Zustand des Impulses anzeigt. Sie ist **TRUE**, solange der Impuls aktiv ist.

##### Internes Netzwerk (FBNetwork)

Der E_PULSE-Baustein verwendet intern zwei Funktionsbausteine, um das gewünschte Verhalten zu realisieren:

1. **E_DELAY**: Dieser Baustein realisiert die Verzögerungszeit **PT**. Wenn das **START**-Ereignis eintritt, beginnt der Timer zu laufen. Wenn die Verzögerungszeit abgelaufen ist, wird das **EO**-Ereignis ausgelöst.
2. **E_SR**: Dieser Baustein ist ein bistabiles Element, das den Zustand des Impulses speichert. Wenn das **S**-Ereignis eintritt, wird der Ausgang **Q** auf **TRUE** gesetzt. Wenn das **R**-Ereignis eintritt, wird der Ausgang **Q** auf **FALSE** gesetzt.

#### Verhalten des E_PULSE-Bausteins

Der E_PULSE-Baustein verhält sich wie ein Impulsgeber, der einen Impuls mit einer bestimmten Dauer **PT** erzeugt. Das Verhalten des Bausteins kann wie folgt beschrieben werden:

1. **Start des Impulses**: Wenn das **REQ**-Ereignis eintritt, wird der Timer gestartet, und der Ausgang **Q** wird auf **TRUE** gesetzt.
2. **Impulsdauer**: Der Ausgang **Q** bleibt solange **TRUE**, bis die Verzögerungszeit **PT** abgelaufen ist.
3. **Ende des Impulses**: Sobald die Verzögerungszeit **PT** abgelaufen ist, wird der Ausgang **Q** auf **FALSE** gesetzt, und das **CNF**-Ereignis wird ausgelöst, um den Abschluss des Impulses zu signalisieren.
4. **Reset**: Wenn das **R**-Ereignis eintritt, wird der Timer zurückgesetzt, und der Ausgang **Q** wird auf **FALSE** gesetzt.

#### Unabhängigkeit vom zyklischen Aufruf

Ein entscheidender Vorteil des E_PULSE-Bausteins ist, dass er **nicht zyklisch aufgerufen werden muss**, um korrekt zu funktionieren. Dies liegt daran, dass der Baustein intern auf dem **E_DELAY**-Baustein basiert, der in der IEC 61499 spezifiziert ist. Der **E_DELAY**-Baustein ist ein ereignisgesteuerter Timer, der unabhängig vom zyklischen Aufruf des übergeordneten Bausteins arbeitet. Das bedeutet, dass der E_PULSE-Baustein auch in Systemen eingesetzt werden kann, die nicht zyklisch arbeiten, z.B. in ereignisgesteuerten oder verteilten Steuerungssystemen.

#### Anwendungsbeispiele

Der E_PULSE-Baustein kann in verschiedenen industriellen Steuerungsanwendungen eingesetzt werden, insbesondere in Szenarien, in denen ein Impuls mit einer bestimmten Dauer erforderlich ist. Einige Beispiele sind:

- **Maschinensteuerung**: Der Baustein kann verwendet werden, um einen kurzen Impuls zu erzeugen, der eine Maschine für eine bestimmte Zeit aktiviert, z.B. um einen Prozess zu starten oder zu stoppen.
- **Beleuchtungssteuerung**: Der Baustein kann in Beleuchtungssystemen eingesetzt werden, um das Licht für eine bestimmte Zeit einzuschalten, z.B. für eine Sicherheitsbeleuchtung.
- **Ventilsteuerung**: Der Baustein kann verwendet werden, um ein Ventil für eine bestimmte Zeit zu öffnen, z.B. um eine bestimmte Menge an Flüssigkeit oder Gas freizugeben.

##

## Zugehörige Übungen

* [Uebung_020h](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_020h.md)
* [Uebung_020i](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_020i.md)

## Fazit

Der E_PULSE-Baustein ist ein vielseitiger Funktionsbaustein in der IEC 61499, der einen Impuls mit einer bestimmten Dauer realisiert. Durch seine interne Verwendung des **E_DELAY**-Bausteins kann er **auch dann korrekt funktionieren, wenn er nicht zyklisch aufgerufen wird**. Dies macht ihn besonders geeignet für ereignisgesteuerte und verteilte Steuerungssysteme, in denen zyklische Aufrufe nicht immer gewährleistet sind.

Der bereitgestellte Quelltext zeigt, wie der E_PULSE-Baustein in der Praxis implementiert werden kann, und bietet eine solide Grundlage für die Entwicklung ähnlicher Bausteine in industriellen Steuerungssystemen. Die Unabhängigkeit vom zyklischen Aufruf ist dabei ein entscheidender Vorteil, der den Baustein für eine Vielzahl von Anwendungen geeignet macht.