# I_PosDeltaHighPrecRapidUpd

* * * * * * * * * *
## Einleitung
Der Funktionsblock `I_PosDeltaHighPrecRapidUpd` implementiert die Verarbeitung des NMEA 2000 Parameter Group Numbers (PGN) 129027 "Position Delta, High Precision Rapid Update". Dieser Baustein ist für Anwendungen konzipiert, die sehr hohe Präzision und sehr schnelle Aktualisierungsraten für Positionsdaten erfordern. Er kann Positionsänderungen (Delta) mit einer Auflösung von bis zu 1 Millimeter und einem Delta-Zeitintervall mit einer Genauigkeit von 5 Millisekunden bereitstellen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
*   **INIT**: Dienstinitialisierung. Wird zusammen mit dem Qualifier `QI` ausgelöst, um den Funktionsblock zu initialisieren oder zu deaktivieren.

### **Ereignis-Ausgänge**
*   **INITO**: Initialisierungsbestätigung. Wird als Antwort auf das `INIT`-Ereignis ausgelöst und gibt den aktuellen Status (`STATUS`) und den Qualifier `QO` zurück.
*   **IND**: Indikation vom Ressourcen-Manager. Wird ausgelöst, wenn neue Positionsdaten verfügbar sind. Überträgt alle relevanten Delta-Positionsdaten sowie Statusinformationen.
*   **TIMEOUT**: Wird ausgelöst, wenn ein Timeout auftritt, z.B. wenn keine neuen Daten innerhalb eines erwarteten Zeitrahmens empfangen wurden.

### **Daten-Eingänge**
*   **QI** (BOOL): Event Input Qualifier. Steuert die Initialisierung. Bei `TRUE` wird der Baustein aktiviert, bei `FALSE` deaktiviert.

### **Daten-Ausgänge**
*   **QO** (BOOL): Event Output Qualifier. Gibt den aktuellen Betriebszustand des Bausteins wider (z.B. aktiv/inaktiv).
*   **STATUS** (STRING): Enthält Status- oder Fehlermeldungen des Funktionsblocks.
*   **Q_timeout** (BOOL): Gibt an, ob die letzten empfangenen Daten aufgrund eines Timeouts veraltet sind.
*   **timestamp_timeout** (DINT): Zeitstempel, der dem `TIMEOUT`-Ereignis zugeordnet ist.
*   **timestamp_data** (DINT): Zeitstempel der zuletzt empfangenen gültigen Positionsdaten.
*   **SID** (UINT): Sequence ID. Identifiziert die Sequenz, der diese Daten zugeordnet sind, um eine Synchronisation mit anderen Fahrzeugdaten derselben Sequenz in einem anderen PGN zu ermöglichen.
*   **TimeDelta** (UINT): Die Zeitdifferenz in Millisekunden, über die die Positionsänderung gemessen wurde.
*   **LatitudeDelta** (INT): Die Änderung der geografischen Breite (Delta) in hochpräziser Auflösung (1/1e-7 min ~= 1.85 mm).
*   **LongitudeDelta** (INT): Die Änderung der geografischen Länge (Delta) in hochpräziser Auflösung (1/1e-7 min ~= 1.85 mm).

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter-Schnittstellen.

## Funktionsweise
Der Baustein wird über das `INIT`-Ereignis mit dem entsprechenden `QI`-Wert gestartet oder gestoppt. Nach erfolgreicher Initialisierung bestätigt er dies mit `INITO`. Im aktiven Zustand lauscht der Baustein auf eingehende PGN 129027 Nachrichten vom NMEA 2000-Netzwerk.

Bei Empfang neuer, gültiger Daten löst er das `IND`-Ereignis aus und stellt alle berechneten Delta-Werte (Zeit, Breite, Länge) zusammen mit der Sequenz-ID (`SID`) und einem Datenzeitstempel an seinen Ausgängen bereit. Der `STATUS`-Ausgang kann dabei zusätzliche Informationen liefern.

Sollte über einen definierten Zeitraum hinweg keine neue Nachricht empfangen werden, kann der Baustein ein `TIMEOUT`-Ereignis generieren. Dies signalisiert, dass die aktuell gehaltenen Daten möglicherweise veraltet sind (`Q_timeout` = TRUE).

## Technische Besonderheiten
*   **Hohe Präzision**: Verarbeitet Positionsdeltas mit einer Auflösung im Millimeterbereich (1/1e-7 Bogenminuten).
*   **Schnelle Aktualisierung**: Unterstützt sehr kurze Update-Intervalle, die durch das `TimeDelta` (min. 5 ms Genauigkeit) abgebildet werden.
*   **Sequenzierung**: Die `SID` (Sequence ID) ermöglicht die korrekte Zuordnung und Synchronisation von Positionsdeltas mit anderen zeitkritischen Datenströmen im System.
*   **Timeout-Erkennung**: Integrierte Überwachung der Datenaktualität zur Erkennung von Kommunikationsausfällen oder verzögerten Nachrichten.

## Zustandsübersicht
Der Funktionsblock besitzt im Wesentlichen zwei Hauptzustände:
1.  **Inaktiv / Initialisiert**: Der Baustein ist initialisiert, aber nicht aktiv (`QI` = FALSE). Es werden keine Daten verarbeitet.
2.  **Aktiv / Lauschend**: Der Baustein ist aktiviert (`QI` = TRUE) und wartet auf eingehende PGN 129027 Nachrichten. Bei Empfang werden diese verarbeitet und über `IND` ausgegeben. Ein fehlendes Signal kann zum Übergang in einen Timeout-Zustand führen, was durch das `TIMEOUT`-Ereignis signalisiert wird.

## Anwendungsszenarien
*   **Präzisionslandwirtschaft**: Für hochgenaue Spurführungssysteme und automatische Lenksysteme, die Echtzeit-Positionskorrekturen benötigen.
*   **Dynamische Positionierung**: In maritimen Anwendungen zur präzisen Lagehaltung von Schiffen oder Offshore-Plattformen.
*   **Autonome Fahrzeuge**: Zur hochfrequenten Odometrie und Pfadkorrektur in Echtzeit.
*   **Vermessung und Kartierung**: Bei der Erfassung von Geländedaten mit sehr hoher räumlicher und zeitlicher Auflösung.

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu Standard-Positionsbausteinen (z.B. solchen, die PGN 129029 "Position, Rapid Update" verarbeiten) bietet `I_PosDeltaHighPrecRapidUpd`:
*   **Delta-basierte Daten**: Statt absoluter Positionen werden Änderungen (Deltas) übertragen, was bei hohen Update-Raten bandbreiteneffizienter sein kann.
*   **Höhere Präzision**: Spezifiziert für Anwendungen, die eine höhere Genauigkeit als die typischen Rapid-Update-PGNs benötigen.
*   **Explizite Zeitdifferenz**: Das `TimeDelta`-Feld ist integraler Bestandteil der Nachricht, was eine präzisere Geschwindigkeits- und Beschleunigungsberechnung ermöglicht.

## Fazit
Der `I_PosDeltaHighPrecRapidUpd` Funktionsblock ist ein spezialisiertes Werkzeug für anspruchsvolle Echtzeit-Positionsbestimmung. Seine Fähigkeit, hochpräzise Positionsänderungen mit sehr hoher Frequenz zu liefern und zu synchronisieren, macht ihn ideal für präzisionskritische Steuerungs- und Regelungsaufgaben in den Bereichen Landtechnik, Maritime und autonome Systeme. Die integrierte Timeout-Erkennung erhöht zudem die Robustheit der Anwendung.