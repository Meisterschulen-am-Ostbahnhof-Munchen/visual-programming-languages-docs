# ℹ️ Allgemeines





In diesem Abschnitt werden grundlegende Konzepte erläutert, die für die Programmierung nach IEC 61131-3 und IEC 61499 sowie für die allgemeine Informatik wichtig sind.

## Identifikatoren (Namenskonventionen)

Namen von Variablen, Funktionsbausteinen, Programmen und anderen Elementen werden als **Identifikatoren** bezeichnet. Um einen sauberen und portablen Code zu gewährleisten, legt die Norm IEC 61131-3 strikte Regeln fest.

### Grundregeln der Norm
1.  **Zeichensatz:** Identifikatoren dürfen nur aus Buchstaben (A-Z, a-z), Ziffern (0-9) und dem Unterstrich (_) bestehen.
2.  **Anfang:** Ein Name darf **nicht mit einer Ziffer** beginnen. Er muss mit einem Buchstaben oder einem Unterstrich starten.
3.  **Leerzeichen:** Leerzeichen sind innerhalb eines Namens nicht erlaubt.
4.  **Sonderzeichen:** Umlaute (ä, ö, ü) und Sonderzeichen ($, %, &, /) sind strikt verboten.
5.  **Groß-/Kleinschreibung:** In der Standard-IEC 61131-3 wird meist nicht zwischen Groß- und Kleinschreibung unterschieden (`Motor_An` ist gleich `motor_an`). Es ist jedoch gute Praxis, eine konsistente Schreibweise beizubehalten.
6.  **Reservierte Wörter:** Schlüsselwörter der Sprache (z. B. `IF`, `THEN`, `VAR`, `END_VAR`) dürfen nicht als Identifikatoren verwendet werden.

### Best Practices (Empfehlungen)
*   **Unterstriche:** Vermeiden Sie einfache Unterstriche am Anfang von Namen, da diese häufig für systeminterne Bibliotheksfunktionen reserviert sind.
*   **Doppelte Unterstriche:** Diese sind in vielen Systemen reserviert oder verboten.
*   **Klarheit:** Namen sollten selbsterklärend sein. Verwenden Sie lieber `Temperatur_Sensor_1` statt `T_S1`.
*   **Schreibweisen:**
    *   **CamelCase:** `MaxTemperatur`
    *   **Snake_Case:** `Max_Temperatur` (in der SPS-Welt sehr verbreitet)

| Erlaubt | Verboten | Grund |
| :--- | :--- | :--- |
| `Maehwerk_An` | `Mähwerk_An` | Sonderzeichen (ä) |
| `Start_Taster_1` | `1_Start_Taster` | Beginnt mit Ziffer |
| `Sollwert_Vorgabe` | `Sollwert Vorgabe` | Leerzeichen |
| `__Internal` | `Internal!` | Sonderzeichen (!) |

---

## Zahlen und Literale

Die Darstellung von Zahlen (Binär, Hexadezimal, Dezimal) und die Verwendung von Literalen im Code sind für die Steuerungsprogrammierung essenziell.

*   Detaillierte Informationen finden Sie hier: **[Zahlen und Zahlensysteme](Zahlen.md)**

---

## 💾 Datentypen

Datentypen legen fest, welche Art von Information eine Variable speichern kann (z. B. eine ganze Zahl, eine Fließkommazahl oder ein Wahrheitswert).

*   Eine Übersicht finden Sie hier: **[Datentypen](Datentypen/index.md)**
*   Informationen zu generischen Datentypen: **[ANY-Typen](Datentypen/GenerischeDatentypen/ANY_Typen.md)**
*   Welche Typen miteinander verbunden werden dürfen: **[Typkompatibilität](Datentypen/Typkompatibilität.md)**

---

## 🚜 Eselsbrücke: Normnummer merken

Wer sich die Nummer **IEC 61499** partout nicht merken kann, findet hier eine Gedächtnisstütze:

*   **[Eselsbrücke: IEC 61499](Eselsbruecke_IEC61499.md)**

