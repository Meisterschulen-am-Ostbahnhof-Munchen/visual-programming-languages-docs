# Q_Size

```{index} single: Q_Size
```

![Q_Size](https://user-images.githubusercontent.com/116869307/214153095-72c9e230-b193-4843-be85-33038f6bd44d.png)

* * * * * * * * * *

## Einleitung  
Der **Q_Size** ist ein standardkonformer Funktionsbaustein zur Größenänderung von Objekten in Virtual Terminals, entwickelt unter EPL-2.0 Lizenz. Die Version 1.0 implementiert die ISO 11783-6 (Teil 6 - F.18) Spezifikation für VT-Objekte.

## Schnittstellenstruktur  

### **Ereignis-Eingänge**  
- `INIT`: Initialisierungsanforderung (mit Objekt-ID)  
- `REQ`: Größenänderungs-Anforderung  

### **Ereignis-Ausgänge**  
- `INITO`: Initialisierungsbestätigung  
- `CNF`: Änderungsbestätigung  

### **Daten-Eingänge**  
- `u16ObjId` (UINT): Objekt-ID (16-bit)  
- `u16Width` (UINT): Neue Breite in Pixeln  
- `u16Height` (UINT): Neue Höhe in Pixeln  

### **Daten-Ausgänge**  
- `STATUS` (STRING): Betriebsstatusmeldung  
- `u16OldWidth` (UINT): Vorherige Breite  
- `u16OldHeight` (UINT): Vorherige Höhe  
- `s16result` (INT): ISO-konformer Ergebniscode  

## Funktionsweise  

1. **Initialisierung**:  
   - `INIT` mit Zielobjekt-ID  
   - `INITO` bestätigt Betriebsbereitschaft  

2. **Größenänderung**:  
   - `REQ` mit neuen Abmessungen  
   - Passt die Objektgeometrie dynamisch an  
   - `CNF` liefert Betriebsstatus und vorherige Maße  

3. **Maßeinheit**:  
   - Alle Werte in Bildschirmpixeln  

## Technische Besonderheiten  

✔ **ISO 11783-6 konform** (F.18)  
✔ **Dynamische Größenanpassung** (Echtzeit-Update)  
✔ **Umfassende Objektunterstützung**  
✔ **Rückverfolgbarkeit** (Vorherige Abmessungen)  

## Größenreferenz  

| Parameter | Wertebereich   | Beschreibung       |  
|-----------|---------------|--------------------|  
| Width     | 1-65535 Pixel | Horizontale Ausdehnung |  
| Height    | 1-65535 Pixel | Vertikale Ausdehnung |  

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

- **Responsive Designs**: Anpassung an Displaygrößen  
- **Zoom-Funktionen**: Dynamische Skalierung  
- **Layoutmanager**: Automatische Größenoptimierung  
- **Animationssteuerung**: Größenänderungseffekte  

## Vergleich mit ähnlichen Bausteinen  

| Feature        | Q_Size | VtResizeObject | VtGeometryManager |  
|---------------|--------|----------------|-------------------|  
| ISO-Standard  | ✔      | ✖              | ✖                 |  
| Echtzeit-Update | ✔    | ✔              | ✖                 |  
| 2D-Steuerung  | ✔      | ✔              | ✔                 |  
| Rückmeldung   | ✔      | ✖              | ✔                 |  

## Fazit  

Der Q_Size-Baustein bietet präzise Größensteuerung:  

- **Flexibel**: Pixelgenaue Anpassung  
- **Performant**: Sofortige Darstellungsaktualisierung  
- **Zuverlässig**: ISO-konforme Implementierung  

Unverzichtbar für:  
- Adaptive Benutzeroberflächen  
- Dynamische Visualisierungen  
- Professionelle VT-Anwendungen
