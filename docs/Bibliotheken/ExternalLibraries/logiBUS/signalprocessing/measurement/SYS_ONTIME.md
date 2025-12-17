# SYS_ONTIME

<img width="1639" height="206" alt="image" src="https://github.com/user-attachments/assets/08d09491-2560-44d8-be18-94d431bac08b" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `SYS_ONTIME` ist ein Service Interface Function Block (SIFB). Seine Hauptaufgabe ist es, die Betriebszeit (Ontime) der Ressource, in der er ausgeführt wird, auszulesen und bereitzustellen. Er dient als standardisierte Schnittstelle zwischen der Anwendungslogik und den systemnahen Diensten der Laufzeitumgebung.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
*   **`INIT`**: Dieses Ereignis initialisiert den Funktionsblock. Es muss ausgelöst werden, bevor der Block seinen Dienst aufnehmen kann.

### **Ereignis-Ausgänge**
*   **`INITO`**: Dieses Ereignis bestätigt die erfolgreiche Initialisierung des Funktionsblocks. Es wird zusammen mit dem ersten gültigen `ONTIME`-Wert ausgelöst.
*   **`IND`**: Dieses Ereignis signalisiert, dass ein neuer, aktualisierter `ONTIME`-Wert vom Systemressourcen-Manager bereitgestellt wurde.

### **Daten-Eingänge**
*   Dieser Funktionsblock besitzt keine Dateneingänge.

### **Daten-Ausgänge**
*   **`ONTIME` (UINT)**: Dieser Ausgang liefert die kumulierte Betriebszeit der Ressource. Die Einheit ist "Dezimalminute", was 0,01 Stunden entspricht (z.B. ein Wert von 150 entspricht 1,5 Stunden).

### **Adapter**
*   Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Der `SYS_ONTIME`-Block agiert als Client für einen systeminternen Dienst. Nach dem Empfang des `INIT`-Ereignisses registriert er sich beim Ressourcen-Manager, um Zugriff auf die Betriebszeitdaten zu erhalten. Sobald die Initialisierung abgeschlossen ist, wird das `INITO`-Ereignis zusammen mit dem aktuellen Betriebszeitwert ausgelöst.

Anschließend überwacht der Block kontinuierlich die Systemressource. Sobald sich die Betriebszeit ändert (typischerweise durch einen System-Tick oder einen ähnlichen Mechanismus), löst der Ressourcen-Manager eine Indikation aus. Der `SYS_ONTIME`-Block empfängt diese, aktualisiert seinen internen `ONTIME`-Wert und gibt das `IND`-Ereignis zusammen mit dem neuen Wert an die angeschlossene Anwendungslogik weiter.

## Technische Besonderheiten
*   **Service Interface FB**: Als SIFB ist seine Implementierung spezifisch für die jeweilige 4diac-Runtime (FORTE) und die zugrunde liegende Hardware/Plattform. Die genaue Art der Zeitmessung (z.B. basierend auf Hochlaufzeit des Prozessors oder der Laufzeitumgebung) ist runtime-definiert.
*   **Einheit**: Die Betriebszeit wird in der ungewöhnlichen, aber für Steuerungsaufgaben praktischen Einheit "Dezimalminute" (1/100 Stunde) geliefert. Dies erleichtert Berechnungen im Dezimalsystem, z.B. für Wartungsintervalle oder Energieverbrauchsschätzungen.
*   **Nur Lese-Zugriff**: Der Block bietet ausschließlich Lesezugriff auf einen systeminternen Wert. Ein Zurücksetzen der Betriebszeit ist über diese Schnittstelle nicht möglich.

## Zustandsübersicht
1.  **Inaktiv**: Der Block ist erstellt, aber noch nicht initialisiert. Keine Kommunikation mit der Systemressource findet statt.
2.  **Initialisiert**: Nach dem Empfang von `INIT`. Der Block ist beim Ressourcen-Manager registriert und wartet auf Daten. Der Zustand wechselt sofort nach erfolgreicher Initialisierung, gefolgt von der Ausgabe von `INITO`.
3.  **Bereit**: Der Block hat den ersten `ONTIME`-Wert erhalten und ist betriebsbereit. Er wartet nun auf Indikations-Ereignisse (`IND`) vom System, um aktualisierte Werte auszugeben.

## Anwendungsszenarien
*   **Vorbeugende Wartung (Predictive Maintenance)**: Überwachung der Laufzeit von Maschinen oder Anlagenteilen, um Wartungsintervalle basierend auf tatsächlicher Nutzung auszulösen.
*   **Energiemanagement**: Erfassung der Betriebsstunden von Verbrauchern (z.B. Motoren, Heizungen) zur Berechnung des Energieverbrauchs oder für Lastprofile.
*   **Betriebsdatenerfassung (BDE)**: Protokollierung der Produktions- oder Maschinenlaufzeiten für Auswertungen zur Overall Equipment Effectiveness (OEE).
*   **Lebensdauerüberwachung**: Überprüfung, ob kritische Komponenten ihre spezifizierte Lebensdauer (in Betriebsstunden) erreicht oder überschritten haben.

## Vergleich mit ähnlichen Bausteinen
*   **`E_CYCLE` / `E_DELAY`**: Diese Blöcke erzeugen selbst periodische Ereignisse oder Verzögerungen. `SYS_ONTIME` hingegen *liest* einen passiv vorhandenen, kumulativen Zeitwert aus dem System aus.
*   **`E_SR` (Set-Reset) mit Zähler**: Ein manuell aufgebauter Zähler für Einschaltvorgänge könnte ähnliche Daten liefern, wäre aber anwendungsseitig implementiert und nicht systemseitig persistent. `SYS_ONTIME` bietet einen zuverlässigen, systemgeführten und meist auch nach einem Neustart persistenten Wert.
*   **Andere SYS_*-Blöcke** (wie `SYS_TIME`): Während `SYS_TIME` die aktuelle Uhrzeit und das Datum liefert, stellt `SYS_ONTIME` spezifisch die reine Betriebsdauer einer Ressource bereit.

## Fazit
Der `SYS_ONTIME`-Funktionsblock ist ein essentielles Werkzeug für alle Anwendungen, die auf der Erfassung und Auswertung von Betriebszeiten basieren. Als standardisierte Service-Schnittstelle abstrahiert er die plattformspezifische Implementierung und bietet der Anwendungslogik einen einfachen, zuverlässigen Zugriff auf diese wichtige Systemkenngröße. Seine Verwendung ist besonders in den Bereichen Instandhaltung, Energieeffizienz und Betriebsdatenerfassung zu empfehlen.
