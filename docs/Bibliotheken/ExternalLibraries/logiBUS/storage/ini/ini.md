# INI

```{index} single: INI
```

<img width="1844" height="338" alt="image" src="https://github.com/user-attachments/assets/e5a9c5f0-2b32-4d82-8784-a0c476e5142a" />

* * * * * * * * * *
## Einleitung
Der INI-Funktionsblock ermöglicht das Laden und Speichern von Daten in einer `settings.ini`-Datei. Er bietet eine einfache Schnittstelle, um Werte anhand eines Sektionsnamens (SECTION) und eines Schlüssels (KEY) persistent zu verwalten. Der Block ist besonders nützlich für die Konfigurationsverwaltung in 4diac FORTE Applikationen, z.B. für das Setzen und Abrufen von Parametern wie IP-Adressen, Schwellwerten oder Betriebsmodi.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
*   **INIT**: Dienst-Initialisierung. Wird bei Start oder Neukonfiguration verwendet. Löst die Initialisierung des Blocks und optional das erste Lesen/Schreiben eines Wertes aus.
*   **SET**: Setzt den Wert für den konfigurierten Schlüssel in der INI-Datei.
*   **GET**: Liest den Wert für den konfigurierten Schlüssel aus der INI-Datei.

### **Ereignis-Ausgänge**
*   **INITO**: Bestätigung der Initialisierung. Wird nach Verarbeitung des INIT-Ereignisses ausgelöst.
*   **SETO**: Bestätigung des Schreibvorgangs. Wird nach Verarbeitung des SET-Ereignisses ausgelöst.
*   **GETO**: Bestätigung des Lesevorgangs. Wird nach Verarbeitung des GET-Ereignisses ausgelöst.

### **Daten-Eingänge**
*   **QI (BOOL)**: Ereignis-Eingangs-Qualifizierer. Steuert bei INIT, ob der Vorgang aktiviert (`TRUE`) oder deaktiviert (`FALSE`) wird.
*   **SECTION (STRING)**: Der Name des Sektionsabschnitts in der `settings.ini`-Datei.
*   **KEY (STRING)**: Der Name des Schlüssels innerhalb des angegebenen Sektionsabschnitts.
*   **VALUE (ANY_ELEMENTARY)**: Der zu schreibende Wert. Dieser Datentyp kann jeden elementaren Typ (z.B. BOOL, INT, REAL, STRING) annehmen.
*   **DEFAULT_VALUE (ANY_ELEMENTARY)**: Der Standardwert, der zurückgegeben wird, wenn der angeforderte Schlüssel in der INI-Datei nicht existiert.

### **Daten-Ausgänge**
*   **QO (BOOL)**: Ereignis-Ausgangs-Qualifizierer. Gibt den Status der Operation wieder (`TRUE` für Erfolg, `FALSE` für Fehler oder Deaktivierung).
*   **STATUS (STRING)**: Detaillierter Status der ausgeführten Operation (z.B. "OK", "FEHLER").
*   **VALUEO (ANY_ELEMENTARY)**: Der gelesene oder geschriebene Wert. Bei GET ist dies der aus der Datei gelesene oder der DEFAULT_VALUE.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Der INI-Block agiert als Schnittstelle zwischen der IEC 61499-Applikation und einer persistenten `settings.ini`-Datei auf dem Dateisystem. Bei einem `INIT`-Ereignis mit `QI=TRUE` wird der Block für die angegebene `SECTION` und `KEY` konfiguriert. Optional kann dabei sofort ein Wert (`VALUE`) geschrieben oder mit `DEFAULT_VALUE` ein Standard gesetzt werden.

Ein `SET`-Ereignis schreibt den aktuellen Wert des `VALUE`-Eingangs unter dem konfigurierten Schlüssel in die Datei. Ein `GET`-Ereignis liest den Wert aus der Datei. Wenn der Schlüssel nicht existiert, wird stattdessen der `DEFAULT_VALUE` zurückgegeben. Jede Operation (`INIT`, `SET`, `GET`) wird durch ein entsprechendes Ausgangsereignis (`INITO`, `SETO`, `GETO`) quittiert, wobei `QO`, `STATUS` und `VALUEO` den Ergebnisstatus anzeigen.

