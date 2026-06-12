# ATM_AX_TOF


![ATM_AX_TOF](./ATM_AX_TOF.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `ATM_AX_TOF` realisiert eine Ausschaltverzögerung (off-delay timing) mit einer modularen Adapter-Schnittstelle auf Basis der Typen `AX` und `ATM`. Er wird typischerweise eingesetzt, um nach dem Wegfallen eines Eingangssignals einen Ausgang für eine definierte Zeit aktiv zu halten. Der Baustein ist als Standard-Timer-FB gemäß IEC 61499-2 klassifiziert und intern mit dem FB `E_TOF` realisiert.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Name | Typ   | Kommentar |
|------|-------|-----------|
| R    | Event | Setzt den Timer zurück (Reset) |

### **Ereignis-Ausgänge**
Keine direkten Ereignis-Ausgänge vorhanden. Der Ausgang erfolgt über den Adapter `Q`.

### **Daten-Eingänge**
Keine direkten Daten-Eingänge vorhanden. Die Daten werden über die Adapter `IN` und `PT` bereitgestellt.

### **Daten-Ausgänge**
Keine direkten Daten-Ausgänge vorhanden. Der Ausgang erfolgt über den Adapter `Q`.

### **Adapter**
| Name | Richtung | Typ  | Beschreibung |
|------|----------|------|--------------|
| IN   | Socket   | AX   | Eingangsadapter: Liefert das boolsche Triggersignal (D1: BOOL) und einen Event (E1) zur Auslösung der Timer-Funktion |
| PT   | Socket   | ATM  | Zeitadapter: Liefert die Verzögerungszeit (D1: TIME) |
| Q    | Plug     | AX   | Ausgangsadapter: Stellt das boolsche Ausgangssignal (D1: BOOL) und einen Bestätigungs-Event (E1) bereit |

## Funktionsweise
Der `ATM_AX_TOF` arbeitet nach dem Prinzip einer **Ausschaltverzögerung** (Off-Delay):

1. **Normalbetrieb:** Solange der Eingang `IN.D1` (BOOL) den Wert `TRUE` hat, ist der Ausgang `Q.D1` sofort `TRUE` (ohne Verzögerung).
2. **Ausschaltverzögerung:** Wechselt `IN.D1` von `TRUE` auf `FALSE`, bleibt `Q.D1` für die in `PT.D1` (TIME) angegebene Zeitspanne auf `TRUE`. Nach Ablauf dieser Zeit geht `Q.D1` auf `FALSE`.
3. **Reset:** Ein Ereignis am Eingang `R` setzt den internen Timer sofort zurück. `Q.D1` wird unverzüglich `FALSE`, unabhängig vom aktuellen Zustand von `IN.D1` oder von der Restzeit.

Die Auslösung erfolgt durch den Event `IN.E1` – ein neuer Wert an `IN.D1` wird erst nach einem Ereignis übernommen. Ein Ereignis auf `Q.E1` bestätigt jede Zustandsänderung von `Q.D1`.

## Technische Besonderheiten
- **Adapterbasierte Schnittstelle:** Die Verwendung der universellen Adapter `AX` und `ATM` ermöglicht eine flexible Anbindung an Adressierungs- oder andere Module ohne feste Verdrahtung.
- **Interne Realisierung:** Der Baustein nutzt den Standard-FB `E_TOF` aus der IEC 61499-Bibliothek, was eine robuste und geprüfte Timerlogik gewährleistet.
- **Reset-Funktion:** Der Reset-Eingang `R` erlaubt ein sofortiges Abbrechen der Verzögerung, z. B. zur Steuerung von Sicherheitsfunktionen.
- **Kompatibilität:** Entwickelt für die 4diac-IDE und basierend auf dem Eclipse Public License 2.0.

## Zustandsübersicht
Der FB durchläuft folgende Betriebszustände:

| Zustand         | Bedingungen                       | Q.D1  | Beschreibung |
|-----------------|-----------------------------------|-------|--------------|
| **Idle**        | IN.D1 = FALSE, Timer läuft nicht  | FALSE | Ruhezustand nach Ablauf oder Reset |
| **Active**      | IN.D1 = TRUE                      | TRUE  | Eingang aktiv, Ausgang sofort TRUE |
| **Timing**      | IN.D1 von TRUE → FALSE, Timer aktiv | TRUE | Verzögerungsphase: Ausgang bleibt TRUE für Dauer PT |
| **Resetting**   | Ereignis R während Timing oder Active | FALSE | Timer wird sofort gestoppt, Ausgang geht auf FALSE |

## Anwendungsszenarien
- **Nachlauf von Lüftern:** Nach Abschalten eines Motors läuft der Lüfter für eine einstellbare Zeit weiter, um Restwärme abzuführen.
- **Entprellung von Signalen:** Kurze Unterbrechungen eines Sensorsignals werden durch die Verzögerung überbrückt.
- **Beleuchtungssteuerung:** Licht bleibt nach Verlassen eines Raumes für eine definierte Nachlaufzeit an.
- **Sicherheitsabschaltungen:** Reset über R ermöglicht ein sofortiges Abschalten in Notfällen.

## Vergleich mit ähnlichen Bausteinen
| Eigenschaft             | ATM_AX_TOF                               | E_TOF (Standard)                     |
|-------------------------|------------------------------------------|--------------------------------------|
| Schnittstelle           | Adapter (AX/ATM)                         | Direkte Events/Daten                 |
| Reset-Funktion          | Ja (Ereignis R)                          | Ja (Ereignis R)                      |
| Auslösung               | Ereignisgesteuert über Adapter-Event     | Ereignisgesteuert über REQ           |
| Flexibilität            | Höher durch Adapter-Kopplung             | Einfacher, aber starrer              |
| Einsatzbereich          | Modulare Automatisierungssysteme         | Grundfunktion in IEC 61499-Editoren  |

## Fazit
Der `ATM_AX_TOF` bietet eine zuverlässige und flexible Ausschaltverzögerung für modulare Automatisierungsprojekte. Dank der Adapter-Schnittstelle lässt er sich leicht in verschiedene Systemlandschaften integrieren und erweitert die Funktionalität des Standard-Timers `E_TOF` um eine Reset-Möglichkeit sowie eine lose Kopplung über AX/AT-Adapter. Er ist ideal für Anwendungen, bei denen eine zeitverzögerte Abschaltung mit optionaler Sofortrücksetzung benötigt wird.