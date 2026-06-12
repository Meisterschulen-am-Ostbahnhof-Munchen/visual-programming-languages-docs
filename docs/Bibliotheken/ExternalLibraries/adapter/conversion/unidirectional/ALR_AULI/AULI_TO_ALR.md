# AULI_TO_ALR

Kein Bild vorhanden.


![AULI_TO_ALR](./AULI_TO_ALR.svg)

* * * * * * * * * *

## Einleitung

Der **AULI_TO_ALR** ist ein zusammengesetzter Funktionsbaustein (Composite FB), der einen eingehenden AULI-Adapter (Daten vom Typ ULINT) in einen ausgehenden ALR-Adapter (Daten vom Typ LREAL) umwandelt. Er dient als standardisierte Schnittstelle zwischen Komponenten, die unterschiedliche Datentypen über Adapter kommunizieren.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Der Baustein besitzt keine direkten Ereignis-Eingänge. Das eingehende Ereignis wird über den Socket-Adapter **AULI_IN** bereitgestellt:

- **AULI_IN.E1** (Ereignis) – Empfängt das Auslösesignal für die Umwandlung.

### **Ereignis-Ausgänge**

Der Baustein besitzt keine direkten Ereignis-Ausgänge. Das ausgehende Ereignis wird über den Plug-Adapter **ALR_OUT** bereitgestellt:

- **ALR_OUT.E1** (Ereignis) – Signalisiert, dass die umgewandelten Daten am Datenausgang anliegen.

### **Daten-Eingänge**

Direkte Daten-Eingänge sind nicht vorhanden. Die Eingangsdaten werden über den Socket-Adapter **AULI_IN** bereitgestellt:

- **AULI_IN.D1** (ULINT) – Der umzuwandelnde Wert im Format unsigned long integer.

### **Daten-Ausgänge**

Direkte Daten-Ausgänge sind nicht vorhanden. Die Ausgangsdaten werden über den Plug-Adapter **ALR_OUT** bereitgestellt:

- **ALR_OUT.D1** (LREAL) – Der umgewandelte Wert im Format long real (64-Bit Gleitkommazahl).

### **Adapter**

Der Baustein verwendet genau zwei Adapter:

- **Socket AULI_IN** (Typ: AULI aus `adapter::types::unidirectional`) – Empfängt die ULINT-Werte und das zugehörige Triggerereignis.
- **Plug ALR_OUT** (Typ: ALR aus `adapter::types::unidirectional`) – Stellt die konvertierten LREAL-Werte und ein Bestätigungsereignis zur Verfügung.

## Funktionsweise

Der Baustein arbeitet nach dem Request-Bestätigungs-Prinzip:

1. Sobald am Eingangsadapter **AULI_IN** ein Ereignis an **E1** eintrifft, wird der interne Funktionsbaustein **F_ULINT_TO_LREAL** (aus der Bibliothek `iec61131::conversion`) aufgerufen.
2. Der Wert **AULI_IN.D1** wird dem Eingang **IN** des Konverters zugeführt.
3. Der Konverter führt die Umwandlung von ULINT nach LREAL durch (Ganzzahl zu Gleitkommazahl).
4. Nach Abschluss der Konvertierung wird das Ergebnis an **ALR_OUT.D1** weitergeleitet.
5. Gleichzeitig wird am Ausgangsadapter das Ereignis **ALR_OUT.E1** ausgelöst, um dem nachgeschalteten Baustein die Verarbeitung der Daten zu signalisieren.

Die gesamte Logik läuft innerhalb eines FB-Netzwerks ab und ist für den Anwender transparent.

## Technische Besonderheiten

- **Adapterbasierte Kommunikation:** Der Baustein kapselt die Typkonvertierung in einer Adapterschnittstelle, sodass er in Systemen mit einheitlichen Adaptertypen (z. B. AULI und ALR) nahtlos eingesetzt werden kann. Dadurch wird die Kompatibilität zwischen Komponenten erhöht.
- **Wiederverwendung vorhandener Bausteine:** Als Composite FB verwendet er den standardisierten Konvertierungsbaustein `F_ULINT_TO_LREAL`, was die Wartbarkeit und Korrektheit der Konvertierungslogik sicherstellt.
- **Kompatibilität mit IEC 61499-2:** Der Baustein erfüllt die Norm und kann in beliebigen 4diac-IDE Projekten verwendet werden.
- **Keine Zustandsmaschine:** Die Umwandlung erfolgt rein kombinatorisch unter Steuerung der Ereignisse – es gibt keine internen Zustände.

## Zustandsübersicht

Der Baustein besitzt keine eigenständigen Zustände. Die Ablaufsteuerung wird durch das Ereignis an **AULI_IN.E1** angestoßen und endet mit dem Ereignis an **ALR_OUT.E1**. Während der Konvertierung befindet sich der Baustein im Zustand "warten auf Bestätigung des internen Funktionsbausteins". Für den Anwender ist dies jedoch nicht sichtbar.

## Anwendungsszenarien

- **Integration von Sensoren oder Aktoren,** die ihre internen Zählerwerte als ULINT liefern, in eine Steuerung, die für Berechnungen LREAL benötigt (z. B. Regelungsalgorithmen).
- **Adapterbrücke** zwischen zwei Subsystemen mit unterschiedlichen Adapterdefinitionen, um ohne Änderung der Schnittstellendefinitionen eine Typumwandlung zu ermöglichen.
- **Datenaufbereitung** in Kommunikationsprotokollen, bei denen empfangene Ganzzahlen in Gleitkommawerte für die weitere Verarbeitung umgerechnet werden müssen.

## Vergleich mit ähnlichen Bausteinen

Statt eines speziellen Adapterkonverters könnte man auch direkt den Baustein `F_ULINT_TO_LREAL` verwenden und die Ereignisse/Daten manuell verbinden. Der Vorteil von **AULI_TO_ALR** liegt in der Kapselung der Adapterschnittstellen: Er erspart dem Entwickler das manuelle Verkabeln der Adapter-Ereignisse und -Daten und sorgt für eine saubere, wiederverwendbare Komponente. Gegenüber einer maßgeschneiderten Lösung bietet er eine standardisierte, dokumentierte Schnittstelle.

## Fazit

Der **AULI_TO_ALR** ist ein nützlicher, spezialisierter Funktionsbaustein für die Umwandlung von ULINT- in LREAL-Werte im Kontext von Adaptern. Er vereinfacht die Einbindung von Komponenten mit unterschiedlichen Datentypen in einheitliche Adapterstrukturen und erhöht die Wartbarkeit von IEC-61499-Systemen. Durch die Verwendung einer standardisierten Konvertierungsfunktion und seiner klaren, ereignisgesteuerten Arbeitsweise ist er zuverlässig und leicht verständlich.