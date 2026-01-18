# Abgrenzung und Einordnung

Um die Besonderheiten der IEC 61499 zu verstehen, ist es hilfreich, sie in die breitere Landschaft der Programmiersprachen einzuordnen. Grundsätzlich lassen sich Programmiersprachen nach der Art ihrer Notation in zwei Hauptgruppen unterteilen: **textuelle** und **visuelle** Sprachen.

## Abgrenzung visuelle/textuelle Programmiersprachen

Der wesentliche Unterschied liegt in der Art und Weise, wie die Logik eines Programms formuliert wird. Während textuelle Sprachen auf sequenziellem Code basieren, nutzen visuelle Sprachen grafische Elemente, um Zusammenhänge und Datenflüsse darzustellen.

```{eval-rst}
.. mermaid:: Diagramm.mmd
```

### Textuelle Programmiersprachen
In textuellen Sprachen wird der Algorithmus durch eine Abfolge von Zeichenfolgen (Schlüsselwörter, Operatoren, Variablen) beschrieben. Diese Sprachen sind oft sehr mächtig und abstrakt, erfordern jedoch eine präzise Kenntnis der Syntax.

```{eval-rst}
.. mermaid:: Diagramm2.mmd
```

Typische Vertreter sind:
*   **C / C++:** Systemnahe Programmierung, hohe Performance.
*   **Python:** Sehr beliebt für Data Science und Automatisierung durch einfache Syntax.
*   **Java / C#:** Objektorientierte Sprachen, weit verbreitet in der Unternehmenssoftware.

### Visuelle Programmiersprachen
Visuelle Programmiersprachen (VPL) nutzen grafische Symbole, Blöcke oder Icons, die durch Linien (Verbindungen) miteinander verknüpft werden. Dies ermöglicht es oft, komplexe Zusammenhänge (wie z. B. Signalflüsse in der Elektrotechnik) intuitiver darzustellen.

```{eval-rst}
.. mermaid:: Diagramm2a.mmd
```

Man unterscheidet hierbei oft nach dem Einsatzzweck:
1.  **Erziehungsorientierte Sprachen:** Diese dienen meist dem Erlernen von Programmierkonzepten ohne Syntax-Hürden. Bekannte Beispiele sind **Scratch** oder **Blockly**.
2.  **Industrielle visuelle Sprachen:** Diese sind für den professionellen Einsatz in der Automatisierungstechnik konzipiert.

---

## Fokus: Industrielle visuelle Programmiersprachen

In der Industrie hat die visuelle Programmierung eine lange Tradition, da sie eng an die Darstellung von Schaltplänen und Prozessabläufen angelehnt ist.

```{eval-rst}
.. mermaid:: Diagramm3.mmd
```

### IEC 61131-3 (Der klassische Standard)
Die IEC 61131-3 ist der weltweit etablierte Standard für speicherprogrammierbare Steuerungen (SPS). Sie bietet sowohl textuelle als auch visuelle Sprachen an:
*   **LD (Ladder Diagram / Kontaktplan):** Angelehnt an Stromlaufpläne.
*   **FBD (Function Block Diagram / Funktionsbausteinsprache):** Darstellung von Logik als verknüpfte Blöcke.
*   **SFC (Sequential Function Chart / Ablaufsprache):** Modellierung von Schrittketten.
*   **ST (Structured Text) & IL (Instruction List):** Die textuellen Vertreter innerhalb der Norm.

### IEC 61499 (Der Standard für verteilte Systeme)
Die **IEC 61499** geht einen Schritt weiter. Sie nutzt das Konzept der **Function Blocks (FB)** konsequent für die Modellierung des gesamten Systems. Ein wesentlicher Unterschied ist die ereignisorientierte Ausführung, die durch die **ECC (Event Execution Control)** innerhalb der Bausteine gesteuert wird.

---

## Zusammenfassung: Warum visuell programmieren?

| Merkmal | Textuelle Sprachen | Visuelle Sprachen |
| :--- | :--- | :--- |
| **Lernkurve** | Oft steiler (Syntax auswendig lernen) | Flacher (Intuitive Symbole) |
| **Abstraktion** | Sehr hoch möglich | Gut für Daten- und Signalflüsse |
| **Fehleranfälligkeit** | Syntaxfehler häufig | Syntaxfehler durch GUI oft unmöglich |
| **Einsatzgebiet** | Web, Desktop, Systemnah | Automatisierung, Lehre, Workflow-Design |

### Literatur und Quellen
*   [Wikipedia: Visuelle Programmiersprache](https://de.wikipedia.org/wiki/Visuelle_Programmiersprache)
*   [YouTube: Visual vs. Textual Programming (Prägnante Zusammenfassung)](https://www.youtube.com/watch?v=MxJcdqOX9V0)
*   [Vergleich bei Print2Forms](https://wiki.print2forms.de/doku.php?id=print2forms:skripte:textuellvsvisuell)