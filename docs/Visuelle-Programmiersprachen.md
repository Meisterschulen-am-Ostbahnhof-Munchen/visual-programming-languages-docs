# Übersicht Visuelle Programmiersprachen

```{index} single: Übersicht Visuelle Programmiersprachen
```

Visuelle Programmiersprachen (VPL) ermöglichen die Erstellung von Programmen durch die grafische Manipulation von Elementen anstatt durch das Schreiben von Text. In der Welt der Technik und Informatik gibt es sehr unterschiedliche Ansätze, die je nach Zielgruppe und Anwendungsfall variieren.

## 1. Erziehungsorientierte und allgemeine Sprachen
Diese Sprachen dienen oft als Einstieg in die Logik der Programmierung. Sie abstrahieren komplexe Syntaxregeln in farbige Blöcke, die wie Puzzleteile zusammengesteckt werden.

*   **Scratch:** Die wohl bekannteste Sprache für Kinder und Jugendliche. Sie vermittelt spielerisch Konzepte wie Schleifen, Bedingungen und Variablen.
*   **Blockly (Google):** Eine Bibliothek, die visuelle Blöcke in textuellen Code (z. B. Python oder JavaScript) übersetzt.
*   **M5Stack / UIFlow:** Eine industrielle Anwendung von Blockly. Hier werden Mikrocontroller (ESP32) visuell programmiert, was den Prototypenbau extrem beschleunigt.

---

## 2. Visuelle Modellierung in der Informatik
Bevor Code geschrieben wird, nutzen Informatiker oft grafische Modelle, um Architekturen zu planen.
*   **UML (Unified Modeling Language):** Ein Standard zur Visualisierung von Softwaresystemen. Klassendiagramme oder Zustandsdiagramme sind hierbei die bekanntesten Werkzeuge.

---

## 3. Ingenieurswissenschaftliche Sprachen (Datenfluss)
In der Mess- und Regelungstechnik haben visuelle Sprachen eine dominierende Rolle, da sie den Fluss von Signalen und Daten intuitiv abbilden.
*   **LabVIEW (National Instruments):** Eine mächtige Umgebung, in der "Virtuelle Instrumente" (VIs) durch das Verdrahten von Funktionsblöcken erstellt werden. Sie wird weltweit in Laboren und Prüfständen eingesetzt.

---

## 4. Automatisierungstechnik (Industrieller Standard)
In der Industrie ist die visuelle Programmierung seit Jahrzehnten Standard, da sie direkt aus der Tradition der Elektrotechnik (Schaltpläne) und Verfahrenstechnik (Ablaufpläne) stammt.

### Die Sprachen der IEC 61131-3
Dieser Standard definiert drei wesentliche visuelle Sprachen für Speicherprogrammierbare Steuerungen (SPS):

| Kürzel | Bezeichnung (DE/EN) | Charakteristik | Anwendung |
| :--- | :--- | :--- | :--- |
| **KOP / LD** | Kontaktplan / Ladder Diagram | Sieht aus wie ein Stromlaufplan. | Einfache Logik, Verriegelungen. |
| **FBS / FBD** | Funktionsbausteinsprache / Function Block Diagram | Logikgatter und Funktionsblöcke werden verbunden. | Komplexe Regelungen, mathematische Berechnungen. |
| **AS / SFC** | Ablaufsprache / Sequential Function Chart | Modellierung von Schritten und Übergängen (Transitionen). | Maschinenabläufe, Chargenprozesse (ähnlich GRAFCET). |

### Die Evolution: IEC 61499
Die IEC 61499 baut auf den Konzepten der IEC 61131-3 auf, führt aber entscheidende Neuerungen ein:

1.  **Function Blocks (FB):** Die Programmierung ähnelt der Funktionsbausteinsprache (FBS), ist aber strikt ereignisorientiert. Ein Block wird nur aktiv, wenn ein Ereignis (Event) eintrifft.
2.  **ECC (Execution Control Chart):** Innerhalb eines Bausteins steuert eine Zustandsmaschine (State Machine), welcher Algorithmus bei welchem Ereignis ausgeführt wird. Dies ermöglicht eine viel präzisere Kontrolle über das Systemverhalten als in klassischen SPS-Zyklen.

---

## Warum visuelle Programmierung in der Industrie?
Die Automatisierungspyramide zeigt, dass auf den unteren Ebenen (Feld- und Steuerungsebene) Echtzeitfähigkeit und klare Diagnosemöglichkeiten zählen. Visuelle Programme lassen sich im Fehlerfall oft schneller "lesen" und debuggen als tausende Zeilen Textcode. Sie schlagen die Brücke zwischen dem Schaltplan des Elektrikers und der Logik des Programmierers.

### Weiterführende Ressourcen
*   [Video: IEC 61131 vs. IEC 61499 (IEEE Webinar)](https://resourcecenter.ies.ieee.org/education/webinars/IESWEB0230.html)
*   [Wikipedia: Visuelle Programmiersprache](https://de.wikipedia.org/wiki/Visuelle_Programmiersprache)
*   [M5Stack UIFlow Dokumentation](https://m5stack.github.io/UIFlow_doc/en/)