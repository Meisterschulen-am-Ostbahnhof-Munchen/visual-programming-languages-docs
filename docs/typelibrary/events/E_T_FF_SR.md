
# E_T_FF_SR

![image](https://github.com/user-attachments/assets/97b33fec-a320-485e-b993-b85252d380ae)



* * * * * * * * * *

Folgender Text wurde erzeugt von <https://chat.deepseek.com/> am 05.02.2025 und noch nicht korrekturgelesen (HF)


### Der Baustein E_T_FF_SR in der IEC 61499: Ein Überblick

#### Einleitung

Die IEC 61499 ist ein internationaler Standard, der die Modellierung von verteilten industriellen Steuerungssystemen ermöglicht. Ein zentrales Konzept in diesem Standard ist der Funktionsbaustein (FB), der als grundlegende Komponente für die Steuerungslogik dient. Der Baustein **E_T_FF_SR** (Event-driven bistable and Toggle) ist ein erweiterter Funktionsbaustein, der sowohl ein bistabiles Verhalten als auch eine Toggle-Funktionalität bietet. Dieser Aufsatz beschreibt die Struktur, das Verhalten und die Anwendung des E_T_FF_SR-Bausteins anhand des bereitgestellten Quelltextes.

#### Struktur des E_T_FF_SR-Bausteins

Der E_T_FF_SR-Baustein ist ein **Basic Function Block (BFB)**, der gemäß der IEC 61499 spezifiziert ist. Ein BFB besteht aus einer Schnittstelle (Interface) und einer internen Logik, die durch einen Execution Control Chart (ECC) und Algorithmen definiert wird.

##### Schnittstelle (Interface)

Die Schnittstelle des E_T_FF_SR-Bausteins besteht aus:

- **Eingangsereignisse (Event Inputs)**:
  - **S (Set)**: Dieses Ereignis setzt den Ausgang **Q** auf den Wert **TRUE**.
  - **R (Reset)**: Dieses Ereignis setzt den Ausgang **Q** auf den Wert **FALSE**.
  - **CLK (Clock)**: Dieses Ereignis dient als Taktgeber, um den Ausgang **Q** zu toggeln (umzuschalten).

- **Ausgangsereignis (Event Output)**:
  - **EO (Event Output)**: Dieses Ereignis wird ausgelöst, wenn sich der Wert von **Q** ändert. Es ist mit der Ausgangsvariable **Q** verknüpft.

- **Ausgangsvariable (Output Variable)**:
  - **Q**: Dies ist eine boolesche Variable, die den aktuellen Zustand des Flip-Flops repräsentiert.

##### Execution Control Chart (ECC)

Der ECC definiert das Verhalten des Bausteins durch Zustände und Übergänge. Der E_T_FF_SR-Baustein hat drei Zustände:

1. **START**: Der Initialzustand des Bausteins.
2. **SET**: Dieser Zustand wird erreicht, wenn das **S**-Ereignis eintritt. In diesem Zustand wird der Algorithmus **SET** ausgeführt, der den Ausgang **Q** auf **TRUE** setzt und das **EO**-Ereignis auslöst.
3. **RESET**: Dieser Zustand wird erreicht, wenn das **R**-Ereignis eintritt. In diesem Zustand wird der Algorithmus **RESET** ausgeführt, der den Ausgang **Q** auf **FALSE** setzt und das **EO**-Ereignis auslöst.

Die Übergänge zwischen den Zuständen werden durch die Bedingungen **S**, **R** und **CLK** gesteuert:

- Von **START** nach **SET**, wenn das **S**-Ereignis eintritt.
- Von **SET** nach **RESET**, wenn das **R**-Ereignis eintritt.
- Von **RESET** nach **SET**, wenn das **S**-Ereignis erneut eintritt.
- Von **SET** nach **RESET**, wenn das **CLK**-Ereignis eintritt.
- Von **RESET** nach **SET**, wenn das **CLK**-Ereignis eintritt.
- Von **START** nach **SET**, wenn das **CLK**-Ereignis eintritt.

##### Algorithmen

Der E_T_FF_SR-Baustein verfügt über zwei Algorithmen:

1. **SET**: Dieser Algorithmus setzt die Ausgangsvariable **Q** auf **TRUE**.
   ```structured-text
   Q := TRUE;
   ```

2. **RESET**: Dieser Algorithmus setzt die Ausgangsvariable **Q** auf **FALSE**.
   ```structured-text
   Q := FALSE;
   ```

#### Verhalten des E_T_FF_SR-Bausteins

Der E_T_FF_SR-Baustein verhält sich wie ein erweitertes bistabiles Element (Flip-Flop), das sowohl durch Set- und Reset-Ereignisse als auch durch einen Taktgeber gesteuert wird. Das **S**-Ereignis setzt den Ausgang **Q** auf **TRUE**, während das **R**-Ereignis den Ausgang **Q** auf **FALSE** zurücksetzt. Das **CLK**-Ereignis toggelt den Ausgang **Q**, d.h., es schaltet den Zustand von **TRUE** auf **FALSE** oder umgekehrt. Jede Änderung des Ausgangs **Q** löst das **EO**-Ereignis aus, das andere Bausteine oder Systemkomponenten über die Zustandsänderung informieren kann.

Das Verhalten des Bausteins kann wie folgt zusammengefasst werden:

1. **Initialzustand**: Der Baustein startet im Zustand **START**.
2. **Setzen**: Wenn das **S**-Ereignis eintritt, wechselt der Baustein in den Zustand **SET**, setzt **Q** auf **TRUE** und löst das **EO**-Ereignis aus.
3. **Zurücksetzen**: Wenn das **R**-Ereignis eintritt, wechselt der Baustein in den Zustand **RESET**, setzt **Q** auf **FALSE** und löst das **EO**-Ereignis aus.
4. **Toggeln**: Wenn das **CLK**-Ereignis eintritt, wechselt der Baustein zwischen den Zuständen **SET** und **RESET**, wodurch der Ausgang **Q** getoggelt wird.

#### Anwendungsbeispiele

Der E_T_FF_SR-Baustein kann in verschiedenen industriellen Steuerungsanwendungen eingesetzt werden, insbesondere in Szenarien, in denen ein bistabiles Verhalten mit zusätzlicher Toggle-Funktionalität erforderlich ist. Einige Beispiele sind:

- **Speicherung von Zuständen**: Der Baustein kann verwendet werden, um den Zustand einer Maschine oder eines Prozesses zu speichern, z.B. ob eine Maschine eingeschaltet (**TRUE**) oder ausgeschaltet (**FALSE**) ist.
- **Ereignisgesteuerte Steuerung**: In Systemen, die auf Ereignisse reagieren müssen, kann der E_T_FF_SR-Baustein verwendet werden, um Zustandsänderungen zu verwalten und andere Komponenten über diese Änderungen zu informieren.
- **Taktgesteuerte Steuerung**: Der Baustein kann in Systemen eingesetzt werden, die eine taktgesteuerte Zustandsänderung erfordern, z.B. in Schaltnetzen oder digitalen Schaltkreisen.

#### Fazit

Der E_T_FF_SR-Baustein ist ein vielseitiger Funktionsbaustein in der IEC 61499, der sowohl ein bistabiles Verhalten als auch eine Toggle-Funktionalität bietet. Durch seine klare Struktur und einfache Zustandsübergänge eignet er sich ideal für Anwendungen, in denen Zustände gespeichert und durch Ereignisse oder Takte gesteuert werden müssen. Der Baustein demonstriert die Flexibilität und Modularität der IEC 61499, die es ermöglicht, komplexe Steuerungssysteme aus einfachen, wiederverwendbaren Komponenten aufzubauen.

Der bereitgestellte Quelltext zeigt, wie der E_T_FF_SR-Baustein in der Praxis implementiert werden kann, und bietet eine solide Grundlage für die Entwicklung ähnlicher Bausteine in industriellen Steuerungssystemen.
