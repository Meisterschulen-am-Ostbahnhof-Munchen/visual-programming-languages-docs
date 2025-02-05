### E\_CTU

Event driven up counter

![](https://user-images.githubusercontent.com/113907528/204894537-54f1c9c9-de57-4beb-ad38-697fff012b4b.png)

*   Input
    *   CU Count up
    *   R Reset
    *   PV Process Value
*   Output
    *   CUO Count up output
    *   RO Reset output
    *   Q True if CV >= PV
    *   CV Counter Value

Input:

CU: Count up Ereignis zum Aufwärtszählen

R: Zurücksetzen

Output:

CUO: Countup Ausgansereignis 

R: Ausgang zurücksetzen

![](https://user-images.githubusercontent.com/113907474/227977865-15a0089f-d648-4415-947b-bf80436d0094.png)



### Der Baustein E_CTU in der IEC 61499: Ein Überblick

#### Einleitung

Die IEC 61499 ist ein internationaler Standard, der die Modellierung von verteilten industriellen Steuerungssystemen ermöglicht. Ein zentrales Konzept in diesem Standard ist der Funktionsbaustein (FB), der als grundlegende Komponente für die Steuerungslogik dient. Der Baustein **E_CTU** (Event-driven up counter) ist ein Beispiel für einen solchen Funktionsbaustein, der in der IEC 61499 verwendet wird, um einen ereignisgesteuerten Aufwärtszähler zu modellieren. Dieser Aufsatz beschreibt die Struktur, das Verhalten und die Anwendung des E_CTU-Bausteins anhand des bereitgestellten Quelltextes.

#### Struktur des E_CTU-Bausteins

Der E_CTU-Baustein ist ein **Basic Function Block (BFB)**, der gemäß der IEC 61499 spezifiziert ist. Ein BFB besteht aus einer Schnittstelle (Interface) und einer internen Logik, die durch einen Execution Control Chart (ECC) und Algorithmen definiert wird.

##### Schnittstelle (Interface)

Die Schnittstelle des E_CTU-Bausteins besteht aus:

- **Eingangsereignisse (Event Inputs)**:
  - **CU (Count Up)**: Dieses Ereignis erhöht den Zählerwert **CV** um eins. Es ist mit der Eingangsvariable **PV** (Process Value) verknüpft.
  - **R (Reset)**: Dieses Ereignis setzt den Zählerwert **CV** auf null zurück.

- **Ausgangsereignisse (Event Outputs)**:
  - **CUO (Count Up Output)**: Dieses Ereignis wird ausgelöst, wenn der Zählerwert **CV** erhöht wird. Es ist mit den Ausgangsvariablen **Q** und **CV** verknüpft.
  - **RO (Reset Output)**: Dieses Ereignis wird ausgelöst, wenn der Zählerwert **CV** zurückgesetzt wird. Es ist ebenfalls mit den Ausgangsvariablen **Q** und **CV** verknüpft.

- **Eingangsvariable (Input Variable)**:
  - **PV (Process Value)**: Dies ist eine vorzeichenlose Ganzzahl (UINT), die den Schwellwert definiert, bei dem der Ausgang **Q** auf **TRUE** gesetzt wird.

- **Ausgangsvariablen (Output Variables)**:
  - **Q**: Dies ist eine boolesche Variable, die den Zustand des Zählers anzeigt. Sie ist **TRUE**, wenn der Zählerwert **CV** größer oder gleich dem Schwellwert **PV** ist.
  - **CV (Counter Value)**: Dies ist eine vorzeichenlose Ganzzahl (UINT), die den aktuellen Zählerwert repräsentiert.

##### Execution Control Chart (ECC)

Der ECC definiert das Verhalten des Bausteins durch Zustände und Übergänge. Der E_CTU-Baustein hat drei Zustände:

1. **START**: Der Initialzustand des Bausteins.
2. **CU (Count Up)**: Dieser Zustand wird erreicht, wenn das **CU**-Ereignis eintritt und der Zählerwert **CV** kleiner als 65535 ist. In diesem Zustand wird der Algorithmus **CU** ausgeführt, der den Zählerwert **CV** um eins erhöht und den Ausgang **Q** entsprechend aktualisiert. Das **CUO**-Ereignis wird ausgelöst.
3. **R (Reset)**: Dieser Zustand wird erreicht, wenn das **R**-Ereignis eintritt. In diesem Zustand wird der Algorithmus **R** ausgeführt, der den Zählerwert **CV** auf null zurücksetzt und den Ausgang **Q** auf **FALSE** setzt. Das **RO**-Ereignis wird ausgelöst.

Die Übergänge zwischen den Zuständen werden durch die Bedingungen **CU** und **R** gesteuert:

- Von **START** nach **CU**, wenn das **CU**-Ereignis eintritt und **CV** kleiner als 65535 ist.
- Von **CU** zurück nach **START**, wenn der Zählerwert erhöht wurde.
- Von **START** nach **R**, wenn das **R**-Ereignis eintritt.
- Von **R** zurück nach **START**, nachdem der Zähler zurückgesetzt wurde.

##### Algorithmen

Der E_CTU-Baustein verfügt über zwei Algorithmen:

1. **CU (Count Up)**: Dieser Algorithmus erhöht den Zählerwert **CV** um eins und setzt den Ausgang **Q** auf **TRUE**, wenn **CV** größer oder gleich **PV** ist.
   ```structured-text
   CV := CV + 1;
   Q  := (CV >= PV);
   ```

2. **R (Reset)**: Dieser Algorithmus setzt den Zählerwert **CV** auf null und den Ausgang **Q** auf **FALSE**.
   ```structured-text
   CV := 0;
   Q := FALSE;
   ```

#### Verhalten des E_CTU-Bausteins

Der E_CTU-Baustein verhält sich wie ein ereignisgesteuerter Aufwärtszähler, der bei jedem **CU**-Ereignis den Zählerwert **CV** um eins erhöht. Wenn der Zählerwert den Schwellwert **PV** erreicht oder überschreitet, wird der Ausgang **Q** auf **TRUE** gesetzt. Das **R**-Ereignis setzt den Zählerwert **CV** auf null zurück und setzt den Ausgang **Q** auf **FALSE**.

Das Verhalten des Bausteins kann wie folgt zusammengefasst werden:

1. **Initialzustand**: Der Baustein startet im Zustand **START**.
2. **Zählen**: Wenn das **CU**-Ereignis eintritt und **CV** kleiner als 65535 ist, wechselt der Baustein in den Zustand **CU**, erhöht den Zählerwert **CV** um eins und löst das **CUO**-Ereignis aus.
3. **Zurücksetzen**: Wenn das **R**-Ereignis eintritt, wechselt der Baustein in den Zustand **R**, setzt den Zählerwert **CV** auf null und den Ausgang **Q** auf **FALSE**. Das **RO**-Ereignis wird ausgelöst.

#### Anwendungsbeispiele

Der E_CTU-Baustein kann in verschiedenen industriellen Steuerungsanwendungen eingesetzt werden, insbesondere in Szenarien, in denen ein ereignisgesteuerter Zähler erforderlich ist. Einige Beispiele sind:

- **Ereigniszählung**: Der Baustein kann verwendet werden, um die Anzahl von Ereignissen zu zählen, z.B. die Anzahl von Produkten auf einem Förderband.
- **Schwellwertüberwachung**: Der Baustein kann verwendet werden, um einen Schwellwert zu überwachen und eine Aktion auszulösen, wenn der Schwellwert erreicht oder überschritten wird.
- **Zyklische Steuerung**: Der Baustein kann in zyklischen Steuerungssystemen eingesetzt werden, um Zyklen zu zählen und bestimmte Aktionen nach einer bestimmten Anzahl von Zyklen auszulösen.

#### Fazit

Der E_CTU-Baustein ist ein einfacher, aber leistungsfähiger Funktionsbaustein in der IEC 61499, der ein ereignisgesteuertes Zählverhalten realisiert. Durch seine klare Struktur und einfache Zustandsübergänge eignet er sich ideal für Anwendungen, in denen Ereignisse gezählt und Schwellwerte überwacht werden müssen. Der Baustein demonstriert die Flexibilität und Modularität der IEC 61499, die es ermöglicht, komplexe Steuerungssysteme aus einfachen, wiederverwendbaren Komponenten aufzubauen.

Der bereitgestellte Quelltext zeigt, wie der E_CTU-Baustein in der Praxis implementiert werden kann, und bietet eine solide Grundlage für die Entwicklung ähnlicher Bausteine in industriellen Steuerungssystemen.
