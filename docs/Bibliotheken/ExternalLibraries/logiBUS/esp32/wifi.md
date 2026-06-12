# wifi


![wifi](./wifi.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock "wifi" ist ein Service-Interface-Funktionsblock (SIFB) zur Steuerung einer WLAN-Verbindung. Er bietet die Ereignisse INIT, START und STOP zur Initialisierung, zum Starten und Stoppen des WLANs. Der Status der Verbindung wird über den Ausgang STATUS als Zeichenkette zurückgegeben. Der Baustein ist für den Einsatz in Automatisierungssystemen konzipiert, die eine drahtlose Netzwerkverbindung benötigen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **INIT** (EInit): Initialisiert den Baustein und bereitet die WLAN-Schnittstelle vor.
- **START** (EInit): Startet die WLAN-Verbindung.
- **STOP** (EInit): Stoppt die WLAN-Verbindung.

### **Ereignis-Ausgänge**
- **INITO** (EInit): Bestätigt die erfolgreiche Initialisierung. Wird in Verbindung mit dem Datenausgang STATUS ausgelöst.

### **Daten-Eingänge**
Keine Daten-Eingänge vorhanden.

### **Daten-Ausgänge**
- **STATUS** (WSTRING): Zeigt den aktuellen Status des WLAN-Dienstes an (z. B. "OK", "Fehler", "Verbunden", "Getrennt").

### **Adapter**
Keine Adapter verfügbar.

## Funktionsweise
Der Baustein arbeitet nach dem Prinzip eines Service-Interface-Funktionsblocks. Die interne Logik wird durch die Laufzeitumgebung bereitgestellt. Typischerweise wird zuerst INIT aufgerufen, um den Baustein zu konfigurieren. Danach kann mit START die WLAN-Verbindung aktiviert werden. Mit STOP wird die Verbindung beendet. Der Ausgang STATUS gibt nach jeder Operation den aktuellen Zustand zurück.

## Technische Besonderheiten
- Der Baustein ist als SIFB (Service Interface Function Block) nach IEC 61499-2 realisiert.
- Die Schnittstelle ist sowohl zur RESOURCE- als auch zur APPLICATION-Seite hin offen, was eine flexible Integration ermöglicht.
- Die genaue Implementierung ist abhängig von der zugrunde liegenden Hardware und dem Betriebssystem.

## Zustandsübersicht
Der Baustein durchläuft folgende grundlegende Zustände:
- **Uninitialisiert**: Nach dem Start, bevor INIT ausgeführt wird.
- **Initialisiert**: Nach erfolgreichem INIT, bereit für START.
- **Aktiv (verbunden)**: Nach erfolgreichem START.
- **Inaktiv (getrennt)**: Nach STOP oder bei einem Fehler.

## Anwendungsszenarien
- Steuerung einer WLAN-Schnittstelle in landwirtschaftlichen Maschinen oder anderen Fahrzeugen.
- Einbindung von Geräten in ein drahtloses Netzwerk zur Datenübertragung in der Automatisierungstechnik.
- Fernwartung und -diagnose über WLAN.

## Vergleich mit ähnlichen Bausteinen
Ähnliche Bausteine sind beispielsweise Ethernet- oder serielle Kommunikationsbausteine. Im Gegensatz zu diesen fokussiert der wifi-Baustein speziell auf die drahtlose WLAN-Verbindung und bietet eine vereinfachte, ereignisgesteuerte Schnittstelle. Andere Bausteine erfordern oft komplexere Konfigurationen oder unterstützen mehrere Protokolle.

## Fazit
Der Funktionsblock "wifi" stellt eine einfache und standardisierte Möglichkeit zur Integration einer WLAN-Verbindung in IEC-61499-Systeme dar. Mit den drei Ereignissen INIT, START und STOP sowie dem STATUS-Ausgang ist er intuitiv bedienbar und eignet sich besonders für Anwendungen, die eine schnelle und zuverlässige kabellose Kommunikation erfordern.