# Uebung_012f: Numeric Value Input PHYS und Speichern NVS mit Subapp

* * * * * * * * * *
## Einleitung
Die Übung demonstriert die Verarbeitung eines physikalischen numerischen Werts (PHYS) und dessen dauerhafte Speicherung in einem nichtflüchtigen Speicher (NVS). Der Wert wird über einen Eingangsobjekt-Pool konfiguriert, in den NVS geschrieben und kann anschließend über einen Qualifier-Baustein ausgegeben werden. Die Übung ist als geschachtelte SubApplikation realisiert, wobei der innere Sub-Baustein die gesamte Logik enthält.

## Verwendete Funktionsbausteine (FBs)
Die Übung besteht aus einem Haupt-Sub-Baustein, der einen weiteren Sub-Baustein enthält. Dieser innere Sub-Baustein kapselt die eigentliche Verarbeitungslogik mit drei internen FBs.

### Sub-Baustein: Uebung_012f_sub
- **Typ**: `Uebungen::Uebung_012f_sub`
- **Schnittstelle**:
  - Ereignisausgang: `IND` (Event)
  - Dateneingänge: `KEY` (STRING), `stObj` (NumericObjectPool_S)
  - Datenausgang: `VALUEO` (REAL)
- **Verwendete interne FBs**:
  - **NumericValue_PHYS** (`isobus::UT::io::NumericValue::NumericValue_PHYS`)
    - Parameter: `QI` = `TRUE`
    - Ereignisausgang: `IND` → wird bei gültigem Wert ausgelöst
    - Dateneingang: `stObj` (NumericObjectPool_S – Konfiguration des physikalischen Objekts)
    - Datenausgang: `rPhys` (REAL) – der gelesene physikalische Wert
  - **NVS** (`logiBUS::storage::esp32_nvs::NVS`)
    - Parameter: `QI` = `TRUE`, `DEFAULT_VALUE` = `REAL#0.0`
    - Ereigniseingänge: `INIT`, `SET`, `GET`
    - Ereignisausgänge: `INITO`, `SETO`, `GETO`
    - Dateneingänge: `KEY` (STRING), `VALUE` (REAL)
    - Datenausgang: `VALUEO` (REAL) – der gelesene oder geschriebene Wert
  - **Q_NumericValue_PHYS** (`isobus::UT::Q::Q_NumericValue_PHYS`)
    - Ereigniseingang: `REQ`
    - Dateneingänge: `stObj` (NumericObjectPool_S), `rPhys` (REAL)
    - Datenausgang: (keine im XML sichtbar, dient der Qualifikation/Weitergabe)
- **Funktionsweise**:
  Der Sub-Baustein `Uebung_012f_sub` empfängt die Konfigurationsdaten `KEY` und `stObj` von außen. Nach der Initialisierung des NVS-Bausteins (Ereignis `INITO`) wird sofort ein `GET` ausgelöst, um den zuletzt gespeicherten Wert zu laden. Bei einem gültigen physikalischen Wert (Ereignis `IND` vom `NumericValue_PHYS`) wird dieser mit dem aktuellen `rPhys` über `SET` im NVS gespeichert. Der geladene oder gespeicherte Wert wird über den Qualifier-Baustein `Q_NumericValue_PHYS` aufbereitet und am Ausgang `VALUEO` bereitgestellt. Die Ereignisse `SETO` und `GETO` werden zum äußeren `IND`-Ausgang weitergeleitet.

## Programmablauf und Verbindungen
Der Ablauf ist ereignisgesteuert:

1. **Initialisierung**: Beim Start erhält der NVS-Baustein ein `INIT`-Ereignis (nicht im Netzwerk sichtbar, aber implizit durch die Umgebung). Der Baustein quittiert mit `INITO` und löst sofort ein `GET` aus (Verbindung `NVS.INITO` -> `NVS.GET`). Dadurch wird der unter dem übergebenen `KEY` gespeicherte Wert aus dem NVS gelesen.
2. **Wertaktualisierung**: Sobald der `NumericValue_PHYS`-Baustein einen gültigen physikalischen Wert erfasst hat, sendet er ein `IND`-Ereignis. Dieses triggert den `SET`-Eingang des NVS, wodurch der aktuelle `rPhys`-Wert unter dem angegebenen `KEY` gespeichert wird.
3. **Ausgabe**: Sowohl nach einem `GET` (bei Initialisierung) als auch nach einem `SET` (nach Speicherung) wird das Ergebnis über `NVS.VALUEO` an den `Q_NumericValue_PHYS`-Baustein und direkt an den Ausgang `VALUEO` weitergeleitet. Der Qualifier-Baustein bereitet den Wert entsprechend der Konfiguration (`stObj`) auf.
4. **Signalweitergabe**: Die Ereignisausgänge `SETO` und `GETO` des NVS werden zum äußeren Ausgang `IND` durchgereicht, sodass die übergeordnete Ebene über Änderungen informiert wird.

**Datenverbindungen**:
- `stObj` (extern) → `NumericValue_PHYS.stObj` (Konfiguration des physikalischen Objekts)
- `KEY` (extern) → `NVS.KEY` (Speicherschlüssel)
- `NumericValue_PHYS.rPhys` → `NVS.VALUE` (zu speichernder Wert)
- `NVS.VALUEO` → `Q_NumericValue_PHYS.rPhys` (weitergeleiteter Wert)
- `stObj` (extern) → `Q_NumericValue_PHYS.stObj` (Konfiguration für die Ausgabe)
- `NVS.VALUEO` → `VALUEO` (externe Ausgabe)

## Zusammenfassung
Die Übung `Uebung_012f` zeigt, wie ein physikalischer Messwert (über den `NumericValue_PHYS`-Baustein) eingelesen, persistent in einem nichtflüchtigen Speicher (`NVS`) abgelegt und über einen Qualifier-Baustein ausgegeben wird. Der Schlüssel für die Speicherung und die Objektkonfiguration werden von außen übergeben, was eine flexible Wiederverwendung ermöglicht. Die ereignisgesteuerte Kopplung sorgt für eine korrekte Ablaufreihenfolge von Lesen, Schreiben und Ausgeben. Diese Struktur eignet sich besonders für Anwendungen, bei denen Werte nach dem Einschalten aus einem Speicher wiederhergestellt werden müssen.