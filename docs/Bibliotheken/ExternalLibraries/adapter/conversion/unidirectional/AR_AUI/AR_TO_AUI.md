# AR_TO_AUI


![AR_TO_AUI](./AR_TO_AUI.svg)

* * * * * * * * * *

## Einleitung
Der Funktionsblock **AR_TO_AUI** ist ein zusammengesetzter Baustein (Composite FB), der eine einheitliche und bidirektionale Konvertierung von einem AR-Adapter (REAL) zu einem AUI-Adapter (UINT) realisiert. Er kapselt die Typumwandlung und vereinfacht die Kommunikation zwischen Komponenten, die unterschiedliche Datentypen über Adapter verwenden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **AR_IN.E1** – Trigger für die Konvertierung: Dieses Ereignis wird vom angeschlossenen AR-Adapter empfangen und startet die Umwandlung des REAL-Wertes.

### **Ereignis-Ausgänge**
- **AUI_OUT.E1** – Abschluss der Konvertierung: Nach erfolgreicher Umwandlung wird dieses Ereignis an den AUI-Adapter gesendet.

### **Daten-Eingänge**
- **AR_IN.D1** – REAL-Eingangswert: Der zu konvertierende Gleitkommawert (REAL), der über den AR-Adapter bereitgestellt wird.

### **Daten-Ausgänge**
- **AUI_OUT.D1** – UINT-Ausgangswert: Das Ergebnis der Konvertierung (UINT) wird über diesen Datenausgang an den AUI-Adapter weitergegeben.

### **Adapter**
- **AR_IN** – Socket vom Typ `AR` (unidirektionaler REAL-Adapter)  
- **AUI_OUT** – Plug vom Typ `AUI` (unidirektionaler UINT-Adapter)

Die Adapter fassen jeweils ein Ereignis- und ein Datensignal zusammen, sodass der Baustein eine saubere, typsichere Schnittstelle bietet.

## Funktionsweise
1. Ein eingehendes Ereignis auf **AR_IN.E1** triggert die Verarbeitung.  
2. Der aktuelle Wert von **AR_IN.D1** (REAL) wird an den integrierten Konvertierungsbaustein **F_REAL_TO_UINT** übergeben.  
3. Die Konvertierung wandelt den REAL-Wert in einen vorzeichenlosen Ganzzahlwert (UINT) um – gemäß IEC 61131-3 Rundungsregeln.  
4. Nach Abschluss wird das Ergebnis auf **AUI_OUT.D1** ausgegeben und gleichzeitig das Ereignis **AUI_OUT.E1** gesendet.

Der gesamte Ablauf erfolgt ohne Zwischenspeicherung oder Verzögerung – jeder Impuls löst eine sofortige Umwandlung aus.

## Technische Besonderheiten
- **Stateless Design**: Der Baustein besitzt keinen internen Zustandsspeicher, jede Konvertierung ist unabhängig von vorherigen.  
- **Einheitliche Adatperschnittstelle**: Durch die Verwendung von unidirektionalen Standardadaptern (AR und AUI) ist der FB leicht in verschiedene Architekturen integrierbar.  
- **Keine Nebenwirkungen**: Es werden keine globalen Variablen oder Systemressourcen beeinflusst.

## Zustandsübersicht
Der AR_TO_AUI ist ein reiner Funktionsbaustein ohne internen Zustandsautomaten (ECC). Die Abarbeitung erfolgt streng ereignisgesteuert und deterministisch. Somit entfällt eine separate Zustandsmaschine.

## Anwendungsszenarien
- **Anbindung analoger Sensorik**: Wenn ein Sensor seinen Messwert als REAL über einen AR-Adapter liefert, das nachgeschaltete Steuerungssystem jedoch UINT erwartet.  
- **Datenbrücke**: Vermittlung zwischen verschiedenen Kommunikationsmodulen oder Bibliotheken mit unterschiedlichen Adaptertypen.  
- **Protokollumsetzung**: Beispielsweise in der Agrartechnik, wo oft REAL-Werte (z. B. Geschwindigkeit) in Ganzzahlen (z. B. für Zähler) umgerechnet werden müssen.

## Vergleich mit ähnlichen Bausteinen
- **AR_TO_ADI**: Wandelt REAL in INT (vorzeichenbehaftet) um. AR_TO_AUI hingegen erzeugt vorzeichenlose Werte (UINT), was für bestimmte Anwendungen wie Zählerstände oder HMI-Indizes vorteilhaft ist.  
- **Direkte Konvertierung mit F_REAL_TO_UINT**: Dieser einzelne Funktionsbaustein bietet die gleiche Logik, erfordert aber die manuelle Verbindung von Ereignissen und Daten. Der Composite FB kapselt diesen Aufwand und reduziert die Fehleranfälligkeit in komplexen Netzwerken.

## Fazit
Der **AR_TO_AUI** ist ein praktischer und zuverlässiger Baustein zur einfachen Adapterkonvertierung von REAL auf UINT. Seine klare Schnittstelle, das rein funktionale Verhalten und die Wiederverwendbarkeit machen ihn zu einem nützlichen Werkzeug im 4diac-Ökosystem. Er eignet sich besonders für Anwendungen, in denen eine saubere Trennung von Adaptertypen und eine einfache Integration in bestehende Projekte gefordert ist.