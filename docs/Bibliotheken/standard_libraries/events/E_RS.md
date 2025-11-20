### E\_RS

:::{tip}
In der IEC 61131-3 wird noch noch zwischen SR(vorrangiges Setzen) und RS(vorrangiges Rücksetzen) unterschieden, in der IEC 61499-1 nicht mehr. Das bedeutet RS und SR haben die gleiche Funktion nur die Anschlüsse Imput S und R sind vertauscht
:::

Event-driven bistable

![](https://user-images.githubusercontent.com/113907528/204902213-fedab003-82e3-4adf-ab40-fbb82a526c02.png)

*   Input
    *   R Reset output Q
    *   S Set output Q
*   Output
    *   EO Output Q has changed
    *   Q



* * * * * * * * * *

Folgender Text wurde erzeugt von <https://chat.deepseek.com/> am 05.02.2025 und noch nicht korrekturgelesen (HF)


### Der Baustein E_RS in der IEC 61499: Ein Überblick

#### Einleitung

Die IEC 61499 ist ein internationaler Standard, der die Modellierung von verteilten industriellen Steuerungssystemen ermöglicht. Ein zentrales Konzept in diesem Standard ist der Funktionsbaustein (FB), der als grundlegende Komponente für die Steuerungslogik dient. Der Baustein **E_RS** (Event-driven bistable) ist ein Beispiel für einen solchen Funktionsbaustein, der in der IEC 61499 verwendet wird, um ein einfaches bistabiles Verhalten zu modellieren. Dieser Aufsatz beschreibt die Struktur, das Verhalten und die Anwendung des E_RS-Bausteins anhand des bereitgestellten Quelltextes.

#### Struktur des E_RS-Bausteins

Der E_RS-Baustein ist ein **Basic Function Block (BFB)**, der gemäß der IEC 61499 spezifiziert ist. Ein BFB besteht aus einer Schnittstelle (Interface) und einer internen Logik, die durch einen Execution Control Chart (ECC) und Algorithmen definiert wird.

##### Schnittstelle (Interface)

Die Schnittstelle des E_RS-Bausteins besteht aus:

- **Eingangsereignisse (Event Inputs)**:
  - **R (Reset)**: Dieses Ereignis setzt den Ausgang **Q** auf den Wert **FALSE**.
  - **S (Set)**: Dieses Ereignis setzt den Ausgang **Q** auf den Wert **TRUE**.

- **Ausgangsereignis (Event Output)**:
  - **EO (Event Output)**: Dieses Ereignis wird ausgelöst, wenn sich der Wert von **Q** ändert. Es ist mit der Ausgangsvariable **Q** verknüpft.

- **Ausgangsvariable (Output Variable)**:
  - **Q**: Dies ist eine boolesche Variable, die den aktuellen Zustand des Flip-Flops repräsentiert.

##### Execution Control Chart (ECC)

Der ECC definiert das Verhalten des Bausteins durch Zustände und Übergänge. Der E_RS-Baustein hat drei Zustände:

1. **START**: Der Initialzustand des Bausteins.
2. **SET**: Dieser Zustand wird erreicht, wenn das **S**-Ereignis eintritt. In diesem Zustand wird der Algorithmus **SET** ausgeführt, der den Ausgang **Q** auf **TRUE** setzt und das **EO**-Ereignis auslöst.
3. **RESET**: Dieser Zustand wird erreicht, wenn das **R**-Ereignis eintritt. In diesem Zustand wird der Algorithmus **RESET** ausgeführt, der den Ausgang **Q** auf **FALSE** setzt und das **EO**-Ereignis auslöst.

Die Übergänge zwischen den Zuständen werden durch die Bedingungen **S** und **R** gesteuert:

- Von **START** nach **SET**, wenn das **S**-Ereignis eintritt.
- Von **SET** nach **RESET**, wenn das **R**-Ereignis eintritt.
- Von **RESET** nach **SET**, wenn das **S**-Ereignis erneut eintritt.

##### Algorithmen

Der E_RS-Baustein verfügt über zwei Algorithmen:

1. **SET**: Dieser Algorithmus setzt die Ausgangsvariable **Q** auf **TRUE**.
   ```structured-text
   Q := TRUE;
   ```

2. **RESET**: Dieser Algorithmus setzt die Ausgangsvariable **Q** auf **FALSE**.
   ```structured-text
   Q := FALSE;
   ```

#### Verhalten des E_RS-Bausteins

Der E_RS-Baustein verhält sich wie ein einfaches bistabiles Element (Flip-Flop), das durch Ereignisse gesteuert wird. Das **S**-Ereignis setzt den Ausgang **Q** auf **TRUE**, während das **R**-Ereignis den Ausgang **Q** auf **FALSE** zurücksetzt. Jede Änderung des Ausgangs **Q** löst das **EO**-Ereignis aus, das andere Bausteine oder Systemkomponenten über die Zustandsänderung informieren kann.

Das Verhalten des Bausteins kann wie folgt zusammengefasst werden:

1. **Initialzustand**: Der Baustein startet im Zustand **START**.
2. **Setzen**: Wenn das **S**-Ereignis eintritt, wechselt der Baustein in den Zustand **SET**, setzt **Q** auf **TRUE** und löst das **EO**-Ereignis aus.
3. **Zurücksetzen**: Wenn das **R**-Ereignis eintritt, wechselt der Baustein in den Zustand **RESET**, setzt **Q** auf **FALSE** und löst das **EO**-Ereignis aus.
4. **Wiederholung**: Der Baustein kann zwischen den Zuständen **SET** und **RESET** hin- und herwechseln, abhängig von den eintreffenden **S**- und **R**-Ereignissen.

#### Anwendungsbeispiele

Der E_RS-Baustein kann in verschiedenen industriellen Steuerungsanwendungen eingesetzt werden, insbesondere in Szenarien, in denen ein bistabiles Verhalten erforderlich ist. Einige Beispiele sind:

- **Speicherung von Zuständen**: Der Baustein kann verwendet werden, um den Zustand einer Maschine oder eines Prozesses zu speichern, z.B. ob eine Maschine eingeschaltet (**TRUE**) oder ausgeschaltet (**FALSE**) ist.
- **Ereignisgesteuerte Steuerung**: In Systemen, die auf Ereignisse reagieren müssen, kann der E_RS-Baustein verwendet werden, um Zustandsänderungen zu verwalten und andere Komponenten über diese Änderungen zu informieren.
- **Sicherheitsfunktionen**: Der Baustein kann in Sicherheitssystemen eingesetzt werden, um kritische Zustände zu speichern und bei Bedarf zurückzusetzen.

#### Fazit

Der E_RS-Baustein ist ein einfacher, aber leistungsfähiger Funktionsbaustein in der IEC 61499, der ein bistabiles Verhalten durch ereignisgesteuerte Logik realisiert. Durch seine klare Struktur und einfache Zustandsübergänge eignet er sich ideal für Anwendungen, in denen Zustände gespeichert und durch Ereignisse gesteuert werden müssen. Der Baustein demonstriert die Flexibilität und Modularität der IEC 61499, die es ermöglicht, komplexe Steuerungssysteme aus einfachen, wiederverwendbaren Komponenten aufzubauen.

Der bereitgestellte Quelltext zeigt, wie der E_RS-Baustein in der Praxis implementiert werden kann, und bietet eine solide Grundlage für die Entwicklung ähnlicher Bausteine in industriellen Steuerungssystemen.
