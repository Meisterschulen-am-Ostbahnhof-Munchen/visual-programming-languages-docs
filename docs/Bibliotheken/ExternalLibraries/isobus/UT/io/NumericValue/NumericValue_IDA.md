# NumericValue_IDA


![NumericValue_IDA](.././NumericValue_IDA.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein **NumericValue_IDA** ist ein Service-Schnittstellen-Baustein (Service Interface Function Block), der speziell für die Verarbeitung von numerischen Eingabedaten (Double Word Input Data) im Kontext von ISOBUS-Universal-Terminals (UT) entwickelt wurde. Er dient dazu, Änderungen von numerischen Werten, die auf einer Benutzeroberfläche (z. B. einem Traktor-Terminal) vorgenommen werden, in die Steuerungslogik zu übernehmen.

Im Gegensatz zu Standard-Eingabebausteinen stellt dieser Baustein die empfangenen Daten nicht über direkte Datenausgänge, sondern über einen Adapter-Anschluss (`IN`) zur Verfügung. Er kapselt die Funktionalität des Bausteins `NumericValue_ID` und leitet dessen Signale auf eine Adapter-Schnittstelle um.

![NumericValue_IDA](NumericValue_IDA.svg)

## Schnittstellenstruktur

Der Baustein verfügt über Standard-Initialisierungs- und Anforderungs-Ereignisse sowie spezifische Konfigurationsparameter. Die eigentliche Datenübertragung erfolgt über den Adapter.

### **Ereignis-Eingänge**

*   **INIT** (Typ: `EInit`): Service-Initialisierung. Dient zum Starten und Konfigurieren des Bausteins.
*   **REQ** (Typ: `Event`): Service-Anforderung. Kann genutzt werden, um den Status zu aktualisieren oder eine spezifische Interaktion anzufordern (abhängig von der internen Implementierung des Service-Layers).

### **Ereignis-Ausgänge**

*   **INITO** (Typ: `EInit`): Bestätigung der Initialisierung. Zeigt an, ob der Baustein erfolgreich konfiguriert wurde.

### **Daten-Eingänge**

*   **QI** (Typ: `BOOL`): Event Input Qualifier. Aktiviert die Ausführung der mit den Ereignissen verknüpften Aktionen.
*   **PARAMS** (Typ: `STRING`): Service-Parameter für spezifische Konfigurationen des darunterliegenden Service-Layers.
*   **u16ObjId** (Typ: `UINT`): Objekt-ID. Referenziert das spezifische numerische Eingabeobjekt auf dem Universal Terminal (UT), dessen Wert überwacht werden soll. Der Standardwert ist `ID_NULL`.

### **Daten-Ausgänge**

*   **QO** (Typ: `BOOL`): Event Output Qualifier. Zeigt an, ob die letzte Operation (z. B. Initialisierung) erfolgreich war.
*   **STATUS** (Typ: `STRING`): Service-Status. Enthält Fehlercodes oder Statusmeldungen zur Diagnose.

### **Adapter**

*   **IN** (Typ: `adapter::types::unidirectional::AD`):
    *   Dies ist ein unidirektionaler Adapter-Plug ("Input data from resource").
    *   Er bündelt das Ereignissignal (E1) und das Datensignal (D1), welches den aktuellen numerischen Wert vom Terminal enthält.
    *   Der Adapter wird getriggert, wenn der interne `NumericValue_ID` Baustein ein `IND` (Indication) oder `CNF` (Confirmation) Ereignis sendet.

## Funktionsweise

Der **NumericValue_IDA** fungiert als Wrapper für den internen Baustein `NumericValue_ID`.

1.  **Initialisierung:** Über das Ereignis `INIT` und die Daten-Eingänge `PARAMS` und `u16ObjId` wird die Verbindung zum spezifischen Objekt auf dem ISOBUS-Terminal hergestellt.
2.  **Datenempfang:** Wenn sich der Wert des referenzierten Objekts auf dem Terminal ändert oder vom System aktualisiert wird, empfängt der interne Baustein diese Informationen.
3.  **Weiterleitung:** Der interne Baustein leitet den neuen Wert (`IN`) und das zugehörige Ereignis an den Adapter `IN` des **NumericValue_IDA** weiter.
    *   Das Ereignis `E1` des Adapters wird ausgelöst.
    *   Der Datenpunkt `D1` des Adapters stellt den numerischen Wert zur Verfügung.

Dieser Mechanismus ermöglicht eine saubere Kapselung der Kommunikation, bei der die Anwendungslogik lediglich den Adapter `IN` verbinden muss, um auf Wertänderungen zu reagieren.

## Technische Besonderheiten

*   **Komposition:** Der Baustein ist als zusammengesetzter Funktionsbaustein (Composite FB) implementiert, der Instanzen aus dem Paket `isobus::UT::io::NumericValue` nutzt.
*   **Adapter-Nutzung:** Die Besonderheit liegt in der Verwendung des Adapters `AD` zur Datenausgabe. Dies reduziert die visuelle Komplexität im Funktionsplan, da Daten- und Ereignisfluss in einer einzigen Verbindungslinie gebündelt werden.
*   **ISOBUS-Kontext:** Der Baustein ist explizit für die Verwendung im ISOBUS-Stack (ISO 11783) vorgesehen, erkennbar an der Verwendung von `u16ObjId` zur Identifikation von UT-Objekten.

## Zustandsübersicht

Da es sich um einen Composite FB handelt, wird der Zustand primär durch die internen Service-Bausteine bestimmt.
*   **Nicht Initialisiert:** Nach dem Start oder bei `QI=FALSE` während `INIT`.
*   **Initialisiert / Bereit:** Nach erfolgreichem `INIT` (`QO=TRUE`). Der Baustein lauscht auf Updates vom Terminal.
*   **Fehler:** Wenn `QO=FALSE` und `STATUS` eine Fehlermeldung enthält (z. B. ungültige Objekt-ID).

## Anwendungsszenarien

*   **Sollwertvorgabe:** Ein Bediener gibt auf dem Terminal eine Menge (z. B. Ausbringmenge in Litern) oder eine Zielgeschwindigkeit ein. Dieser Baustein empfängt den Wert.
*   **Parametrierung:** Einstellung von Maschinenparametern über numerische Felder auf dem Display.
*   **Modulare Anwendungen:** Einsatz in Anwendungen, die stark auf Adapter-Verbindungen setzen, um den "Spaghetti-Code" von parallelen Event- und Datenleitungen zu vermeiden.

## Vergleich mit ähnlichen Bausteinen

*   **NumericValue_ID:** Dies ist der interne Basisbaustein. Er bietet dieselbe Funktionalität, stellt die Daten jedoch über klassische `IND`/`CNF` Ereignisse und einen `IN` Datenausgang bereit. **NumericValue_IDA** ist die Adapter-Variante dieses Bausteins.
*   **Andere `_IDA` Bausteine:** Ähnlich wie `Button_IDA` (für Schaltflächen) oder `String_IDA` (für Texte), folgt dieser Baustein dem Entwurfsmuster, Terminal-Eingaben über Adapter bereitzustellen.


## Zugehörige Übungen

* [Uebung_011_AUDI](../../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_011_AUDI.md)

## Fazit

Der **NumericValue_IDA** ist ein spezialisierter Schnittstellenbaustein für ISOBUS-Anwendungen in 4diac. Durch die Verwendung eines Adapters für die Datenausgabe ermöglicht er eine kompakte und übersichtliche Verschaltung von numerischen Eingabewerten im Funktionsplan. Er eignet sich ideal für Entwickler, die eine strukturierte und modulare Anwendungsarchitektur bevorzugen und numerische Eingaben vom Universal Terminal verarbeiten müssen.