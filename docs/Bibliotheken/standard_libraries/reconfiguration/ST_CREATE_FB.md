# ST_CREATE_FB

![ST_CREATE_FB](https://user-images.githubusercontent.com/116869307/214154744-19129832-9477-4d2a-a6e6-11e55744ad45.png)

* * * * * * * * * *

## Einleitung

Der ST_CREATE_FB Funktionsblock dient zur dynamischen Erstellung von Funktionsblock- oder Resource-Instanzen während der Laufzeit eines IEC 61499-Systems. Dieser Baustein ermöglicht die Rekonfiguration von Automatisierungssystemen durch das Erzeugen neuer Funktionsblöcke basierend auf bestimmten FB-Typen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **REQ**: Ereignis zur Anforderung der Erstellung einer FB- oder Resource-Instanz

### **Ereignis-Ausgänge**

- **CNF**: Ereignis zur Bestätigung, dass die FB- oder Resource-Instanz erstellt wurde

### **Daten-Eingänge**

- **QI** (BOOL): Ereignis-Eingangsqualifizierer
- **FB_NAME** (WSTRING): Name der zu erstellenden FB-Instanz
- **FB_TYPE** (WSTRING): FB-Typname
- **DST** (WSTRING): Zielort, an dem die FB- oder Resource-Instanz erstellt werden soll (Syntax: ResourceName)

### **Daten-Ausgänge**

- **QO** (BOOL): Ereignis-Ausgangsqualifizierer
- **STATUS** (WSTRING): Service-Status (RDY, UNSUPPORTED_TYPE, INVALID_OPERATION, INVALID_STATE)

### **Adapter**

Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise

Der ST_CREATE_FB Funktionsblock empfängt über das REQ-Ereignis eine Anforderung zur Erstellung einer neuen Funktionsblock-Instanz. Dabei werden die erforderlichen Parameter (FB_NAME, FB_TYPE, DST) mitgeliefert. Nach erfolgreicher Verarbeitung der Anforderung gibt der Baustein über das CNF-Ereignis eine Bestätigung zurück, die den Status der Operation im STATUS-Ausgang enthält.

## Technische Besonderheiten

- Unterstützt dynamische Rekonfiguration von IEC 61499-Systemen
- Verwendet WSTRING-Datentypen für internationale Zeichensatzunterstützung
- Bietet detaillierte Statusrückmeldungen für Fehlerdiagnose
- Implementiert als Structural Service gemäß IEC 61499-1 Standard

## Zustandsübersicht

Der Funktionsblock verfügt über mehrere Service-Sequenzen:
- **normal_establishment**: Erfolgreiche Initialisierung
- **unsuccessful_establishment**: Fehlgeschlagene Initialisierung
- **request_confirm**: Erfolgreiche Anforderungsbearbeitung
- **request_inhibited**: Unterdrückte Anforderung
- **request_error**: Fehlerhafte Anforderungsbearbeitung
- **application_initiated_termination**: Anwendungsinitiierte Beendigung
- **resource_initiated_termination**: Resource-initiierte Beendigung

## Anwendungsszenarien

- Dynamische Erweiterung von Automatisierungssystemen
- Adaptive Steuerungssysteme, die sich an veränderte Produktionsanforderungen anpassen
- Systeme mit modularem Aufbau, bei denen Komponenten zur Laufzeit hinzugefügt werden
- Rekonfigurierbare Fertigungsanlagen

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zu statischen Funktionsblöcken bietet ST_CREATE_FB die einzigartige Fähigkeit, Instanzen zur Laufzeit zu erzeugen. Während Standard-Funktionsblöcke zur Kompilierungszeit festgelegt werden, ermöglicht dieser Baustein eine flexible Systemarchitektur.

## Fazit

Der ST_CREATE_FB Funktionsblock ist ein essentielles Werkzeug für die Entwicklung dynamischer und rekonfigurierbarer Automatisierungssysteme nach IEC 61499. Seine Fähigkeit, Funktionsblock-Instanzen zur Laufzeit zu erzeugen, macht ihn besonders wertvoll für Anwendungen, die Anpassungsfähigkeit und Flexibilität erfordern.