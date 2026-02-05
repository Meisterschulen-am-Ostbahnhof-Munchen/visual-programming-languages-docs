# 🧩 Funktionsbausteine in IEC 61499

Die Norm IEC 61499 definiert ein Modell für verteilte industrielle Leitsysteme. Der zentrale Baustein dieses Modells ist der Funktionsbaustein (Function Block, FB). Im Gegensatz zur IEC 61131-3 kapselt ein FB in IEC 61499 nicht nur Daten und Algorithmen, sondern auch die **Steuerung seiner Ausführung**.

## Aufbau eines Funktionsbausteins

Ein Funktionsbaustein besteht immer aus zwei Teilen:
1.  **Schnittstelle (Interface):** Die "Hülle" des Bausteins.
2.  **Rumpf (Body):** Das Innere des Bausteins (die Implementierung).

### Schnittstelle (Interface)
Die Schnittstelle ist in zwei Bereiche unterteilt:
*   **Kopf (Head):** Hier befinden sich die **Ereignis-Eingänge** (Event Inputs) und **Ereignis-Ausgänge** (Event Outputs).
*   **Rumpf-Schnittstelle (Body Interface):** Hier befinden sich die **Daten-Eingänge** (Data Inputs) und **Daten-Ausgänge** (Data Outputs).

**Wichtig:** Daten werden immer mit Ereignissen synchronisiert. Die Verbindung zwischen einem Ereignis und den zugehörigen Daten wird durch den **WITH-Qualifier** definiert. Das bedeutet: "Wenn Ereignis X eintritt, sind die Daten A und B gültig/aktualisiert."

---

## Typen von Funktionsbausteinen

Es gibt drei Haupttypen von Funktionsbausteinen in IEC 61499:

### 1. Basis-Funktionsbaustein (Basic Function Block)
Dies ist der elementare Baustein, in dem **Algorithmen** (Code in ST, C, etc.) ausgeführt werden.
*   Die Steuerung *wann* welcher Algorithmus ausgeführt wird, übernimmt eine **Zustandsmaschine**, das sogenannte **ECC** (siehe unten).
*   Er hat keinen internen parallelen Ablauf; er befindet sich immer in genau einem Zustand.

### 2. Zusammengesetzter Funktionsbaustein (Composite Function Block)
Dieser Baustein enthält keine Algorithmen oder ECCs. Stattdessen besteht sein Rumpf aus einem **Netzwerk** von anderen Funktionsbausteinen (Basis- oder zusammengesetzte FBs), die miteinander verschaltet sind. Er dient zur Strukturierung und Kapselung komplexer Logik.

### 3. Dienstschnittstellen-Baustein (Service Interface Function Block - SIFB)
Dieser Baustein stellt die Schnittstelle zur Hardware oder zum Betriebssystem dar.
*   Beispiele: Lesen/Schreiben von digitalen E/As, Netzwerkkommunikation (UDP/TCP), Zugriff auf Systemzeit.
*   Die interne Implementierung ist meist nicht in IEC 61499 sichtbar (Black Box).

---

## ⚙️ ECC (Execution Control Chart)

Das **ECC (Execution Control Chart)**, auf Deutsch *Plan der Ausführungssteuerung*, ist das Herzstück eines jeden **Basis-Funktionsbausteins**. Es ist eine Zustandsmaschine, die steuert, wie der Baustein auf eingehende Ereignisse reagiert.

Das ECC besteht aus drei Elementen:

### 1. EC-Zustände (EC States)
Ein Zustand repräsentiert eine Situation, in der sich der Baustein befindet (z. B. `START`, `INIT`, `RUN`, `ERROR`).
*   Der Baustein ist immer in genau einem Zustand aktiv.
*   Jedem Zustand können eine oder mehrere **EC-Aktionen** zugeordnet sein.

### 2. EC-Transitionen (EC Transitions)
Transitionen sind die Verbindungen zwischen den Zuständen. Sie definieren, wann der Baustein von einem Zustand in den nächsten wechselt.
Eine Transition schaltet (feuert), wenn:
*   Das zugehörige **Ereignis** (Event Input) eintrifft (z. B. `REQ`).
*   **UND** eine optionale **Wächterbedingung** (Guard Condition) wahr ist (z. B. `x > 10`).

*Beispiel:* `REQ [x > 10]` -> Wechsle den Zustand nur, wenn Ereignis `REQ` kommt UND `x` größer 10 ist.

### 3. EC-Aktionen (EC Actions)
Aktionen werden ausgeführt, sobald ein Zustand aktiv wird. Eine Aktion besteht aus zwei Teilen (beide optional):
1.  **Algorithmus:** Ein Stück Programmcode (z. B. in Strukturiertem Text), der Berechnungen durchführt.
2.  **Ausgabe-Ereignis:** Ein Ereignis (Event Output), das nach Abarbeitung des Algorithmus nach außen gesendet wird (z. B. `CNF`).

### Ablauf im ECC
1.  Der Baustein befindet sich in einem Zustand (z. B. `START`) und wartet.
2.  Ein Ereignis trifft am Eingang ein.
3.  Das ECC prüft alle vom aktuellen Zustand ausgehenden Transitionen.
4.  Wenn eine Transition gültig ist (Ereignis passt + Bedingung wahr), wechselt das ECC in den neuen Zustand.
5.  Im neuen Zustand werden nacheinander alle zugeordneten **Algorithmen** ausgeführt.
6.  Danach werden die zugeordneten **Ausgabe-Ereignisse** gefeuert.
7.  Das ECC wartet im neuen Zustand auf das nächste Ereignis.
