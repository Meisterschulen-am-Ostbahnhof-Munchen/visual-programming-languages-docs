# Zahlen und Zahlensysteme

```{index} single: Zahlen und Zahlensysteme
```

In der Automatisierungstechnik begegnen uns Zahlen in verschiedenen Formaten. Je nachdem, ob wir einen physikalischen Wert (z. B. Temperatur), einen Zählerstand oder den Status einzelner Bits (z. B. digitale Eingänge) betrachten, wählen wir das passende Zahlensystem.

## 🎧 Podcast

* [ISOBUS-Terminals: Zahlen verstehen – NumberVariable, InputNumber & OutputNumber erklärt](https://podcasters.spotify.com/pod/show/isobus-vt-objects/episodes/ISOBUS-Terminals-Zahlen-verstehen--NumberVariable--InputNumber--OutputNumber-erklrt-e36aatd)

## Zahlensysteme

### Dezimalsystem (Basis 10)
Das uns vertraute System mit den Ziffern 0 bis 9. Es wird in der Programmierung meist für menschlich lesbare Werte wie Sollwerte, Zähler oder Zeitangaben verwendet.
*Beispiel:* `125`

### Binärsystem (Basis 2)
Da Computer und Steuerungen intern mit Zuständen (An/Aus, 0/1) arbeiten, ist das Binärsystem das grundlegendste System. Es besteht nur aus den Ziffern `0` und `1`.
In der IEC 61131-3 werden Binärzahlen mit dem Präfix `2#` gekennzeichnet.
*Beispiel:* `2#1011` (entspricht dezimal 11)

### Hexadezimalsystem (Basis 16)
Das Hexadezimalsystem ist für Programmierer besonders nützlich, da ein Byte (8 Bit) exakt durch zwei Hex-Ziffern (0-9 und A-F) dargestellt werden kann. Es bietet eine kompakte Darstellung von Bitmustern.
In der IEC 61131-3 werden Hex-Zahlen mit dem Präfix `16#` gekennzeichnet.
*Beispiel:* `16#FF` (entspricht dezimal 255 oder binär `2#11111111`)

---

## Literale in der IEC 61131-3 / IEC 61499

Literale sind fest im Programmcode geschriebene Werte. Um der Steuerung mitzuteilen, wie ein Wert zu interpretieren ist, können Typ-Präfixe verwendet werden.

### Ganzzahlen (Integer)
Ganzzahlen können ohne Nachkommastelle angegeben werden.
*   `1234` (Dezimal)
*   `-567` (Negativ)
*   `16#ABCD` (Hexadezimal)
*   `2#1010_0101` (Binär, Unterstriche dienen der Lesbarkeit)

### Gleitpunktzahlen (Real)
Werte mit Nachkommastellen oder in wissenschaftlicher Notation.
*   `1.234`
*   `-0.5`
*   `1.0E-3` (entspricht 0.001)

### Typisierte Literale
Manchmal ist es wichtig, den Datentyp explizit anzugeben, um Mehrdeutigkeiten zu vermeiden.
*   `INT#15`
*   `UINT#15`
*   `REAL#15.0`
*   `TIME#5s` (Zeitdauer von 5 Sekunden)

---

## Mathematische Hintergründe
Für tiefere Einblicke in die Mengenlehre der Zahlen (natürliche, ganze, reelle Zahlen) bieten folgende Begriffe eine gute Grundlage:

*   **Natürliche Zahlen (ℕ):** Positive ganze Zahlen {1, 2, 3, ...} – oft als Grundlage für `UINT` (Unsigned Integer).
*   **Ganze Zahlen (ℤ):** Zahlen ohne Nachkommastelle, inkl. Null und negativer Zahlen – Grundlage für `INT`, `DINT`, `LINT`.
*   **Reelle Zahlen (ℝ):** Zahlen mit Nachkommastellen – Grundlage für `REAL` und `LREAL`.