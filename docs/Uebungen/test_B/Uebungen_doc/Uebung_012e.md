# Uebung_012e: Numeric Value Input PHYS und Speichern INI mit Subapp

* * * * * * * * * *

## Einleitung

Diese Übung demonstriert das Einlesen eines numerischen Werts über einen physikalischen Eingangsbaustein (`NumericValue_PHYS`) und das dauerhafte Speichern des Werts mittels eines INI-Datei-Bausteins. Die gesamte Logik ist in einer Subapp gekapselt, die als wiederverwendbare Komponente dient. Ziel ist es, einen Wert über eine objektbasierte Konfiguration zu erfassen, zwischenzuspeichern und bei Bedarf wieder auszulesen.

## Verwendete Funktionsbausteine (FBs)

### Haupt-Subapp: `Uebung_012e`

- Instanziiert die Subapp `Uebung_012e_sub` mit vorgegebenen Parametern für Schlüssel, Abschnitt und Objekt.
- Die Haupt-Subapp hat keine eigenen Ein-/Ausgänge; das Verhalten wird vollständig durch den Sub-Baustein definiert.

### Sub-Bausteine: `Uebung_012e_sub`

- **Typ**: `SubAppType`
- **Verwendete interne FBs**:
  - **`NumericValue_PHYS`**: `isobus::UT::io::NumericValue::NumericValue_PHYS`
    - Parameter: `QI` = `TRUE`
    - Ereignisausgang: `IND` (wird nach erfolgreicher Werteerfassung ausgelöst)
    - Dateneingang: `stObj` (Objektkonfiguration vom Typ `NumericObjectPool_S`)
    - Datenausgang: `rPhys` (physikalischer Wert als `REAL`)
  - **`INI`**: `eclipse4diac::storage::INI`
    - Parameter:
      - `QI` = `TRUE`
      - `DEFAULT_VALUE` = `REAL#0.0`
    - Ereigniseingänge: `SET`, `GET`, `INIT`
    - Ereignisausgänge: `SETO`, `GETO`, `INITO`
    - Dateneingänge: `KEY` (`STRING`), `SECTION` (`STRING`), `VALUE` (`REAL`)
    - Datenausgang: `VALUEO` (`REAL`)
  - **`Q_NumericValue_PHYS`**: `isobus::UT::Q::Q_NumericValue_PHYS`
    - Ereigniseingang: `REQ`
    - Dateneingänge: `stObj` (Objektkonfiguration), `rPhys` (Wert)
    - Funktion: Qualifiziert den physikalischen Wert (z. B. zur Skalierung oder Offsetsetzung)
- **Funktionsweise**:
  1. Der Baustein `NumericValue_PHYS` liest gemäß der Objektkonfiguration (`stObj`) einen Wert und gibt diesen als `rPhys` aus. Nach erfolgreicher Erfassung wird das Ereignis `IND` gesendet.
  2. Das Ereignis `IND` löst den `SET`-Eingang des `INI`-Bausteins aus. Dieser speichert den Wert unter dem angegebenen `KEY` in der `SECTION` der INI-Datei.
  3. Nach dem Speichern wird `SETO` ausgelöst, welches über den Ausgang `IND` der Subapp weitergereicht wird.
  4. Gleichzeitig startet die Initialisierungskette: `INITO` von `INI` wird mit `GET` verbunden, sodass nach dem Start der Subapp der gespeicherte Wert ausgelesen wird.
  5. Der ausgelesene Wert (`VALUEO`) wird an den Baustein `Q_NumericValue_PHYS` übergeben, der ihn mit der Objektkonfiguration qualifiziert und an den Ausgang `VALUEO` der Subapp weiterleitet.

## Programmablauf und Verbindungen

Die Subapp arbeitet in zwei Hauptphasen:

1. **Initialisierung (Start)**:
   - Das Ereignis `INITO` des `INI`-Bausteins wird intern mit dem `GET`-Eingang verbunden.
   - Dadurch wird sofort der gespeicherte Wert aus der INI-Datei gelesen.
   - Der gelesene Wert wird über `VALUEO` an `Q_NumericValue_PHYS` und an den Ausgang der Subapp weitergegeben.
   - Das Ereignis `GETO` wird ebenfalls an den Ausgang `IND` der Subapp gesendet.

2. **Zyklischer Betrieb (bei Wertänderung)**:
   - `NumericValue_PHYS` erfasst bei Aktivierung einen neuen physikalischen Wert.
   - Dieser Wert wird über `rPhys` an den `VALUE`-Eingang des `INI`-Bausteins gelegt.
   - Das Ereignis `IND` von `NumericValue_PHYS` triggert den `SET`-Eingang von `INI`, wodurch der Wert gespeichert wird.
   - Nach erfolgreichem Speichern wird `SETO` ausgelöst, das als `IND` der Subapp nach außen gegeben wird.

**Datenverbindungen**:
- Die Objektkonfiguration (`stObj`) wird von außen an `NumericValue_PHYS` und an `Q_NumericValue_PHYS` übergeben.
- Die Schlüssel- und Abschnittsnamen (`KEY`, `SECTION`) werden von außen an den `INI`-Baustein übergeben.
- Der gespeicherte Wert (`VALUEO`) wird sowohl an `Q_NumericValue_PHYS` als auch direkt an den Ausgang `VALUEO` der Subapp geführt.

## Zusammenfassung

Die Übung vermittelt den Umgang mit physikalischen Werteingaben und persistenter Datenspeicherung in 4diac. Sie zeigt, wie man mit der Subapp-Technik eine wiederverwendbare Komponente erstellt, die:
- einen numerischen Wert über ein Objekt einliest,
- diesen Wert in einer INI-Datei speichert,
- den gespeicherten Wert bei Systemstart wiederherstellt und
- den Wert über einen Qualifier-Baustein prozessiert.

Durch die Kombination der Bausteine `NumericValue_PHYS`, `INI` und `Q_NumericValue_PHYS` wird ein typisches Szenario aus der Automatisierungstechnik (Erfassen, Speichern und Wiederherstellen von Parametern) abgebildet.