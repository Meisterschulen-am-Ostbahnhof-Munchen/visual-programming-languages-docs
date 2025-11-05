# Aux_IXA

<img width="1383" height="318" alt="image" src="https://github.com/user-attachments/assets/d064bd8f-6af0-4b04-9952-995892584e9a" />

* * * * * * * * * *

## Einleitung
Der Aux_IXA ist ein Composite-Funktionsblock zur Verarbeitung von booleschen Eingangsdaten. Er dient als Wrapper für den Basis-Funktionsblock Aux_IX und bietet eine erweiterte Schnittstelle für die Integration in ISOBUS-kompatible Systeme.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Service-Initialisierung mit den zugehörigen Daten QI, PARAMS und u16ObjId
- **REQ**: Service-Anfrage mit dem zugehörigen Daten QI

### **Ereignis-Ausgänge**
- **INITO**: Initialisierungsbestätigung mit den zugehörigen Daten QO und STATUS

### **Daten-Eingänge**
- **QI**: Event Input Qualifier (BOOL) - Qualifizierer für Ereigniseingänge
- **PARAMS**: Service Parameters (STRING) - Konfigurationsparameter für den Service
- **u16ObjId**: Object ID (UINT) - Objektkennung mit Initialwert ID_NULL

### **Daten-Ausgänge**
- **QO**: Event Output Qualifier (BOOL) - Qualifizierer für Ereignisausgänge
- **STATUS**: Service Status (STRING) - Statusinformationen des Services

### **Adapter**
- **IN**: Unidirektionaler Adapter vom Typ AX für die Datenkommunikation

## Funktionsweise
Der Aux_IXA fungiert als Composite-Block, der den Basis-Funktionsblock Aux_IX kapselt. Bei INIT-Ereignis werden alle Parameter an den internen IX-Block weitergeleitet. REQ-Ereignisse lösen Service-Anfragen aus, während INITO die erfolgreiche Initialisierung bestätigt. Der Adapter IN ermöglicht die bidirektionale Kommunikation mit externen Komponenten.

## Technische Besonderheiten
- Integration in ISOBUS-Umgebungen durch spezielle Package-Struktur
- Verwendung von TypeHash für Typidentifikation
- Unidirektionaler Adapter für standardisierte Schnittstellen
- Initialisierung mit NULL-Objekt-ID als Standardwert

## Zustandsübersicht
Der Block durchläuft folgende Zustände:
1. **Nicht initialisiert**: Vor INIT-Ereignis
2. **Initialisierung**: Während INIT-Verarbeitung
3. **Bereit**: Nach erfolgreicher Initialisierung (INITO)
4. **Service-Modus**: Bei REQ-Ereignisverarbeitung

## Anwendungsszenarien
- ISOBUS-kompatible Landmaschinensteuerung
- Boolesche Signalverarbeitung in Agrartechnik-Systemen
- Wrapper-Implementierung für bestehende IO-Funktionalität
- Parameterkonfiguration für Auxiliary-Inputs

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen booleschen Eingangsblöcken bietet Aux_IXA:
- Erweiterte Parametrisierungsmöglichkeiten
- ISOBUS-Spezifikation
- Adapter-basierte Schnittstelle
- Composite-Struktur für bessere Wiederverwendbarkeit

## Fazit
Der Aux_IXA stellt einen robusten Composite-Funktionsblock für die boolesche Eingangsdatenverarbeitung in ISOBUS-Umgebungen dar. Durch seine klare Schnittstellendefinition und Adapter-Integration ermöglicht er eine flexible Einbindung in komplexe Steuerungssysteme der Agrartechnik.
