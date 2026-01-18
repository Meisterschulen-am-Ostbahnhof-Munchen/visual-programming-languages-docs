# Normen und Standards

In der industriellen Automatisierung bilden Normen das Fundament für Interoperabilität, Sicherheit und Effizienz. Sie stellen sicher, dass Systeme verschiedener Hersteller zusammenarbeiten können und Software portabel bleibt.

## IEC 61499: Der Standard für verteilte Systeme

Die IEC 61499 ist die zentrale Norm für dieses Projekt. Sie erweitert das Modell der IEC 61131-3 um eine systemweite Architektur für verteilte Steuerungssysteme.

### Struktur der Norm
Die Norm ist in mehrere Teile gegliedert, die unterschiedliche Aspekte abdecken:

*   **Teil 1: Architektur:** Definiert das grundlegende Modell für verteilte Systeme, einschließlich Funktionsbausteinen (Function Blocks), Ressourcen und Geräten.
*   **Teil 2: Anforderungen an Software-Werkzeuge:** Legt fest, welche Eigenschaften Software-Werkzeuge (wie die 4diac IDE) besitzen müssen, um konforme Anwendungen zu erstellen.
*   **Teil 4: Regeln für Compliance-Profile:** Definiert, wie spezifische Profile erstellt werden müssen, um die Interoperabilität zwischen verschiedenen Systemen (z. B. für eine bestimmte Branche) zu garantieren.

### Bezugsquellen
Normen sind in Deutschland klassischerweise über den **Beuth Verlag** (DIN) zu beziehen. Ein hilfreicher Tipp aus der Praxis ist der Bezug über die **EVS (Estonian Centre for Standardisation and Accreditation)**. Dort sind die identischen europäischen Normen oft deutlich kostengünstiger erhältlich (besonders die "3 User Licence").

**Links:**
* [Wikipedia (DE): EN 61499](https://de.wikipedia.org/wiki/EN_61499)
* [Wikipedia (EN): IEC 61499](https://en.wikipedia.org/wiki/IEC_61499)
* [Beuth Verlag: DIN EN 61499](https://www.beuth.de/de/norm/din-en-61499-1/209152944)
* [EVS Estland: EVS-EN 61499](https://www.evs.ee/en/evs-en-61499-1-2013)

---

## IEC 61131-3: Die klassische SPS-Programmierung

Bevor die IEC 61499 Einzug hielt, war (und ist) die IEC 61131-3 der weltweite Standard für Programmiersprachen von speicherprogrammierbaren Steuerungen (SPS). Sie definiert Sprachen wie:
*   Anweisungsliste (AWL / IL)
*   Strukturierter Text (ST)
*   Kontaktplan (KOP / LD)
*   Funktionsbausteinsprache (FBS / FBD)
*   Ablaufsprache (AS / SFC)

In modernen Systemen dient die IEC 61131-3 oft als Grundlage für die Logik innerhalb eines IEC 61499 Funktionsbausteins.

---

## ISO 11783 (ISOBUS): Kommunikation in der Landtechnik

Der ISOBUS-Standard basiert auf dem CAN-Bus und ist entscheidend für die Kommunikation zwischen Traktoren und Anbaugeräten. Er stellt sicher, dass ein Terminal im Traktor Geräte verschiedener Hersteller steuern kann.

Die Norm ist extrem umfangreich und umfasst 14 Teile, von der physikalischen Schicht (Kabel/Stecker) über das Netzwerkmanagement bis hin zum Task-Controller und der Diagnose.

---

## Grafische Symbole und Sicherheit

Für die Gestaltung von Benutzeroberflächen (HMIs) und die Kennzeichnung von Hardware sind einheitliche Symbole unerlässlich.

*   **ISO 7000 / IEC 60417:** Eine umfangreiche Sammlung grafischer Symbole für die Verwendung auf Geräten (z. B. "Ein/Aus", Warnhinweise).
*   **ISO 7010:** Spezifische Sicherheitszeichen und -farben zur Unfallverhütung.

**Ressource:**
Alle registrierten Symbole können in der [ISO Online Browsing Platform (OBP)](https://www.iso.org/obp) eingesehen werden.