## Technische Besonderheiten
*   **Typflexibilität**: Die Daten-Ein-/Ausgänge `VALUE`, `DEFAULT_VALUE` und `VALUEO` verwenden den generischen Datentyp `ANY_ELEMENTARY`. Dies erlaubt die Speicherung verschiedenster elementarer Datentypen (z.B. Zahlen, Boolesche Werte, Strings) mit demselben Funktionsblock.
*   **Persistenz**: Die Daten werden in einer textbasierten INI-Datei gespeichert, die auch außerhalb von FORTE manuell bearbeitet werden kann.
*   **Fehlerbehandlung**: Der `STATUS`-Ausgang bietet eine textuelle Rückmeldung über Erfolg oder Misserfolg der Operation, was das Debuggen erleichtert.
*   **Package**: Der Block ist im Package `eclipse4diac::storage` enthalten.

## Zustandsübersicht
Der Block besitzt keine explizite, komplexe Zustandsmaschine im nutzerzugänglichen Sinne. Sein Verhalten ist ereignisgesteuert: Nach der Initialisierung (`INIT`) wartet er auf `SET`- oder `GET`-Anfragen, verarbeitet diese und kehrt anschließend in einen wartenden Zustand zurück. Der interne Zustand (konfigurierter Sektion/Schlüssel) bleibt nach `INIT` erhalten.

## Anwendungsszenarien
*   **Konfigurationsmanagement**: Laden von Geräte-IP-Adressen, Kommunikationsports oder Netzwerkeinstellungen beim Start einer Applikation.
*   **Parametrierung**: Speichern von anlagen- oder produktspezifischen Parametern (z.B. Sollwerte, Zeiten), die zwischen Neustarts erhalten bleiben sollen.
*   **Betriebsdatenerfassung**: Persistentes Speichern einfacher Betriebszustände oder Zählerstände.
*   **Benutzereinstellungen**: Verwalten von Spracheinstellungen oder anderen Benutzerpräferenzen.

## Vergleich mit ähnlichen Bausteinen
*   **`E_SR` (SR-Flip-Flop) / `E_RS` (RS-Flip-Flop)**: Diese Blöcke speichern einen binären Zustand (`BOOL`) nur während der Laufzeit im Arbeitsspeicher. Der INI-Block speichert beliebige Typen dauerhaft auf nicht-flüchtigem Speicher.
*   **`E_DEMUX` / `E_MUX`**: Diese dienen der Ereignis- und Datenverteilung, nicht der persistenten Speicherung.
*   **`FB_RETAIN` (aus `eclipse4diac::core`)** : Speichert Daten persistent, nutzt jedoch typischerweise ein gerätespezifisches, nicht direkt zugängliches Retain-Memory. Der INI-Block verwendet eine standardisierte, lesbare Textdatei.
*   **Datenbank- oder File-IO-Blöcke**: Allgemeinere Blöcke für Dateizugriffe bieten mehr Flexibilität, sind aber auch komplexer in der Handhabung. Der INI-Block ist eine spezialisierte, einfache Lösung für den häufigen Anwendungsfall der Schlüssel-Wert-Speicherung.

## Fazit
Der INI-Funktionsblock ist ein praktisches und unkompliziertes Werkzeug zur persistenten Speicherung von Konfigurations- und Parametrierdaten in 4diac FORTE Applikationen. Seine Stärken liegen in der einfachen Bedienung über Sektion und Schlüssel, der Flexibilität durch den `ANY_ELEMENTARY`-Typ und der menschlichen Lesbarkeit der gespeicherten INI-Datei. Für Anwendungen, die eine einfache, dauerhafte Schlüssel-Wert-Datenbank benötigen, ist er eine ausgezeichnete Wahl.