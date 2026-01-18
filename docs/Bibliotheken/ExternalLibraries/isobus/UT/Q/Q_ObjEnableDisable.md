# Q_ObjEnableDisable

```{index} single: Q_ObjEnableDisable
```

![Q_ObjEnableDisable](https://user-images.githubusercontent.com/116869307/214148082-167eae93-48d4-40cd-96e2-d0983e475187.png)

* * * * * * * * * *

## Einleitung  
Der **Q_ObjEnableDisable** ist ein standardkonformer Funktionsbaustein zur Aktivierung/Deaktivierung von Eingabeobjekten in Virtual Terminals, entwickelt unter EPL-2.0 Lizenz. Die Version 1.0 implementiert die ISO 11783-6 (Teil 6 - F.4) Spezifikation für VT-Eingabeelemente.  

## Schnittstellenstruktur  

### **Ereignis-Eingänge**  
- `INIT`: Initialisierungsanforderung (mit Objekt-ID)  
- `REQ`: Aktivierungs-/Deaktivierungsanforderung  

### **Ereignis-Ausgänge**  
- `INITO`: Initialisierungsbestätigung  
- `CNF`: Betriebsbestätigung  

### **Daten-Eingänge**  
- `u16ObjId` (UINT): Objekt-ID (16-bit)  
- `qAbility` (BOOL): Aktivierungsstatus (TRUE=aktivieren, FALSE=deaktivieren)  

### **Daten-Ausgänge**  
- `STATUS` (STRING): Betriebsstatusmeldung  
- `qOldAbility` (BOOL): Vorheriger Aktivierungsstatus  
- `s16result` (INT): ISO-konformer Ergebniscode  

## Funktionsweise  

1. **Initialisierung**:  
   - `INIT` mit Zielobjekt-ID  
   - `INITO` bestätigt Betriebsbereitschaft  

2. **Statusänderung**:  
   - `REQ` mit gewünschtem Aktivierungszustand  
   - Ändert die Interaktionsfähigkeit des Objekts  
   - `CNF` liefert Betriebsstatus und vorherigen Zustand  

3. **Spezialfälle**:  
   - Bei ungültigen Objekt-IDs wird VT_E_HANDLE_INVALID zurückgegeben  

## Technische Besonderheiten  

✔ **ISO 11783-6 konform** (F.4)  
✔ **Einfache Binärsteuerung** (Aktiviert/Deaktiviert)  
✔ **Zustandsrückmeldung** (Vorheriger Status)  
✔ **Breite Objektunterstützung** (Alle Eingabeelemente)  

## Statusreferenz  

| qAbility | Objektzustand        |  
|----------|----------------------|  
| FALSE (0)| Deaktiviert (grau)   |  
| TRUE (1) | Aktiviert (normal)   |  

## Rückgabecodes (s16result)  

| Code | Konstante               | Bedeutung                          |  
|------|-------------------------|------------------------------------|  
| 0    | VT_E_NO_ERR             | Erfolgreiche Ausführung           |  
| -6   | VT_E_OVERFLOW           | Pufferüberlauf                   |  
| -8   | VT_E_NOACT              | VT nicht bereit                   |  
| -21  | VT_E_NO_INSTANCE        | Kein VT-Client verfügbar          |  
| -128 | VT_E_HANDLE_INVALID     | Ungültige Objekt-ID               |  
| -129 | VT_E_ISO_INSTANCE_INVALID | Ungültige VT-Instanz             |  
| -130 | VT_E_NOT_ALIVE          | VT nicht aktiv                    |  

## Anwendungsszenarien  

- **Formularsteuerung**: Konditionelle Eingabefreigabe  
- **Sicherheitsfunktionen**: Kritische Eingaben sperren  
- **Workflow-Management**: Schrittweise Freischaltung  
- **Diagnosemodi**: Eingabebeschränkungen  

## Vergleich mit ähnlichen Bausteinen  

| Feature        | Q_ObjEnableDisable | VtInputControl | VtObjectState |  
|---------------|--------------------|----------------|---------------|  
| ISO-Standard  | ✔                  | ✖              | ✖             |  
| Binärsteuerung| ✔                  | ✔              | ✖             |  
| Rückmeldung   | ✔                  | ✖              | ✔             |  
| Objekttyp     | Eingabeobjekte     | Alle           | Alle          |  

## Fazit  

Der Q_ObjEnableDisable-Baustein bietet essentielle Eingabesteuerung:  

- **Einfach**: Klare Aktivierungslogik  
- **Zuverlässig**: Integrierte Fehlererkennung  
- **Flexibel**: Für alle Eingabeelementtypen  

Unverzichtbar für:  
- Interaktive Formulare  
- Sichere Bedienoberflächen  
- Zustandsgesteuerte Anwendungen
