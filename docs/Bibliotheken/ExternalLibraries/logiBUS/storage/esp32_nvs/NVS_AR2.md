# NVS_AR2


![NVS_AR2](./NVS_AR2.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein NVS_AR2 dient zum Speichern und Laden von REAL-Werten (Gleitkommazahlen) in einen nichtflüchtigen Speicher (NVS – Non-Volatile Storage) über einen Schlüssel (Key). Er kapselt die Logik des zugrundeliegenden NVS-Bausteins und bietet eine bidirektionale Adapterschnittstelle vom Typ AR2 für eine asynchrone Kommunikation. Dadurch kann der Baustein in eine ereignisgesteuerte Umgebung integriert werden, bei der Lese- und Schreiboperationen asynchron ausgelöst werden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Initialisiert den Baustein. Mit diesem Ereignis werden die Parameter QI (Qualifier), KEY (Schlüssel) und DEFAULT_VALUE (Standardwert) übergeben. Nach erfolgreicher Initialisierung wird der Ausgang INITO ausgelöst.

### **Ereignis-Ausgänge**
- **INITO**: Bestätigung der Initialisierung. Dieses Ereignis signalisiert, dass der Baustein bereit ist. Es wird auch nach einer Lese- oder Schreiboperation über den Adapter ausgelöst (da die Ereignisse verkettet sind).

### **Daten-Eingänge**
- **QI** (BOOL): Eingangsqualifizierer zur Steuerung der Ausführung. Typischerweise wird dieser auf TRUE gesetzt, um die Initialisierung zu aktivieren.
- **KEY** (STRING): Der Schlüsselname, unter dem der Wert im NVS gespeichert oder gelesen werden soll.
- **DEFAULT_VALUE** (REAL): Der Wert, der zurückgegeben wird, falls im NVS kein Eintrag unter dem angegebenen Schlüssel existiert.

### **Daten-Ausgänge**
- **QO** (BOOL): Ausgangsqualifizierer. Zeigt den Status der ausgeführten Operation an.
- **STATUS** (STRING): Statusmeldung der Operation (z. B. Erfolg, Fehlercode).

### **Adapter**
- **VAL** (vom Typ `adapter::types::bidirectional::AR2`): Bidirektionaler Adapter zum asynchronen Lesen und Schreiben von Werten. Der Adapter besitzt zwei Ereignisse (EO1 – vom Baustein zum Adapter; EI1 – vom Adapter zum Baustein) sowie zwei Datenports (DO1 – Daten vom Baustein zum Adapter; DI1 – Daten vom Adapter zum Baustein). Über diesen Adapter können externe Komponenten Lese- und Schreibanforderungen an den NVS_AR2 senden und Ergebnisse empfangen.

## Funktionsweise
Der NVS_AR2 fungiert als Vermittler zwischen dem eigentlichen NVS-Speicherbaustein (`logiBUS::storage::esp32_nvs::NVS`) und einer übergeordneten Steuerung über den bidirektionalen Adapter. Beim Eintreffen des INIT-Ereignisses werden die Parameter an den internen NVS-Baustein weitergeleitet. Der NVS-Baustein führt eine Initialisierung durch und quittiert mit INITO.

Nach der Initialisierung wird automatisch ein Lesevorgang (GET) ausgelöst: Der NVS-Baustein liest den Wert unter dem angegebenen Schlüssel. Falls kein Eintrag existiert, wird DEFAULT_VALUE verwendet. Das gelesene Ergebnis wird über den Adapter-Ausgang (VAL.DI1) und das Ereignis VAL.EI1 an die angeschlossene Komponente gesendet.

Ein Schreibzugriff erfolgt, wenn die externe Komponente über den Adapter (VAL.EO1) einen Schreibbefehl sendet. Dabei wird der gewünschte Wert über VAL.DO1 an den NVS_AR2 übergeben, der ihn an den NVS-Baustein weiterleitet (SET). Nach erfolgreichem Schreiben quittiert der NVS-Baustein mit SETO, was wiederum das Ereignis VAL.EI1 auslöst, um die Bestätigung an die externe Komponente zurückzugeben.

## Technische Besonderheiten
- **Asynchrone Kommunikation**: Der Baustein unterstützt asynchrone Lese- und Schreiboperationen über den AR2-Adapter, sodass er in nebenläufige Systeme integriert werden kann, ohne blockierende Aufrufe.
- **Standardwert**: Durch die Angabe eines DEFAULT_VALUE wird sichergestellt, dass auch bei erstmaliger Nutzung eines Schlüssels ein definierter Wert zurückgegeben wird.
- **Fehlerbehandlung**: STATUS und QO geben Aufschluss über den Erfolg oder Misserfolg der Operation.
- **Wiederverwendung**: Der Baustein kapselt den allgemeinen NVS-Baustein und fügt eine standardisierte Adapterschnittstelle hinzu, was die Wiederverwendung in verschiedenen Steuerungslogiken erleichtert.

## Zustandsübersicht
Der Baustein hat keinen explizit definierten Zustandsautomaten im XML, da er über den internen NVS-Baustein und die Ereignisverkettung gesteuert wird. Der Zustand ergibt sich aus der Abfolge der Ereignisse:
1. Warten auf INIT → Initialisierung läuft → INITO und GET werden ausgelöst.
2. Nach GET: Warten auf Leseergebnis → Wert an Adapter gesendet.
3. Warten auf Schreibanforderung über Adapter → SET ausgeführt → Bestätigung zurück.
4. Nach jedem Schritt ist der Baustein bereit für neue Anforderungen.

## Anwendungsszenarien
- **Persistente Konfigurationsspeicher**: Speichern und Abrufen von Einstellungen (z. B. Sollwerten, Parametern) in einem eingebetteten System mit NVS (wie ESP32 NVS).
- **Datenprotokollierung**: Asynchrones Ablegen von Messwerten im NVS.
- **Initiale Standardwerte laden**: Bei Systemstart einen gespeicherten Wert laden oder einen Standardwert verwenden, falls noch nie gespeichert.

## Vergleich mit ähnlichen Bausteinen
- **NVS**: Der Basisbaustein NVS ohne Adapter hat direkte Ereignisschnittstellen (INIT, REQ, etc.) und erfordert eine direkte Anbindung. NVS_AR2 fügt eine bidirektionale Adapterschnittstelle hinzu, die eine flexiblere, protokollunabhängige Anbindung ermöglicht.
- **Andere Speicherbausteine (z. B. EEPROM, Dateisystem)**: Diese Bausteine haben oft andere Datentypen und Zugriffsmethoden. NVS_AR2 ist speziell auf REAL-Werte und den NVS-Zugriff optimiert.

## Fazit
Der Funktionsbaustein NVS_AR2 bietet eine saubere, adapterbasierte Schnittstelle zum asynchronen Lesen und Schreiben von REAL-Daten im nichtflüchtigen Speicher. Durch die Kapselung des NVS-Bausteins und die Integration des AR2-Adapters eignet er sich hervorragend für modulare, ereignisgesteuerte Steuerungssysteme, die persistente Datenverwaltung benötigen.