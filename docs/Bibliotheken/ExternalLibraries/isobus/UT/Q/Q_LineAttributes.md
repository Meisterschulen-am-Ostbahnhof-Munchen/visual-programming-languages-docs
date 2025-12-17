# Q_LineAttributes

![Q_LineAttributes](https://user-images.githubusercontent.com/116869307/214147948-3b9f6d08-00a5-43c0-895b-f2a997773b97.png)

* * * * * * * * * *

## Einleitung  
Der **Q_LineAttributes** ist ein standardkonformer Funktionsbaustein zur Änderung von Linienattributen in Virtual Terminals, entwickelt unter EPL-2.0 Lizenz. Die Version 1.0 implementiert die ISO 11783-6 (Teil 6 - F.30) Spezifikation für VT-Systeme.  

## Schnittstellenstruktur  

### **Ereignis-Eingänge**  
- `INIT`: Initialisierungsanforderung (mit Objekt-ID)  
- `REQ`: Attributänderungs-Anforderung (mit neuen Linienattributen)  

### **Ereignis-Ausgänge**  
- `INITO`: Initialisierungsbestätigung  
- `CNF`: Änderungsbestätigung (mit Status und alten Attributen)  

### **Daten-Eingänge**  
- `u16ObjId` (UINT): Objekt-ID (16-bit)  
- `u8LineColour` (USINT): Neue Linienfarbe  
- `u8LineWidth` (USINT): Neue Linienbreite  
- `u16LineArt` (UINT): Neuer Linienstil  

### **Daten-Ausgänge**  
- `STATUS` (STRING): Betriebsstatusmeldung  
- `u8OldLineColour` (USINT): Alte Linienfarbe  
- `u8OldLineWidth` (USINT): Alte Linienbreite  
- `u16OldLineArt` (UINT): Alter Linienstil  
- `s16result` (INT): ISO-konformer Ergebniscode  

## Funktionsweise  

1. **Initialisierung**:  
   - `INIT` mit Objekt-ID  
   - `INITO` bestätigt Betriebsbereitschaft  

2. **Attributänderung**:  
   - `REQ` mit neuen Linienattributen  
   - Ändert Linieneigenschaften des Objekts  
   - `CNF` liefert Ergebnisstatus und vorherige Werte  

3. **Fehlerbehandlung**:  
   - ISO-standardisierte Fehlercodes  
   - Detaillierte Statusmeldungen  

## Technische Besonderheiten  

✔ **ISO 11783-6 konform** (F.30)  
✔ **Umfassende Liniensteuerung** (Farbe, Breite, Stil)  
✔ **Rückmeldung alter Werte** für Reversionsmöglichkeit  
✔ **Transaktionssicher** (Atomare Ausführung)  

## Attribut-Referenz  

| Attribut     | Wertebereich          | Beschreibung                     |  
|--------------|-----------------------|----------------------------------|  
| Farbe        | 0-255 (8-bit)        | Farbindex nach ISO 11783-6 A.3   |  
| Breite       | 1-255 Pixel          | Linienstärke in Pixeln           |  
| Stil         | 16-bit Bitmaske      | Linienart nach B.14.3            |  

## Rückgabecodes (s16result)  

| Code | Konstante               | Bedeutung                          |  
|------|-------------------------|------------------------------------|  
| 0    | VT_E_NO_ERR             | Erfolgreiche Änderung             |  
| -6   | VT_E_OVERFLOW           | Pufferüberlauf                   |  
| -8   | VT_E_NOACT              | VT nicht bereit                   |  
| -21  | VT_E_NO_INSTANCE        | Kein VT-Client verfügbar          |  
| -129 | VT_E_ISO_INSTANCE_INVALID | Ungültige VT-Instanz             |  
| -130 | VT_E_NOT_ALIVE          | VT nicht aktiv                    |  

## Anwendungsszenarien  

- **Grafikdesign**: Dynamische Linienanpassungen  
- **Diagramme**: Hervorhebung wichtiger Elemente  
- **Benutzerführung**: Visuelle Markierungen  
- **Maschinenvisualisierung**: Zustandsanzeigen  

## Vergleich mit ähnlichen Bausteinen  

| Feature        | Q_LineAttributes | VtLineStyle | VtGraphicAttributes |  
|---------------|------------------|-------------|---------------------|  
| ISO-Standard  | ✔                | ✖           | ✖                   |  
| Farbsteuerung | ✔                | ✔           | ✔                   |  
| Breitensteuerung | ✔            | ✔           | ✖                   |  
| Stilsteuerung | ✔                | ✔           | ✔                   |  

## Fazit  

Der Q_LineAttributes-Baustein bietet präzise Kontrolle über Linienattribute:  

- **Flexibel**: Vollständige Gestaltungsfreiheit  
- **Zuverlässig**: ISO-konforme Implementierung  
- **Rückverfolgbar**: Vorherige Zustandsspeicherung  

Unverzichtbar für:  
- Technische Zeichnungen  
- Prozessvisualisierungen  
- Interaktive Grafikanwendungen
