# I_VP1

```{index} single: I_VP1
```

<img width="1306" height="390" alt="image" src="https://github.com/user-attachments/assets/0d8b45f8-4fd0-475e-a261-694c0e7ecac1" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `I_VP1` dient zur Verarbeitung und Bereitstellung von Fahrzeugpositionsdaten gemäß dem ISO-11783-Standard (ISOBUS). Er implementiert speziell die Funktion "Vehicle Position 1", die durch das Parameter Group Number (PGN) 65267 definiert ist. Der Baustein empfängt Positionsdaten von einer Ressource (z. B. einem GNSS-Empfänger) und stellt diese über standardisierte Schnittstellen für nachgelagerte Steuerungs- und Anzeigefunktionen in einem landwirtschaftlichen oder mobilen Arbeitsmaschinen-Netzwerk zur Verfügung.

![I_VP1](I_VP1.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
*   **`INIT`**: Initialisierungsereignis. Wird bei `QI=TRUE` ausgelöst, um den Baustein zu starten. Bei `QI=FALSE` wird der Baustein deaktiviert.

### **Ereignis-Ausgänge**
*   **`INITO`**: Bestätigt den Abschluss der Initialisierung. Wird als Antwort auf das `INIT`-Ereignis gesendet.
*   **`IND`**: Indikationsereignis. Signalisiert den erfolgreichen Empfang neuer, gültiger Positionsdaten von der angeschlossenen Ressource.
*   **`TIMEOUT`**: Zeitüberschreitungsereignis. Wird ausgelöst, wenn innerhalb eines konfigurierten Zeitrahmens keine neuen Positionsdaten empfangen wurden.

### **Daten-Eingänge**
*   **`QI` (BOOL)**: Qualifiziert das `INIT`-Ereignis. Steuert den Aktivierungszustand des Funktionsblocks (`TRUE` = aktivieren, `FALSE` = deaktivieren).

### **Daten-Ausgänge**
*   **`QO` (BOOL)**: Qualifiziert die Ereignisausgänge `INITO` und `IND`. Gibt den aktuellen Betriebszustand des Bausteins wider (`TRUE` = aktiv und betriebsbereit).
*   **`STATUS` (STRING)**: Stellt Status- oder Fehlermeldungen des Bausteins in lesbarer Form bereit.
*   **`Q_timeout` (BOOL)**: Signalisiert, ob ein Timeout aufgetreten ist (`TRUE` = Timeout aktiv, `FALSE` = keine Zeitüberschreitung).
*   **`timestamp_timeout` (DINT)**: Zeitstempel (z. B. in Millisekunden), der dem `TIMEOUT`-Ereignis zugeordnet ist.
*   **`timestamp_data` (DINT)**: Zeitstempel der zuletzt empfangenen und über `IND` ausgegebenen Positionsdaten.
*   **`Latitude` (REAL)**: Der geografische Breitengrad der Fahrzeugposition in Grad. Der Wert ist gemäß PGN 65267 (SPN 584) skaliert und beinhaltet einen Offset von -210°.
*   **`Longitude` (REAL)**: Der geografische Längengrad der Fahrzeugposition in Grad. Der Wert ist gemäß PGN 65267 (SPN 585) skaliert und beinhaltet einen Offset von -210°.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter-Schnittstellen.

## Funktionsweise
1.  **Initialisierung**: Durch das Senden eines `INIT`-Ereignisses mit `QI=TRUE` wird der Baustein aktiviert. Er meldet den erfolgreichen Start mit dem `INITO`-Ausgangsereignis zurück, begleitet von `QO=TRUE` und einem `STATUS`-String.
2.  **Datenempfang und -verarbeitung**: Im aktiven Zustand überwacht der Baustein eine angeschlossene Ressource (z. B. einen ISOBUS-Datenstrom) auf das Eintreffen von Positionsdaten gemäß PGN 65267. Bei Empfang gültiger Daten werden diese dekodiert, die Skalierung und der Offset werden angewendet, und die resultierenden `Latitude`- und `Longitude`-Werte werden berechnet.
3.  **Datenausgabe**: Bei erfolgreicher Verarbeitung löst der Baustein das `IND`-Ereignis aus. Gleichzeitig werden die berechneten Positionsdaten (`Latitude`, `Longitude`), ein zugehöriger Zeitstempel (`timestamp_data`), der aktive Zustand (`QO=TRUE`) und ein Status über die Ausgangsvariablen bereitgestellt. `Q_timeout` wird auf `FALSE` gesetzt.
4.  **Timeout-Überwachung**: Der Baustein überwacht kontinuierlich den Datenstrom. Wenn für einen konfigurierten Zeitraum keine neuen Positionsdaten empfangen werden, löst er das `TIMEOUT`-Ereignis aus. Dabei werden `Q_timeout=TRUE`, ein Zeitstempel (`timestamp_timeout`) und ein entsprechender `STATUS` gesetzt.
5.  **Deaktivierung**: Ein `INIT`-Ereignis mit `QI=FALSE` setzt den Baustein in einen inaktiven Zustand zurück, was durch `INITO` mit `QO=FALSE` quittiert wird.

## Technische Besonderheiten
*   **ISOBUS-Konformität**: Der Baustein ist spezifisch für den Einsatz in ISO 11783 (ISOBUS)-Netzwerken entwickelt und verarbeitet Daten gemäß der offiziellen Spezifikation für PGN 65267.
*   **Datenkodierung**: Die Rohdaten für Breiten- (`Latitude`, SPN 584) und Längengrad (`Longitude`, SPN 585) werden als 4-Byte-Werte empfangen. Der Baustein wendet die in den Attributen definierte Skalierung und einen Offset von -210 Grad an, um die finalen `REAL`-Werte zu berechnen.
*   **Attribut-basierte Metadaten**: Die Ausgangsvariablen für die Positionsdaten sind mit detaillierten Attributen (SPN, Name, Länge, Offset, Referenz-Link) annotiert. Dies erleichtert die Konfiguration, Dokumentation und Wartung innerhalb einer IEC 61499-Entwicklungsumgebung.

## Zustandsübersicht
Der Baustein kann vereinfacht in folgende Hauptzustände übergehen:
*   **Inaktiv**: Ausgangszustand. `QO=FALSE`. Keine Datenverarbeitung.
*   **Aktiv (Warten auf Daten)**: Nach erfolgreicher Initialisierung. `QO=TRUE`. Der Baustein überwacht den Eingangsdatenstrom.
*   **Datenverarbeitung**: Bei Empfang eines neuen PGN 65267-Datenpakets. Dekodierung, Skalierung und Berechnung der Positionswerte.
*   **Datenausgabe**: Auslösen des `IND`-Ereignisses und Setzen der Ausgangsvariablen.
*   **Timeout**: Auslösen des `TIMEOUT`-Ereignisses bei ausbleibenden Daten.

## Anwendungsszenarien
*   **Precision Farming / Teilflächenmanagement**: Bereitstellung präziser Fahrzeugpositionen für Applikationskarten, Spurführungssysteme oder Dokumentationszwecke.
*   **Maschinen- und Flottenmanagement**: Ortung von landwirtschaftlichen oder kommunalen Fahrzeugen innerhalb eines Betriebsgeländes.
*   **Assistenzsysteme**: Grundlage für kollisionsvermeidende Systeme oder automatische Lenksysteme, die eine genaue und standardisierte Positionsinformation benötigen.

## ⚖️ Vergleich mit ähnlichen Bausteinen
*   **Generische Eingangsbausteinen (z. B., `E_SR`, `E_RTRIG`)**: Diese bieten grundlegende Einlese- oder Triggerfunktionen, sind aber nicht auf die Verarbeitung eines spezifischen ISOBUS-PGNs ausgelegt. `I_VP1` hingegen enthält die komplette Logik zur Dekodierung, Skalierung und Fehlerbehandlung für PGN 65267.
*   **Allgemeine ISOBUS-Eingangsbausteinen**: Es könnten allgemeinere Bausteinen existieren, die verschiedene PGNs einlesen. `I_VP1` ist spezialisiert und optimiert für die effiziente und zuverlässige Verarbeitung von Fahrzeugpositionsdaten, was die Konfiguration vereinfacht und die Fehleranfälligkeit verringert.

## Fazit
Der `I_VP1`-Funktionsblock ist ein spezialisiertes und standardkonformes Werkzeug für die Integration von Fahrzeugpositionsdaten in IEC 61499-basierte Steuerungssysteme für mobile Arbeitsmaschinen. Durch die direkte Implementierung der ISOBUS-Spezifikation (PGN 65267) und integrierte Features wie Timeout-Überwachung bietet er eine zuverlässige und einfach zu verwendende Schnittstelle für Anwendungen in den Bereichen Precision Farming und Automatisierung. Seine attributbasierte Dokumentation unterstützt Entwickler bei der korrekten Implementierung und Wartung.