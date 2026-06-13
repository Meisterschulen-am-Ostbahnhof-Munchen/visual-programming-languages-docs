# IE


## 🎧 Podcast

* [4diac IDE: Dein "Hello World" der Automatisierung – Das Blinking Tutorial Lokal](https://podcasters.spotify.com/pod/show/eclipse-4diac-de/episodes/4diac-IDE-Dein-Hello-World-der-Automatisierung--Das-Blinking-Tutorial-Lokal-e36971r)
* [4diac IDE: Dein Open-Source-Werkzeugkasten für verteilte Industrieautomatisierung nach IEC 61499](https://podcasters.spotify.com/pod/show/eclipse-4diac-de/episodes/4diac-IDE-Dein-Open-Source-Werkzeugkasten-fr-verteilte-Industrieautomatisierung-nach-IEC-61499-e36821e)
* [4diac IDE: Wie der IEC 61499 Standard die Industrieautomatisierung revolutioniert](https://podcasters.spotify.com/pod/show/eclipse-4diac-de/episodes/4diac-IDE-Wie-der-IEC-61499-Standard-die-Industrieautomatisierung-revolutioniert-e36756a)
* [4diac-Präsentation: Zielgruppen, Struktur und Alleinstellungsmerkmal Schärfen](https://podcasters.spotify.com/pod/show/eclipse-4diac-de/episodes/4diac-Prsentation-Zielgruppen--Struktur-und-Alleinstellungsmerkmal-Schrfen-e38ckbo)
* [Den Software-Drachen zähmen: Industrielle Automatisierung und die Zukunft der Produktion](https://podcasters.spotify.com/pod/show/eclipse-4diac-de/episodes/Den-Software-Drachen-zhmen-Industrielle-Automatisierung-und-die-Zukunft-der-Produktion-e372eg1)

## 📺 Video

* [Die große Migration](https://www.youtube.com/watch?v=XcBu7y6ch4E)
* [Die Kunst des Lötens](https://www.youtube.com/watch?v=I6Srdxx6fzU)
* [Die Welt der Normung](https://www.youtube.com/watch?v=9phDmkJVaGM)
* [Löten wie ein Profi](https://www.youtube.com/watch?v=8ulMWcxaB-c)
* [The secret of the field](https://www.youtube.com/watch?v=MmMrEXum4w4)

## Einleitung
Der IE-Funktionsblock (Input Event) ist ein Service-Interface-Funktionsblock für die Verarbeitung von Ereigniseingangsdaten. Er dient als Schnittstelle zwischen der Steuerungslogik und externen Eingabegeräten oder -signalen und ermöglicht die Initialisierung, Abfrage und Indikation von Eingabeereignissen.

![IE](IE.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Service-Initialisierung - Initialisiert den Funktionsblock mit Parametern
- **REQ**: Service-Anfrage - Löst eine Abfrage des Eingabezustands aus

### **Ereignis-Ausgänge**
- **INITO**: Initialisierungsbestätigung - Bestätigt die erfolgreiche Initialisierung
- **CNF**: Service-Bestätigung - Bestätigt die verarbeitete Service-Anfrage
- **IND**: Indikation von der Ressource - Signalisiert eingehende Ereignisse von der Hardware

### **Daten-Eingänge**
- **QI** (BOOL): Ereignis-Eingangs-Qualifier - Aktiviert/deaktiviert die Ereignisverarbeitung
- **PARAMS** (STRING): Service-Parameter - Konfigurationsparameter für den Service

### **Daten-Ausgänge**
- **QO** (BOOL): Ereignis-Ausgangs-Qualifier - Status der Ereignisverarbeitung
- **STATUS** (STRING): Service-Status - Rückmeldung über den aktuellen Betriebszustand

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Der IE-Funktionsblock arbeitet als bidirektionale Schnittstelle für Eingabeereignisse. Bei der Initialisierung (INIT) werden die Service-Parameter konfiguriert. Über REQ-Ereignisse können gezielte Abfragen des Eingabezustands durchgeführt werden. Gleichzeitig kann der Block asynchron IND-Ereignisse generieren, wenn von der Hardware spontan Eingabeereignisse erkannt werden.

## Technische Besonderheiten
- Unterstützt sowohl poll-basierte (REQ/CNF) als auch interrupt-basierte (IND) Betriebsmodi
- String-basierte Parameter- und Statusübertragung für flexible Konfiguration
- Separate Qualifier für Eingangs- und Ausgangsereignisse (QI/QO)
- Robuste Fehlerbehandlung durch STATUS-Rückmeldungen

## Zustandsübersicht
Der Funktionsblock durchläuft folgende Hauptzustände:
1. **Nicht initialisiert**: Block wartet auf INIT-Ereignis
2. **Initialisiert**: Block ist betriebsbereit und kann REQ- und IND-Ereignisse verarbeiten
3. **Abfrage aktiv**: Verarbeitung einer REQ-Anfrage
4. **Indikation aktiv**: Verarbeitung eines spontanen Eingabeereignisses

## Anwendungsszenarien
- Abfrage von digitalen Eingängen (z.B. Taster, Schalter)
- Überwachung von Sensorsignalen
- Schnittstelle zu externen Eingabegeräten
- Ereignisgesteuerte Steuerungsanwendungen
- Hardware-nahe E/A-Verwaltung in Automatisierungssystemen

## ⚖️ Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfacheren Eingabeblöcken bietet IE erweiterte Funktionalität:
- Gegenüber reinen E/A-Blöcken: Unterstützt sowohl poll- als auch event-basierte Abfragen
- Gegenüber statischen Eingabeblöcken: Dynamische Parametrierung zur Laufzeit
- Erweiterte Statusrückmeldungen für verbesserte Fehlerdiagnose






## 🛠️ Zugehörige Übungen

* [Uebung_004a](../../../Uebungen/test_B/Uebungen_doc/Uebung_004a.md)
* [Uebung_004a2](../../../Uebungen/test_B/Uebungen_doc/Uebung_004a2.md)
* [Uebung_004a2_2](../../../Uebungen/test_B/Uebungen_doc/Uebung_004a2_2.md)
* [Uebung_004a2_3](../../../Uebungen/test_B/Uebungen_doc/Uebung_004a2_3.md)
* [Uebung_004a2_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_004a2_AX.md)
* [Uebung_004a3](../../../Uebungen/test_B/Uebungen_doc/Uebung_004a3.md)
* [Uebung_004a3_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_004a3_AX.md)
* [Uebung_004a4](../../../Uebungen/test_B/Uebungen_doc/Uebung_004a4.md)
* [Uebung_004a4_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_004a4_AX.md)
* [Uebung_004a5](../../../Uebungen/test_B/Uebungen_doc/Uebung_004a5.md)
* [Uebung_004a5_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_004a5_AX.md)
* [Uebung_004a6](../../../Uebungen/test_B/Uebungen_doc/Uebung_004a6.md)
* [Uebung_004a6_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_004a6_AX.md)
* [Uebung_004a7](../../../Uebungen/test_B/Uebungen_doc/Uebung_004a7.md)
* [Uebung_004a7_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_004a7_AX.md)
* [Uebung_004a8](../../../Uebungen/test_B/Uebungen_doc/Uebung_004a8.md)
* [Uebung_004a8_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_004a8_AX.md)
* [Uebung_004a9](../../../Uebungen/test_B/Uebungen_doc/Uebung_004a9.md)
* [Uebung_004a9_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_004a9_AX.md)
* [Uebung_004a_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_004a_AX.md)
* [Uebung_004b](../../../Uebungen/test_B/Uebungen_doc/Uebung_004b.md)
* [Uebung_004b2](../../../Uebungen/test_B/Uebungen_doc/Uebung_004b2.md)
* [Uebung_004b3](../../../Uebungen/test_B/Uebungen_doc/Uebung_004b3.md)
* [Uebung_004b_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_004b_AX.md)
* [Uebung_004b_AX_ASR](../../../Uebungen/test_AX/Uebungen_doc/Uebung_004b_AX_ASR.md)
* [Uebung_004b_AX_ASR_X](../../../Uebungen/test_AX/Uebungen_doc/Uebung_004b_AX_ASR_X.md)
* [Uebung_004c1](../../../Uebungen/test_B/Uebungen_doc/Uebung_004c1.md)
* [Uebung_004c1_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_004c1_AX.md)
* [Uebung_004c2](../../../Uebungen/test_B/Uebungen_doc/Uebung_004c2.md)
* [Uebung_004c2_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_004c2_AX.md)
* [Uebung_004c3](../../../Uebungen/test_B/Uebungen_doc/Uebung_004c3.md)
* [Uebung_004c3_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_004c3_AX.md)
* [Uebung_004c4](../../../Uebungen/test_B/Uebungen_doc/Uebung_004c4.md)
* [Uebung_004c4_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_004c4_AX.md)
* [Uebung_004c5](../../../Uebungen/test_B/Uebungen_doc/Uebung_004c5.md)
* [Uebung_004c5_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_004c5_AX.md)
* [Uebung_006](../../../Uebungen/test_B/Uebungen_doc/Uebung_006.md)
* [Uebung_006_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_006_AX.md)
* [Uebung_006a](../../../Uebungen/test_B/Uebungen_doc/Uebung_006a.md)
* [Uebung_006a2](../../../Uebungen/test_B/Uebungen_doc/Uebung_006a2.md)
* [Uebung_006a2_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_006a2_AX.md)
* [Uebung_006a3](../../../Uebungen/test_B/Uebungen_doc/Uebung_006a3.md)
* [Uebung_006a3_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_006a3_AX.md)
* [Uebung_006a4](../../../Uebungen/test_B/Uebungen_doc/Uebung_006a4.md)
* [Uebung_006a4_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_006a4_AX.md)
* [Uebung_006a_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_006a_AX.md)
* [Uebung_006b](../../../Uebungen/test_B/Uebungen_doc/Uebung_006b.md)
* [Uebung_006b_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_006b_AX.md)
* [Uebung_006d](../../../Uebungen/test_B/Uebungen_doc/Uebung_006d.md)
* [Uebung_006d_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_006d_AX.md)
* [Uebung_007a1](../../../Uebungen/test_B/Uebungen_doc/Uebung_007a1.md)
* [Uebung_007a1_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_007a1_AX.md)
* [Uebung_007a2](../../../Uebungen/test_B/Uebungen_doc/Uebung_007a2.md)
* [Uebung_007a2_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_007a2_AX.md)
* [Uebung_007a3](../../../Uebungen/test_B/Uebungen_doc/Uebung_007a3.md)
* [Uebung_007a3_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_007a3_AX.md)
* [Uebung_009a](../../../Uebungen/test_B/Uebungen_doc/Uebung_009a.md)
* [Uebung_010b2](../../../Uebungen/test_B/Uebungen_doc/Uebung_010b2.md)
* [Uebung_010b2_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_010b2_AX.md)
* [Uebung_010b3](../../../Uebungen/test_B/Uebungen_doc/Uebung_010b3.md)
* [Uebung_010b3_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_010b3_AX.md)
* [Uebung_010b6](../../../Uebungen/test_B/Uebungen_doc/Uebung_010b6.md)
* [Uebung_010b6_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_010b6_AX.md)
* [Uebung_010b7](../../../Uebungen/test_B/Uebungen_doc/Uebung_010b7.md)
* [Uebung_010b7_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_010b7_AX.md)
* [Uebung_010b8](../../../Uebungen/test_B/Uebungen_doc/Uebung_010b8.md)
* [Uebung_010b8_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_010b8_AX.md)
* [Uebung_010b9](../../../Uebungen/test_B/Uebungen_doc/Uebung_010b9.md)
* [Uebung_010b9_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_010b9_AX.md)
* [Uebung_010bA](../../../Uebungen/test_B/Uebungen_doc/Uebung_010bA.md)
* [Uebung_010bA2](../../../Uebungen/test_B/Uebungen_doc/Uebung_010bA2.md)
* [Uebung_010bA2_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_010bA2_AX.md)
* [Uebung_010bA3](../../../Uebungen/test_B/Uebungen_doc/Uebung_010bA3.md)
* [Uebung_010bA3_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_010bA3_AX.md)
* [Uebung_010bA4](../../../Uebungen/test_B/Uebungen_doc/Uebung_010bA4.md)
* [Uebung_010bA4_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_010bA4_AX.md)
* [Uebung_010bA_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_010bA_AX.md)
* [Uebung_013](../../../Uebungen/test_B/Uebungen_doc/Uebung_013.md)
* [Uebung_013_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_013_AX.md)
* [Uebung_014](../../../Uebungen/test_B/Uebungen_doc/Uebung_014.md)
* [Uebung_015](../../../Uebungen/test_B/Uebungen_doc/Uebung_015.md)
* [Uebung_015a](../../../Uebungen/test_B/Uebungen_doc/Uebung_015a.md)
* [Uebung_016](../../../Uebungen/test_B/Uebungen_doc/Uebung_016.md)
* [Uebung_016a](../../../Uebungen/test_B/Uebungen_doc/Uebung_016a.md)
* [Uebung_017](../../../Uebungen/test_B/Uebungen_doc/Uebung_017.md)
* [Uebung_018](../../../Uebungen/test_B/Uebungen_doc/Uebung_018.md)
* [Uebung_018a](../../../Uebungen/test_B/Uebungen_doc/Uebung_018a.md)
* [Uebung_019](../../../Uebungen/test_B/Uebungen_doc/Uebung_019.md)
* [Uebung_019a](../../../Uebungen/test_B/Uebungen_doc/Uebung_019a.md)
* [Uebung_019b](../../../Uebungen/test_B/Uebungen_doc/Uebung_019b.md)
* [Uebung_019c](../../../Uebungen/test_B/Uebungen_doc/Uebung_019c.md)
* [Uebung_020f3](../../../Uebungen/test_B/Uebungen_doc/Uebung_020f3.md)
* [Uebung_020f3_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_020f3_AX.md)
* [Uebung_020h](../../../Uebungen/test_B/Uebungen_doc/Uebung_020h.md)
* [Uebung_020h_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_020h_AX.md)
* [Uebung_020i](../../../Uebungen/test_B/Uebungen_doc/Uebung_020i.md)
* [Uebung_020i_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_020i_AX.md)
* [Uebung_021](../../../Uebungen/test_B/Uebungen_doc/Uebung_021.md)
* [Uebung_022](../../../Uebungen/test_B/Uebungen_doc/Uebung_022.md)
* [Uebung_023](../../../Uebungen/test_B/Uebungen_doc/Uebung_023.md)
* [Uebung_024](../../../Uebungen/test_B/Uebungen_doc/Uebung_024.md)
* [Uebung_025](../../../Uebungen/test_B/Uebungen_doc/Uebung_025.md)
* [Uebung_026](../../../Uebungen/test_B/Uebungen_doc/Uebung_026.md)
* [Uebung_031](../../../Uebungen/test_B/Uebungen_doc/Uebung_031.md)
* [Uebung_034b](../../../Uebungen/test_B/Uebungen_doc/Uebung_034b.md)
* [Uebung_035](../../../Uebungen/test_B/Uebungen_doc/Uebung_035.md)
* [Uebung_035a](../../../Uebungen/test_B/Uebungen_doc/Uebung_035a.md)
* [Uebung_035a1_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_035a1_AX.md)
* [Uebung_035a1b_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_035a1b_AX.md)
* [Uebung_035a2](../../../Uebungen/test_B/Uebungen_doc/Uebung_035a2.md)
* [Uebung_035a2_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_035a2_AX.md)
* [Uebung_035a3](../../../Uebungen/test_B/Uebungen_doc/Uebung_035a3.md)
* [Uebung_035a3_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_035a3_AX.md)
* [Uebung_035b](../../../Uebungen/test_B/Uebungen_doc/Uebung_035b.md)
* [Uebung_035c](../../../Uebungen/test_B/Uebungen_doc/Uebung_035c.md)
* [Uebung_036](../../../Uebungen/test_B/Uebungen_doc/Uebung_036.md)
* [Uebung_037](../../../Uebungen/test_B/Uebungen_doc/Uebung_037.md)
* [Uebung_038](../../../Uebungen/test_B/Uebungen_doc/Uebung_038.md)
* [Uebung_038_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_038_AX.md)
* [Uebung_039](../../../Uebungen/test_B/Uebungen_doc/Uebung_039.md)
* [Uebung_039a](../../../Uebungen/test_B/Uebungen_doc/Uebung_039a.md)
* [Uebung_039a_sub_Outputs](../../../Uebungen/test_B/Uebungen_doc/Uebung_039a_sub_Outputs.md)
* [Uebung_040](../../../Uebungen/test_B/Uebungen_doc/Uebung_040.md)
* [Uebung_040_2](../../../Uebungen/test_B/Uebungen_doc/Uebung_040_2.md)
* [Uebung_040_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_040_AX.md)
* [Uebung_041](../../../Uebungen/test_B/Uebungen_doc/Uebung_041.md)
* [Uebung_042](../../../Uebungen/test_B/Uebungen_doc/Uebung_042.md)
* [Uebung_043](../../../Uebungen/test_B/Uebungen_doc/Uebung_043.md)
* [Uebung_080](../../../Uebungen/test_B/Uebungen_doc/Uebung_080.md)
* [Uebung_080b](../../../Uebungen/test_B/Uebungen_doc/Uebung_080b.md)
* [Uebung_080c](../../../Uebungen/test_B/Uebungen_doc/Uebung_080c.md)
* [Uebung_081](../../../Uebungen/test_B/Uebungen_doc/Uebung_081.md)
* [Uebung_082](../../../Uebungen/test_B/Uebungen_doc/Uebung_082.md)
* [Uebung_083](../../../Uebungen/test_B/Uebungen_doc/Uebung_083.md)
* [Uebung_083_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_083_AX.md)
* [Uebung_084](../../../Uebungen/test_B/Uebungen_doc/Uebung_084.md)
* [Uebung_085](../../../Uebungen/test_B/Uebungen_doc/Uebung_085.md)
* [Uebung_087](../../../Uebungen/test_B/Uebungen_doc/Uebung_087.md)
* [Uebung_087a1](../../../Uebungen/test_B/Uebungen_doc/Uebung_087a1.md)
* [Uebung_091](../../../Uebungen/test_B/Uebungen_doc/Uebung_091.md)
* [Uebung_093](../../../Uebungen/test_B/Uebungen_doc/Uebung_093.md)
* [Uebung_093b](../../../Uebungen/test_B/Uebungen_doc/Uebung_093b.md)
* [Uebung_094](../../../Uebungen/test_B/Uebungen_doc/Uebung_094.md)
* [Uebung_094a](../../../Uebungen/test_B/Uebungen_doc/Uebung_094a.md)
* [Uebung_094a_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_094a_AX.md)
* [Uebung_095](../../../Uebungen/test_B/Uebungen_doc/Uebung_095.md)
* [Uebung_095_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_095_AX.md)
* [Uebung_110](../../../Uebungen/test_B/Uebungen_doc/Uebung_110.md)
* [Uebung_111](../../../Uebungen/test_B/Uebungen_doc/Uebung_111.md)
* [Uebung_124](../../../Uebungen/test_B/Uebungen_doc/Uebung_124.md)
* [Uebung_127](../../../Uebungen/test_B/Uebungen_doc/Uebung_127.md)
* [Uebung_128](../../../Uebungen/test_B/Uebungen_doc/Uebung_128.md)
* [Uebung_128b](../../../Uebungen/test_B/Uebungen_doc/Uebung_128b.md)
* [Uebung_132](../../../Uebungen/test_B/Uebungen_doc/Uebung_132.md)
* [Uebung_150_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_150_AX.md)
* [Uebung_151_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_151_AX.md)
* [Uebung_152](../../../Uebungen/test_B/Uebungen_doc/Uebung_152.md)
* [Uebung_153](../../../Uebungen/test_B/Uebungen_doc/Uebung_153.md)
* [Uebung_160b](../../../Uebungen/test_B/Uebungen_doc/Uebung_160b.md)
* [Uebung_160b_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_160b_AX.md)
* [Uebung_171_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_171_AX.md)
* [Uebung_179](../../../Uebungen/test_B/Uebungen_doc/Uebung_179.md)
* [Uebung_180](../../../Uebungen/test_B/Uebungen_doc/Uebung_180.md)

## Fazit
Der IE-Funktionsblock stellt eine flexible und robuste Lösung für die Behandlung von Eingabeereignissen in 4diac-basierten Steuerungssystemen dar. Seine Fähigkeit, sowohl synchrone Abfragen als auch asynchrone Indikationen zu verarbeiten, macht ihn besonders geeignet für Anwendungen, die sowohl reaktive als auch proaktive Eingabeverarbeitung erfordern.