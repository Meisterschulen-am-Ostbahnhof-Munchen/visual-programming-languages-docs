# NumericValue_ID

```{index} single: NumericValue_ID
```

<img width="1399" height="290" alt="image" src="https://github.com/user-attachments/assets/d47cfe0c-6224-4132-bb02-d186bc0e0c55" />

* * * * * * * * * *

## Einleitung
Der NumericValue_ID Funktionsblock ist ein Eingabeservice-Interface-Funktionsblock für Doppelwort-Eingabedaten (DWORD). Er dient als Schnittstelle zur Kommunikation mit Ressourcen und ermöglicht die Verarbeitung von numerischen Eingabewerten in ISOBUS-kompatiblen Systemen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Service-Initialisierung
  - Verknüpft mit: QI, PARAMS, u16ObjId
- **REQ**: Service-Anfrage
  - Verknüpft mit: QI

### **Ereignis-Ausgänge**
- **INITO**: Initialisierungsbestätigung
  - Verknüpft mit: QO, STATUS
- **CNF**: Bestätigung der angeforderten Service-Anfrage
  - Verknüpft mit: QO, STATUS, IN
- **IND**: Indikation von der Ressource
  - Verknüpft mit: QO, STATUS, IN

### **Daten-Eingänge**
- **QI** (BOOL): Ereignis-Eingangsqualifizierer
- **PARAMS** (STRING): Service-Parameter
- **u16ObjId** (UINT): Objekt-ID mit Initialwert ID_NULL

### **Daten-Ausgänge**
- **QO** (BOOL): Ereignis-Ausgangsqualifizierer
- **STATUS** (STRING): Service-Status
- **IN** (DWORD): Eingabedaten von der Ressource

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Der Funktionsblock initialisiert sich über das INIT-Ereignis und kann über REQ Service-Anfragen stellen. Bei erfolgreicher Initialisierung gibt er INITO zurück, während CNF und IND die Bestätigung von Service-Anfragen bzw. Indikationen von der Ressource darstellen. Die Datenübertragung erfolgt über DWORD-Werte (32-Bit), die über den IN-Ausgang bereitgestellt werden.

## Technische Besonderheiten
- Verwendet DWORD-Datentyp für numerische Eingabewerte
- ISOBUS-kompatible Implementierung
- Initialisierung mit standardisierter Objekt-ID (ID_NULL)
- String-basierte Statusrückmeldungen
- Unterstützt parametrierbare Service-Konfiguration

## Zustandsübersicht
Der Funktionsblock durchläuft folgende Zustände:
1. **Nicht initialisiert**: Vor INIT-Aufruf
2. **Initialisiert**: Nach erfolgreicher INIT-Verarbeitung
3. **Service-aktiv**: Bei aktiven REQ-Anfragen
4. **Datenbereitstellung**: Bei aktiver IND-Indikation

## Anwendungsszenarien
- Landwirtschaftliche Steuerungssysteme (ISOBUS)
- Industrielle Automatisierung mit numerischen Sensordaten
- Embedded Systems mit Doppelwort-Datenverarbeitung
- Systeme mit standardisierten Objekt-Identifikationen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen Eingabeblöcken bietet NumericValue_ID erweiterte Service-Funktionalität mit Initialisierungsprozeduren, Statusrückmeldungen und parametrierbaren Konfigurationsmöglichkeiten. Die spezielle Ausrichtung auf ISOBUS-Umgebungen unterscheidet ihn von generischen Eingabeblöcken.

## Fazit
Der NumericValue_ID Funktionsblock stellt eine robuste Lösung für die Verarbeitung von Doppelwort-Eingabedaten in ISOBUS-basierten Systemen dar. Durch seine strukturierte Initialisierung, klare Statusrückmeldungen und flexible Parametrierung eignet er sich ideal für industrielle Anwendungen mit hohen Anforderungen an Zuverlässigkeit und Diagnosefähigkeit.