### E\_SR = (Holzspalter Schalter)

:::{tip}
In der IEC 61131-3 wird noch noch zwischen SR(vorrangiges Setzen) und RS(vorrangiges Rücksetzen) unterschieden, in der IEC 61499-1 nicht mehr. Das bedeutet RS und SR haben die gleiche Funktion nur die Anschlüsse Imput S und R sind vertauscht
:::

Event-driven bistable

Der Funktionsblock E\_SR (Set-Reset) ist ein wichtiger Bestandteil der IEC 61499 Norm und wird häufig in Steuerungssystemen verwendet. Er dient dazu, eine bestimmte Aktion auszulösen, wenn eine bestimmte Bedingung erfüllt ist.

Der Funktionsblock E\_SR besteht aus zwei Eingängen und einem Ausgang. Der erste Eingang (S) dient dazu, die Aktion auszulösen, während der zweite Eingang (R) dazu dient, die Aktion zurückzusetzen. Der Ausgang des Funktionsblocks gibt an, ob die Aktion ausgelöst wurde oder nicht.

![](https://user-images.githubusercontent.com/113907528/204904299-a6a3580a-42b4-4ea9-80c9-52b38b2d002b.png)

*   Input
    *   S Set output Q
    *   R Reset output Q
*   Output
    *   EO Output Q has changed

![](https://agro-center.de/out/pictures/master/product/1/ETZXXX961020_1.jpg)

https://agro-center.de/schalter-fuer-holzspaltermotor-etzxxx961020.html

*   Ein Schalter = Einschalten
*   Aus Schalter = Ausschalten

Siehe auch: \[https://www.holobloc.com/doc/fb/rt/events/E_SR.htm](https://www.holobloc.com/doc/fb/rt/events/E_SR.htm)


* * * * * * * * * *

Folgender Text wurde erzeugt von <https://chat.deepseek.com/> am 05.02.2025 und noch nicht korrekturgelesen (HF)

### Der Baustein E_SR in der IEC 61499: Ein Überblick

#### Einleitung

Die IEC 61499 ist ein internationaler Standard, der die Modellierung von verteilten industriellen Steuerungssystemen ermöglicht. Ein zentrales Konzept in diesem Standard ist der Funktionsbaustein (FB), der als grundlegende Komponente für die Steuerungslogik dient. Der Baustein **E_SR** (Event-driven bistable) ist ein Beispiel für einen solchen Funktionsbaustein, der in der IEC 61499 verwendet wird, um ein einfaches bistabiles Verhalten zu modellieren. Dieser Aufsatz beschreibt die Struktur, das Verhalten und die Anwendung des E_SR-Bausteins anhand des bereitgestellten Quelltextes.

#### Struktur des E_SR-Bausteins

Der E_SR-Baustein ist ein **Basic Function Block (BFB)**, der gemäß der IEC 61499 spezifiziert ist. Ein BFB besteht aus einer Schnittstelle (Interface) und einer internen Logik, die durch einen Execution Control Chart (ECC) und Algorithmen definiert wird.

##### Schnittstelle (Interface)

Die Schnittstelle des E_SR-Bausteins besteht aus:

- **Eingangsereignisse (Event Inputs)**:
  - **S (Set)**: Dieses Ereignis setzt den Ausgang **Q** auf den Wert **TRUE**.
  - **R (Reset)**: Dieses Ereignis setzt den Ausgang **Q** auf den Wert **FALSE**.

- **Ausgangsereignis (Event Output)**:
  - **EO (Event Output)**: Dieses Ereignis wird ausgelöst, wenn sich der Wert von **Q** ändert. Es ist mit der Ausgangsvariable **Q** verknüpft.

- **Ausgangsvariable (Output Variable)**:
  - **Q**: Dies ist eine boolesche Variable, die den aktuellen Zustand des Flip-Flops repräsentiert.

##### Execution Control Chart (ECC)

Der ECC definiert das Verhalten des Bausteins durch Zustände und Übergänge. Der E_SR-Baustein hat drei Zustände:

1. **START**: Der Initialzustand des Bausteins.
2. **SET**: Dieser Zustand wird erreicht, wenn das **S**-Ereignis eintritt. In diesem Zustand wird der Algorithmus **SET** ausgeführt, der den Ausgang **Q** auf **TRUE** setzt und das **EO**-Ereignis auslöst.
3. **RESET**: Dieser Zustand wird erreicht, wenn das **R**-Ereignis eintritt. In diesem Zustand wird der Algorithmus **RESET** ausgeführt, der den Ausgang **Q** auf **FALSE** setzt und das **EO**-Ereignis auslöst.

Die Übergänge zwischen den Zuständen werden durch die Bedingungen **S** und **R** gesteuert:

- Von **START** nach **SET**, wenn das **S**-Ereignis eintritt.
- Von **SET** nach **RESET**, wenn das **R**-Ereignis eintritt.
- Von **RESET** nach **SET**, wenn das **S**-Ereignis erneut eintritt.

##### Algorithmen

Der E_SR-Baustein verfügt über zwei Algorithmen:

1. **SET**: Dieser Algorithmus setzt die Ausgangsvariable **Q** auf **TRUE**.
   ```structured-text
   Q := TRUE;
   ```

2. **RESET**: Dieser Algorithmus setzt die Ausgangsvariable **Q** auf **FALSE**.
   ```structured-text
   Q := FALSE;
   ```

#### Verhalten des E_SR-Bausteins

Der E_SR-Baustein verhält sich wie ein einfaches bistabiles Element (Flip-Flop), das durch Ereignisse gesteuert wird. Das **S**-Ereignis setzt den Ausgang **Q** auf **TRUE**, während das **R**-Ereignis den Ausgang **Q** auf **FALSE** zurücksetzt. Jede Änderung des Ausgangs **Q** löst das **EO**-Ereignis aus, das andere Bausteine oder Systemkomponenten über die Zustandsänderung informieren kann.

Das Verhalten des Bausteins kann wie folgt zusammengefasst werden:

1. **Initialzustand**: Der Baustein startet im Zustand **START**.
2. **Setzen**: Wenn das **S**-Ereignis eintritt, wechselt der Baustein in den Zustand **SET**, setzt **Q** auf **TRUE** und löst das **EO**-Ereignis aus.
3. **Zurücksetzen**: Wenn das **R**-Ereignis eintritt, wechselt der Baustein in den Zustand **RESET**, setzt **Q** auf **FALSE** und löst das **EO**-Ereignis aus.
4. **Wiederholung**: Der Baustein kann zwischen den Zuständen **SET** und **RESET** hin- und herwechseln, abhängig von den eintreffenden **S**- und **R**-Ereignissen.

#### Anwendungsbeispiele

Der E_SR-Baustein kann in verschiedenen industriellen Steuerungsanwendungen eingesetzt werden, insbesondere in Szenarien, in denen ein bistabiles Verhalten erforderlich ist. Einige Beispiele sind:

- **Speicherung von Zuständen**: Der Baustein kann verwendet werden, um den Zustand einer Maschine oder eines Prozesses zu speichern, z.B. ob eine Maschine eingeschaltet (**TRUE**) oder ausgeschaltet (**FALSE**) ist.
- **Ereignisgesteuerte Steuerung**: In Systemen, die auf Ereignisse reagieren müssen, kann der E_SR-Baustein verwendet werden, um Zustandsänderungen zu verwalten und andere Komponenten über diese Änderungen zu informieren.
- **Sicherheitsfunktionen**: Der Baustein kann in Sicherheitssystemen eingesetzt werden, um kritische Zustände zu speichern und bei Bedarf zurückzusetzen.

#### Fazit

Der E_SR-Baustein ist ein einfacher, aber leistungsfähiger Funktionsbaustein in der IEC 61499, der ein bistabiles Verhalten durch ereignisgesteuerte Logik realisiert. Durch seine klare Struktur und einfache Zustandsübergänge eignet er sich ideal für Anwendungen, in denen Zustände gespeichert und durch Ereignisse gesteuert werden müssen. Der Baustein demonstriert die Flexibilität und Modularität der IEC 61499, die es ermöglicht, komplexe Steuerungssysteme aus einfachen, wiederverwendbaren Komponenten aufzubauen.

Der bereitgestellte Quelltext zeigt, wie der E_SR-Baustein in der Praxis implementiert werden kann, und bietet eine solide Grundlage für die Entwicklung ähnlicher Bausteine in industriellen Steuerungssystemen.
